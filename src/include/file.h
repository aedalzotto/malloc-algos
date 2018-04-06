#ifndef MMALGO_FILE_H
#define MMALGO_FILE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class mem_index {
public:
    mem_index(unsigned int size);
    bool is_hole;
    unsigned int start;
    unsigned int size;
};

class mem_list {
public:
    mem_list(unsigned int id, unsigned int size);
    unsigned int id;
    std::vector<mem_index> index;
};

class jobs {
public:
    jobs(unsigned int id, unsigned int size);
    unsigned int id;
    unsigned int size;
};

class mmalgo_parser {
public:
    mmalgo_parser();
    void open_list(std::string file_name);
    void open_task(std::string file_name);

    std::vector<mem_list> memory;
    std::vector<jobs> task;

private:
    const std::vector<std::string> explode(const std::string& s, const char& c);
    bool isInteger(const std::string &s);
};



#endif