#pragma once
#include <string>
#include <vector>

struct Ingredient {
    std::string name;
    double volume;

    void DisplayIngredientInformation();
};

class Commission {
public:
    Commission();
    Commission(std::string address, std::vector<Ingredient> prohibited_ingredients, int verification_period);
    Commission(const Commission& other);
    ~Commission();

    std::string getAddress() const;
    std::vector<Ingredient> getProhibitedIngredients() const;
    int getVerificationPeriod() const;

    void setAddress(std::string address);
    void setProhibitedIngredients(std::vector<Ingredient> prohibited_ingredients);
    void setVerificationPeriod(int verification_period);

    bool ProductInspection(const Product& product);

protected:
    bool IsVerificationPeriodValid(int verification_period);

private:
    std::string address_;
    std::vector<Ingredient> prohibited_ingredients_;
    int verification_period_;
};