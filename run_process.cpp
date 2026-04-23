#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include "run_process.h"


std::string Runner::execCommand(const std::string& cmd) {
    std::string result;
    FILE* pipe = popen(cmd.c_str(),"r");
    if (!pipe) {
        return "ERROR: popen failed";
    }
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    
    pclose(pipe);
    return result;
}


 int Runner::exec(const std::string& cmd) {
        if (fork() == 0) {
            execl("/bin/sh", "sh", "-c", ("/usr/bin/" + cmd).c_str(), nullptr);
            exit(1);
        }
        int status;
        wait(&status);
        return WEXITSTATUS(status);
    };
