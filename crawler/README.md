Hitler Crawler  
This console app takes a Wikipedia article URL as input and tries to find a path to the Wikipedia page about Adolf Hitler by following internal Wikipedia links.
It searches by crawling linked Wikipedia pages up to a maximum of 6 hops. If it finds the Hitler page, it outputs the path. If not, it prints “Hitler not found”.

How to build and run  
Compile: g++ main.cpp -o start -lcurl  

Run: ./start (https://en.wikipedia.org/wiki/Philosophy)  

Complexity  
BFS ensures shortest path in terms of hops.  
Time depends mostly on network latency and number of pages crawled.  
Max depth is 6, so worst case the algorithm visits a large branching factor to this depth.  
But the application is too slow due to a lack of multithreading
