/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * TestExpression.cpp
 * c++ -std=c++20 -o TestExpression TestExpression.cpp Expression.cpp -lgtest -lpthread
 */

#include <sstream>
#include <iostream>
#include <utility>

#include <gtest/gtest.h>

#include "Expression.hpp"


//// Number ////

TEST( TestExpression, TestPrintNumber )
// Construction of a number and printing of its value
{
    Nombre *n = new Nombre(2.7);
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "2.7" );

    delete n;
}


//// Variable ////

TEST( TestExpression, TestPrintVariable )
// Construction of a variable and printing of its name
{
    Variable *x = new Variable("x");
    std::ostringstream os;
    os << x;
    EXPECT_EQ( os.str(), "x" );

    delete x;
}


//// Derivation ////

TEST( TestExpression, TestDerive1 )
{
    // Construction of a variable, derivation according to this
    // same variable
    Variable *x = new Variable("x");
    Expression *derivee = x->derive("x");
    std::ostringstream os;
    os << derivee;
    EXPECT_EQ( os.str(), "1" );

    // Check that first variable is not changed
    std::ostringstream os_2;
    os_2 << x;
    EXPECT_EQ( os_2.str(), "x" );

    delete x;
    delete derivee;
}


TEST( TestExpression, TestDerive0 )
{
    // Construction of a variable, derivation according to another
    Variable *x = new Variable("x");
    Expression *derivee = x->derive("y");
    std::ostringstream os;
    os << derivee;
    EXPECT_EQ( os.str(), "0" );

    // Check that first variable is not changed
    std::ostringstream os_2;
    os_2 << x;
    EXPECT_EQ( os_2.str(), "x" );

    delete x;
    delete derivee;
}


//// Operations ////

TEST( TestExpression, TestAdditionPrintNumbers )
{ 
    Nombre *n1 = new Nombre(1.5);
    Nombre *n2 = new Nombre(0.7);
    Addition *add = new Addition( n1, n2 );
    std::ostringstream os;
    os << add;
    EXPECT_EQ( os.str(), "(1.5 + 0.7)" );

    delete add;
}

TEST( TestExpression, TestAdditionPrintVariables )
{ 
    Variable *x = new Variable("x");
    Variable *y = new Variable("y");
    Addition *add = new Addition( x, y );
    std::ostringstream os;
    os << add;
    EXPECT_EQ( os.str(), "(x + y)" );

    delete add;
}

TEST( TestExpression, TestAdditionPrintBoth )
{ 
    Nombre *n1 = new Nombre(0.9);
    Nombre *n2 = new Nombre(1.7);
    Variable *x = new Variable("x");
    Addition *add1 = new Addition( x, n1 );
    Addition *add2 = new Addition( add1, n2 );
    std::ostringstream os;
    os << add2;
    EXPECT_EQ( os.str(), "((x + 0.9) + 1.7)" );

    delete add2;
}

TEST( TestExpression, TestAdditionDerive )
{ 
    Nombre *n = new Nombre(0.3);
    Variable *x = new Variable("x");
    Addition *add = new Addition( n, x );
    Expression *derivee = add->derive("x");
    std::ostringstream os1;
    os1 << derivee;
    EXPECT_EQ( os1.str(), "(0 + 1)" );

    // Check that addition has not changed
    std::ostringstream os2;
    os2 << add;
    EXPECT_EQ( os2.str(), "(0.3 + x)" );

    delete add;
    delete derivee;
}


//// Cloning ////

TEST( TestExpression, TestCloningNumber )
{
    Nombre *n = new Nombre(0.5);
    Nombre *clone = n->clone();
    delete n;

    // Checking that clone is not deleted
    std::ostringstream os;
    os << clone;
    EXPECT_EQ( os.str(), "0.5" );

    delete clone;
}

TEST( TestExpression, TestCloningVariable )
{
    Variable *v = new Variable("x");
    Variable *clone = v->clone();
    delete v;

    // Checking that clone is not deleted
    std::ostringstream os;
    os << clone;
    EXPECT_EQ( os.str(), "x" );

    delete clone;
}

