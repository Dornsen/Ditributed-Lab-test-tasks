Maze Generator

This console C++ program generates a 2D maze with these cell types:  
    S — Entrance (one, on outer border)  
    E — Exit (one, on outer border)  
    # — Wall (impassable)  
    SPACE — Road (walkable)  
    T — Treasure (optional, reachable)  

How to build and run  
Compile: g++ main.cpp -o start  

Run: ./start  
Enter maze size (width and height). If even, sizes auto-incremented by 1.

Efficiency:  
    Time complexity: O(W×H) — every cell visited once.  
    Space complexity: O(W×H) for maze storage.