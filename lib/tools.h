
#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string>

/**
 * condition为false时抛出错误，错误信息为error_message
 */
#define ASSERT(condition,error_message) ((condition)?0:(error(__FILE__, __func__, __LINE__,error_message),-1))
/**
 * condition为false时抛出警告，错误信息为warning_message
 */
#define WARNING(condition,warning_message) ((condition)?0:(warning(__FILE__, __func__, __LINE__,warning_message),-1))

void error(const std::string &filePath, const std::string &function,
           int line, const std::string &info);

void warning(const std::string &filePath, const std::string &function,
                    int line, const std::string &info);
#endif //TOOLS_H
