#include <cwchar>
#include <clocale>
#include <cctype>
#include <utility>
#include "tools.h"
#include "CvText.h"

using namespace Utils;

CvText::CvText(const char *fontName,TextEncoding encoding) {
    ASSERT(fontName != nullptr, "字体名称为空");

    // 打开字库文件, 创建一个字体
    ASSERT(FT_Init_FreeType(&m_library) == 0, "初始化字库失败，请检查freetype库配置是否正确");
    ASSERT(FT_New_Face(m_library, fontName, 0, &m_face) == 0,
           "载入字体失败，请检查字体文件是否存在");

    //选择字符编码
    switch (encoding){
        case UTF8:
            FT_Select_Charmap(m_face,FT_ENCODING_UNICODE);
            m_textEncoding = "zh_CN.utf8";
            break;
        case GB2312:
            FT_Select_Charmap(m_face,FT_ENCODING_GB2312);
            m_textEncoding = "zh_CN.gb2312";
            break;
        default:
            ASSERT(false, "不支持的文本编码");
    }

    // 设置字体输出参数
    resetTextStyle();
}

// 释放FreeType资源
CvText::~CvText() {
    FT_Done_Face(m_face);
    FT_Done_FreeType(m_library);
}

// 设置文本属性
void CvText::setTextStyle(int fontSize, float spaceSize, float separatorSize, float fontDiaphaneity) {
    if(fontSize>0)
        m_fontSize = fontSize;
    if(spaceSize>0)
        m_spaceRatio = spaceSize;
    if(separatorSize>0)
        m_separatorRatio = separatorSize;
    if(fontDiaphaneity>0)
        m_fontDiaphaneity = fontDiaphaneity;
}

// 恢复默认的文本设置
void CvText::resetTextStyle() {
    m_fontSize = 20;        // 字体大小
    m_spaceRatio = 0.5;     // 空白字符大小比例
    m_separatorRatio = 0.1;     // 间隔大小比例
    m_fontDiaphaneity = 1.0;    // 透明度
}


int CvText::putText(cv::Mat &frame, std::string text, cv::Point pos, cv::Scalar color) {
    return putText(frame,text.c_str(),pos, std::move(color));
}

int CvText::putText(cv::Mat &frame, const char *text, cv::Point pos, cv::Scalar color) {

    if (frame.empty())
        return -1;
    if (text == nullptr)
        return -1;

    wchar_t *w_str ;
    int count = char2Wchar(text, w_str,m_textEncoding.c_str());
    //
    for (int i=0; i<count; ++i) {
        wchar_t wc = w_str[i];
        //如果是ascii字符(范围0~127)，调整字体大小
        //因为ascii字符在同样的m_fontSize下更小，所以要放大1.15倍
        if(wc<128)
            FT_Set_Pixel_Sizes(m_face, (FT_UInt)(m_fontSize*1.15), 0);
        else
            FT_Set_Pixel_Sizes(m_face, (FT_UInt)m_fontSize, 0);
        // 输出当前的字符
        putWChar(frame, wc, pos, color);
    }
    delete(w_str);
    return count;
}

/**
 * 将char字符数组转换为wchar_t字符数组
 * @param src char字符数组
 * @param dst wchar_t字符数组
 * @param locale 语言环境，mbstowcs函数依赖此值来判断src的编码方式
 * @return 运行成功返回0,否则返回-1
 */
int CvText::char2Wchar(const char *&src, wchar_t *&dst, const char *locale)
{
    if (src == nullptr) {
        dst = nullptr;
        return -1;
    }
    // 设置C语言的字符集环境
    char *result = setlocale(LC_CTYPE, locale);
    // 检查设置编码是否成功，失败的话抛出异常"设置字符编码失败"等信息
    ASSERT(result != nullptr, "设置字符编码失败。\n"
                              "对于zh_CN.GBK或者zh_CN.GB2312编码，"
                              "先安装中文语言包，然后根据下面链接来设置：\n"
                              "https://blog.csdn.net/wenwenxiong/article/details/17116791\n");
    // 得到转化为需要的宽字符大小
    int w_size = (int)mbstowcs(nullptr, src, 0) + 1;
    // w_size = 0 说明mbstowcs返回值为-1。即在运行过程中遇到了非法字符(很有可能是locale没有设置正确)
    if (w_size == 0) {
        dst = nullptr;
        return -1;
    }
    // 分配内存
    dst = new wchar_t[w_size];
    // 把char字符数组转换为wchar_t字符数组
    auto ret =  (int)mbstowcs(dst, src, strlen(src)+1);
    // 恢复默认的字符编码，以免影响程序的其他部分
    setlocale(LC_CTYPE,"");
    return ret;
}


// 输出当前字符, 更新m_pos位置
void CvText::putWChar(cv::Mat &frame, wchar_t wc, cv::Point &pos, cv::Scalar color) {
    // 根据unicode生成字体的二值位图  
    IplImage img = IplImage(frame);

    FT_UInt glyph_index = FT_Get_Char_Index(m_face, (FT_ULong)wc);
    FT_Load_Glyph(m_face, glyph_index, FT_LOAD_DEFAULT);
    FT_Render_Glyph(m_face->glyph, FT_RENDER_MODE_MONO);

    FT_GlyphSlot slot = m_face->glyph;

    // 行列数
    int rows = slot->bitmap.rows;
    int cols = slot->bitmap.width;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int off = ((img.origin == 0) ? i : (rows - 1 - i)) * slot->bitmap.pitch + j / 8;

            if (slot->bitmap.buffer[off] & (0xC0 >> (j % 8))) {
                int r = (img.origin == 0) ? pos.y - (rows - 1 - i) : pos.y + i;;
                int c = pos.x + j;

                if (r >= 0 && r < img.height && c >= 0 && c < img.width) {
                    CvScalar scalar = cvGet2D(&img, r, c);

                    // 进行色彩融合
                    float p = m_fontDiaphaneity;
                    for (int k = 0; k < 4; ++k) {
                        scalar.val[k] = scalar.val[k] * (1 - p) + color.val[k] * p;
                    }
                    cvSet2D(&img, r, c, scalar);
                }
            }
        } // end for  
    } // end for  

    // 修改下一个字的输出位置
    double space = m_fontSize * m_spaceRatio;
    double sep = m_fontSize * m_separatorRatio;

    pos.x += (int) ((cols ? cols : space) + sep);
}
