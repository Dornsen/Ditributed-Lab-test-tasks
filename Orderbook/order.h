#ifndef ORDER_H
#define ORDER_H

#include <set>
#include "user.h"

class Order
{
private:
    User* user;
    double amount;
    double price;
    bool side;
public:
    Order(User *user, double amount, double price, bool side) 
          : user(user), amount(amount), price(price), side(side) {}

    User *getUser() const;
    double getAmount() const;
    double getPrice() const;
    bool getSide() const;

    void changeAmount(double n);

    bool operator<(const Order &other) const {
        return price < other.price;
    }
};

struct BuyOrderComparator {
    bool operator()(const Order &A, const Order &B) const;
};

class OrderBook
{
private:
    std::multiset<Order> sellOrders;
    std::multiset<Order, BuyOrderComparator> buyOrders;
public:
    void addOrder();
    void balanceChange(User* user, double UAH, double USD);
    void matching();
};

#endif