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

result part 2:  6493634986625 
				
*/

using namespace std; 

using ull = unsigned long long; 


void printVec (vector<int>& vec){
	for (const auto& i : vec){
		printf(" %d ", i); 
	}
	printf ("\n"); 
}
/*
To calculate the checksum, add up the result of multiplying each of these blocks' position with the file ID number it contains. The leftmost block is in position 0. If a block contains free space, skip it instead.
*/

ull calculateChecksum (vector<int>& vec){
	ull res = 0ULL;
	
	for (int i = 0 ; i < vec.size(); ++i){
		
		if (vec[i] >= 0) res += i*vec[i]; 
	}
	
	return res; 
}

/*
The eager amphipod already has a new plan: rather than move individual blocks, he'd like to try compacting the files on his disk by moving whole files instead.

This time, attempt to move whole files to the leftmost span of free space blocks that could fit the file. Attempt to move each file exactly once in order of decreasing file ID number starting with the file with the highest file ID number. If there is no span of free space to the left of a file that is large enough to fit the file, the file does not move.

The first example from above now proceeds differently:

00...111...2...333.44.5555.6666.777.888899
0099.111...2...333.44.5555.6666.777.8888..
0099.1117772...333.44.5555.6666.....8888..
0099.111777244.333....5555.6666.....8888..
00992111777.44.333....5555.6666.....8888..
*/

void makeFragment(vector<int>& data){
	
	int idB = data.size()-1; 
	int mID = 1000000; 

	while (idB > 0){
		while (data[idB] < 0) --idB;	// find num pos
		if (idB <= 0) break;  			// no num left to move
		
		int cNms = 1; 	 			// counter for block size 
		int blockID = data[idB]; 	// block ID
		// count block size 
		while ((idB - cNms) > 0 && data[idB - cNms] == blockID ) ++cNms; 
		
		// skip previosly moved ID
		if ( blockID < mID) {			
			int limit = idB - cNms + 1; 
			// try to find the place to the block 
			for (int i = 0 ; i < limit ; ++i){
				// its a space
				if (data[i] < 0){
					// count free space
					int cSps = 1;    
					while (data[cSps + i] < 0 && (cSps + i) < limit) ++cSps;   
							
					if (cSps >= cNms) {
						for (int k = 0; k < cNms; ++k){
							data[i + k] = blockID; 
							data[idB - k] = -1;
						}
						break; 					// we find the place 
					}
				}		
			}
			mID = blockID; // update last ID  
		} 
		idB = (idB - cNms); 
	}
	return;  
}

int main (){
         
    //std::ifstream inputFile("input.txt"); // Open the input file
    std::ifstream inputFile("input-big.txt"); // Open the input file
    
	if (!inputFile) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1; // Exit with error code
    }
	
	// -1 for the '.'
	vector<int> data{}; 

	unsigned long long result{}; 
	char ch {}; 
	int id {}; // total chars readed 
	bool space = false; 
	
	// read page ordering rules
	while (inputFile.get(ch)) {
		if (std::isdigit(ch)){
			int put {}; 
			if (!space) put = id++; 
			else put = -1 ;
			
			for (char i = 0; i < ch - '0' ; ++i){
				data.push_back(put); 
			}
			space = !space;  
		}  		
	}
	
	
	//printVec(data); 
	makeFragment (data); 
	
	//printVec(data); 
	auto res = calculateChecksum (data); 
	
	printf ("result %llu \n", res); 
	//cout << "result: " << res << endl;   
	
    return 0;
}