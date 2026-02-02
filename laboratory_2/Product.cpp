#include <iostream>
#include "Product.hpp"

Product::Product(){
    name_ = "Untitled";
    price_ = 0.0;
    expiration_date_ = 0;
}

Product::Product(std::string name, double price, std::vector<std::string> composition, int expiration_date){
    name_ = name;
    if (IsPriceValid(price)){
        price_ = price;
    }
    composition_ = composition;
    if (IsExpirationDateValid(expiration_date)){
        expiration_date_ = expiration_date;
    }
}

Product::Product(const Product& other_product){
    name_ = other_product.name_;
    price_ = other_product.price_;
    composition_ = other_product.composition_;
    expiration_date_ = other_product.expiration_date_;
}

Product::~Product(){
    composition_.clear();
    std::cout << "The product has been removed." << std::endl; 
}

Product& Product::operator=(const Product& other_product){
    if (&other_product != this){
        name_ = other_product.name_;
        price_ = other_product.price_;
        composition_ = other_product.composition_;
        expiration_date_ = other_product.expiration_date_;
    }
    return *this;
}

Product Product::operator+(const Product& other_product){
    std::string _name_ = "смесь " + name_ + " и " + other_product.name_;
    double _price_ = (price_ + other_product.price_) - (price_ + other_product.price_)*0.1;
    int _expiration_date_ = FindMinimumExpirationDate(expiration_date_, other_product.expiration_date_);
    std::vector<std::string> _composition_ = FindGeneralComposition(composition_, other_product.composition_);        
    
    return Product(_name_, _price_, _composition_, _expiration_date_);
}

Product Product::operator-(const Product& other_product){
    std::string _name_ = "выбор " + name_ + " без " + other_product.name_;
    double _price_ = price_ - price_*0.1;
    int _expiration_date_ = expiration_date_ - 2;
    if (_expiration_date_ < 0){
        _expiration_date_ = 0;
    }
    std::vector<std::string> copy_composition = composition_;
    std::vector<std::string> _composition_ = RemoveDuplicate(copy_composition, other_product.composition_);

    return Product(_name_, _price_, _composition_, _expiration_date_);
}

Product& Product::operator-=(const Product& other_product){
    if (&other_product != this){
        name_ = "выбор " + name_ + " без " + other_product.name_;
        price_ = price_ - price_*0.9;
        expiration_date_ = expiration_date_ - 2;
        if (expiration_date_ < 0){
            expiration_date_ = 0;
        }
        composition_ = RemoveDuplicate(composition_, other_product.composition_);
    }
    return *this;
}

bool Product::IsPriceValid(double price){
    if (price < 0.000000001){
        std::cout << "Price have to be positive." << std::endl;
        return false;
    }
    return true;
}

bool Product::IsExpirationDateValid(int expiration_date){
    if (expiration_date < 0){
        std::cout << "Expiration date have to be positive." << std::endl;
        return false;
    }
    return true;
}

int Product::FindMinimumExpirationDate(int expiration_date_1, int expiration_date_2){
    int minimum_expiration_date = 0;
    if (expiration_date_1 < expiration_date_2){
        minimum_expiration_date = expiration_date_1;
    }
    else{
        minimum_expiration_date = expiration_date_2;
    }
    return minimum_expiration_date;
}

std::vector<std::string> Product::FindGeneralComposition(const std::vector<std::string>& composition_1, const std::vector<std::string>& composition_2){
    std::vector<std::string> general_composition;

    for (size_t i = 0; i < composition_1.size(); i++){
        bool found_element = false;
        for (size_t j = 0; j < composition_2.size(); j++){
            if (composition_1[i] == composition_2[j]){
                found_element = true;
                break;
            }
        }
        if (!found_element){
            general_composition.push_back(composition_1[i]);
        }
    }

    for (size_t j = 0; j < composition_2.size(); j++){
        bool found_element = false;
        for (size_t i = 0; i < composition_1.size(); i++){
            if (composition_2[j] == composition_1[i]){
                found_element = true;
                break;
            }
        }
        if (!found_element){
            general_composition.push_back(composition_2[j]);
        }
    }
    
    return general_composition;
}

std::vector<std::string> Product::RemoveDuplicate(std::vector<std::string>& composition_1, const std::vector<std::string>& composition_2){
    std::vector<std::string> composition;
    for (size_t i = 0; i < composition_1.size(); i++){
        bool found_element = false;
        for (size_t j = 0; j < composition_2.size(); j++){
            if (composition_1[i] == composition_2[j]){
                found_element = true;
                break;
            }
        }
        if (!found_element){
            composition.push_back(composition_1[i]);
        }
    }
    composition.push_back("консервант Т1000");
    return composition;
}

std::string Product::getName() const{
    return name_;
}

double Product::getPrice() const{
    return price_;
}

int Product::getExpirationDate() const{
    return expiration_date_;
}

std::vector<std::string> Product::getComposition() const{
    return composition_;
}

void Product::setPrice(double price){
    if (IsPriceValid(price)){
        price_ = price;
    }
    return;
}

void Product::DisplayAllInformation(){
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Price: " << getPrice() << std::endl;
    std::cout << "Composition: (";
    for (size_t i = 0; i < composition_.size(); i++){
        std::cout << composition_[i];
        if (i != composition_.size() - 1){
            std::cout << ", ";
        }
    }
    std::cout << ") " << std::endl;
    std::cout << "Expiration date (in days): " << getExpirationDate() << std::endl;
    return;
}

void Product::ChangeExpirationDate(int days){
    if (IsExpirationDateValid(expiration_date_)){
        if (days > 0){
            expiration_date_ = expiration_date_ - days;
            if (expiration_date_ <= 0){
                std::cout << "The product's expiration date has expired." << std::endl;
            }
            std::cout << "The expiration date of the product has been changed to " << days << "days." << std::endl;
        }
        else{
            std::cout << "Days have to be positive." << std::endl;
        }
    }
    return;
}

