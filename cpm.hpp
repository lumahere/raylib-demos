#pragma once

#ifndef __cplusplus
#error cpm.hpp is to be used with c++ only
#endif

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>


#ifndef CPP_COMPILER
#define CPP_COMPILER "g++"
#endif

#define KERR "\x1B[31m" // RED
#define KWAR "\x1B[33m" // YELLOW
#define KMSG "\x1B[35m" // MAGENTA
#define KNRM "\x1B[0m"  // NORMAL COLOR


enum class Loglevel{
    CPM_INFO,CPM_WARNING,CPM_ERROR,CPM_MSG
};
void cpm_log(Loglevel lvl, const char *fmt, ...) {
  std::string msg("");
  time_t time_now;
  struct tm *time_info;
  time(&time_now);
  time_info = localtime(&time_now);
  char timenow[128];
  sprintf(timenow, "(%02d:%02d:%02d)", time_info->tm_hour, time_info->tm_min,
          time_info->tm_sec);
  switch (lvl) {
  case Loglevel::CPM_INFO:
    msg.append(KMSG);
    msg.append("LOG");
    msg.append(" ");
    msg.append(timenow);
    msg.append(":");
    msg.append(" ");
    std::cout << msg;
    break;
  case Loglevel::CPM_WARNING:
    msg.append(KWAR);
    msg.append("WARNING");
    msg.append(" ");
    msg.append(timenow);
    msg.append(":");
    msg.append(" ");
    std::cout << msg;
    break;
  case Loglevel::CPM_ERROR:
    msg.append(KERR);
    msg.append("ERROR");
    msg.append(" ");
    msg.append(timenow);
    msg.append(":");
    msg.append(" ");
    std::cout << msg;
    break;
  case Loglevel::CPM_MSG:
    msg.append(KMSG);
    std::cout << msg;
    break;
  }

  va_list args;
  va_start(args, fmt);
  vfprintf(stdout, fmt, args);
  va_end(args);
  fprintf(stdout, "%s", KNRM);
}

class Cmd{
public:
    Cmd(const char* program): internalcmd(program){}

    Cmd& arg(const char* arg){
        internalcmd.append(" ");
        internalcmd.append(arg);
        return *this;
    }


    Cmd& args(std::vector<const char*> args){
        for (const char* elem : args){
            internalcmd.append(" ");
            internalcmd.append(elem);
        }
        return *this;
    }

    void exec(){
        std::system(internalcmd.c_str());
    }
    Cmd& echo(){
        cpm_log(Loglevel::CPM_MSG, internalcmd.c_str());
        std::cout << "\n";
        return *this;
    }

private:
    std::string internalcmd;

};



bool file_exists(const char* file){
    std::ifstream tst(file);
    if (tst.fail()){
        return false;
    }
    return true;
}

bool file_exists(std::string filepath){
    std::ifstream tst(filepath);
    if (tst.fail()){
        return false;
    }
    return true;

}
//Detects and runs a build.cpp in a folder
void cpm_submodule(const char* folder, std::vector<const char*> args){
    std::string buildc(folder);
    buildc.append("/build.cpp");
    if (file_exists(buildc)){
        Cmd cpy("cp");
        cpy.args({"cpm.hpp", folder});
        cpy.exec();
        std::string target = folder;
        target.append("/buildscript");
        cpm_log(Loglevel::CPM_MSG, "===============BEGIN SUBMODULE (build.c)================\n");
        Cmd build(CPP_COMPILER);
        build.args({buildc.c_str(), "-o", target.c_str(),});
        build.exec();
        build.echo();

        Cmd run("cd");
        run.args({folder, "&&", "./buildscript"});
        run.exec();

        std::string targetrm = folder;
        targetrm.append("/cpm.hpp");
        Cmd rm("rm");
        rm.arg(targetrm.c_str());
        rm.exec();

        cpm_log(Loglevel::CPM_MSG, "=====================END SUBMODULE=====================\n");
    }
}
