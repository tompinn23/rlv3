#ifndef U_UTIL_H
#define U_UTIL_H

#include "top-level.h"

#include <string>

void init_stuff();
void init_logging();

void quit(std::string msg, int error_code);

#endif