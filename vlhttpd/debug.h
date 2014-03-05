#ifndef DEBUG_H
#define DEBUG_H
#define DEBUG
#ifdef DEBUG
#include <cstdio>
#define printError printf("[%s]", __FILE__), printf
#endif
#endif