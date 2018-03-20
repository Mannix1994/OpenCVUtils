//
// Created by creator on 18-3-13.
//

#ifndef COMPAREMATS_H
#define COMPAREMATS_H

#include <opencv2/opencv.hpp>
namespace Utils {
    class CompareMats {
    public:
        /**
         * 完成两个Mat的比较
         * @param mat0 Mat0
         * @param mat1 Mat1
         */
        CompareMats(cv::Mat mat0, cv::Mat mat1);

        /**
         * 返回比对报告，包含两个mat是否相同，相同点数量，不同点数量
         * @return 比对报告
         */
        std::string report();

        /**
         * 两张图片是否相同
         * @return 相同返回true，否则返回false
         */
        bool same();

        /**
         * 返回以红色作为不同点的标记的Mat
         * @return mat
         */
        cv::Mat mask();

        /**
         * 返回不同点的坐标向量
         * @return vector
         */
        std::vector<cv::Point> points();

        /**
         * 保存报告
         * @param fileName 文件名
         */
        void saveReport(std::string fileName);

        /**
         * 返回相同点的数量
         * @return 大于等于0的值
         */
        long long sameCount();

        /**
         * 返回不同点的数量
         * @return 大于等于0的值
         */
        long long differentCount();

    private:
        /**
         * 比对两个Mat，并计算出相同点，不同点的数量。
         * 记录下不同点的坐标；很据不同点的数量是否等
         * 于0来判断两个Mat是否相等。
         * @param mat1 Mat1
         * @param mat2 Mat2
         */
        void compare(cv::Mat mat1, cv::Mat mat2);

    private:
        long long _sameCount;
        long long _differentCount;
        bool _same;
        std::vector<cv::Point> _differentPoints;
        cv::Mat _mask;
    };
}

#endif //COMPAREMATS_H
