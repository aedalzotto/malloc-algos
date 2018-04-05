#ifndef MMALGO_FILE_H
#define MMALGO_FILE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class mmalgo_parser {
public:
    mmalgo_parser();
    void open_list(std::string file_name);
    void open_task(std::string file_name);

private:
    std::vector<int> list;
    std::vector<int> task;
    std::ifstream task_file;
    std::ifstream list_file;

    void open_file(std::string file_name);

};

#endif