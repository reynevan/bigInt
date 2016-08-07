#include "bigint.h"

BigInt::BigInt(std::string number)
{
    _sign = 1;
    std::string character;
    for (unsigned int i = 0; i < number.size(); i++){
        character = number.substr(i, 1);
        if (_isDigit(character)){
            _number.push_back(std::stoi(character));
        } else if (i == 0 && character == std::string("-")){
            _sign = -1;
        }
    }
}

BigInt::BigInt(int number)
{
    (*this) = BigInt(std::to_string(number));
}

BigInt::BigInt()
{
    (*this) = BigInt(0);
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

void BigInt::operator +=(BigInt num)
{
    if (_sign > 0 && num._sign < 0){
        return (*this) -= num.abs();
    }
    if (_sign < 0 && num._sign > 0){
        (*this) = num - (*this).abs();
        return;
    }
    BigInt num1, num2;
    if (getLength() >= num.getLength()){
        num1 = (*this);
        num2 = num;
    } else {
        num1 = num;
        num2 = (*this);
    }
    bool carry = false;
    int index = num2.getLength() - 1;
    std::deque<int>::reverse_iterator digit;
    for (digit = num1._number.rbegin(); digit != num1._number.rend(); ++digit, index--){
        if (index >= 0){
            (*digit) += num2._number.at(index);
        }
        if (carry){
            (*digit)++;
        }
        carry = false;
        if (*digit >= 10){
            (*digit) -= 10;
            if (digit == (num1._number.rend() - 1)){
                num1._number.push_front(1);
            } else {
                carry = true;
            }
        }
    }
    (*this) = num1;
}

void BigInt::operator +=(std::string num)
{
    (*this) += BigInt(num);
}

void BigInt::operator +=(int num)
{
    (*this) += BigInt(num);
}

void BigInt::operator -=(BigInt num)
{
    if (num._sign < 0){
        return (*this) += num.abs();
    }
    if (_sign < 0){
        *this = (*this).abs() + num;
        (*this)._sign = -1;
        return;
    }
    BigInt minuent;
    BigInt subtrahend;
    if ((*this) >= num){
        minuent = (*this);
        subtrahend = num;
    } else {
        minuent = num;
        subtrahend = (*this);
    }
    int index = subtrahend.getLength() - 1;
    bool carry = false;
    for (std::deque<int>::reverse_iterator digit = minuent._number.rbegin(); digit != minuent._number.rend(); ++digit, index--){
        if (index >= 0){
            (*digit) -= subtrahend._number.at(index);
        }
        if (carry){
            (*digit)--;
        }
        carry = false;
        if (*digit < 0){
            if (digit != minuent._number.rbegin() - 1){
                (*digit) += 10;
                carry = true;
            } else {
                (*digit) *= -1;
                minuent._sign = -1;
            }
        }
    }
    bool negative = (*this) < num;
    (*this) = minuent.copy();
    if (negative && (*this) != 0){
        _sign = -1;
    }
    _lTrim();
}

void BigInt::operator -=(std::string num)
{
    (*this) -= BigInt(num);
}

void BigInt::operator -=(int num)
{
    (*this) -= BigInt(num);
}

void BigInt::operator *=(BigInt num)
{
    if ((*this) == 0 || num == 0){
        (*this) = 0;
        return;
    }
    BigInt result = BigInt(0);
    std::deque<int>::reverse_iterator multiplicant_digit;
    std::deque<int>::reverse_iterator multiplier_digit;
    std::deque<BigInt> rows;
    int carry = 0;
    int partResult = 0;
    int index = 0;
    for (multiplicant_digit = num._number.rbegin(); multiplicant_digit != num._number.rend(); multiplicant_digit++){
        rows.push_back(BigInt(0));
        rows.back()._number.pop_back();
        for (int i = 0; i < index; i++){
            rows.back()._number.push_back(0);
        }
        index++;
        carry = 0;
        for (multiplier_digit = _number.rbegin(); multiplier_digit != _number.rend(); multiplier_digit++){
            partResult = (*multiplicant_digit) * (*multiplier_digit) + carry;
            //std::cout <<(*multiplicant_digit) <<"*"<< (*multiplier_digit) <<"+"<<carry<<"="<<partResult<<std::endl;
            if (partResult >= 10){
                carry = (int)partResult / 10;
                partResult %= 10;
            } else {
                carry = 0;
            }
            rows.back()._number.push_front(partResult);
        }
        if (carry > 0){
            rows.back()._number.push_front(carry);
        }
    }
    for (std::deque<BigInt>::iterator row = rows.begin(); row != rows.end(); row++){
        result += (*row);
    }
    if (_sign ^ num._sign){
        result._sign = -1;
    } else {
        result._sign = 1;
    }
    (*this) = result;
}

void BigInt::operator *=(int num)
{
    (*this) *= BigInt(num);
}

BigInt BigInt::operator +(int num)
{
    BigInt copy = (*this).copy();
    copy += num;
    return copy;
}

BigInt BigInt::operator +(BigInt num)
{
    BigInt copy = (*this).copy();
    copy += num;
    return copy;
}

BigInt BigInt::operator -(int num)
{
    BigInt copy = (*this).copy();
    copy -= num;
    return copy;
}

BigInt BigInt::operator -(BigInt num)
{
    BigInt copy = (*this).copy();
    copy -= num;
    return copy;
}

BigInt BigInt::operator *(BigInt num)
{
    BigInt copy = (*this).copy();
    copy *= num;
    return copy;
}

BigInt BigInt::operator *(int num)
{
    BigInt copy = (*this);
    copy *= num;
    return copy;
}

BigInt BigInt::operator ++(int a)
{
    BigInt copy = (*this).copy();
    (*this) += 1;
    return copy;
}

BigInt BigInt::operator --(int a)
{
    BigInt copy = (*this).copy();
    (*this) -= 1;
    return copy;
}

bool BigInt::operator == (const BigInt &other)
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

bool BigInt::operator == (const int& other)
{
    return (*this) == BigInt(other);
}

bool BigInt::operator != (const int& other)
{
    return !((*this) == BigInt(other));
}

bool BigInt::operator != (const BigInt& other)
{
    return !((*this) == BigInt(other));
}

bool BigInt::operator < (const BigInt& other)
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

    return false;
}

bool BigInt::operator > (const BigInt& other)
{
    return !((*this) < other) && !((*this) == other);
}

bool BigInt::operator <= (const BigInt& other)
{
    return ((*this) < other || (*this) == other);
}

bool BigInt::operator >= (const BigInt& other)
{
    return ((*this) > other || (*this) == other);
}

BigInt BigInt::abs()
{
    BigInt num = (*this).copy();
    num._sign = 1;
    return num;
}

BigInt BigInt::copy()
{
    BigInt copy = BigInt((std::string)(*this));
    return copy;
}

void BigInt::print(){
    std::cout << (std::string)(*this);
}

int BigInt::getLength() const
{
    return _number.size();
}

void BigInt::_lTrim()
{
    for(std::deque<int>::iterator it = _number.begin(); it != _number.end(); ++it){
        if (*it == 0 && it != _number.end() - 1){
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
