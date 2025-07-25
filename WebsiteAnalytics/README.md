Website Analytics  
This console app analyzes two CSV files with users’ page visits over two separate days.
The goal is to find all users who:  
Visited some pages on both days  
On the second day, visited at least one page they did not visit on the first day  

The program outputs user IDs and the list of their new pages visited on day two.

How to build and run  
Compile: g++ main.cpp -o start  
Run: ./start day1.csv day2.csv

Algorithm Complexity (Big O)  
Loading files: O(N), where N is the number of lines in the file.  
Insertion into map and set: roughly O(log⁡M) per operation, M = size of the set/map.  
Iterating over users: O(Ulog⁡U), U = number of unique users on day one.  
std::set_difference: O(P), P = number of pages per user.  
Overall complexity: about O(Nlog⁡M), which is efficient for this task.  

Why is it efficient?  
map and set provide fast lookups and automatic duplicate elimination.  
Only unique pages per user are stored, saving memory.  
Standard library set operations are optimized for speed.  