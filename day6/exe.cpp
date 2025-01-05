#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm> 
#include <cstdlib>
#include <sstream>
#include <cctype> // For std::isdigit

/*
result part 1: 5067 
result part 2: 
*/

using namespace std; 

using Map = vector<string>; 

// area limits 
static int MAP_L = 0; 
static int MAP_H = 0;
static bool OUT = false; // set true if OUT of board

// position on map 
struct Position {
	int x; 
	int y; 
}; 


// 4
unsigned goLeft (Map& map, Position& pos){
	unsigned res{}; 
	for (int i = pos.y - 1 ; i >= 0; --i){
		if (map[pos.x][i] == '#') return res;
		
		if (map[pos.x][i] != 'X'){ 
			res++;
			map[pos.x][i] = 'X'; 
		}
		pos.y = i;
	}
	OUT = true; 
	return res; 
}

// 3
unsigned goDown (Map& map, Position& pos){
	unsigned res{}; 
	for (int i = pos.x + 1 ; i < MAP_L; ++i){
		if (map[i][pos.y] == '#') return res;
		
		if (map[i][pos.y] != 'X'){ 
			res++;
			map[i][pos.y] = 'X'; 
		}
		pos.x = i;
	}
	OUT = true; 
	return res; 
}

// 2
unsigned goRight (Map& map, Position& pos){
	unsigned res{}; 
	for (int i = pos.y + 1 ; i < MAP_H; ++i){
		if (map[pos.x][i] == '#') return res;
		
		if (map[pos.x][i] != 'X'){ 
			res++;
			map[pos.x][i] = 'X'; 
		}
		pos.y = i;
	}
	OUT = true; 
	return res; 
}

// 1
unsigned goUp (Map& map, Position& pos){
	unsigned res{}; 
	for (int i = pos.x - 1 ; i >= 0; --i){
		if (map[i][pos.y] == '#') return res;
		
		if (map[i][pos.y] != 'X'){ 
			res++;
			map[i][pos.y] = 'X'; 
		}
		
		pos.x = i;
	}
	OUT = true; 
	return res; 
}

// count steps needed to go out the map, starting from position start 
unsigned long countSteps (Map& map, Position& pos){
	
	map[pos.x][pos.y] = 'X'; // mark as we was there 
	unsigned long res = 1; 
	
	while (1){
		res += goUp(map , pos);
		//cout << "U : "<< res << endl; 
		if (OUT) break;
		res += goRight(map , pos);
		//cout << "R : "<< res << endl;
		if (OUT) break;
		res += goDown(map , pos);
		//cout << "D : "<< res << endl;
		if (OUT) break;
		res += goLeft(map , pos);
		//cout << "L : "<< res << endl;
		if (OUT) break; 
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
	
    unsigned long long res = 0u; 
    std::string line;
	
	Map map {};  // playground  
	
	// read page ordering rules
	while (std::getline(inputFile, line)) {
		// remove new line char 
		line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());		
		map.push_back(line);  		
	}
	
	MAP_L = map.size();			// x limit
	MAP_H = map[0].size(); 	// y limit 
	
	Position pos {};  
	// find start pos 
	for (int i = 0 ; i < MAP_L ; ++i){
		for (int j = 0 ; j < MAP_H ; ++j){
			if (map[i][j] == '^'){
				pos = {i , j};
				break; 
			}
		}
	}
	
	res = countSteps(map,pos);
	
	for (auto& i : map){
		cout << i << endl; 
	}
	
	cout << "Result : " <<  res << endl;
    inputFile.close(); // Close the file
    return 0;
}