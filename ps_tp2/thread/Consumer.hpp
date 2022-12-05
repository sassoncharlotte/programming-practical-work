/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../osyncstream.hpp"

#include "ProdOrCons.hpp"

using microseconds = std::chrono::duration< int, std::micro >;

 
/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        // TODO :
        // - Retirer de box_ nb_messages_ entiers avec attente aléatoire avant
        //   chaque retrait.
        // - Afficher des messages entre chaque étape pour suivre l'avancement.
        // - Afficher un message d'erreur si un nombre négatif est extrait.
        for (int i = 0; i < nb_messages_; i++) {
            // Attente aléatoire
            {
                std::this_thread::sleep_for( microseconds{ random_engine_() });
            }
            // Retrait du message
            int message = box_.get( );
            // Affichage du message
            if (message < 0) osyncstream{ std::cerr } << "consumer got negative value " << message << "\n";
            else osyncstream{ std::cout } << "consumer got " << message << "\n";
        }
    }
};