TEST( TestExpression, TestCloningAddition )
{
    Nombre *n = new Nombre(0.5);
    Variable *x = new Variable("x");
    Addition *add = new Addition{ n, x };
    Addition *clone = add->clone();
    delete add;

    // Checking that clone is not deleted
    std::ostringstream os;
    os << clone;
    EXPECT_EQ( os.str(), "(0.5 + x)" );

    delete clone;
}

TEST( TestExpression, TestMultiplicationPrintNumber )
{
    Nombre *n1 = new Nombre(0.5);
    Nombre *n2 = new Nombre(5.1);
    Multiplication *mult = new Multiplication{ n1, n2 };
    std::ostringstream os;
    os << mult;
    EXPECT_EQ( os.str(), "(0.5 * 5.1)" );

    delete mult;
}

TEST( TestExpression, TestMultiplicationPrintVariable )
{
    Variable *x = new Variable("x");
    Variable *y = new Variable("y");
    Multiplication *mult = new Multiplication{ x, y };
    std::ostringstream os;
    os << mult;
    EXPECT_EQ( os.str(), "(x * y)" );

    delete mult;
}

TEST( TestExpression, TestMultiplicationPrintBoth )
{
    Variable *x = new Variable("x");
    Nombre *n = new Nombre(5.2);
    Multiplication *mult = new Multiplication{ x, n };
    std::ostringstream os;
    os << mult;
    EXPECT_EQ( os.str(), "(x * 5.2)" );

    delete mult;
}

TEST( TestExpression, TestCloningMultiplication )
{
    Nombre *n = new Nombre(0.5);
    Variable *x = new Variable("x");
    Multiplication *mult = new Multiplication{ n, x };
    Multiplication *clone = mult->clone();
    delete mult;

    // Checking that clone is not deleted
    std::ostringstream os;
    os << clone;
    EXPECT_EQ( os.str(), "(0.5 * x)" );

    delete clone;
}

TEST( TestExpression, TestMultiplicationDerive )
{ 
    Nombre *n = new Nombre(0.3);
    Variable *x = new Variable("x");
    Multiplication *mult = new Multiplication( n, x );
    Expression *derivee = mult->derive("x");
    std::ostringstream os1;
    os1 << derivee;
    EXPECT_EQ( os1.str(), "((0 * x) + (0.3 * 1))" );

    // Checking that multiplication is not changed
    std::ostringstream os2;
    os2 << mult;
    EXPECT_EQ( os2.str(), "(0.3 * x)" );

    delete mult;
    delete derivee;
}

TEST( TestExpression, TestMultiplicationDeriveComplex )
{ 
    Nombre *n = new Nombre(0.3);
    Variable *x = new Variable("x");
    Variable *y = new Variable("y");
    Multiplication *mult1 = new Multiplication( n, x );
    Multiplication *mult2 = new Multiplication( mult1, y );
    Expression *derivee = mult2->derive("x");
    std::ostringstream os1;
    os1 << derivee;
    EXPECT_EQ( os1.str(), "((((0 * x) + (0.3 * 1)) * y) + ((0.3 * x) * 0))" );
    
    // Checking that multiplication is not changed
    std::ostringstream os2;
    os2 << mult2;
    EXPECT_EQ( os2.str(), "((0.3 * x) * y)" );

    delete mult2;
    delete derivee;
}


//// SIMPLIFICATION ////

TEST( TestExpression, TestSimplificationAdditionLeft)
{
    Nombre *n = new Nombre(0.0);
    Variable *x = new Variable("x");
    Addition *add = new Addition{ n, x };
    Expression *add_simpl = add->simplifier();
    std::ostringstream os;
    os << add_simpl;
    EXPECT_EQ( os.str(), "x" );

    delete add;
    delete add_simpl;
}

TEST( TestExpression, TestSimplificationAdditionRight)
{
    Variable *x = new Variable("x");
    Nombre *n = new Nombre(0.0);
    Addition *add = new Addition{ x, n };
    Expression *add_simpl = add->simplifier();
    std::ostringstream os;
    os << add_simpl;
    EXPECT_EQ( os.str(), "x" );

    delete add;
    delete add_simpl;
}

TEST( TestExpression, TestSimplificationAdditionNumber)
{
    Nombre *n1 = new Nombre(1.5);
    Nombre *n2 = new Nombre(2.5);
    Addition *add = new Addition{ n1, n2 };
    Expression *add_simpl = add->simplifier();
    std::ostringstream os;
    os << add_simpl;
    EXPECT_EQ( os.str(), "4" );

    delete add;
    delete add_simpl;
}

