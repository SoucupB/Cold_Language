#include "runner.h"

Conditionals *Run::main_function = new Conditionals();

int Run::get_var_value(unordered_map<string, int> &mem, string exp, int &index) {
    string var_name = "";
    while(index < exp.size() && Utils::is_letter(exp[index])) {
        var_name += exp[index];
        index++;
    }
    if(var_name == "")
        return 0;
    if(mem.find(var_name) != mem.end())
        return mem[var_name];
    else
    {
        Utils::error();
        return -1;
    }
}

void Run::process_file(vector< vector<char> > &buffer_matrix, Conditionals *&head, Conditionals *&tail) {
    int current_index = 0;
    main_function->type = FUNCTION;
    Parse::process_line(buffer_matrix, head, tail, main_function);
}

int Run::get_expression(string exp, int &index, unordered_map<string, int> &mem) {
    int sum = get_var_value(mem, exp, index);
    if(exp[index] == '(') {
        index++;
        sum += execute_expresion(index, exp, mem);
        index++;
    }
    while(index < exp.size() && Utils::is_digit(exp[index])) {
        sum *= 10;
        sum += exp[index] - 48;
        index++;
    }
    return sum;
}

int Run::execute_product(string expression, unordered_map<string, int> &mem, int &index) {
    int get_initial_value = get_expression(expression, index, mem);
    while(index < expression.size() && (expression[index] == '*' || expression[index] == '/' || expression[index] == '%')) {
        if(expression[index] == '*') {
            index++;
            get_initial_value *= get_expression(expression, index, mem);
        }
        if(expression[index] == '/') {
            index++;
            get_initial_value /= get_expression(expression, index, mem);
        }
        if(expression[index] == '%') {
            index++;
            get_initial_value %= get_expression(expression, index, mem);
        }
    }
    return get_initial_value;
}

int Run::execute_expresion(int &index, string expression, unordered_map<string, int> &mem) {
    int get_initial_value = execute_product(expression, mem, index);
    while(index < expression.size() && (expression[index] == '-' || expression[index] == '+')) {
        if(expression[index] == '+') {
            index++;
            get_initial_value += execute_product(expression, mem, index);
        }
        if(expression[index] == '-') {
            index++;
            get_initial_value -= execute_product(expression, mem, index);
        }
    }
    return get_initial_value;
}

void Run::check_preexistance(string var_name, unordered_map<string, int> &mem, Conditionals *condition) {
    if(mem.find(var_name) != mem.end() && condition->type == VARIABLE) {
        perror("var is already initialized");
        exit(0);
    }

    if(mem.find(var_name) == mem.end() && condition->type == EXPRESSION) {
        perror("var is not initialized");
        exit(0);
    }
}

void Run::execute_var_parser(unordered_map<string, int> &mem, Conditionals *&var) {
    check_preexistance(var->left, mem, var);
    int index = 0;
    if(var->type == IF) {
        int first_value = execute_expresion(index, var->left, mem);
        if(var->right != "NULL")
        {
            index = 0;
            int second_value = execute_expresion(index, var->right, mem);
            var->left_int = first_value;
            var->right_int = second_value;
            if(var->condition == "<=") {
                if(first_value > second_value) {
                    var->jump_next = 1;
                }
            }
            if(var->condition == ">=") {
                if(first_value < second_value) {
                    var->jump_next = 1;
                }
            }
            if(var->condition == "==") {
                if(first_value != second_value) {
                    var->jump_next = 1;
                }
            }
            if(var->condition == "!=") {
                if(first_value == second_value) {
                    var->jump_next = 1;
                }
            }
        }
    }
    if(var->type == WHILE) {
        int first_value = execute_expresion(index, var->left, mem);
        if(var->right != "NULL")
        {
            index = 0;
            int second_value = execute_expresion(index, var->right, mem);
            var->left_int = first_value;
            var->right_int = second_value;
            if(var->condition == "<=") {
                if(first_value > second_value) {
                    var->jump_next = 1;
                    var->end->jump_back = 0;
                    return ;
                }
            }
            if(var->condition == ">=") {
                if(first_value < second_value) {
                    var->jump_next = 1;
                    var->end->jump_back = 0;
                    return ;
                }
            }
            if(var->condition == "==") {
                if(first_value != second_value) {
                    var->jump_next = 1;
                    var->end->jump_back = 0;
                    return ;
                }
            }
            if(var->condition == "!=") {
                if(first_value == second_value) {
                    var->jump_next = 1;
                    var->end->jump_back = 0;
                    return ;
                }
            }
            var->end->jump_back = 1;
            return ;
        }
    }
    if(var->type == FOR) {
        int start_interval = execute_expresion(index, var->left, mem);
        if(var->right != "NULL") {
            index = 0;
            int end_interval = execute_expresion(index, var->right, mem);
            index = 0;
            int incremental = execute_expresion(index, var->incremental, mem);
            var->index_name_value = incremental;
            if(Utils::is_in_mem(var->var_name, mem)) {
                mem[var->var_name] = start_interval;
            }
            if(mem[var->var_name] > end_interval) {
                var->jump_next = 1;
                var->end->jump_back = 0;
                mem.erase(var->var_name);
                return ;
            }
            var->end->jump_back = 1;
        }
    }
    if(var->type == VARIABLE || var->type == EXPRESSION) {
        if(var->right != "NULL")
            mem[var->left] = execute_expresion(index, var->right, mem);
        else {
            mem[var->left] = 0;
        }
    }
}

void Run::next_pointer(Conditionals *&conditional, unordered_map<string, int> &mem) {
    if(conditional->jump_next) {
        conditional = conditional->end;
        conditional->belongs->jump_next = 0;
        return ;
    }
    if(conditional->jump_back)
    {
        if(conditional->type == ENDFOR) {
            mem[conditional->belongs->var_name] += conditional->belongs->index_name_value;
        }
        conditional = conditional->belongs;
        conditional->jump_back = 0;
        return ;
    }
    conditional = conditional->next;
}

void Run::execute(vector<Conditionals*> stacker, Conditionals *head) {
    unordered_map<string, int> mem;
    Conditionals *new_head = head;
    while(new_head) {
        execute_var_parser(mem, new_head);
        Utils::show_bar(new_head, mem);
        next_pointer(new_head, mem);
    }
}