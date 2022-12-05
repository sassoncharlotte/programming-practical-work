/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * tris.cpp
 */

#include <stdbool.h>
#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <string>
using namespace std;

#include <cstdlib>
#include <ctime>
// Nommons notre type pour plus de facilité d'écriture
using int_tab_t = std::vector< int >;


void print_tab(const int_tab_t &table) {
    string res = "[";
    for (int i = 0; i < table.size(); i++) {
        res = res + std::to_string(table[i]) + " ";
    }
    res.pop_back();
    std::cout << res << "]" << std::endl;
}

void test_11() {
    std::cout << "*** test_11 ***" << std::endl;
    const int_tab_t tab{ 1, -2, 3, -4, 5, -6 };
    print_tab(tab);
}

void random_tab(int_tab_t &tab) {
    for (int i = 0; i < tab.size(); i++) {
        int random_variable = std::rand();
        int sign = std::rand() % 2;
        if (sign == 1) tab[i] = random_variable % 10;
        else tab[i] = - random_variable % 10;
    }
}

void test_12() {
    std::cout << "*** test_12 ***" << std::endl;
    int_tab_t tab(10);
    random_tab(tab);
    print_tab(tab);
}

void sort_tab_1(int_tab_t &tab) {
    for (int i = 0; i < tab.size(); i++) {
        int min_ind = i;
        for (int j = i + 1; j < tab.size(); j++) {
            if (tab[j] < tab[min_ind]) {
                min_ind = j;
            }
        }
        if (i != min_ind) {
            std::swap(tab[i], tab[min_ind]);
        }
    }
}

void test_13() {
    std::cout << "*** test_13 ***" << std::endl;
    int_tab_t tab(10);
    random_tab(tab);
    print_tab(tab);
    sort_tab_1(tab);
    print_tab(tab);
}

bool less_func(int a, int b) { // "less" generates an error
    if (a < b) {
        return 1;
    }
    return 0;
}

bool greater_func(int a, int b) { // "greater" generates an error
    if (a > b) {
        return 1;
    }
    return 0;
}

void sort_tab_2(int_tab_t &tab, bool (*comp_function)(int, int)) {
    for (int i = 0; i < tab.size(); i++) {
        int min_ind = i;
        for (int j = i + 1; j < tab.size(); j++) {
            if (comp_function(tab[j], tab[min_ind])) {
                min_ind = j;
            }
        }
        if (i != min_ind) {
            std::swap(tab[i], tab[min_ind]);
        }
    }
}

void test_14() {
    std::cout << "*** test_14 ***" << std::endl;
    int_tab_t tab(10);
    random_tab(tab);
    print_tab(tab);
    sort_tab_2(tab, &less_func);
    print_tab(tab);
    sort_tab_2(tab, &greater_func);
    print_tab(tab);
}

void sort_tab_3(int_tab_t &tab, std::function<bool(const int, const int)> comp_function) {
    for (int i = 0; i < tab.size(); i++) {
        int min_ind = i;
        for (int j = i + 1; j < tab.size(); j++) {
            if (comp_function(tab[j], tab[min_ind])) {
                min_ind = j;
            }
        }
        if (i != min_ind) {
            std::swap(tab[i], tab[min_ind]);
        }
    }
}

void test_15() {
    std::cout << "*** test_15 ***" << std::endl;
    int_tab_t tab(10);
    random_tab(tab);
    print_tab(tab);
    auto less_func_lambda = [](int a, int b){return abs(a) < abs(b);};
    sort_tab_3(tab, less_func_lambda);
    print_tab(tab);
    auto greater_func_lambda = [](int a, int b){return abs(a) > abs(b);};
    sort_tab_3(tab, greater_func_lambda);
    print_tab(tab);
}

int main()
{
    std::srand( std::time( nullptr ));
    // test_11();
    // test_12();
    // test_13();
    // test_14();
    test_15();
    return 0;
}

