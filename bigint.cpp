#include "bigint.h"

BigInt::BigInt(std::string number = "0")
{
    _sign = 1;
    std::string character;
    for (int i = 0; i < number.size(); i++){
        character = number.substr(i, 1);
        if (_isDigit(character)){
            _number.push_back(std::stoi(character));
        } else if (i == 0 && character == std::string("-")){
            _sign = -1;
        }
    }
}

int BigInt::getLength() const
{
    return _number.size();
}

bool BigInt::operator<(const BigInt other)
{
    if (other._sign > 0 && _sign < 0){
        return true;
    }
    if (other._sign < 0 && _sign > 0){
       return false;
    }
    if (other._sign > 0 && _sign > 0){
        if (other.getLength() > getLength()){
            return true;
        }
        if (other.getLength() < getLength()){
            return false;
        }
    }
    if (other._sign < 0 && _sign < 0){
        if (other.getLength() < getLength()){
            return true;
        }
        if (other.getLength() > getLength()){
            return false;
        }
    }
    for (int i = 0; i < getLength(); i++){
        if (_number.at(i) == other._number.at(i)){
            continue;
        }
        return ((_number.at(i) < other._number.at(i)) && _sign > 0) || ((_number.at(i) > other._number.at(i)) && _sign < 0);
    }
}

BigInt BigInt::operator ++(int a)
{
    BigInt copy((std::string)(*this));
    (*this) += 1;
    return copy;
}

BigInt BigInt::operator +(int num)
{
    BigInt bigInt = BigInt((std::string)(*this));
    bigInt += num;
    return bigInt;

}

BigInt BigInt::operator -(BigInt subtrahend)
{
    /*std::string strSubtrahend = (std::string)subtrahend;
    int index = subtrahend.getLength();
    std::deque<int>::reverse_iterator digit;
    int subtrahendDigit = 0;
    for (digit = _number.begin(); digit != _number.end(); ++digit, index--){
        subtrahendDigit = std::stoi(strNum.substr(index, 1));
        if (index >= 0){
            (*digit) -= subtrahendDigit;
        } else {
            (*digit) = 10 - *digit;
        }
    }*/
}

void BigInt::operator +=(std::string num)
{
    bool carry = false;
    int index = num.size() - 1;
    std::deque<int>::reverse_iterator digit;
    for (digit = _number.rbegin(); digit != _number.rend(); ++digit, index--){
        if (index >= 0){
            (*digit) += std::stoi(num.substr(index, 1));
        }
        if (carry){
            (*digit)++;
        }
        if (*digit >= 10){
            carry = true;
            (*digit) -= 10;
        } else {
            carry = false;
        }
    }
}

void BigInt::operator -=(std::string num)
{
    int index = num.size() - 1;
    bool carry = false;
    for (std::deque<int>::reverse_iterator digit = _number.rbegin(); digit != _number.rend(); ++digit, index--){
        if (index >= 0){
            (*digit) -= std::stoi(num.substr(index, 1));
        }
        if (carry){
            (*digit)--;
        }
        if (*digit < 0){
            (*digit) += 10;
            carry = true;
        } else {
            carry = false;
        }
    }
    _lTrim();
}

void BigInt::operator +=(int num)
{
    (*this) += std::to_string(num);
}

void BigInt::operator -=(int num)
{
    (*this) -= std::to_string(num);
}

bool BigInt::operator==(const BigInt& other)
{
    if (_sign ^ other._sign){
        return false;
    }
    if (getLength() != other.getLength()){
        return false;
    }
    for (int i = 0; i < getLength(); i++){
        if (_number.at(i) != other._number.at(i)){
            return false;
        }
    }
    return true;
}

BigInt::operator std::string()
{
    std::string str = std::string();
    if (_sign == -1){
        str.append("-");
    }
    for (std::deque<int>::iterator it = _number.begin(); it != _number.end(); ++it){
        str.append(std::to_string(*it));
    }
    return str;
}

void BigInt::print(){
    std::cout << (std::string)(*this);
}

void BigInt::_lTrim()
{
    for(std::deque<int>::iterator it = _number.begin(); it != _number.end(); ++it){
        if (*it == 0){
            _number.pop_front();
        } else {
            break;
        }
    }
}

bool BigInt::_isDigit(const std::string & digit)
{
    if(digit.empty()) return false;

    char * p ;
    strtol(digit.c_str(), &p, 10) ;

    return (*p == 0) ;
}
