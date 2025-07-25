#include <iostream>
#include <unordered_map>
#include "order.h"
#include "user.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

std::unordered_map<std::string, User> users;
User *currentUser = nullptr;
OrderBook orderbook;

void registerUser() {
    std::string name, password;
    std::cout << "Username: ";
    std::cin >> name;

    if (users.find(name) != users.end()) {
        std::cout << "❌ User already exists.\n";
        return;
    }

    std::cout << "Password: ";
    std::cin >> password;

    unsigned int newID = users.size() + 1;
    users[name] = User(newID, name, password, 0, 0);
    std::cout << "✅ Registered successfully!\n";
}

void loginUser() {
    string name, password;
    cout << "Username: ";
    cin >> name;
    cout << "Password: ";
    cin >> password;

    if (users.find(name) == users.end()) {
        cout << "User not found." << endl;
        return;
    }
    if (users[name].getPassword() != password) {
        cout << "Incorrect password." << endl;
        return;
    }

    currentUser = &users[name];
    cout << "Logged in as " << currentUser->getName() << endl;
}

int main(void) {
    users["alice"] = User(1, "alice", "pass123", 1000.0, 500.0);
    users["bob"] = User(2, "bob", "qwerty", 2000.0, 1000.0);

    while (true) {
        cout << "\n1. Login\n2. Add order\n3. Log out\n4. Exit\nChoose: ";
        int choice; cin >> choice;
        if (choice == 1) {
            loginUser();
        } else if (choice == 2) {
            if (currentUser == nullptr) {
                cout << "Login first!" << endl;
            } else {
                orderbook.addOrder();
            }
        } else if (choice == 3) {
            currentUser = nullptr;
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
    User user = users["alice"];
    cout << "\n\nUser: " <<  user.getName() << "\n ID: " << user.getID() << "\nUAH: " << user.getBalanceUAH() << "\nUSD: " << user.getBalanceUSD();
    user = users["bob"];
    cout << "\n\nUser: " <<  user.getName() << "\n ID: " << user.getID() << "\nUAH: " << user.getBalanceUAH() << "\nUSD: " << user.getBalanceUSD();
    return 0;
}