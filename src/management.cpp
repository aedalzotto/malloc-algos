#include <random>
#include <algorithm>
#include <chrono>
#include "management.h"

mmalgo_rithm::mmalgo_rithm()
{

}

bool mmalgo_rithm::fits(mem_list mem)
{
    searched++;
    if(mem.available >= compare_to->size)
        return true;
    else
        return false;
}

void mmalgo_rithm::run_first(mmalgo_parser& parser)
{
    searched=0;
    failed = 0;

    auto then = std::chrono::high_resolution_clock::now();
    auto last = parser.memory.begin();
    ///////////////////////////////////////////////////////////////
    for(compare_to = parser.task.begin(); compare_to != parser.task.end(); ++compare_to){
        auto it = std::find_if(last, parser.memory.end(),
                        std::bind1st(std::mem_fun(&mmalgo_rithm::fits), this));

        if(it != parser.memory.end()){
            it->available -= compare_to->size;
            last = it;
            ++last;
            continue;
        }
        
        it = std::find_if(parser.memory.begin(), last,
                        std::bind1st(std::mem_fun(&mmalgo_rithm::fits), this)); 

        if(it != last){
            it->available -= compare_to->size;
            last = it;
            ++last;
        } else {
            failed++;
        }
    }
    ////////////////////////////////////////////////////////////////
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - then).count();

    holes.clear();
    total_holes = 0;
    for(auto& mem : parser.memory){
        if(mem.available){
            total_holes++;
            bool found = false;
            for(auto& hole : holes){
                if(hole.first == mem.available){
                    hole.second++;
                    found = true;
                    break;
                }
            }
            if(!found)
                holes.push_back(std::pair<unsigned int, unsigned int>(mem.available, 1));
        }
    }
}

void mmalgo_rithm::run_next(mmalgo_parser& parser){
    searched=0;
    failed = 0;
    //Qualquer preparação para o algoritmo acima
    auto then = std::chrono::high_resolution_clock::now();
    //Algoritmo abaixo
    //////////////////////////////////////////////////////



    /////////////////////////////////////////////////////
    //Fim do algoritmo
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - then).count();
    holes.clear();
    total_holes = 0;
    for(auto& mem : parser.memory){
        if(mem.available){
            total_holes++;
            bool found = false;
            for(auto& hole : holes){
                if(hole.first == mem.available){
                    hole.second++;
                    found = true;
                    break;
                }
            }
            if(!found)
                holes.push_back(std::pair<unsigned int, unsigned int>(mem.available, 1));
        }
    }
}

void mmalgo_rithm::run_best(mmalgo_parser& parser)
{
    searched=0;
    failed = 0;
    //Qualquer preparação para o algoritmo acima
    auto then = std::chrono::high_resolution_clock::now();
    //Algoritmo abaixo
    //////////////////////////////////////////////////////
    
    for(auto& job : parser.task){

        std::vector<mem_list>::iterator best = parser.memory.begin();
        
        for(auto mem = parser.memory.begin(); mem != parser.memory.end(); ++mem){
            searched++;

            long int hole_sz = mem->available - job.size;
            if(hole_sz < 0)
                continue;

            if(!hole_sz){
                best = mem;
                break;
            }

            if((mem->available < best->available && mem->available >= job.size)
                || best->available < job.size)
                best = mem;
            
        }

        if(best->available >= job.size){
            std::cout << "Alocou job " << job.id << " em bloco " << best->id << std::endl;
            best->available -= job.size;
        } else {
            failed++;
            std::cout << "Nenhum bloco disponível para job " << job.id << std::endl;
        }

    }

    /////////////////////////////////////////////////////
    //Fim do algoritmo
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - then).count();
    holes.clear();
    total_holes = 0;
    for(auto& mem : parser.memory){
        if(mem.available){
            total_holes++;
            bool found = false;
            for(auto& hole : holes){
                if(hole.first == mem.available){
                    hole.second++;
                    found = true;
                    break;
                }
            }
            if(!found)
                holes.push_back(std::pair<unsigned int, unsigned int>(mem.available, 1));
        }
    }
}

void mmalgo_rithm::run_worst(mmalgo_parser& parser)
{
    searched=0;
    failed = 0;
    //Qualquer preparação para o algoritmo acima
    auto then = std::chrono::high_resolution_clock::now();
    //Algoritmo abaixo
    //////////////////////////////////////////////////////
    
    for(auto& job : parser.task){

        std::vector<mem_list>::iterator worst = parser.memory.begin();
        
        for(auto mem = parser.memory.begin(); mem != parser.memory.end(); ++mem){
            searched++;
            if(mem->available > worst->available)
                worst = mem;
        }

        if(worst->available >= job.size){
            worst->available -= job.size;
            std::cout << "Alocou job " << job.id << " em bloco " << worst->id << std::endl;
        } else {
            failed++;
            std::cout << "Nenhum bloco disponível para job " << job.id << std::endl;
        }

    }

    /////////////////////////////////////////////////////
    //Fim do algoritmo
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - then).count();

    holes.clear();
    total_holes = 0;
    for(auto& mem : parser.memory){
        if(mem.available){
            total_holes++;
            bool found = false;
            for(auto& hole : holes){
                if(hole.first == mem.available){
                    hole.second++;
                    found = true;
                    break;
                }
            }
            if(!found)
                holes.push_back(std::pair<unsigned int, unsigned int>(mem.available, 1));
        }
    }
}

void mmalgo_rithm::run_lucky(mmalgo_parser& parser)
{
    searched=0;
    failed = 0;
    


    //Qualquer preparação para o algoritmo acima
    auto then = std::chrono::high_resolution_clock::now();
    //Algoritmo abaixo
    //////////////////////////////////////////////////////

    for(auto& job : parser.task){

        //Random access to memory blocks
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(parser.memory.begin(), parser.memory.end(), std::default_random_engine(seed));
        bool alloc = false;

        //First fit
        for(auto& mem : parser.memory){
            searched++;
            if(mem.available >= job.size){
                std::cout << "Alocou job " << job.id << " em bloco " << mem.id << std::endl;
                mem.available -= job.size;
                alloc = true;
                break;
            }
        }
        if(!alloc){
            failed++;
            std::cout << "Nenhum bloco disponível para job " << job.id << std::endl;
        }
    }

    /////////////////////////////////////////////////////
    //Fim do algoritmo
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - then).count();
    holes.clear();
    total_holes = 0;
    for(auto& mem : parser.memory){
        if(mem.available){
            total_holes++;
            bool found = false;
            for(auto& hole : holes){
                if(hole.first == mem.available){
                    hole.second++;
                    found = true;
                    break;
                }
            }
            if(!found)
                holes.push_back(std::pair<unsigned int, unsigned int>(mem.available, 1));
        }
    }
}

unsigned int mmalgo_rithm::get_searched()
{
    return searched;
}

unsigned int mmalgo_rithm::get_unalloced()
{
    return failed;
}
unsigned int mmalgo_rithm::get_hole_number()
{
    return total_holes;
}

std::vector<std::pair<unsigned int, unsigned int> >& mmalgo_rithm::get_hole_info()
{
    return holes;
}

unsigned long int mmalgo_rithm::get_runtime()
{
    return duration;
}