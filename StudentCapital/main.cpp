#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;
using std::vector;

struct Laptop {
    double price;
    double gain;
};

bool comparatorGain(const Laptop &a, const Laptop &b) {
    return a.gain > b.gain;
}

vector<Laptop> readLaptop(int K) {
    vector<Laptop> laptops(K);
    for (int i = 0; i < K; i++) {
        cout << "Enter price for #" << i << " laptop: ";
        cin >> laptops[i].price;
        cout << "Enter gain: ";
        cin >> laptops[i].gain;
    }
    return laptops;
}

void maximizeCapital(vector<Laptop> laptops, int N, double &C) {
    int size = laptops.size();
    while (N--) {
        int i = 0;
        while (i < size) {
            if (laptops[i].price <= C) break;
            ++i;
        }
        C -= laptops[i].price;
        C += laptops[i].gain;
    }
}

int main(void) {
    int N, K;
    double C;
    cout << "Enter maximum number of laptops to buy (N): ";
    cin >> N;
    cout << "Enter initial capital (C): ";
    cin >> C;
    cout << "Enter total number of available laptops (K): ";
    cin >> K;
    vector<Laptop> laptops = readLaptop(K);
    std::sort(laptops.begin(), laptops.end(), comparatorGain);
    maximizeCapital(laptops, N, C);
    cout << "Final capital: " << C << endl;
    return 0;
}