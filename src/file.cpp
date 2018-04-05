#include "file.h"

mmalgo_parser::mmalgo_parser()
{

}

void mmalgo_parser::open_list(std::string file_name)
{
    try{
        list_file.open(file_name);
    } catch(...){
        throw;
    }
   
}

void mmalgo_parser::open_task(std::string file_name)
{
    try{
        task_file.open(file_name);
    } catch(...){
        throw;
    }

}