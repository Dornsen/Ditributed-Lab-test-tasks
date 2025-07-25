#include "order.h"
#include "user.h"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

enum e_side {
    BUY,
    SELL
};

User* Order::getUser() const { return user; }
double Order::getAmount() const { return amount; }
double Order::getPrice() const { return price; }
bool Order::getSide() const { return side; }
void Order::changeAmount(double n) { amount += n; }


bool BuyOrderComparator::operator()(const Order &A, const Order &B) const {
    return A.getPrice() > B.getPrice();
}

void OrderBook::addOrder() {
    if (currentUser == nullptr) {
        cout << "You must login first." << endl;
        return;
    }
    double amount, price;
    bool side;

    cout << "Add Order:" << endl;
    do {
        cout << "Enter amount: ";
        cin >> amount;
        if (amount < 0) cout << "Error: Ammount < 0" << endl;
    } while (amount < 0);
    do {
        cout << "Enter price: ";
        cin >> price;
        if (price < 0) cout << "Error: Price < 0" << endl;
    } while (price < 0);
    cout << "Enter side (0 - BUY/1 - SELL): ";
    cin >> side;

    Order order(currentUser, amount, price, side);
    if (side == SELL) {
        if (currentUser->getBalanceUAH() < amount) {
            cout << "Not enough UAH to sell! Your balance: " << currentUser->getBalanceUAH() << endl;
            return;
        }
        currentUser->changeBalanceUAH(-amount);
        currentUser->freezeUAH(amount);
        sellOrders.insert(order);
    } else {
        double totalCost = amount * price;
        if (currentUser->getBalanceUSD() < totalCost) {
            cout << "Not enough USD to buy! You need " << totalCost << ", your balance: " << currentUser->getBalanceUSD() << endl;
            return;
        }
        currentUser->changeBalanceUSD(-totalCost);
        currentUser->freezeUSD(totalCost);
        buyOrders.insert(order);
    }
    matching();
}

void OrderBook::balanceChange(User *user, double UAH, double USD) {
    if (UAH < 0) {
        user->freezeUAH(UAH);
        user->changeBalanceUSD(USD);
    }
    if (USD < 0) {
        user->freezeUSD(USD);
        user->changeBalanceUAH(UAH);
    }
    cout << "User: " << user->getName()
         << "\t" << (UAH >= 0 ? "+" : "") << UAH << " UAH\t"
         << (USD >= 0 ? "+" : "") << USD << " USD" << endl;
}

void OrderBook::matching() {
    while (!buyOrders.empty() && !sellOrders.empty()) {
        Order topSellOrder = *sellOrders.begin();
        sellOrders.erase(sellOrders.begin());
        Order topBuyOrder = *buyOrders.begin();
        buyOrders.erase(buyOrders.begin());
        if (topSellOrder.getPrice() <= topBuyOrder.getPrice()) {
            double tradedAmount = std::min(topBuyOrder.getAmount(), topSellOrder.getAmount());
            double totalPrice = tradedAmount * topSellOrder.getPrice();

            balanceChange(topSellOrder.getUser(), -tradedAmount, totalPrice);
            balanceChange(topBuyOrder.getUser(), tradedAmount, -totalPrice);

            topBuyOrder.changeAmount(-tradedAmount);
            topSellOrder.changeAmount(-tradedAmount);
            
            if (topBuyOrder.getAmount() > 0)  { 
                buyOrders.insert(topBuyOrder);
            } else {
                cout << "The buy order has been deleted." << endl;
            }
            if (topSellOrder.getAmount() > 0) {
                sellOrders.insert(topSellOrder);
            } else {
                cout << "The sales order has been deleted." << endl;
            }
        } else {
            break;
        }   
    }
}