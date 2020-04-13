#pragma once
#include <string>
#include <iostream>
#include <ctype.h>
#include <vector>
template <class T>
std::string arg_to_string (T&& arg)
{
    std::stringstream s;
    s << arg;

    return s.str();
}

template <class... ArgsT>
std::string format(const std::string& val, ArgsT&&... args) // в скобках допустимо любое целое число, не только цифры
{
    std::string result = "";
    std::vector<std::string> params{arg_to_string(std::forward<ArgsT>(args))...};
    for (int j=0; j<val.length(); j++)
    {
        if  (val[j] == '}') throw std::runtime_error("error");
        if (val[j] == '{')
        {
            if (j  == val.length() - 1) throw std::runtime_error("error");
            j+=1;
            std::string tmp = "";
            while(val[j]!='}'){
                if (j > val.length()-2) throw std::runtime_error("error");
                if (!isdigit(val[j])) throw std::runtime_error("error");
                tmp+=val[j];
                j+=1;
            }
            if (tmp.empty()) throw std::runtime_error("error");
            int num = std::stoi(tmp);
            if (num > params.size()-1) throw std::runtime_error("error");
            result+=params[num];
        }
        else result+=val[j];
    }
    return result;

}

