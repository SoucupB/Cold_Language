#pragma once
#include <fstream>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
struct Conditionals {
    string left, right, condition, for_variable, var_name, incremental;
    int type, jump_next = 0, jump_back = 0;
    int if_end_index = 0, left_int, right_int, index_name_value;
    Conditionals *next, *else_pointer, *belongs, *end;
};