#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <sys/stat.h>

int sort_by_merge(std::string file_to_sort);
void mymerge(std::vector<uint64_t>& vec, int start, int mid, int end);
void merge_sort(std::vector<uint64_t>& vec, int start, int end);
void mergeF(std::string input1, const std::string input2, const std::string output);
int batch_toF(std::string strF);
int sort_by_merge(std::string file_to_sort);
