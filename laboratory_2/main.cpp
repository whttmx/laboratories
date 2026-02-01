#include "Product.hpp"
#include <iostream>

int main(){

    std::vector<std::string> composition1 = {"а", "б", "в"};
    Product product1("A", 100, composition1, 50);

    std::vector<std::string> composition2 = {"а", "м", "н"};
    Product product2("B", 100, composition2, 30);

    product1.DisplayAllInformation();

    product2.DisplayAllInformation();

    Product assignment1;
    assignment1 = product1;
    assignment1.DisplayAllInformation();

    Product assignment2;
    assignment2 = product2;
    assignment2.DisplayAllInformation();

    Product sum = product1 + product2;
    sum.DisplayAllInformation();

    Product minus = product1 - product2;
    minus.DisplayAllInformation();

    Product minus_equal = product1;
    minus_equal -= product2;
    minus_equal.DisplayAllInformation();

    return 0;
}