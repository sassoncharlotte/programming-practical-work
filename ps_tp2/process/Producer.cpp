/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.cpp
 * c++ -std=c++20 Producer.cpp -o Producer -lpthread -lrt
 */

#include <iostream>
#include <thread>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "../Random.hpp"

#include "ProdOrCons.hpp"
#include "MessageBox.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons {
    // Le constructeur de ProdOrCons peut être utilisé pour Producer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        // TODO : déposer dans box nb_messages nombres entiers positifs avec attente
        // aléatoire entre chaque. Afficher des messages pour suivre l'avancement.
    }
};
 
int main()
{
    using namespace boost::interprocess;

    // TODO : créer la mémoire partagée, la projeter en mémoire,
    // y construire la boîte à lettres, lancer le producteur
    
    return 0;
}

