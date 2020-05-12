#include <string>
#include <iostream>
#include <ctype.h>
#include <vector>
#include "pool.h"

void foo(int a) {
    std::cout << a << '\n';
    return;
}

void goo(int a, int b) {
    std::cout << a << '\n';
    std::cout << b << '\n';
    return;
}

int loo(std::string str){
    return str.length();
}


int main(){

    ThreadPool pool(5);
    auto task1 = pool.exec(foo, 51);
    task1.get();
    auto task2 = pool.exec(goo, 31, 1);
    task2.get();
    auto task3 = pool.exec(foo, 21);
    task3.get();
    auto task4 = pool.exec(loo, "dff");
    int res = task4.get();
    std::cout << res;

}
