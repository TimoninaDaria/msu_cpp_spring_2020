#include <string>
#include <iostream>
#include <ctype.h>
#include <vector>
#include "pool.h"
#include <sstream>
#include <fstream>
#include <future>
#include <atomic>

std::atomic_int sum_result = {0};

void sumline(const std::string& line){
    int sum_result = 0;
    std::istringstream iss(line);
    int i = 0;
    while (iss >> i)
    {
        ::sum_result += i;
    }
}

int sum(const std::string file){
    ThreadPool pool(2);
    int result = 0;
    std::string line;
    std::ifstream myfile;
    myfile.open(file);
    if(!myfile.is_open())
        throw std::runtime_error("Could not open file");

    std::vector <std::future<void>> taskes;
    while(getline(myfile, line)){
        taskes.emplace_back(pool.exec(sumline, line));
    }

    for(auto &task: taskes)
        task.wait();

    return ::sum_result;
}

int main(){
    std::cout<<sum("data.txt");
    return 0;
}
