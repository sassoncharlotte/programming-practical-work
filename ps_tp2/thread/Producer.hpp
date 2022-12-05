/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.hpp
 */

#pragma once

#include <iostream>
#include <thread>
#include <chrono>

#include "../Random.hpp"

#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"

using microseconds = std::chrono::duration< int, std::micro >;


/*
 * Producteur de messages
 */
class Producer : public ProdOrCons {
public:
    // Le constructeur de ProdOrCons peut être utilisé pour Producer
    using ProdOrCons::ProdOrCons;

    void operator()() override {
        // TODO : 
        // - Déposer dans box_ nb_messages_ entiers positifs avec attente
        // aléatoire avant chaque dépôt.
        // - Afficher des messages entre chaque étape pour suivre l'avancement.
        for (int i = 0; i < nb_messages_; i++) {
            // Attente aléatoire
            {
                std::this_thread::sleep_for( microseconds{ random_engine_() });
            }
            // Envoi du message
            box_.put( i );
            // Affichage du message
            osyncstream{ std::cout } << "producer put " << i << "\n";
        }
    }
};
 
