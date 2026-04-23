#include <iostream>
#include <future>
#include <queue>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <random>



struct Task {
    
    std::string _id;
    std::vector<std::string> _command;
    std::string _status;
    std::string _result;
};


class TaskManager {
private:
std::condition_variable cv;
std::mutex mtx;
std::mutex store_mtx;
bool stop = false;
size_t id = 0;
std::vector<std::thread> _workers;  // Потоки-воркеры (кто выполняет задачи)
std::queue<std::function<void()>> _task_queue; // ОЧЕРЕДЬ ЗАДАЧ (что ждет выполнения)
std::map<int, Task> _task_store; // ХРАНИЛИЩЕ ЗАДАЧ (статусы и результаты по task_id)
 public:
    size_t submit_task(std::vector<std::string> command);
    void worker_loop();
    TaskManager(size_t N);
    std::string get_status(const int & id);
    std::string get_result(const int & id);
    ~TaskManager();
};

