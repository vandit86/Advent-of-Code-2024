#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm> 
#include <cstdlib>
#include <sstream>
#include <cctype> 
#include <cassert>

/*

for debug print : g++ -DDEBUG -o exe exe.cpp
for GDB 		: g++ -DDEBUG -g -o exe exe.cpp
run GDB 		: gdb ./exe
optimization 	: g++ -O2 -o exe exe.cpp

result part 1:  6463499258318

result part 2: 

*/

using namespace std; 

using ull = unsigned long long; 
using MAP = vector<vector<char>>; // our playground 

static ull totalScore = 0; 	// total score 
static int L , H; 			// map dimentions   

struct Pos {
	int i;
	int j; 
}; 

void printVec (const vector<char>& vec){
	for (const auto& i : vec){
		printf(" %d ", i); 
	}
	printf ("\n"); 
}

void printMap (const MAP& map){
	for (const auto& i : map){
		printVec(i); 
	}
}

void findTrail (MAP& map, Pos pos, int height){
	
	if (pos.i > 0 && (map[pos.i - 1][pos.j] - height == 1)){
		if (map[pos.i - 1][pos.j] == 9) { map[pos.i - 1][pos.j] = -1; ++totalScore;}
		else findTrail(map, {pos.i - 1, pos.j}, height+1);  
	}
	if (pos.i < L-1 && (map[pos.i + 1][pos.j] - height == 1)){
		if (map[pos.i + 1][pos.j] == 9) {map[pos.i + 1][pos.j] = -1; ++totalScore;}
		else findTrail(map, {pos.i + 1, pos.j}, height+1);  
	}
	if (pos.j > 0 && (map[pos.i][pos.j - 1] - height == 1)){
		if (map[pos.i][pos.j - 1] == 9) {map[pos.i][pos.j - 1] = -1; ++totalScore;}
		else findTrail(map, {pos.i, pos.j-1}, height+1);  
	}
	if (pos.j < H-1 && (map[pos.i][pos.j + 1] - height == 1)){
		if (map[pos.i][pos.j + 1] == 9) { map[pos.i][pos.j + 1] = -1; ++totalScore;}
		else findTrail(map, {pos.i, pos.j+1}, height+1);  
	}
}

void countScore (const MAP& map) {
	
	for (int i = 0; i < L; ++i){
		for (int j = 0; j < H; ++j){
			
			if (map[i][j] == 0){
				
				MAP mp = map; 
				findTrail (mp, {i,j}, 0); 
				
			}
			
		}
	}
	
}

/*
89010123
78121874
87430965
96549874
45678903
32019012
01329801
10456732
*/

int main (){
         
    //std::ifstream inputFile("input.txt"); // Open the input file
    std::ifstream inputFile("input-big.txt"); // Open the input file
    
	if (!inputFile) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1; // Exit with error code
    }
	
	
	MAP map {}; 
	ull res{}; 
	string line;
	
	// Read each line into the string, check EOL to be -> unix LF 
    while (getline(inputFile, line)) { 
		vector<char> data{};
		for (char& c : line) if (c != '\n') data.push_back(c - '0'); 
		map.push_back(data); 
    }
	
	printMap(map); 
	
	L = map.size(); 
	H = map[0].size(); 
	printf ("size %d x %d \n", L,H); 
	
	countScore(map); 
	
	cout << "result: " << totalScore << endl;   
	
    return 0;
}