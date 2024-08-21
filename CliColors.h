#ifndef CLI_COLORS_H
#define CLI_COLORS_H

#define COLOR_RESET "\x1B[0m"
#define COLOR_RED   "\x1B[1;31m"
#define COLOR_GRN   "\x1B[1;32m"
#define COLOR_YEL   "\x1B[1;33m"
#define COLOR_BLU   "\x1B[1;34m"
#define COLOR_MAG   "\x1B[1;35m"
#define COLOR_CYN   "\x1B[1;36m"
#define COLOR_WHT   "\x1B[1;37m"


#define RED(str)     COLOR_RED str COLOR_RESET
#define GREEN(str)   COLOR_GRN str COLOR_RESET
#define MAGENTA(str) COLOR_MAG str COLOR_RESET



#endif // CLI_COLORS_H
