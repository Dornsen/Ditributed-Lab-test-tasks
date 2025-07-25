#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_map>

class User;

extern std::unordered_map<std::string, User> users;
extern User *currentUser;

class User
{
private:
    unsigned int ID;
    std::string name;
    std::string password;
    double balanceUAH;
    double balanceUSD;
    double frozenUAH;
    double frozenUSD;
public:
    User() = default;
    User(unsigned int ID, std::string name, std::string password, double balanceUAH = 0, double balanceUSD = 0) 
            : ID(ID), name(name), password(password), balanceUAH(balanceUAH), balanceUSD(balanceUSD) {}
    unsigned int getID() const;
    std::string getName() const;
    std::string getPassword() const;
    double getBalanceUAH() const;
    double getBalanceUSD() const;

    void changeBalanceUAH(double n);
    void changeBalanceUSD(double n);

    void freezeUAH(double amount);
    void freezeUSD(double amount);
};

#endif