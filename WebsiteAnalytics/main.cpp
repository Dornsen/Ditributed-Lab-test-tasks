#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::set;

map<string, set<string>> loadDayData(string path) {
    map<string, set<string>> result;
    std::ifstream iFile(path);
    string buff;
    while (std::getline(iFile, buff)) {
        std::stringstream line(buff);
        string user, product;
        std::getline(line, user, ',');
        std::getline(line, product, ',');
        result[user].insert(product);
    }
    iFile.close();
    return result;
}

map<string, set<string>> findAllTheUsersThat(map<string, set<string>> day1, map<string, set<string>> day2) {
    map<string, set<string>> result;
    for (const auto& [user1, pages1] : day1) {
        auto user2 = day2.find(user1);
        if (user2 != day2.end()) {
            set<string> pages2 = user2->second;
            set<string> newPages;
            std::set_difference(pages2.begin(), pages2.end(),
                                pages1.begin(), pages1.end(),
                                std::inserter(newPages, newPages.begin()) );
            if (!newPages.empty()) {
                result[user1] = newPages; 
            }
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    map<string, set<string>> dataDay1 = loadDayData(argv[1]);
    map<string, set<string>> dataDay2 = loadDayData(argv[2]);
    
    map<string, set<string>> result = findAllTheUsersThat(dataDay1, dataDay2);

    for (const auto& [user, products] : result) {
        cout << user << ": ";
        for (const auto& product : products) {
            cout << product << " ";
        }
        cout << endl;
    }

    return 0;
}