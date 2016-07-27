#include <iostream>
#include "bigint.h"
#include <string>

int main(int argc, char *argv[])
{
    BigInt num = BigInt("2");
    //std::string a = (std::string)(num - 4);
    BigInt num2 = BigInt("2");
    if (num==num2){
        std::cout <<"rowne"<<std::endl;
    } else {
        std::cout <<"nierowne"<<std::endl;
    }
    num.print();
    return 0;
}
