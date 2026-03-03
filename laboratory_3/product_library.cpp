#include <iostream>
#include "product_library.hpp"
#include "Product.hpp"      

void Ingredient::DisplayIngredientInformation() {
    std::cout << "Ingredient: " << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Volume: " << volume << std::endl;
}

Commission::Commission() {
    address_ = "Not specified";
    prohibited_ingredients_ = {};
    verification_period_ = 0;
}

Commission::Commission(std::string address, std::vector<Ingredient> prohibited_ingredients, int verification_period) {
    address_ = address;
    prohibited_ingredients_ = prohibited_ingredients;
    verification_period_ = verification_period;
}

Commission::Commission(const Commission& other) {
    address_ = other.address_;
    prohibited_ingredients_ = other.prohibited_ingredients_;
    verification_period_ = other.verification_period_;
}

Commission::~Commission() {
    prohibited_ingredients_.clear();
    std::cout << "The commission was disbanded." << std::endl;
}

std::string Commission::getAddress() const {
    return address_;
}

std::vector<Ingredient> Commission::getProhibitedIngredients() const {
    return prohibited_ingredients_;
}

int Commission::getVerificationPeriod() const {
    return verification_period_;
}

void Commission::setAddress(std::string address) {
    address_ = address;
}

void Commission::setProhibitedIngredients(std::vector<Ingredient> prohibited_ingredients) {
    prohibited_ingredients_ = prohibited_ingredients;
}

bool Commission::IsVerificationPeriodValid(int verification_period) {
    if (verification_period <= 0) {
        std::cout << "Verification period must be positive." << std::endl;
        return false;
    }
    return true;
}

void Commission::setVerificationPeriod(int verification_period) {
    if (IsVerificationPeriodValid(verification_period)) {
        verification_period_ = verification_period;
    }
}

bool Commission::ProductInspection(const Product& product) {
    std::vector<Ingredient> composition = product.getComposition();
    int expiration_date = product.getExpirationDate();

    const std::vector<Ingredient>& prohibited = prohibited_ingredients_;
    int verification_period = verification_period_;

    bool isIllegal = false;
    bool isExpired = false;

    for (size_t i = 0; i < composition.size(); ++i) {
        for (size_t j = 0; j < prohibited.size(); ++j) {
            if (composition[i].name == prohibited[j].name) {
                isIllegal = true;
                break;
            }
        }
        if (isIllegal) break;
    }

    if (expiration_date < verification_period) {
        isExpired = true;
    }
    if (isIllegal || isExpired){
        return false;
    }

    return true;
}