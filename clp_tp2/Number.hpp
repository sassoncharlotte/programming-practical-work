/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * Number.hpp
 */

#ifndef NUMBER_HPP_INCLUDED
#define NUMBER_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>


class Number {
public:
    // Constructor
    Number( unsigned long l ) {
        this->first_ = new Digit(l);
    }
    //Destructor
    ~Number() {
        delete this->first_;
    }
    // Constructor for copy
    Number( const Number & n ) {
        first_ = new Digit(*n.first_);
    }
    // Copy assignment
    Number& operator= ( const Number & n ) {
        first_ = new Digit(*n.first_);
        return (*this);
    }
    void print( std::ostream & out ) const {
        first_->print( out );
    }

    // Addition
    void add ( unsigned int i ) {
        this->first_->add(i);
    }
    // Multiplication
    void multiply ( unsigned int i ) {
        this->first_->multiply(i);
    }

private:
    using DigitType = unsigned int;
    // Un chiffre décimal par maillon : l'objectif ici n'est pas la performance
    // mais votre code doit être écrit en tenant compte de cet aspect
    static const DigitType number_base{ 10u };
    struct Digit {
        DigitType digit_;
        Digit * next_;
        // Constructor
        Digit(unsigned long l) {
            if (l >= number_base) {
                digit_ = l % number_base;
                next_ = new Digit(l/number_base);
            } else {
                digit_ = l;
                next_ = nullptr;
            }
        }
        //Destructor
        ~Digit() {
            if (next_ != nullptr) delete next_;
        }
        // Constructor for copy
        Digit( const Digit & d ) {
            if (d.next_ == nullptr) {
                digit_ = d.digit_;
                next_ = nullptr;
            } else {
                digit_ = d.digit_;
                next_ = new Digit(*d.next_);
            }
        }
        void print(std::ostream & out ) {
            if (next_ == nullptr) {
                out << digit_;
                return;
            }
            next_->print(out);
            out << digit_;
        }

        // Addition
        void add(unsigned int i) {
            unsigned int sum = digit_ + i;
            if (sum >= number_base) {
                digit_ = sum % number_base;
                if (next_ != nullptr) next_->add(sum/number_base);
                else next_ = new Digit(sum/number_base);
            } else digit_ = sum;
        }
        // Multiplication
        void multiply(unsigned int i) {
            unsigned int prod = digit_ * i;
            if (next_ != nullptr) next_->multiply(i);
            if (prod >= number_base) {
                digit_ = prod % number_base;
                if (next_ != nullptr) next_->add(prod/number_base);
                else next_ = new Digit(prod/number_base);
            } else digit_ = prod;
        }

    };
    Digit * first_;
};

inline std::ostream & operator<<( std::ostream & out, const Number & n )
{
    n.print( out );
    return out;
}

#endif
