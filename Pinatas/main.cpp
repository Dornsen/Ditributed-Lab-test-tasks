#include <iostream>
#include <vector>
#include <algorithm>

long long maxSum(std::vector<int> pinatas) {
    int size = pinatas.size();
    std::vector<std::vector<int>> dp(size, std::vector<int>(size, 0));
    for (int len = 2; len < size; len++) {
        for (int i = 0; i < size - len; i++) {
            int j = i + len;
            for (int k = i + 1; k < j; k++) {
                dp[i][j] = std::max(dp[i][j], dp[i][k] + dp[k][j] + pinatas[i] * pinatas[k] * pinatas[j]);
            }
        }
    }
    return dp[0][size - 1];
}

int main(int argc, char *argv[]) {
    int size = argc - 1;
    std::vector<int> pinatas;
    pinatas.push_back(1);
    for (int i = 1; i < argc; i++) {
        pinatas.push_back(std::atoi(argv[i]));
    }
    pinatas.push_back(1);
    long long sum = maxSum(pinatas);
    std::cout << sum;
    return 0;
}