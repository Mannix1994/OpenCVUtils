#ifndef SAVEMAT_H
#define SAVEMAT_H
#include <opencv2/opencv.hpp>
namespace Utils{
    class SaveMat {
    public:
        /**
         * 以二进制文件来存储Mat数据；读取这个函数存储的文件，需要用到下面的read函数。
         * @param fileName 文件名(后缀推荐为.mb)
         * @param src 要存储的mat
         */
        static void save(std::string fileName, cv::Mat src);
        /**
         * 读取save函数保存的Mat
         * @param fileName 文件名
         * @return 返回读取到的mat
         */
        static cv::Mat read(std::string fileName);

    private:
        /**
         * 保存mat头的关键信息
         */
        typedef struct {
            int rows;
            int cols;
            int type;
        } MatHeader;
    };
}


#endif //SAVEMAT_H
