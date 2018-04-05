#ifndef MMALGO_MANAGER_H
#define MMALGO_MANAGER_H

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
};

#endif
