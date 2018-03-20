#include "SaveMat.h"
#include <fstream>
#include "tools.h"

using namespace std;
using namespace cv;
using namespace Utils;

void SaveMat::save(std::string fileName,cv::Mat src) {
    ASSERT(!fileName.empty(),"文件名为空");
    ASSERT(!src.empty(),"mat为空");
    MatHeader matHeader{src.rows,src.cols,src.type()};
//    printf("%d %d %d\n",matHeader.rows,matHeader.cols,matHeader.type);

    //打开文件
    ofstream out(fileName,ios::binary);
    ASSERT(out.is_open(),"打开文件"+fileName+"失败");

    //写入一个表示数字，表示为这个类型的数据
    char tag = 'm';
    out.write(&tag, sizeof(char));

    //写入Mat头
    out.write((char *)&matHeader, sizeof(MatHeader));

    //写入数据
    //http://blog.csdn.net/dcrmg/article/details/52294259
    out.write((char *)src.data,src.rows*src.cols*src.elemSize());

    out.flush();
    out.close();
}

cv::Mat SaveMat::read(std::string fileName) {
    //打开文件
    ifstream in(fileName,ios::binary);
    ASSERT(in.is_open(),"打开文件"+fileName+"失败");

    //读取第一个字节，看是不是通过本方法存储的mat
    char tag;
    in.read(&tag, sizeof(char));
    ASSERT(tag == 'm',fileName+"非Mat类型的数据");

    //读取Mat头
    MatHeader matHeader{0,0,0};
    in.read((char *)&matHeader, sizeof(MatHeader));
//    printf("%d %d %d\n",matHeader.rows,matHeader.cols,matHeader.type);

    //初始化一个Mat
    Mat mat(matHeader.rows,matHeader.cols,matHeader.type);

    //写入数据
    in.read((char *)mat.data,mat.rows*mat.cols*mat.elemSize());

    in.close();
    return mat;
}
