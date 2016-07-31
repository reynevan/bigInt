#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <deque>
#include <iostream>
#include <cctype>

class BigInt
{
public:
    BigInt();
    BigInt(std::string);
    BigInt(int);
    BigInt operator ++ (int);
    operator std::string();
    void operator -=(BigInt num);
    void operator -=(int num);
    void operator -=(std::string num);
    void operator +=(BigInt num);
    void operator +=(std::string num);
    void operator +=(int num);
    BigInt operator +(BigInt num);
    BigInt operator +(int num);
    BigInt operator -(int num);
    BigInt operator -(BigInt num);
    bool operator == (const BigInt& other);
    bool operator == (const int& other);
    bool operator != (const BigInt& other);
    bool operator != (const int& other);
    bool operator < (const BigInt& other);
    bool operator > (const BigInt& other);
    bool operator <= (const BigInt& other);
    bool operator >= (const BigInt& other);
    void print();
    int getLength() const;
    BigInt copy();
    BigInt abs();
private:
    std::deque<int> _number;
    int _sign;
    bool _isDigit(const std::string & digit);
    void _lTrim();
};

#endif // BIGINT_H
