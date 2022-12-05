/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.cpp
 * c++ -std=c++20 Consumer.cpp -o Consumer -lpthread -lrt
 */

#include <iostream>
#include <thread>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "../Random.hpp"
#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"
#include "MessageBox.hpp"

/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        // TODO : déposer dans box nb_messages nombres entiers positifs avec attente
        // aléatoire entre chaque. Afficher des messages, via un osyncstream,
        // pour suivre l'avancement.
    }
};


int main ()
{
    using namespace boost::interprocess;

    // TODO : accéder à la mémoire partagée, la projeter en mémoire,
    // y accéder comme boîte à lettres, lancer le consommateur
    
    return 0;
}

