#include <iostream>
#include <string>
#include <exception>

class Product{

public:

    Product(){
        name_ = "Без названия";
        description_ = "Без описания";
        price_ = 0.0;
        expiration_date_ = 0;
        place_ = "Не указано";   
    }

    Product(std::string name, std::string description, float price, int expiration_date, std::string place){
        name_ = name;
        description_ = description;
        if (IsPriceValid(price)){
            price_ = price;
        }
        expiration_date_ = expiration_date;
        place_ = place;
    }

    Product(const Product& p){

        name_ = p.name_;
        description_ = p.description_;
        price_ = p.price_;
        expiration_date_ = p.expiration_date_;
        place_ = p.place_;
    }
    
    ~Product(){
        std::cout << "The product has been removed" << std::endl;
    }

    void setPrice(float price){
        if (IsPriceValid(price)){
            price_ = price;
        }
        return;
    }

    std::string getName() const{
        return name_;
    }

    std::string getDescription() const{
        return description_;
    }

    float getPrice() const{
        return price_;
    }

    int getExpirationDate() const{
        return expiration_date_;
    }

    std::string getPlace() const{
        return place_;
    }
    
    void ReduceShelfLife(int days){
        if (IsExpirationDateValid(expiration_date_)){
             if (days > 0){
                expiration_date_ = expiration_date_ - days;
                if (expiration_date_<= 0){
                    std::cout << "The product's expiration date has expired." << std::endl;
                }
                std::cout << "The expiration date of the product has been changed to " << days << "days." << std::endl;
            }
        }
        return;
       
    }

    void DisplayAllInformation(){
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "Description: " << getDescription() << std::endl;
        std::cout << "Price: " << getPrice() << std::endl;
        std::cout << "Expiration date: " << getExpirationDate() << std::endl;
        std::cout << "Place: " << getPlace() << std::endl;
    }

    void DisplayPlaceInformation(){
        std::cout << "Place product:" << std::endl;
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "Place: " << getPlace() << std::endl;
    }

protected:

    float price_;
    int expiration_date_;

    bool IsExpirationDateValid(int expiration_date){
        if (expiration_date < 0){
            std::cout << ("Expiration date have to be positive.") << std::endl;
            return false;
        }
        return true;
    }

    bool IsPriceValid(float price){
        if (price < 0.000001){
            std::cout << ("Price have to be positive.") << std::endl;
            return false;
        }
        return true;
    }

private:

    std::string name_;
    std::string description_;
    std::string place_;

};


int main()
{
    Product product_1;
    std::cout << "Default product:" << std::endl;
    product_1.DisplayAllInformation();
    std::cout << std::endl;
    product_1.DisplayPlaceInformation();
    std::cout << std::endl;

    Product product_2("Red Bull", "Энергетический напиток", 354, 730, "Напитки");
    std::cout << "Заполненный товар:" << std::endl;
    product_2.DisplayAllInformation();
    std::cout << std::endl;
    product_2.DisplayPlaceInformation();
    std::cout << std::endl;

    product_2.setPrice(240);
    product_2.setPrice(-100);
    product_2.getPrice();
    std::cout << std::endl;

    product_2.ReduceShelfLife(700);
    product_2.ReduceShelfLife(-10);
    product_2.getExpirationDate();
    std::cout << std::endl;

    Product product_3(product_2);
    std::cout << "Скопированный товар: " << std::endl;
    product_3.DisplayAllInformation();
    std::cout << std::endl;
    product_3.DisplayPlaceInformation();
    std::cout << std::endl;

    product_2.getDescription();
    std::cout << std::endl;

    product_1.getExpirationDate();
    std::cout << std::endl;

    product_3.getName();
    std::cout << std::endl;

    return 0;
}