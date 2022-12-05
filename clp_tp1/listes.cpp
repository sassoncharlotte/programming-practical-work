/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * listes.cpp
 */

#include <iostream>
#include <forward_list>
#include <functional>
#include <limits>
#include <string>
using namespace std;

#include <cstdlib>
#include <ctime>
// Type liste unidirectionnelle d'entiers
using int_list_t = std::forward_list< int >;
using int_list_iter_t = int_list_t::const_iterator;


int_list_t random_list(int n) {
    if (n<0) {
        std::cout << "n parameter must be positive" << std::endl;
        return {};
    }
    int_list_t list;
    for (int i = 0; i < n; i++) {
        int rd_number = std::rand() % 100;
        list.push_front( rd_number );
    }
    return list;
}

void print_list(const int_list_t &list) {
    string res = "(";
    for( auto i : list ) {
        res = res + std::to_string(i) + " ";
    }
    if (res.size() != 1) {
        res.pop_back();
        std::cout << res << ")" << std::endl;
    }
    else std::cout << "" << std::endl;
}

void test_21() {
    std::cout << "*** test_21 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
}

int_list_t map_iter(const int_list_t &list, std::function<int(const int)> func) {
    int_list_t final_list;
    for (auto i : list) {
        final_list.push_front(func(i));
    }
    return final_list;
}

void test_22() {
    std::cout << "*** test_22 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    list = map_iter(list, [](int i){return i * 3;});
    print_list(list);
}

int_list_t filter_iter(const int_list_t &list, std::function<bool(const int)> func) {
    int_list_t final_list;
    for (auto i : list) {
        if (func(i)) final_list.push_front(i);
    }
    return final_list;
}

void test_23() {
    std::cout << "*** test_23 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    list = map_iter(list, [](int i){return i * 3;});
    print_list(list);
    list = filter_iter(list, [](int i){return i % 2 == 0;});
    print_list(list);
}

void test_24() {
    std::cout << "*** test_24 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    int rd_number = std::rand() % 6;
    std::cout << "Random number: " << rd_number << std::endl;
    list = map_iter(list, [rd_number](int i){return i * rd_number;});
    print_list(list);
    list = filter_iter(list, [](int i){return i % 2 == 0;});
    print_list(list);
}

int reduce(
    const int_list_t &list,
    int n,
    std::function<int(const int, const int)> func
) {
    int current_val = n;
    for (auto i : list) {
        current_val = func(current_val, i);
    }
    return current_val;
}

void test_25() {
    std::cout << "*** test_25 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    int min_elem = reduce(
        list,
        std::numeric_limits<int>::max(),
        [](int a, int b){
            if (a < b ) return a ;
            else return b;
        }
    );
    std::cout << "Min element: " << min_elem << std::endl;
    int max_elem = reduce(
        list,
        std::numeric_limits<int>::min(),
        [](int a, int b){
            if (a > b ) return a ;
            else return b;
        }
    );
    std::cout << "Max element: " << max_elem << std::endl;
}

int fold_left_aux(
    int_list_iter_t it_current_elem,
    int_list_iter_t it_end_elem,
    int current_val,
    std::function<int(const int, const int)> func
) {
    if (it_current_elem == it_end_elem) {
        return current_val;
    }
    else {
        int new_val = func(current_val, *it_current_elem);
        return fold_left_aux(
            std::next(it_current_elem, 1),
            it_end_elem,
            new_val,
            func
        );
    }
}

int fold_left(
    const int_list_t &list,
    int n,
    std::function<int(const int, const int)> func
)
{ return fold_left_aux(list.begin(), list.end(), n, func); }

void test_31() {
    std::cout << "*** test_31 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    int min_elem = fold_left(
        list,
        std::numeric_limits<int>::max(),
        [](int a, int b){
            if (a < b ) return a ;
            else return b;
        }
    );
    std::cout << "Min element: " << min_elem << std::endl;
    int max_elem = fold_left(
        list,
        std::numeric_limits<int>::min(),
        [](int a, int b){
            if (a > b ) return a ;
            else return b;
        }
    );
    std::cout << "Max element: " << max_elem << std::endl;
}

void map_aux(
    int_list_iter_t it_current_elem,
    int_list_iter_t it_end_elem,
    std::function<int(const int)> func,
    int_list_t &list
) {
    if (it_current_elem == it_end_elem) {
        return ;
    }
    else {
        list.push_front(func(*it_current_elem));
        return map_aux(
            std::next(it_current_elem, 1),
            it_end_elem,
            func,
            list
        );
    }
}

int_list_t map(const int_list_t &list, std::function<int(const int)> func) {
    int_list_t result_list;
    map_aux(list.begin(), list.end(), func, result_list);
    return result_list;
}

void filter_aux(
    int_list_iter_t it_current_elem,
    int_list_iter_t it_end_elem,
    std::function<bool(const int)> func,
    int_list_t &list
) {
    if (it_current_elem == it_end_elem) return ;
    if (func(*it_current_elem)) list.push_front(*it_current_elem);
    return filter_aux(std::next(it_current_elem, 1), it_end_elem, func, list);
}

int_list_t filter(const int_list_t &list, std::function<bool(const int)> func) {
    int_list_t result_list;
    filter_aux(list.begin(), list.end(), func, result_list);
    return result_list;
}

void test_32() {
    std::cout << "*** test_32 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    int rd_number = std::rand() % 6;
    std::cout << "Random number: " << rd_number << std::endl;
    list = map(list, [rd_number](int i){return i * rd_number;});
    print_list(list);
    list = filter(list, [](int i){return i % 2 == 0;});
    print_list(list);
}

void test_41()
{
    std::cout << " *** test_41 ***" << std::endl;
    int_list_t list = random_list(10);
    print_list(list);
    int rd_number = std::rand() % 6;
    std::cout << "Random number: " << rd_number << std::endl;

    std::multiplies< int > mul_int;
    list = map(list, [rd_number, mul_int](int i){return mul_int(i, rd_number);});
    print_list(list);
    list = filter(list, [](int i){return i % 2 == 0;});
    print_list(list);
}


int main()
{
    std::srand( std::time( nullptr ));
    // test_21();
    // test_22();
    // test_23();
    // test_24();
    // test_25();
    // test_31();
    // test_32();
    test_41();
    return 0;
}

