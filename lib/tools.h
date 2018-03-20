
#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string>

/**
 * condition为false时抛出错误，错误信息为error_message
 */
#define ASSERT(condition,error_message) ((condition)?0:assertion(__FILE__, __func__, __LINE__,error_message))

inline int assertion(const std::string &filePath, const std::string &function,
                     int line, const std::string &info){
    //获取文件名
    unsigned long pos=filePath.find_last_of('/');
    std::string filename(filePath.substr(pos+1));
    std::string err = filename+" "+function+" "+std::to_string(line)+">>  "+info;
    //抛出错误
    throw std::runtime_error(err);
}

#endif //TOOLS_H
