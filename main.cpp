#include <iostream>
#include "bigint.h"
#include <string>

int main(int argc, char *argv[])
{
    BigInt num = BigInt("125436");
    BigInt c = BigInt("2354");
    num /= c;
    std::cout<< num <<std::endl;
    /*if (num2+num == -1){
        std::cout <<"rowne"<<std::endl;
    } else {
        std::cout <<"nierowne"<<std::endl;
    }*/
   // num.print();


    return 0;
}
