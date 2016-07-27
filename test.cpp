#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BigInt
#include <boost/test/unit_test.hpp>
#include "bigint.h"
#include <string>

std::string addInt(BigInt a, int b)
{
	return (std::string)(a + b);
}

bool compareLess(BigInt a, BigInt b)
{
	return a < b;
}

bool compareEqual(BigInt a, BigInt b)
{
	return a == b;
}

BOOST_AUTO_TEST_CASE(universeInOrder)
{
	BigInt a = BigInt("2");
	BigInt b = BigInt("10");
	BigInt c = BigInt("15");
	BigInt d = BigInt("-30");
	BigInt e = BigInt("-32");
	BigInt f = BigInt("-3");
    BOOST_CHECK(addInt(a, 2) == (std::string)"4");
	BOOST_CHECK(compareLess(a, b) == true);	
	BOOST_CHECK(compareLess(b, a) == false);	
	BOOST_CHECK(compareLess(b, c) == true);	
	BOOST_CHECK(compareLess(a, c) == true);	
	BOOST_CHECK(compareLess(c, a) == false);	
	BOOST_CHECK(compareLess(e, d) == true);	
	BOOST_CHECK(compareLess(f, a) == true);	
	BOOST_CHECK(compareLess(d, f) == true);	
	BOOST_CHECK(compareLess(a, f) == false);	
	
	BigInt a2 = BigInt("2");
	BigInt am = BigInt("-2");
	BigInt am2 = BigInt("-2");
	BOOST_CHECK(compareEqual(a, b) == false);	
	BOOST_CHECK(compareEqual(a, a2) == true);	
	BOOST_CHECK(compareEqual(a, am) == false);	
	BOOST_CHECK(compareEqual(am, am2) == true);	
	BOOST_CHECK(compareEqual(e, f) == false);	
	BOOST_CHECK(compareEqual(b, c) == false);	
}
