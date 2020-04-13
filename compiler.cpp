#include "compiler.h"
int Parse::file_index = 0;

void Parse::process_line(vector< vector<char> > &buffer_matrix, Conditionals *&head, Conditionals *&tail, Conditionals *father) {
    if(Parse::file_index == buffer_matrix.size()) {
        return ;
    }
    vector<char> line;
    int line_index = 0;
    line = buffer_matrix[Parse::file_index];
    if(line.size()) {
        int type = check_type(line, line_index);
        Conditionals *new_condition = new Conditionals();
        new_condition->type = type;
        new_condition->belongs = father;
        if(type == ENDIF || type == ENDFOR || type == ENDWHILE) {
            if(type == ENDIF) {
                father->end = new_condition;
                new_condition->belongs = father;
            }
            if(type == ENDWHILE) {
                father->end = new_condition;
                new_condition->belongs = father;
            }
            if(type == ENDFOR) {
                father->end = new_condition;
                new_condition->belongs = father;
            }
            Utils::add_instruction(new_condition, head, tail);
            return ;
        }
        process_entity(buffer_matrix, new_condition, line, line_index, head, tail, father);
    }
    Parse::file_index++;
    process_line(buffer_matrix, head, tail, father);
}

int Parse::check_type(vector<char> line, int &index) {
    Utils::remove_spaces(line, index);
    if(Utils::is_expression(line, 0)) {
        return EXPRESSION;
    }
    vector<char> prefix;
    while(index < line.size() && Utils::is_letter(line[index])) {
        prefix.push_back(line[index]);
        index++;
    }
    if(Utils::check_values(prefix, "var")) {
        return VARIABLE;
    }
    if(Utils::check_values(prefix, "for")) {
        return FOR;
    }
    if(Utils::check_values(prefix, "while")) {
        return WHILE;
    }
    if(Utils::check_values(prefix, "if")) {
        return IF;
    }
    if(Utils::check_values(prefix, "function")) {
        return FUNCTION;
    }
    if(Utils::check_values(prefix, "endif")) {
        return ENDIF;
    }
    if(Utils::check_values(prefix, "endw")) {
        return ENDWHILE;
    }
    if(Utils::check_values(prefix, "endf")) {
        return ENDFOR;
    }
    return WRONG_TYPE;
}

void Parse::process_entity(vector< vector<char> > &buffer_matrix, Conditionals *new_condition,
                           vector<char> line, int &index, Conditionals *&head, Conditionals *&tail, Conditionals *father) {
    if(new_condition->type == VARIABLE) {
        new_condition->left = get_var_left_name(line, index);
        new_condition->right = get_var_right_name(line, index);
        Utils::add_instruction(new_condition, head, tail);
    }
    if(new_condition->type == EXPRESSION) {
        new_condition->left = get_var_left_name(line, index);
        new_condition->right = get_var_right_name(line, index);
        Utils::add_instruction(new_condition, head, tail);
    }
    if(new_condition->type == IF) {
        new_condition->left = Utils::get_first_condition(index, line);
        new_condition->condition = Utils::get_middle_condition(index, line);
        new_condition->right = Utils::get_last_condition(index, line);
        Parse::file_index++;
        Utils::add_instruction(new_condition, head, tail);
        process_line(buffer_matrix, head, tail, new_condition);
    }

    if(new_condition->type == WHILE) {
        new_condition->left = Utils::get_first_condition(index, line);
        new_condition->condition = Utils::get_middle_condition(index, line);
        new_condition->right = Utils::get_last_condition(index, line);
        Parse::file_index++;
        Utils::add_instruction(new_condition, head, tail);
        process_line(buffer_matrix, head, tail, new_condition);
    }

    if(new_condition->type == FOR) {
        new_condition->var_name = Utils::get_sections(index, line);
        new_condition->left = Utils::get_sections(index, line);
        new_condition->right = Utils::get_sections(index, line);
        new_condition->incremental = Utils::get_sections(index, line);
        Parse::file_index++;
        Utils::add_instruction(new_condition, head, tail);
        process_line(buffer_matrix, head, tail, new_condition);
    }

}

string Parse::get_var_left_name(vector<char> line, int &index) {
    Utils::remove_spaces(line, index);
    string left = "";
    while(index < line.size() && Utils::is_letter(line[index])) {
        left += line[index];
        index++;
    }
    return left;
}

string Parse::get_var_right_name(vector<char> line, int &index) {
    Utils::remove_spaces(line, index);
    string right_expression = "";
    if(index >= line.size() || line[index] != '=') {
        return "NULL";
    }
    index++;
    while(index < line.size()) {
        Utils::remove_spaces(line, index);
        right_expression += line[index];
        index++;
    }
    return right_expression;
}