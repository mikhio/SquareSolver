#ifndef CLI_COLORS_H
#define CLI_COLORS_H

/** @file CliColors.h */

#define COLOR_RESET "\x1B[0m"     ///< Constant for ASCII reset color
#define COLOR_RED   "\x1B[1;31m"  ///< Constant for ASCII red bold color
#define COLOR_GRN   "\x1B[1;32m"  ///< Constant for ASCII green bold color
#define COLOR_YEL   "\x1B[1;33m"  ///< Constant for ASCII yellow bold color
#define COLOR_BLU   "\x1B[1;34m"  ///< Constant for ASCII blue bold color
#define COLOR_MAG   "\x1B[1;35m"  ///< Constant for ASCII magenta bold color
#define COLOR_WHT   "\x1B[1;37m"  ///< Constant for ASCII white bold color


#define RED(str)     COLOR_RED str COLOR_RESET ///< Macros that set red color to str
#define GREEN(str)   COLOR_GRN str COLOR_RESET ///< Macros that set green color to str
#define MAGENTA(str) COLOR_MAG str COLOR_RESET ///< Macros that set magenta color to str



#endif // CLI_COLORS_H
