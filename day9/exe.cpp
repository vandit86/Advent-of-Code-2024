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
So, a disk map like 12345 would represent a one-block file, two blocks of free space, a three-block file, four blocks of free space, and then a five-block file.
Each file on disk also has an ID number based on the order of the files as they appear before they are rearranged, starting with ID 0. So, the disk map 12345 has three files: a one-block file with ID 0, a three-block file with ID 1, and a five-block file with ID 2. Using one character for each block where digits are the file ID and . is free space, the disk map 12345 represents these individual blocks:

0..111....22222
*/

void makeFragment(vector<int>& data){
	
	size_t idB = data.size()-1; 
	
	for (size_t i = 0 ; i < idB; ++i){
		
		// its a space , fill with last 
		if (data[i] < 0){
			while (data[idB] < 0) --idB;	// find num pos
			if (idB <= i) break;  			// no num left to move
			data[i] = data[idB]; 
			data[idB] = -1;
			--idB;  
		}		
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
	cout << "result: " << res << endl;   
	
    return 0;
}