TEST( TestExpression, TestSimplificationMultiplication1Left)
{
    Nombre *n = new Nombre(1.0);
    Variable *x = new Variable("x");
    Multiplication *mult = new Multiplication{ n, x };
    Expression *mult_simpl = mult->simplifier();
    std::ostringstream os;
    os << mult_simpl;
    EXPECT_EQ( os.str(), "x" );

    delete mult;
    delete mult_simpl;
}

TEST( TestExpression, TestSimplificationMultiplicaiton1Right)
{
    Variable *x = new Variable("x");
    Nombre *n = new Nombre(1.0);
    Multiplication *mult = new Multiplication{ x, n };
    Expression *mult_simpl = mult->simplifier();
    std::ostringstream os;
    os << mult_simpl;
    EXPECT_EQ( os.str(), "x" );

    delete mult;
    delete mult_simpl;
}

TEST( TestExpression, TestSimplificationMultiplication0Left)
{
    Nombre *n = new Nombre(0.0);
    Variable *x = new Variable("x");
    Multiplication *mult = new Multiplication{ n, x };
    Expression *mult_simpl = mult->simplifier();
    std::ostringstream os;
    os << mult_simpl;
    EXPECT_EQ( os.str(), "0" );

    delete mult;
    delete mult_simpl;
}

TEST( TestExpression, TestSimplificationMultiplication0Right)
{
    Variable *x = new Variable("x");
    Nombre *n = new Nombre(0.0);
    Multiplication *mult = new Multiplication{ x, n };
    Expression *mult_simpl = mult->simplifier();
    std::ostringstream os;
    os << mult_simpl;
    EXPECT_EQ( os.str(), "0" );

    delete mult;
    delete mult_simpl;
}

TEST( TestExpression, TestSimplificationMultiplicationNumbers)
{
    Nombre *n1 = new Nombre(6.0);
    Nombre *n2 = new Nombre(5.0);
    Multiplication *mult = new Multiplication{ n1, n2 };
    Expression *mult_simpl = mult->simplifier();
    std::ostringstream os;
    os << mult_simpl;
    EXPECT_EQ( os.str(), "30" );

    delete mult;
    delete mult_simpl;
}

// TEST( TestExpression, TestSimplificationComplex)
// // Simplification d'une expression complexe (((((5 + -5) * x) + (2 * y)) + (1 * (x + (1 * y)))) + ((1 * 3) * x)) = (((2 * y) + (x + y)) + (3 * x))
// // Dans ce test, on vérifie le fonctionnement de la simplification dans le cas de:
// // - Globalement, simplification en profondeur dans les opérations
// // - Ajout de deux nombres (5 + -5 = 0)
// // - Multiplication par 0
// // - Addition de 0
// // - Multiplication par 1

// {
//     Addition *a_1 = new Addition(new Nombre(5), new Nombre(-5));
//     Multiplication *m_1 = new Multiplication(a_1, new Variable("x"));
//     Multiplication *m_2 = new Multiplication(new Nombre(2), new Variable("y"));
//     Addition *a_2 = new Addition(m_1, m_2);
//     Multiplication *m_3 = new Multiplication(new Nombre(1), new Variable("y"));
//     Addition *a_3 = new Addition(new Variable("x"), m_3);
//     Multiplication *m_4 = new Multiplication(new Nombre(1), a_3);
//     Addition *a_4 = new Addition(a_2, m_4);
//     Multiplication *m_5 = new Multiplication(new Nombre(1), new Nombre(3));
//     Multiplication *m_6 = new Multiplication(m_5, new Variable("x"));
//     Addition *a_5 = new Addition(a_4, m_6);
//     Expression *a_5_simpl = a_5->simplifier();
//     std::ostringstream os;
//     os << a_5_simpl;
//     EXPECT_EQ( os.str(), "(((2 * y) + (x + y)) + (3 * x))" );

//     delete a_5;
//     delete a_5_simpl;
// }


//// Number of created and destroyed instances ////

TEST( TestExpression, TestDestructionInstances )
{
    EXPECT_EQ( Expression::nb_created_instances, Expression::nb_destroyed_instances );
}


int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
