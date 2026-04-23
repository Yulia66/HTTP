#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>


class Runner {
    public:
    static int exec(const std::string& cmd);
    static std::string execCommand(const std::string& cmd);
};

/*
struct ProcessResult {
    int return_code;      // 0 если успех, иначе код ошибки
    std::string stdout;   // что программа напечатала в консоль
    std::string stderr;   // ошибки программы
    
    // TODO: добавить конструктор по умолчанию?
    // TODO: добавить метод is_success()?
};

class ProcessRunner {
public:
    // Запускает команду с аргументами и ждет завершения
    ProcessResult run(const std::vector<std::string>& command);
    
    // TODO: добавить метод для запуска с таймаутом?
    // ProcessResult run_with_timeout(const std::vector<std::string>& command, int seconds);
    
private:
    // TODO: какие приватные методы нужны?
    // - maybe_read_from_pipe()
    // - setup_io_redirection()
    // - wait_for_process()
};
*/