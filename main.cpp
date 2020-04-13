#include <fstream>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <unordered_map>
#include <vector>
#include "global_vars.h"
#include "var_types.h"
#include "runner.h"
#include "Utils.h"


using namespace std;


int main(int argv, char *args[]) {
    std::ifstream file(args[1]);
    if(!file) {
        cout << "Couldn't open the file";
        exit(0);
    }
    while(file.getline(line, 1024)) {
        Utils::add_array(line, buffer_matrix);
    }
    Run::process_file(buffer_matrix, head, tail);
    Run::execute(stack_cond, head);
}