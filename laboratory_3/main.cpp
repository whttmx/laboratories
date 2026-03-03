#include <iostream>
#include "Product.hpp"
#include "product_library.hpp"

int main() {
    Ingredient sugar{"Сахар", 0.2};
    Ingredient flour{"Мука", 0.5};
    Ingredient milk{"Молоко", 0.3};
    Ingredient conservant{"Е50", 0.01};

    std::vector<Ingredient> comp1 = {sugar, flour};
    Product bread("Хлеб", "Чёрный хлеб хлеб", "Полка", 50.0, comp1, 7);

    std::vector<Ingredient> comp2 = {milk, sugar};
    Product cake("Пирожное", "С черникой", "Витрина", 120.0, comp2, 3);

    std::cout << "Информация о продуктах" << std::endl;
    bread.DisplayAllInformation();
    std::cout << std::endl;
    cake.DisplayAllInformation();
    std::cout << std::endl;

    std::cout << "Оператор +" << std::endl;
    Product mix = bread + cake;
    mix.DisplayAllInformation();
    std::cout << std::endl;

    std::cout << "Оператор -" << std::endl;
    Product withoutSugar = bread - cake;
    withoutSugar.DisplayAllInformation();
    std::cout << std::endl;

    std::cout << "Оператор -=" << std::endl;
    bread -= cake;
    bread.DisplayAllInformation();
    std::cout << std::endl;

    std::vector<Ingredient> prohibited = {harmful};
    Commission commission("Калининград, Ленинский проспект, 3", prohibited, 10);

    std::cout << "Проверка продуктов комиссией" << std::endl;
    if (commission.ProductInspection(bread)) {
        std::cout << "Хлеб прошёл проверку." << std::endl;
    } 
    else {
        std::cout << "Хлеб не прошёл проверку." << std::endl;
    }

    std::vector<Ingredient> comp3 = {sugar, harmful};
    Product badProduct("Вредный продукт", "С консервантом", "Склад", 80.0, comp3, 5);
    if (commission.ProductInspection(badProduct)) {
        std::cout << "Вредный продукт прошёл проверку." << std::endl;
    } 
    else {
        std::cout << "Вредный продукт не прошёл проверку." << std::endl;
    }

    std::cout << "Изменение срока годности" << std::endl;
    std::cout << "Текущий срок хлеба: " << bread.getExpirationDate() << " дней" << std::endl;
    bread.ChangeExpirationDate(2);
    std::cout << "Новый срок: " << bread.getExpirationDate() << " дней" << std::endl;

    return 0;
}