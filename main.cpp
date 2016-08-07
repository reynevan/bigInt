#include <iostream>
#include "bigint.h"
#include <string>

int main(int argc, char *argv[])
{
    BigInt num = BigInt("99999999999999999999999999999");
    //std::string a = (std::string)(num - 4);
    BigInt num2 = BigInt(6150);
    BigInt c = BigInt("99999999999999999999999999999");
    num *= c;
    std::cout<< (std::string)(num)<<std::endl;
    /*if (num2+num == -1){
        std::cout <<"rowne"<<std::endl;
    } else {
        std::cout <<"nierowne"<<std::endl;
    }*/
   // num.print();
    return 0;
}
