#include <iostream>
#include <vector>
#include <string>

class mmalgo_parser {
public:
    mmalgo_parser();
    void mmalgo_open_list();
    void mmalgo_open_task();

private:
    std::vector<int> list;
    std::vector<int> task;
    void open_file(std::string file_name);

};