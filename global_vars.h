#pragma once
#include <string.h>

#include <iostream>
#include <unordered_map>
#include <vector>
#include "var_types.h"
using namespace std;

vector<Conditionals*> stack_cond;
Conditionals *head, *tail;
int buffer_index, line_number;
vector< vector<char > > buffer_matrix;
char line[1024];
