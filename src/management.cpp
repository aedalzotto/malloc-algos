#include "management.h"

mmalgo_rithm::mmalgo_rithm()
{

}

void mmalgo_rithm::run_first(mmalgo_parser& parser)
{
    searched=0;
    failed = 0;
    //Percorre as tarefas

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
    

    //Cada lista acessada deve incrementar a variável searched
    //Cada processo que falha a alocar deve incrementar variável failed
    //Cada job alocado deve tirar o seu tamanho da variável size da lista



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
    

    //Cada lista acessada deve incrementar a variável searched
    //Cada processo que falha a alocar deve incrementar variável failed
    //Cada job alocado deve tirar o seu tamanho da variável size da lista


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
    

    //Cada lista acessada deve incrementar a variável searched
    //Cada processo que falha a alocar deve incrementar variável failed
    //Cada job alocado deve tirar o seu tamanho da variável size da lista


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
    

    //Cada lista acessada deve incrementar a variável searched
    //Cada processo que falha a alocar deve incrementar variável failed
    //Cada job alocado deve tirar o seu tamanho da variável size da lista



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