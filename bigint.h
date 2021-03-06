#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <deque>
#include <iostream>
#include <cctype>

class BigInt
{
public:
    const static int SIGN_NEGATIVE = -1;
    const static int SIGN_POSITIVE = 1;
    BigInt();
    BigInt(std::string);
    BigInt(int);
    operator std::string();
    friend std::ostream& operator <<(std::ostream& os, const BigInt num);
    void operator +=(BigInt num);
    void operator +=(std::string num);
    void operator +=(int num);

    void operator -=(BigInt num);
    void operator -=(int num);
    void operator -=(std::string num);

    void operator *=(BigInt num);
    void operator *=(int num);
    void operator *=(std::string num);

    void operator /=(BigInt num);
    void operator /=(int num);
    void operator /=(std::string num);

    BigInt operator +(BigInt num);
    BigInt operator +(int num);

    BigInt operator -(BigInt num);
    BigInt operator -(int num);

    BigInt operator *(BigInt num);
    BigInt operator *(int num);

    BigInt operator /(BigInt num);
    BigInt operator /(int num);

    BigInt operator ++ (int);
    BigInt operator -- (int);

    bool operator == (const BigInt& other);
    bool operator == (const int& other);
    bool operator != (const BigInt& other);
    bool operator != (const int& other);
    bool operator < (const BigInt& other);
    bool operator > (const BigInt& other);
    bool operator <= (const BigInt& other);
    bool operator >= (const BigInt& other);
    int getLength() const;
    BigInt copy();
    BigInt abs();
private:
    std::deque<int> _number;
    int _sign;
    bool _isDigit(const std::string & digit);
    void _lTrim();
};

BigInt operator +(int num1, BigInt num2);
BigInt operator -(int num1, BigInt num2);
BigInt operator *(int num1, BigInt num2);

#endif // BIGINT_H
