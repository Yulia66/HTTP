#include <iostream>
#include <future>
#include <queue>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <random>
#include "task_manager.hpp"
#include "run_process.h"

    

    size_t TaskManager::submit_task(std::vector<std::string> command){ //производитель 
        std::lock_guard<std::mutex> lock(store_mtx);
        int task_id = id++;
        Task task;
        task._id = task_id;
        task._status = "pending";
        task._command = command;
        _task_store[task_id] = task;


        auto task_function = [this, task_id, command]() {
            {
            std::lock_guard<std::mutex> lock(store_mtx);
            _task_store[task_id]._status = "running";
            }   

            std::string result;
    
            for (const auto& str : command) {
                if (!result.empty()) result += ' ';
                result += str;
            }
           // std::cout << "Команда: " << result << std::endl;  // ← что выводится?

            std::string cmd = Runner::execCommand(result);
           // std::cout << "Вывод: " << cmd << std::endl;  // ← что выводится?
            //std::this_thread::sleep_for(std::chrono::seconds(5)); // вызов процессов пока заглушка
            {
            std::lock_guard<std::mutex> lock(store_mtx);
            _task_store[task_id]._status = "completed";
            _task_store[task_id]._result = cmd;
            }
            
           // std::cout << "Завершение потока\\n";
        };

        _task_queue.push(task_function);
        cv.notify_one();
        return task_id;
    }


    std::string TaskManager::get_status(const int & id){
        std::lock_guard<std::mutex> lock(store_mtx);
        auto it = _task_store.find(id);
        if (it == _task_store.end()) return "not_found";

        return it->second._status;

    }
    std::string TaskManager::get_result(const int & id){
        std::lock_guard<std::mutex> lock(store_mtx);
        auto it = _task_store.find(id);
        if (it == _task_store.end()) return "not_found";

        return it->second._result;

    }

    void TaskManager::worker_loop(){//потребитель
        while (true)
        {
            std::function<void()> task;
            {
                
            std::unique_lock <std::mutex> lock(mtx); 
            cv.wait(lock, [this] { return !_task_queue.empty() || stop; });
            if(stop && _task_queue.empty()) {
                break;
            }
           
            task = _task_queue.front();
            _task_queue.pop();
        }
            task();
            
        }

    }
    
    TaskManager::TaskManager(size_t N){
        for(int i =0; i< N; i++){
            _workers.emplace_back([this]{worker_loop();});
        }
    }



  TaskManager::~TaskManager(){
    stop = true;
    cv.notify_all();
    for(auto& worker:_workers){
        if(worker.joinable()) {
            worker.join();  // ← ЖДЕМ ПОХОРОН
        }
    }
 }