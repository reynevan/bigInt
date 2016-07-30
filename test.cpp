#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BigInt
#include <boost/test/unit_test.hpp>
#include "bigint.h"
#include <string>
#include <iostream>

std::string addInt(BigInt a, int b)
{
	return (std::string)(a + b);
}

BOOST_AUTO_TEST_SUITE(comparing)
BOOST_AUTO_TEST_CASE(testCompare)
{
	BigInt a = BigInt("0");
	BigInt a2 = BigInt("0");
	BigInt b = BigInt("1");
	BigInt b2 = BigInt("1");
	BigInt c = BigInt("-1");
	BigInt c2 = BigInt("-1");
	BigInt d = BigInt("10");
	BigInt e = BigInt("-10");
	BigInt f = BigInt("123");
	BigInt g = BigInt("-123");
	BigInt h = BigInt("-99999999999999999999999999999999999999999999999");
	BigInt i = BigInt("99999999999999999999999999999999999999999999999");

	BOOST_CHECK(b > a == true);
	BOOST_CHECK(a > a2 == false);
	BOOST_CHECK(a > a2 == false);
	BOOST_CHECK(b < a == false);
	BOOST_CHECK(b > c == true);
	BOOST_CHECK(b < c == false);
	BOOST_CHECK(b < d == true);
	BOOST_CHECK(e < c == true);
	BOOST_CHECK(g < d == true);
	BOOST_CHECK(h < i == true);
	BOOST_CHECK(h > i == false);
	BOOST_CHECK(a <= b  == true);
	BOOST_CHECK(a <= a2  == true);
	BOOST_CHECK((a == b) == false);
	BOOST_CHECK((b == c) == false);
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(arithmetics)
BOOST_AUTO_TEST_CASE(testArithmetics)
{
	BigInt a = BigInt(0);
	BigInt b = BigInt(-1);
	BigInt c = BigInt("10000000000000");
	BigInt d = BigInt( "9999999999999");
	BOOST_CHECK((a+b) == BigInt(-1));
	BOOST_CHECK((d+1) == c);
	BOOST_CHECK((c-1) == d);
	BOOST_CHECK((c-c) == 0);
}
BOOST_AUTO_TEST_SUITE_END()
