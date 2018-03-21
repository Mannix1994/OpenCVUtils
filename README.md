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

## 二、如何使用
1. CompareMats.h
```
#include "CompareMats.h"
using namespace Utils;
//
void func(){
    //其他代码
    //
    CompareMats cm(mat1,mat2);//初始化
    cout<<cm.report()<<endl;//输出报告
    //还有非常多的方法在CompareMats.h中的说明
    //
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
    //
    //保存
    write("test.mb",mat);
    //读取
    Mat m = read("test.mb");
    //
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