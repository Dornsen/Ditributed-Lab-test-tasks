#include "user.h"

unsigned int User::getID() const { return ID; }
std::string User::getName() const { return name; }
std::string User::getPassword() const { return password; }
double User::getBalanceUAH() const { return balanceUAH; }
double User::getBalanceUSD() const { return balanceUSD; }

void User::changeBalanceUAH(double n) { balanceUAH += n; }
void User::changeBalanceUSD(double n) { balanceUSD += n; }

void User::freezeUAH(double amount) { frozenUAH += amount; }
void User::freezeUSD(double amount) { frozenUSD += amount; }
