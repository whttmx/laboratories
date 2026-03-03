#pragma once

#include <string>
#include <vector>
#include "product_library.hpp"

class Product {
public:
    Product();
    Product(std::string name, std::string description, std::string locate, double price, std::vector<Ingredient> composition, int expiration_date);
    Product(const Product& other_product);
    ~Product();

    Product& operator=(const Product& other_product);
    Product operator+(const Product& other_product);
    Product operator-(const Product& other_product);
    Product& operator-=(const Product& other_product);

    std::string getName() const;
    std::string getLocate() const;
    std::string getDescription() const;
    double getPrice() const;
    int getExpirationDate() const;
    std::vector<Ingredient> getComposition() const;

    void setPrice(double price);
    void setName(std::string name);
    void setLocate(std::string locate);

    void DisplayAllInformation();
    void DisplayLocateInformation();
    void ChangeExpirationDate(int days);

protected:
    double price_;
    int expiration_date_;
    std::string description_;
    std::vector<Ingredient> composition_;

    bool IsPriceValid(double price);
    bool IsExpirationDateValid(int expiration_date);
    int FindMinimumExpirationDate(int expiration_date_1, int expiration_date_2);
    std::vector<Ingredient> FindGeneralComposition(const std::vector<Ingredient>& composition_1, const std::vector<Ingredient>& composition_2);
    std::vector<Ingredient> RemoveDuplicate(std::vector<Ingredient>& composition_1, const std::vector<Ingredient>& composition_2);

private:
    std::string name_;
    std::string locate_;
};