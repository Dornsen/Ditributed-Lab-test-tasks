#include <iostream>
#include <curl/curl.h>
#include <string>
#include <regex>
#include <vector>
#include <set>
#include <unordered_set>
#include <queue>

using std::string;
using std::vector;
using std::set;

const string WIKI_PREF = "https://en.wikipedia.org";
const string RESULT_LINK = "/wiki/Adolf_Hitler";
const int MAX_DEPTH = 6;

struct PageNode {
    string link;
    vector<string> path;
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string downloadPageHTML(const string &url) {
    string html;
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl error: " << curl_easy_strerror(res) << std::endl;
    }
    curl_easy_cleanup(curl);
    return html;
}

std::unordered_set<string> extractLinks(const string& html) {
    std::unordered_set<string> links;
    std::regex href_regex(R"(<a\s+(?:[^>]*?\s+)?href=["']([^"']+)["'])", std::regex::icase);
    auto begin = std::sregex_iterator(html.begin(), html.end(), href_regex);
    auto end = std::sregex_iterator();

    for (auto i = begin; i != end; ++i) {
        std::smatch match = *i;
        if (match.size() > 1) {
            string url = match[1];
            int pos = url.find("/wiki/");
            if (pos == string::npos) continue;
            url = url.substr(pos);
            if (url.find(':') != string::npos) continue;
            links.insert(url);
        }
    }
    return links;
}

void bfs(const string &startLink) {
    std::unordered_set<string> visited;
    std::queue<PageNode> queueLinks;
    queueLinks.push({startLink, {startLink}});
    visited.insert(startLink);
    while (!queueLinks.empty()) {
        PageNode currentPage = queueLinks.front();
        queueLinks.pop();
        std::cout << "Open page: " << currentPage.link << "\tDepth: " << currentPage.path.size() << std::endl;
        if (currentPage.path.size() > MAX_DEPTH) break;
        
        string url = WIKI_PREF + currentPage.link;
        string html = downloadPageHTML(url);
        std::unordered_set<string> newLinks = extractLinks(html);
        if (newLinks.find(RESULT_LINK) != newLinks.end()) {
            currentPage.path.push_back(RESULT_LINK);
            std::cout << RESULT_LINK << " IS FOUND\nSteps to found:" << std::endl;
            for (const string &l : currentPage.path) {
                std::cout << l << std::endl;
            }
            return;
        }
        for (const string &l : newLinks) {
            if (visited.find(l) != visited.end()) continue;
            visited.insert(l);
            PageNode newPage = currentPage;
            newPage.link = l;
            newPage.path.push_back(l);
            queueLinks.push(newPage);
            std::cout << "\tAdd new page: " << l << std::endl; 
        }
    
    }
    std::cout << "Is not found" << std::endl;
}

int main(int argc, char *argv[]) {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    string startUrl = argv[1];
    string relativeUrl = startUrl.substr(WIKI_PREF.length());
    bfs(relativeUrl);
    curl_global_cleanup();
    return 0;
}
