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

result part 1:  423

result part 2: 1287

*/

using namespace std; 
using Map = vector<vector<char>>;

// area limits 
static int MAP_L = 0; // x
static int MAP_H = 0; // y


// position on map 
struct Position {
	int x; 
	int y;
	
	// return true if position is on the map 
	bool isValid (){
		if (x >= MAP_L || x < 0) return false; 
		if (y >= MAP_H || y < 0) return false;
		return true; 
	}
}; 


Position operator+(const Position& a , const Position& b){
	
	Position tmp {}; 
	tmp.x = a.x + b.x;
	tmp.y = a.y + b.y;
	return tmp; 
	
}; 

Position operator-(const Position& a , const Position& b){
	
	Position tmp {}; 
	tmp.x = a.x - b.x;
	tmp.y = a.y - b.y;
	return tmp; 
}; 



#ifdef DEBUG
#endif

// print MAP 
void printMap (const Map& map){
	cout << endl; 
	for (auto& i : map){
		for (auto& j : i)
		 cout << j ;
		cout << endl; 
	}
	cout << endl; 
}

void printPosition (const Position pos){
	cout << "x : " << pos.x << " , " << "y : " << pos.y << endl;   
}

// set antinode for simbol at position pos (for each pair on next same simbols in map) 
void setAntinode (Map& map, Position pos, Map& antinodes){
	
	auto simb =  map[pos.x][pos.y];
	antinodes[pos.x][pos.y] = '#'; 
	int initJ = pos.y + 1; 
	
	for (int i = pos.x; i < MAP_L; i++){
		for (int j = initJ ; j < MAP_H; j++){
			if (map[i][j] == simb){
				
				Position posSimb {i,j};			// pos of similar simbol 
				Position diff = pos - posSimb;	// diff with antena in case 
				
				
				Position p1 = pos + diff; 
				Position p2 = posSimb - diff; 
				
				// set antinodes
				while (p1.isValid()){
					antinodes[p1.x][p1.y] = '#';
					p1 = p1 + diff; 
				}
				
				while (p2.isValid()){
					antinodes[p2.x][p2.y] = '#';
					p2 = p2 - diff;
				}
			}
		}
		initJ = 0; 
	}
	
	//printMap(map); 
	//printMap(antinodes); 
}

unsigned long countAntinode (Map& map, Map& antinodes){
	
	unsigned long res {}; 
	
	for (int i = 0; i < MAP_L; i++){
		for (int y = 0; y < MAP_H; y++){
			
			auto simb = map[i][y];  
			
			if (simb != '.' && simb != '#'){
				Position pos {i,y}; 				// get pos of next simb 
				setAntinode (map, pos, antinodes);	// set antenas for each pair 
			}
			
		}
	}
	
	for (int i = 0; i < MAP_L; i++){
		for (int y = 0; y < MAP_H; y++){
			if (antinodes[i][y] == '#') ++res; 
		}
	}
	return res; 
}

int main (){
         
    //std::ifstream inputFile("input.txt"); // Open the input file
    std::ifstream inputFile("input-big.txt"); // Open the input file
    
	if (!inputFile) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1; // Exit with error code
    }
	
	unsigned long result{}; 
    std::string line;
	Map map {};  		// playground  input 
	Map antinodes {}; 	// antinode antenas here 	
	
	// read page ordering rules
	while (std::getline(inputFile, line)) {
		vector<char> v{}; 
		for (char c : line) {
			v.push_back(c); 
		}
		map.push_back(v);  		
	}
	
	MAP_L = map.size();			// x limit
	MAP_H = map[0].size(); 		// y limit 
	
	cout<< "L " << MAP_L << " x  H " << MAP_H << endl; 
	
	for (int i = 0 ; i < MAP_L; i ++){
		vector<char> v{};
		for (int j = 0; j < MAP_H ; j ++){
			v.push_back('.'); 
		}
		antinodes.push_back(v); 
	}
	
	result = countAntinode(map, antinodes); 
	//printMap (map); 
	
	
	cout << "Res  : " <<  result << endl;
    inputFile.close(); // Close the file
    return 0;
}