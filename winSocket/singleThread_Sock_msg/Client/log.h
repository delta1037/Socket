//
// Created by liubo on 2018/7/9.
//

#ifndef WINSOCK_LOG_H
#define WINSOCK_LOG_H

#include <stdio.h>
#include <errno.h>

#define INFO   "[INFO]"
#define ERROR  "[ERROR]"
#define NEW_LINE "\n"

#define LOG_ERROR(...)  { printf(__TIME__); \
                          printf(ERROR);\
                          printf(__VA_ARGS__);   \
                          printf(NEW_LINE); \
                        }

#define LOG_INFO(...)   { printf(__TIME__); \
                          printf(INFO); \
                          printf(__VA_ARGS__);  \
                          printf(NEW_LINE); \
                        }

#define CHECK(x,m,handle) if((x)==(m)){\
                           handle;\
                           return -1;\
                         }

#endif //WINSOCK_LOG_H
