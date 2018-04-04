#include <opencv2/opencv.hpp>
#include <CvText.h>
#include "MatIO.h"
#include "CompareMats.h"
#include "tools.h"

using namespace std;
using namespace cv;
using namespace Utils;

void testCompareMats();
void testSaveMat();
void testCvText();

int main( int argc, char** argv )
{
    testCompareMats();
    testSaveMat();
    testCvText();
    return 0;
}

void testCompareMats(){

    //test case 1
    Mat mat = imread("image170.bmp");
    Mat mat1 = imread("image1701.bmp");

    //test case 1.1
    CompareMats cm(mat,mat);
    ASSERT(cm.same(),"测试失败");

    //test case 1.2
    CompareMats cm2(mat,mat1);
    ASSERT(!cm2.same(),"测试失败");

    //test case2
    Mat mat2(500,500,CV_32FC2);
    Mat mat3(500,500,CV_32FC2);
    mat3.at<Vec2f>(10,10) = Vec2f(1,1);

    //test case 2.1
    CompareMats cm3(mat2,mat2);
    ASSERT(cm3.same(),"测试失败");

    //test case 2.2
    CompareMats cm4(mat2,mat3);
    ASSERT(!cm4.same(),"测试失败");
    printf("CompareMats测试成功\n");
}

void testSaveMat(){
    //test case 1
    Mat mat = imread("image170.jpg");
    write("mat0.mb", mat);
    Mat m0 = read("mat0.mb");
    CompareMats cm0(mat,m0);
    ASSERT(cm0.same(),"测试失败");

    //test case 2
    Mat mat1(500,500,CV_32FC2,Scalar(1,5,2.2));
    write("mat1.mb", mat1);
    Mat m1 = read("mat1.mb");
    CompareMats cm1(mat1,m1);
    ASSERT(cm1.same(),"测试失败");

    printf("SaveMat测试成功\n");
}

void testCvText() {
    //test case 1
    Mat mat = imread("image170.jpg");
    CvText text("simhei.ttf");
    string str = "EnglishTest中文测试"; //替换成需要输出的字符串
    Point pos(5,25);                   //输出起始位置
    Scalar color(255,255,255);         //字的颜色，默认为白色
    text.putText(mat,str,pos,color);
//    imwrite("CvText.bmp",mat);
    Mat base = imread("CvText.bmp");
    CompareMats cm(base,mat);
    ASSERT(cm.same(),"测试失败");

    printf("CvText测试成功\n");
}
