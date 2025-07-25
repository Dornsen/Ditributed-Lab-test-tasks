This is a console C++ application that implements a digital order book for trading UAH for USD. It supports account creation, login, adding buy/sell orders, and automatic order matching.

How to run
Compile
g++ -o start main.cpp order.cpp user.cpp

Run
./start


User interface
In the menu:
1. Login
2. Add order
3. Log out
4. Exit


Initial accounts:
 alice / pass123 — 1000 UAH, 500 USD
 bob / qwerty — 2000 UAH, 1000 USD

Commands:
After logging in, you can add an order to buy or sell:
Enter amount: 100
Enter price: 0.025
Enter side (0 - BUY / 1 - SELL): 0
