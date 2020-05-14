#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <atomic>
#include <mutex>
#include <deque>
#include <vector>
#include <condition_variable>
#include <string>
#include <iostream>
#include <ctype.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <future>
#include <atomic>

#include "pool.h"

int sumline(const std::string& line){
    int sum_result = 0;
    std::istringstream iss(line);
    int i = 0;
    while (iss >> i)
    {
        sum_result += i;
    }
    return sum_result;
}

int sum(const std::string file){
    ThreadPool pool(2);
    int result = 0;
    std::string line;
    std::ifstream myfile;
    myfile.open(file);
    if(!myfile.is_open())
        throw std::runtime_error("Could not open file");

    std::vector <std::future<int>> taskes;
    int sum_result {0};
    while(getline(myfile, line)){
        taskes.emplace_back(pool.exec(sumline, line));
    }

    for(auto &task: taskes)
        sum_result += task.get();

    return sum_result;
}

int main(){
    std::cout<<sum("data.txt");
    return 0;
}
