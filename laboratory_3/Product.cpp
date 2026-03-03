#include <iostream>
#include "Product.hpp"
#include "product_library.hpp" 

Product::Product() {
    name_ = "Untitled";
    price_ = 0.0;
    expiration_date_ = 0;
}

Product::Product(std::string name, std::string description, std::string locate, double price, std::vector<Ingredient> composition, int expiration_date) {
    name_ = name;
    description_ = description;
    locate_ = locate;
    if (IsPriceValid(price)) {
        price_ = price;
    }
    composition_ = composition;
    if (IsExpirationDateValid(expiration_date)) {
        expiration_date_ = expiration_date;
    }
}

Product::Product(const Product& other_product) {
    name_ = other_product.name_;
    description_ = other_product.description_;
    locate_ = other_product.locate_;
    price_ = other_product.price_;
    composition_ = other_product.composition_;
    expiration_date_ = other_product.expiration_date_;
}

Product::~Product() {
    composition_.clear();
    std::cout << "The product has been removed." << std::endl;
}

Product& Product::operator=(const Product& other_product) {
    if (this != &other_product) {
        name_ = other_product.name_;
        description_ = other_product.description_;
        locate_ = other_product.locate_;
        price_ = other_product.price_;
        composition_ = other_product.composition_;
        expiration_date_ = other_product.expiration_date_;
    }
    return *this;
}

Product Product::operator+(const Product& other_product) {
    std::string _name_ = "смесь " + name_ + " и " + other_product.name_;
    double _price_ = (price_ + other_product.price_) * 0.9;
    int _expiration_date_ = FindMinimumExpirationDate(expiration_date_, other_product.expiration_date_);
    std::vector<Ingredient> _composition_ = FindGeneralComposition(composition_, other_product.composition_);

    return Product(_name_, description_, locate_, _price_, _composition_, _expiration_date_);
}

Product Product::operator-(const Product& other_product) {
    std::string _name_ = "выбор " + name_ + " без " + other_product.name_;
    double _price_ = price_ * 0.9;
    int _expiration_date_ = expiration_date_ - 2;
    if (_expiration_date_ < 0) {
        _expiration_date_ = 0;
    }
    std::vector<Ingredient> copy_composition = composition_;
    std::vector<Ingredient> _composition_ = RemoveDuplicate(copy_composition, other_product.composition_);

    return Product(_name_, description_, locate_, _price_, _composition_, _expiration_date_);
}

Product& Product::operator-=(const Product& other_product) {
    if (this != &other_product) {
        name_ = "выбор " + name_ + " без " + other_product.name_;
        locate_ = other_product.locate_;
        price_ = price_ * 0.1; 
        expiration_date_ = expiration_date_ - 2;
        if (expiration_date_ < 0) {
            expiration_date_ = 0;
        }
        composition_ = RemoveDuplicate(composition_, other_product.composition_);
    }
    return *this;
}

bool Product::IsPriceValid(double price) {
    if (price < 0.000001) {
        std::cout << "Price must be positive." << std::endl;
        return false;
    }
    return true;
}

bool Product::IsExpirationDateValid(int expiration_date) {
    if (expiration_date < 0) {
        std::cout << "Expiration date cannot be negative." << std::endl;
        return false;
    }
    return true;
}

int Product::FindMinimumExpirationDate(int expiration_date_1, int expiration_date_2) {
    int minimum_expiration_date = 0;
    if (expiration_date_1 < expiration_date_2){
        minimum_expiration_date = expiration_date_1;
    }
    else{
        minimum_expiration_date = expiration_date_2;
    }
    return minimum_expiration_date;
}

std::vector<Ingredient> Product::FindGeneralComposition(const std::vector<Ingredient>& composition_1,
                                                         const std::vector<Ingredient>& composition_2) {
    std::vector<Ingredient> general_composition;

    for (size_t i = 0; i < composition_1.size(); ++i){
        bool found = false;
        for (size_t j = 0; j < general_composition.size(); ++j){
            if (composition_1[i].name == general_composition[j].name){
                general_composition[j].volume += composition_1[i].volume;
                found = true;
                break;
            }
        if (!found){
            general_composition.push_back(composition_1[i]);
        }
        }
    }

    for (size_t i = 0; i < composition_2.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < general_composition.size(); ++j) {
            if (composition_2[i].name == general_composition[j].name) {
                general_composition[j].volume += composition_2[i].volume;
                found = true;
                break;
            }
        }
        if (!found) {
            general_composition.push_back(composition_2[i]);
        }
    }

    return general_composition;
}

std::vector<Ingredient> Product::RemoveDuplicate(std::vector<Ingredient>& composition_1, const std::vector<Ingredient>& composition_2) {
    std::vector<Ingredient> result;
    for (size_t i = 0; i < composition_1.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < composition_2.size(); ++j) {
            if (composition_1[i].name == composition_2[j].name) {
                found = true;
                break;
            }
        }
        if (!found) {
            result.push_back(composition_1[i]);
        }
    }
    return result;
}

std::string Product::getLocate() const {
    return locate_;
}

std::string Product::getDescription() const {
    return description_;
}

void Product::setName(std::string name) {
    name_ = name;
}

void Product::setLocate(std::string locate) {
    locate_ = locate;
}

std::string Product::getName() const {
    return name_;
}

double Product::getPrice() const {
    return price_;
}

int Product::getExpirationDate() const {
    return expiration_date_;
}

std::vector<Ingredient> Product::getComposition() const {
    return composition_;
}

void Product::setPrice(double price) {
    if (IsPriceValid(price)) {
        price_ = price;
    }
}

void Product::DisplayAllInformation() {
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Price: " << getPrice() << std::endl;
    std::cout << "Composition: (";
    for (size_t i = 0; i < composition_.size(); ++i) {
        std::cout << "[ " << composition_[i].name << ", " << composition_[i].volume << " ]";
        if (i != composition_.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << ")" << std::endl;
    std::cout << "Expiration date (in days): " << getExpirationDate() << std::endl;
}

void Product::DisplayLocateInformation() {
    std::cout << "Place product:" << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Place: " << getLocate() << std::endl;
}

void Product::ChangeExpirationDate(int days) {
    if (days <= 0) {
        std::cout << "Days must be positive." << std::endl;
        return;
    }
    if (!IsExpirationDateValid(expiration_date_)) {
        return;
    }
    expiration_date_ -= days;
    if (expiration_date_ <= 0) {
        std::cout << "The product's expiration date has expired." << std::endl;
    } else {
        std::cout << "The expiration date has been reduced by " << days << " days." << std::endl;
    }
}