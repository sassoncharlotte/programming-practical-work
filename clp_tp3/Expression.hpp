/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * Expression.hpp
 */

#ifndef EXPRESSION_HPP_INCLUDED
#define EXPRESSION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>
#include <memory>



class Expression {
public:
    static int nb_created_instances;
    static int nb_destroyed_instances;

    Expression() { ++nb_created_instances; }
    virtual ~Expression() {++nb_destroyed_instances;};
    // Method for printing
    // Adds the expression to the output stream and returns it
    virtual std::ostream & print(std::ostream& os) const = 0;
    // Method for derivation
    // Returns the pointer to the new expression
    virtual Expression *derive(std::string variable_name) const = 0;
    // Method for cloning
    virtual Expression *clone() const = 0;
    // Method for simplification
    virtual Expression *simplifier() const = 0;

private:
};


inline std::ostream & operator<<( std::ostream & os, const Expression *e )
{
    return e->print( os );
}


class Nombre: public Expression {
public:
    Nombre(float value) : value_(value) {};
    ~Nombre() {};
    std::ostream & print(std::ostream& os) const {
        os << value_;
        return os;
    }
    Nombre *derive(std::string variable_name) const {
        return new Nombre(0);
    }
    Nombre *clone() const {
        return new Nombre(value_);
    }
    Nombre *simplifier() const {
        return this->clone();
    };

    // For simplification
    float getValue() const {
        return value_;
    }

private:
    const float value_;
};


class Variable: public Expression {
public:
    Variable(std::string name) : name_(name) {};
    ~Variable() {};
    std::ostream & print(std::ostream& os) const {
        os << name_;
        return os;
    }
    Nombre *derive(std::string variable_name) const {
        if (variable_name == name_) {
            return new Nombre(1);
        }
        return new Nombre(0);
    }
    Variable *clone() const {
        return new Variable(name_);
    }
    Variable *simplifier() const {
        return this->clone();
    };

private:
    std::string name_;
};


// Two attributes : left and right which represent the operands
// The operands are pointers to the Expression objects
// It should appropriate the received objects
class Operation : public Expression {
public:
    Operation(Expression *left, Expression *right) {
        left_ = left;
        right_ = right;
    }

    ~Operation() {
        if (left_ != nullptr) {
            delete left_;
        }
        if (right_ != nullptr) {
            delete right_;
        }
    }
    virtual Operation *clone() const = 0;
    virtual Expression *simplifier() const = 0;

    Expression *left_;
    Expression *right_;
private:
};


class Addition : public Operation {
public:
    Addition(Expression *left, Expression *right) : Operation(left, right) {}

    ~Addition() {}

    std::ostream & print(std::ostream& os) const {
        os << "(";
        this->left_->print(os);
        os << " + ";
        this->right_->print(os);
        os << ")";
        return os;
    }

    Addition *derive(std::string variable_name) const {
        return new Addition(left_->derive(variable_name), right_->derive(variable_name));
    }
    Addition *clone() const {
        return new Addition(left_->clone(), right_->clone());
    };
    Expression *simplifier() const {
        Expression *left_simple = left_->simplifier();
        Expression *right_simple = right_->simplifier();
        Nombre *n_gauche = dynamic_cast<Nombre *>(left_simple);
        Nombre *n_droite = dynamic_cast<Nombre *>(right_simple);

        if (n_gauche != nullptr && n_droite != nullptr) {
            Nombre *res = new Nombre(n_gauche->getValue() + n_droite->getValue());
            delete left_simple;
            delete right_simple;
            return res;
        } else if (n_gauche != nullptr && n_gauche->getValue() == 0.0) {
            delete left_simple;
            return right_simple;
        } else if (n_droite != nullptr && n_droite->getValue() == 0.0) {
            delete right_simple;
            return left_simple;
        }
        return new Addition(left_simple, right_simple);
    }

private:
};


class Multiplication : public Operation {
public:
    Multiplication(Expression *left, Expression *right) : Operation(left, right) {}

    ~Multiplication() {}

    std::ostream & print(std::ostream& os) const {
        os << "(";
        this->left_->print(os);
        os << " * ";
        this->right_->print(os);
        os << ")";
        return os;
    }

    // Formula : (uv)' = u'v + uv'
    Addition *derive(std::string variable_name) const {
        Expression *u = left_->clone();
        Expression *v = right_->clone();
        Expression *u_bis = u->derive(variable_name);
        Expression *v_bis = v->derive(variable_name);
        return new Addition(new Multiplication(u_bis, v), new Multiplication(u, v_bis));
    }

    Multiplication *clone() const {
        return new Multiplication(left_->clone(), right_->clone());
    };

    Expression *simplifier() const {
        Expression *left_simple = left_->simplifier();
        Expression *right_simple = right_->simplifier();
        Nombre *n_gauche = dynamic_cast<Nombre *>(left_simple);
        Nombre *n_droite = dynamic_cast<Nombre *>(right_simple);

        if (n_gauche != nullptr && n_droite != nullptr) {
            Nombre *res = new Nombre(n_gauche->getValue() * n_droite->getValue());
            delete left_simple;
            delete right_simple;
            return res;
        }

        if (n_gauche != nullptr) {
            if (n_gauche->getValue() == 0.0) {
                delete left_simple;
                delete right_simple;
                return new Nombre(0.0);
            } else if (n_gauche->getValue() == 1.0) {
                delete left_simple;
                return right_simple;
            }
        }
        if (n_droite != nullptr) {
            if (n_droite->getValue() == 0.0) {
                delete right_simple;
                delete left_simple;
                return new Nombre(0.0);
            } else if (n_droite->getValue() == 1.0) {
                delete right_simple;
                return left_simple;
            }
        }

        return new Multiplication(left_simple, right_simple);
    }


private:
};


#endif
