#include "cpm.hpp"
const char* cflags = "-I ../../raylib/include -L../../raylib/lib -Wall -Wextra";
const char* rpath = "-Wl,-rpath,'$ORIGIN'/../../raylib/lib";

int main(){

    Cmd("gcc").arg(cflags).arg(rpath).arg("text-scroll.c").args({"-o", "textscrl", "-lraylib"}).echo().exec();
}
