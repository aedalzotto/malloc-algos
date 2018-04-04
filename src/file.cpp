#include "file.h"
#include <fstream>

mmalgo_parser::mmalgo_parser(){

}

void mmalgo_parser::open_file(string file_name){
    ifstream file_obj;

    try{
        file_obj.open(file_name);
    }
    catch(...){
        throw std::runtime_error("Error opening File");
    }

}

void mmalgo_parser::mmalgo_open_list(){
    
}

void mmalgo_parser::mmalgo_open_tasks(){

}