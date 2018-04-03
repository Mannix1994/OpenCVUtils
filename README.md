# OpenCV工具库
这是一个基于OpenCV的工具库。建立这个库的初衷是便于存储
代码，便于共享。还在慢慢的增加和完善中。

## 一、头文件列表
1. CompareMats.h  
CompareMats.h包含了一个类CompareMats。CompareMats
的作用比对两个相同类型的Mat，并可以生成统计报告。已知
bug，不能正确的比较类型为jpg格式的图片文件。
2. MatIO.h  
MatIO.h中包含了一个save函数和read函数，可以仅仅通过
一个save函数和一个read函数就能完成任意类型的Mat的存储
和读取。
3. CvText.h  
CvText.h中包含了一个类CvText。CvText的作用是解决Ope
nCV输出中文乱码的问题，经过测试，能完美显示中英文。这个
类依赖于freetype库。
## 二、如何使用
使用前将头文件和对应的cpp文件拷贝到你的项目中。  
1. CompareMats.h  
```
#include "CompareMats.h"
using namespace Utils;
//
void func(){
    //其他代码
    CompareMats cm(mat1,mat2);//初始化
    cout<<cm.report()<<endl;//输出报告
    //还有非常多的方法在CompareMats.h中说明
    //其他代码
}
```
2. MatIO.h  
```
#include "MatIO.h"
using namespace Utils;
//
void func(){
    //其他代码
    //保存
    write("test.mb",mat);
    //读取
    Mat m = read("test.mb");
    //其他代码
}
```
  
3. CvText.h  
```
//使用这个类时，需要配置freetype库。对于含有  
//CMakeLists.txt的项目，请参考本项目中的配置。
#include "CvText.h"
using namespace Utils;
void func{
    //其他代码
    Mat mat = ...;
    CvText text("simhei.ttf");//载入字体文件
    string str = "EnglishTest中文测试";//替换成需要输出的字符串
    Point pos(5,25);//输出起始位置
    Scalar color(255,255,255);//字的颜色，默认为白色
    text.putText(mat,str,pos,color);//输出文字
    //其他代码
}
```

## 三、关于作者
```javascript
  var whoAmI = {
    name   : "Mannix1994",
    gitee  : "https://gitee.com/Mannix1994",
    github : "https://github.com/Mannix1994"
  }
```