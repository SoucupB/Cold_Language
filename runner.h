#pragma once
#include <fstream>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <unordered_map>
#include <vector>
#include "Utils.h"
#include "var_types.h"
#include "compiler.h"

using namespace std;
class Run{
public:
    static Conditionals *main_function;
    static int get_var_value(unordered_map<string, int> &mem, string exp, int &index);
    static int get_expression(string exp, int &index, unordered_map<string, int> &mem);
    static int execute_product(string expression, unordered_map<string, int> &mem, int &index);
    static int execute_expresion(int &index, string expression, unordered_map<string, int> &mem);
    static void check_preexistance(string var_name, unordered_map<string, int> &mem, Conditionals *condition);
    static void execute_var_parser(unordered_map<string, int> &mem, Conditionals *&var);
    static void execute(vector<Conditionals*> stacker, Conditionals *head);
    static void process_file(vector< vector<char> > &buffer_matrix, Conditionals *&head, Conditionals *&tail);
    static void next_pointer(Conditionals *&conditional, unordered_map<string, int> &mem);
    static char check_values(vector<char> str1, string str2);
};