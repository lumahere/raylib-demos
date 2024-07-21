#include "cpm.hpp"
const char* cflags = "-I ../../raylib/include -L../../raylib/lib -Wall -Wextra";
const char* rpath = "-Wl,-rpath=../../raylib/lib";

int main(){

    Cmd("gcc").arg(cflags).arg(rpath).arg("gradient.c").args({"-o", "gradient", "-lraylib"}).echo().exec();
}
