#include <iostream>
#include "sort.h"

using namespace algorithm::sort;


void print_vector(const std::vector<double> vt){
    for(auto v:vt){
        std::cout<<v<<",";
    }
    std::cout<<std::endl;
}

int main(void){

    std::vector<double> vt;
    for(int8_t i = 10;i>0;--i){
        vt.push_back(i*1.1);
    }

    print_vector(vt);

    quick_sort<double>(vt,0,10);

    print_vector(vt);

    cin.get();
    return 0;
}