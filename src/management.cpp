#include <random>
#include <algorithm>

#include "management.h"

mmalgo_rithm::mmalgo_rithm()
{

}

void mmalgo_rithm::run_first(mmalgo_parser& parser)
{
    searched=0;
    failed = 0;

    auto then = std::chrono::high_resolution_clock::now();
    ///////////////////////////////////////////////////////////////
    for(auto& job : parser.task){
        bool alloc=false;
        //Percorre as listas
        for(auto& mem : parser.memory){
            searched++;
            if(mem.available >= job.size){
                std::cout << "Alocou job " << job.id << " em bloco " << mem.id << std::endl;
                mem.available -= job.size;
                alloc=true;
                break;
            }
        }
        if(!alloc){
            failed++;
            std::cout << "Nenhum bloco disponível para job " << job.id << std::endl;
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

    std::vector<mem_list>::iterator it = parser.memory.begin();
    auto last_alloc = parser.memory.end();
    --it;
    
    for(auto& job : parser.task){
        //Percorre as listas
        bool alloc = false;
        while(++it != last_alloc) {
            if(it == parser.memory.end())
                it = parser.memory.begin();

            searched++;
            if(it->available >= job.size){
                std::cout << "Alocou job " << job.id << " em bloco " << it->id << std::endl;
                it->available -= job.size;
                last_alloc = it;
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

            if(hole_sz < (long int)(best->available - job.size) ||
                             (long int)(best->available - job.size) < 0)
                best = mem;
            
        }

        if((long int)(best->available - job.size) >= 0){
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
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,parser.memory.size()-1);
    std::vector<int> indexes;

    searched=0;
    failed = 0;
    //Qualquer preparação para o algoritmo acima
    auto then = std::chrono::high_resolution_clock::now();
    //Algoritmo abaixo
    //////////////////////////////////////////////////////

    for(auto& job : parser.task){
        int roll;
        indexes.clear();
        while(indexes.size() < parser.memory.size()){
            do {
                roll = distribution(generator);
            } while(std::find(indexes.begin(), indexes.end(), roll) != indexes.end());
            indexes.push_back(roll);
            searched++;
            if(parser.memory[roll].available >= job.size)
                break;
        }

        if(parser.memory[roll].available >= job.size){
            parser.memory[roll].available -= job.size;
            std::cout << "Alocou job " << job.id << " em bloco " << parser.memory[roll].id << std::endl;
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