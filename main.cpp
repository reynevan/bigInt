#include <iostream>
#include "bigint.h"
#include <string>

int main(int argc, char *argv[])
{
    BigInt num = BigInt(-10);
    //std::string a = (std::string)(num - 4);
    BigInt num2 = BigInt(0);
    BigInt c = BigInt(34);
    c++;
    std::cout<< (std::string)(num+4)<<std::endl;
    /*if (num2+num == -1){
        std::cout <<"rowne"<<std::endl;
    } else {
        std::cout <<"nierowne"<<std::endl;
    }*/
   // num.print();
    return 0;
}
