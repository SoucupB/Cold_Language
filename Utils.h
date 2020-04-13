#pragma once
#include <fstream>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#define VARIABLE 1
#define FOR 2
#define WHILE 3
#define IF 4
#define WRONG_TYPE 5
#define FUNCTION 6
#define EXPRESSION 7
#define ENDIF 8
#define ENDFOR 9
#define ENDWHILE 10
#include "var_types.h"
//#include "global_vars.h"

class Utils {
public:
    static void add_array(char line[], vector< vector<char> > &buffer_matrix);
    static void remove_spaces(vector<char> line, int &index);
    static char is_letter(char element);
    static char is_digit(char element);
    static void error();
    static int is_expression(vector<char> line, int index);
    static void show_bar(Conditionals *show_stack_trace, unordered_map<string, int> mem);
    static char check_values(vector<char> str1, string str2);
    static string get_first_condition(int &index, vector<char> line);
    static string get_last_condition(int &index, vector<char> line);
    static void add_instruction(Conditionals *instruction, Conditionals *&head, Conditionals *&tail);
    static string get_middle_condition(int &index, vector<char> line);
    static bool compare_signs(char sign);
    static bool is_conditional(char elem);
    static void remove_spaces_from_string(string &value);
    static string get_sections(int &index, vector<char> line);
    static bool is_in_mem(string variable, unordered_map<string, int> value);
};