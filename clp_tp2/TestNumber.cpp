/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * TestNumber.cpp
 * c++ -std=c++20 -o TestNumber Number.cpp TestNumber.cpp -lgtest -lpthread
 */

#include <exception>
#include <sstream>
#include <utility>

#include <gtest/gtest.h>

#include "Number.hpp"


TEST( TestNumber, TestNumber0 )
{
    Number n{ 0 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "0" );
}

TEST( TestNumber, TestNumber12345678 )
{
    Number n{ 12345678 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345678" );
}

TEST( TestNumber, TestNumberBig )
{
    Number n{ 12345123451234512345UL };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345123451234512345" );
}

TEST( TestNumber, TestNumberConstructeurCopie )
{
    Number *number1;
    number1 = new Number{ 12345678 };
    // Construction of number2 with number1
    Number number2{ *number1 };
    delete number1;
    std::ostringstream os;
    os << number2;
    // Checking if copy was successfull
    EXPECT_EQ( os.str(), "12345678" );
}

TEST( TestNumber, TestNumberConstructeurCopie0 )
{
    Number *number1;
    number1 = new Number{ 0 };
    Number number2{ *number1 };
    delete number1;
    std::ostringstream os;
    os << number2;
    EXPECT_EQ( os.str(), "0" );
}

TEST( TestNumber, TestNumberConstructeurCopieBig )
{
    Number *number1;
    number1 = new Number{ 12345123451234512345UL };
    Number number2{ *number1 };
    delete number1;
    std::ostringstream os;
    os << number2;
    EXPECT_EQ( os.str(), "12345123451234512345" );
}

TEST( TestNumber, TestNumberAffectationCopie )
{
    // Creation of first number
    Number *number1;
    number1 = new Number{ 12345678 };
    // Assignation of first number to second number
    Number number2 = *number1;
    // number2 = *number1;
    delete number1;
    // Checking if the assignation as successfull
    std::ostringstream os;
    os << number2;
    EXPECT_EQ( os.str(), "12345678" );
}

TEST( TestNumber, TestNumberAffectationCopie0 )
{
    // Creation of first number
    Number *number1;
    number1 = new Number{ 0 };
    // Assignation of first number to second number
    Number number2 = *number1;
    // number2 = *number1;
    delete number1;
    // Checking if the assignation as successfull
    std::ostringstream os;
    os << number2;
    EXPECT_EQ( os.str(), "0" );
}

TEST( TestNumber, TestNumberAffectationCopieBig )
{
    // Creation of first number
    Number *number1;
    number1 = new Number{ 12345123451234512345UL };
    // Assignation of first number to second number
    Number number2 = *number1;
    // number2 = *number1;
    delete number1;
    // Checking if the assignation as successfull
    std::ostringstream os;
    os << number2;
    EXPECT_EQ( os.str(), "12345123451234512345" );
}

TEST( TestNumber, TestAddition )
{
    Number number1{ 231 };
    unsigned int number2{ 82 };
    number1.add( number2 );
    std::ostringstream os;
    os << number1;
    EXPECT_EQ( os.str(), "313" );
}

TEST( TestNumber, TestAddition0 )
{
    Number number1{ 958 };
    unsigned int number2{ 0 };
    number1.add( number2 );
    std::ostringstream os;
    os << number1;
    EXPECT_EQ( os.str(), "958" );
}

TEST( TestNumber, TestAdditionBig )
{
    Number number1{ 12345123451234512345UL };
    unsigned int number2{ 1288 };
    number1.add( number2 );
    std::ostringstream os;
    os << number1;
    EXPECT_EQ( os.str(), "12345123451234513633" );
}

TEST( TestNumber, TestMultiplication )
{
    Number number1{ 117 };
    unsigned int number2{ 28 };
    number1.multiply( number2 );
    std::ostringstream os;
    os << number1;
    EXPECT_EQ( os.str(), "3276" );
}

TEST(TestNumber, TestNumberMultiply0) {
    Number number1{ 0 };
    unsigned int number2{ 17 };
    number1.multiply( number2 );
    std::ostringstream os;
    os << number1;
    EXPECT_EQ( os.str(), "0" );
}

TEST( TestNumber, TestMultiplicationBig )
{
    Number number1{ 12345123451234512345UL };
    unsigned int number2{ 3 };
    number1.multiply( number2 );
    std::ostringstream os;
    os << number1;
    EXPECT_EQ( os.str(), "37035370353703537035" );
}

Number factorial( unsigned int i ) {
    Number number{ 1 };
    for ( unsigned int j = 1; j <= i; ++j ) {
        number.multiply( j );
    }
    return number;
}

TEST( TestNumber, TestFactorial123 )
{
    std::ostringstream os;
    os << factorial( 123 );;
    EXPECT_EQ( os.str(), "121463043670253296757662432418812958554542170884833823153289181618292"
                         "358923621676688311569606126402021707358352212940477825910915704116514"
                         "72186029519906261646730733907419814952960000000000000000000000000000" );
}


int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
