#include "MatIO.h"
#include <fstream>
#include "tools.h"

using namespace std;
using namespace cv;

namespace Utils {
    /**
     * 保存mat头的关键信息
     */
    typedef struct {
        int rows;//行数
        int cols;//列数
        int type;//类型
    } MatHeader;
}

void Utils::write(std::string fileName, cv::Mat src) {
    ASSERT(!fileName.empty(), "文件名为空");
    ASSERT(!src.empty(), "mat为空");
    MatHeader matHeader{src.rows, src.cols, src.type()};
//    printf("%d %d %d\n",matHeader.rows,matHeader.cols,matHeader.type);

    //打开文件
    ofstream out(fileName, ios::binary);
    ASSERT(out.is_open(), "打开文件" + fileName + "失败");

    //写入文件类型，表示为这个类型的数据，长度为两字节
    char fileType[3] = "mb";
    out.write(fileType, 2*sizeof(char));

    //写入Mat头
    out.write((char *) &matHeader, sizeof(MatHeader));

    //写入数据
    //http://blog.csdn.net/dcrmg/article/details/52294259
    out.write((char *) src.data, src.rows * src.cols * src.elemSize());

    out.flush();
    out.close();
}

cv::Mat Utils::read(std::string fileName) {
    //打开文件
    ifstream in(fileName, ios::binary);
    ASSERT(in.is_open(), "打开文件" + fileName + "失败");

    char fileType[3]={'\0','\0','\0'};//初始化一个默认值

    //读取前两字节
    in.read(fileType, 2*sizeof(char));

    //判断是否是"mb"这种文件
    ASSERT(strcmp(fileType, "mb") == 0, fileName + "非Mat类型的数据");

    //读取Mat头
    MatHeader matHeader{0, 0, 0};
    in.read((char *) &matHeader, sizeof(MatHeader));
//    printf("%d %d %d\n",matHeader.rows,matHeader.cols,matHeader.type);

    //初始化一个Mat
    Mat mat(matHeader.rows, matHeader.cols, matHeader.type);

    //写入数据
    in.read((char *) mat.data, mat.rows * mat.cols * mat.elemSize());

    in.close();
    return mat;
}
