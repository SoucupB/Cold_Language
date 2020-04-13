#include "Utils.h"

int Utils::is_expression(vector<char> line, int index) {
    string name = "";
    remove_spaces(line, index);
    while(index < line.size() && is_letter(line[index])) {
        index++;
    }
    remove_spaces(line, index);
    if(line[index] != '=')
        return false;
    return true;
}

void Utils::add_array(char line[], vector< vector<char> > &buffer_matrix) {
    int sz = strlen(line);
    vector<char> liner;
    for(int i = 0; i < sz; ++i) {
        if(line[i] != '\t')
            liner.push_back(line[i]);
    }
    buffer_matrix.push_back(liner);
}

string Utils::get_sections(int &index, vector<char> line) {
    remove_spaces(line, index);
    if(line[index] == '(')
        index++;
    string var_name = "";
    while(index < line.size() && line[index] != ',' && line[index] != ')') {
        var_name += line[index];
        index++;
    }
    index++;
    remove_spaces_from_string(var_name);
    return var_name;
}

string Utils::get_first_condition(int &index, vector<char> line) {
    remove_spaces(line, index);
    if(line[index] != '(') {
        return "NULL";
    }
    index++;
    string condition = "";
    remove_spaces(line, index);
    while(index < line.size() && !is_conditional(line[index])) {
        condition += line[index];
        index++;
    }
    remove_spaces_from_string(condition);
    return condition;
}

string Utils::get_middle_condition(int &index, vector<char> line) {
    remove_spaces(line, index);
    string middle = "";
    while(is_conditional(line[index])) {
        middle += line[index];
        index++;
    }
    remove_spaces_from_string(middle);
    return middle;
}

string Utils::get_last_condition(int &index, vector<char> line) {
    remove_spaces(line, index);
    string condition = "";
    while(index < line.size() && line[index] != ')') {
        condition += line[index];
        index++;
    }
    remove_spaces_from_string(condition);
    return condition;
}

bool Utils::compare_signs(char sign) {
    if(sign == '=' || sign == '>' || sign == '<')
        return true;
    return false;
}

void Utils::add_instruction(Conditionals *instruction, Conditionals *&head, Conditionals *&tail) {
    if(!head) {
        head = instruction;
        tail = instruction;
    }
    else {
        tail->next = instruction;
        tail = instruction;
        tail->next = NULL;
    }
}

void Utils::remove_spaces(vector<char> line, int &index) {
    while(index < line.size() && (line[index] == ' ' || line[index] == '\t')) {
        index++;
    }
}

char Utils::is_letter(char element) {
    if((element >= 'a' && element <= 'z') || (element >= 'A' && element <= 'Z'))
        return 1;
    return 0;
}

char Utils::is_digit(char element) {
    if(element >= '0' && element <= '9')
        return 1;
    return 0;
}

void Utils::error() {
    perror("Variable is not initialized");
    exit(0);
}

bool Utils::is_in_mem(string variable, unordered_map<string, int> value) {
    if(value.find(variable) == value.end()) {
        return true;
    }
    return false;
}

void Utils::show_bar(Conditionals *show_stack_trace, unordered_map<string, int> mem) {
    if(show_stack_trace->type == VARIABLE) {
        cout << "Init var: " << show_stack_trace->left << " -> " << mem[show_stack_trace->left] << "\n";
    }
    if(show_stack_trace->type == EXPRESSION) {
        cout << "Expression: " << show_stack_trace->left << " -> " << mem[show_stack_trace->left] << "\n";
    }
    if(show_stack_trace->type == IF) {
        cout << "If condition: " << show_stack_trace->left_int << " " << show_stack_trace->condition << " "
                                 << show_stack_trace->right_int << "\n";
    }
    if(show_stack_trace->type == WHILE) {
        cout << "While condition: " << show_stack_trace->left_int << " " << show_stack_trace->condition << " "
                                    << show_stack_trace->right_int << "\n";
    }
}

bool Utils::is_conditional(char elem) {
    if(elem == '=')
        return true;
    if(elem == '<')
        return true;
    if(elem == '>')
        return true;
    if(elem == '!')
        return true;
    return false;
}

void Utils::remove_spaces_from_string(string &value) {
    std::string::iterator end_pos = std::remove(value.begin(), value.end(), ' ');
    value.erase(end_pos, value.end());
}

char Utils::check_values(vector<char> str1, string str2) {
    if(str1.size() != str2.size())
        return 0;
    for(int i = 0; i < str1.size(); i++)
        if(str1[i] != str2[i])
            return 0;
    return 1;
}
