#ifndef MMALGO_MANAGER_H
#define MMALGO_MANAGER_H

#include <vector>
#include <chrono>

#include "file.h"

#include <iostream>

class mmalgo_rithm {
public:
    mmalgo_rithm();

    void run_first(mmalgo_parser& parser);
    void run_next(mmalgo_parser& parser);
    void run_best(mmalgo_parser& parser);
    void run_worst(mmalgo_parser& parser);
    void run_lucky(mmalgo_parser& parser);

    unsigned int get_searched();
    unsigned int get_unalloced();
    unsigned int get_hole_number();
    unsigned long int get_runtime();
    std::vector<std::pair<unsigned int, unsigned int> >& get_hole_info();

private:
    unsigned int searched;
    unsigned int failed;
    unsigned int total_holes;
    unsigned long duration;
    std::vector<std::pair<unsigned int, unsigned int> > holes;
    bool fits(mem_list mem);
    std::vector<jobs>::iterator compare_to;

};

#endif
