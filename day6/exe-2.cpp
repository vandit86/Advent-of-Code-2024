#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm> 
#include <cstdlib>
#include <sstream>
#include <cctype> // For std::isdigit
#include <cassert>

/*

for debug print : g++ -DDEBUG -o exe exe-2.cpp
for GDB 		: g++ -DDEBUG -g -o exe exe-2.cpp
run GDB 		: gdb ./exe
optimization 	: g++ -O2 -o exe exe-2.cpp

result part 1: 5067 

// correct result for small (exampe) input ,, stuck in some loop for big input . stop after
result part 2: 
*/

using namespace std; 
//using Map = vector<string>; 

using Map = vector<vector<char>>;

// area limits 
static int MAP_L = 0; 
static int MAP_H = 0;
static bool OUT = false; // set true if OUT of board

// position on map 
struct Position {
	int x; 
	int y; 
}; 

// Direction of movement
enum class Direction {
	Up = 0,
	Right,
	Down,
	Left
};

// combine Position and Direction 
struct PosDir{
	Position pos;
	Direction dir;	
};

bool operator==(const PosDir& a , const PosDir& b){
	
	if (a.pos.x == b.pos.x && a.pos.y == b.pos.y && a.dir == b.dir) return true; 
	return false; 
	
}; 

static unsigned loopCount = 0u; // count loops
static PosDir initPd; 


// get nex directio based on actual 
Direction getNextDir (Direction dir){
    switch (dir) {
        case Direction::Up:
            return Direction::Right;
        case Direction::Right:
            return Direction::Down;
        case Direction::Down:
            return Direction::Left;
		case Direction::Left:
            return Direction::Up;
        default:
			assert(false); 
    }
}


#ifdef DEBUG
// clear all 'x' on map 
void clearX (Map& map){
	for (auto& i : map){
		// Replace all occurrences of 'x' with '.'
		std::replace(i.begin(), i.end(), 'x', '.');
	}
}

// print MAP 
void printMap (Map& map){
	cout << endl; 
	for (auto& i : map){
		 cout << i << endl; 
	}
	cout << endl; 
}
#endif

// fofward declaration 
bool walk (Map& map, PosDir pd); 

// 4. Go left , return true if go out the board 
bool goLeft (Map& map, PosDir& pd, bool checkLoop = false){
	for (int i = pd.pos.y; i >= 0; --i){
		if (map[pd.pos.x][i] == '#') return false;
		pd.pos.y = i;
		if (checkLoop){
			initPd = pd; 				// save start position and direction 
			walk(map, initPd); 
		}
		else{
			
	#ifdef DEBUG
			map[pd.pos.x][i] = 'x'; 
	#endif
			if (initPd == pd) {
				++loopCount;
				break; 			// we are in loop, stop 
			}
		}
	}
	return true;  
}

// 3. Go Down , return true if go out the board
bool goDown (Map& map, PosDir& pd, bool checkLoop = false){
	for (int i = pd.pos.x; i < MAP_L; ++i){
		if (map[i][pd.pos.y] == '#') return false;
		pd.pos.x = i;
		if (checkLoop){
			initPd = pd; 				// save start position and direction 
			walk(map, initPd);  
		}
		else{
			
	#ifdef DEBUG
			map[i][pd.pos.y] = 'x'; 
	#endif
			if (initPd == pd) {
				++loopCount;
				break; 			// we are in loop, stop 
			}
		}
	} 
	return true; 
}

// 2. Go Right , return true if go out the board
bool goRight (Map& map, PosDir& pd, bool checkLoop = false){
	for (int i = pd.pos.y; i < MAP_H; ++i){
		if (map[pd.pos.x][i] == '#') return false;
		pd.pos.y = i;
		if (checkLoop){
			initPd = pd; 				// save start position and direction 
			walk(map, initPd);  
		}
		else{
			
	#ifdef DEBUG
			map[pd.pos.x][i] = 'x';
	#endif
			if (initPd == pd) {
				++loopCount;
				break; 			// we are in loop, stop 
			}
		}
	} 
	return true; 
}

// 1. Go Up , return true if go out the board
bool goUp (Map& map, PosDir& pd, bool checkLoop = false){
	for (int i = pd.pos.x; i >= 0; --i){
		if (map[i][pd.pos.y] == '#') return false;
		pd.pos.x = i; 
		if (checkLoop){
			initPd = pd; 				// save start position and direction 
			walk(map, initPd); 
		}
		else{
			
	#ifdef DEBUG
			map[i][pd.pos.y] = 'x'; 
	#endif
			if (initPd == pd) {
				++loopCount;
				break; 			// we are in loop, stop 
			}
		} 
	}	
	return true; 
}


// walk on Map until the exit or until the loop found  
// receive map, the current pos, and direction 
bool walk (Map& map, PosDir pd){
	    
	pd.dir = getNextDir(pd.dir);  		// change direction, get next one
	
	bool out = false; 					// are we out the board ?
	
	while (1) {
        switch (pd.dir) {
            case Direction::Up:
                out = goUp(map, pd);
                break;
            case Direction::Right:
                out = goRight(map, pd);
                break;
            case Direction::Down:
                out = goDown(map, pd);
                break;
            case Direction::Left:
                out = goLeft(map, pd);
                break;
        }
			
		if (out){ 
			break; 				// we are out, stop or in loop 
		}
		
        // Increment direction (cyclically)
        pd.dir = getNextDir(pd.dir);  
	}
	#ifdef DEBUG
	printMap(map);
	clearX(map);
	#endif
		
	return true; 
}



int main (){
         
    //std::ifstream inputFile("input.txt"); // Open the input file
    std::ifstream inputFile("input-big.txt"); // Open the input file
    
	if (!inputFile) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1; // Exit with error code
    }
	
    std::string line;
	Map map {};  // playground  
	
	// read page ordering rules
	while (std::getline(inputFile, line)) {
		// remove new line char 
		//line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
		vector<char> v{}; 
		for (char c : line) {
			v.push_back(c); 
		}
		map.push_back(v);  		
	}
	
	MAP_L = map.size();			// x limit
	MAP_H = map[0].size(); 		// y limit 
	
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
	
	PosDir pd {pos, Direction::Up}; // init pos and direction
	
	while (true){
		if (goUp(map, pd, true)) break;		// check loop true
		pd.dir = getNextDir(pd.dir);  		// change direction, get next one		 
		if (goRight(map, pd, true)) break;
		pd.dir = getNextDir(pd.dir);  		// change direction, get next one
		if (goDown(map, pd, true)) break;
		pd.dir = getNextDir(pd.dir);  		// change direction, get next one
		if (goLeft(map, pd, true)) break;
		pd.dir = getNextDir(pd.dir);  		// change direction, get next one
		
		cout << "count : " << loopCount << endl; 
	}
	
	cout << "Result : " <<  loopCount << endl;
    inputFile.close(); // Close the file
    return 0;
}