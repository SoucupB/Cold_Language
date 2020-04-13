#pragma once
#include <vector>
#include "var_types.h"
#include "Utils.h"

using namespace std;


class Parse {
public:
    static int file_index;
    static void process_line(vector< vector<char> > &buffer_matrix, Conditionals *&head, Conditionals *&tail, Conditionals *father);
    static int check_type(vector<char> line, int &index);
    static void process_entity(vector< vector<char> > &buffer_matrix, Conditionals *new_condition,
                               vector<char> line, int &index, Conditionals *&head, Conditionals *&tail, Conditionals *father);
    static string get_var_left_name(vector<char> line, int &index);
    static string get_var_right_name(vector<char> line, int &index);
};