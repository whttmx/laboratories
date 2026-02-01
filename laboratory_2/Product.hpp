#pragma once
#include <string>
#include <vector>

class Product{

public:

    Product();
    Product(std::string name, double price, std::vector<std::string> composition, int expiration_date);
    Product(const Product& other_product);
    ~Product();

    Product& operator=(const Product& other_product);
    Product operator+(const Product& other_product);
    Product operator-(const Product& other_product);
    Product& operator-=(const Product& other_product);

    std::string getName() const;
    double getPrice() const;
    int getExpirationDate() const;
    std::vector<std::string> getComposition() const;

    void setPrice(double price);

    void DisplayAllInformation();
    void ChangeExpirationDate(int days);

protected:

    double price_;
    int expiration_date_;
    std::vector<std::string> composition_;

    bool IsPriceValid(double price);
    bool IsExpirationDateValid(int expiration_date);
    int FindMinimumExpirationDate(int expiration_date_1, int expiration_date_2);
    std::vector<std::string> FindGeneralComposition(const std::vector<std::string>& composition_1, const std::vector<std::string>& composition_2);
    std::vector<std::string> RemoveDuplicate(std::vector<std::string>& composition_1, const std::vector<std::string>& composition_2);

private:
    std::string name_;
};