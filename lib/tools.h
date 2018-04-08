
#ifndef TOOLS_H
#define TOOLS_H

#include <string>

/**
 * condition为false时抛出错误，错误信息为error_message
 */
#define ASSERT(condition,error_message) \
    if (!(condition)){\
        error(__FILE__, __func__, __LINE__,error_message); \
    }
/**
 * condition为false时输出警告，错误信息为warning_message
 */
#define WARNING(condition,warning_message)\
    if (!(condition)){\
        warning(__FILE__, __func__, __LINE__,error_message); \
    }

void error(const std::string &filePath, const std::string &function,
           int line, const std::string &info);

void warning(const std::string &filePath, const std::string &function,
                    int line, const std::string &info);

/**
 * IF_INT中的IF表示这是一个条件宏，INT表示这个宏返回的值是整形类型的值.
 * condition为true时返回0;
 * condition为false时输出false_message,并返回return_code指定的整数.
 */
#define IF_INT(condition,false_message,return_code) ((condition)?0:(std::cerr<<(false_message)<<std::endl,return_code))

/**
 * IF_ANY中的IF表示这是一个条件宏，ANY表示这个宏返回的值是可以是任意类型的值。
 * condition为true时不做任何动作;
 * condition为false时输出false_message,并返回false_value.
 */
#define IF_ANY(condition,false_message,false_value) \
    if (!(condition)){\
        std::cerr<<(false_message)<<std::endl; \
        return (false_value); \
    }
#endif //TOOLS_H
