/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * Expression.cpp
 */

#include <iostream>
#include <string>
#include <utility>
#include <memory>

#include "Expression.hpp"

// Inititalisation des compteurs d'instances créées et détruites
int Expression::nb_created_instances = 0;
int Expression::nb_destroyed_instances = 0;


