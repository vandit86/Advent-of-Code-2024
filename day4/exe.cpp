#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <cstdlib>
#include <sstream>
#include <cctype> // For std::isdigit


/*
result part 1: 2406
*/

using namespace std; 


int countXMAS (std::vector<std::vector<char>>& matrix, int i, int j){
	
	int count {}; 
	const string PATTERN {"MAS"};
	string tmp {};
	// tmp.push_back();  
	// tmp.clear()
	
	// left
	if (j >= 3){
		for (int k = 1; k < 4; ++k) tmp.push_back(matrix[i][j-k]);
		if (PATTERN == tmp) ++count;
		tmp.clear(); 
	}
	
	// right
	if (j + 3 < matrix[i].size()){
		for (int k = 1; k < 4; ++k) tmp.push_back(matrix[i][j+k]);
		if (PATTERN == tmp) ++count;
		tmp.clear(); 
	}
	
	// up
	if (i >= 3){
		for (int k = 1; k < 4; ++k) tmp.push_back(matrix[i-k][j]);
		if (PATTERN == tmp) ++count;
		tmp.clear(); 
	}
	
	// down  
	if (i + 3 < matrix.size()){
		for (int k = 1; k < 4; ++k) tmp.push_back(matrix[i+k][j]);
		if (PATTERN == tmp) ++count;
		tmp.clear(); 
	}
	
	// left up 
	if (j >= 3 && i >= 3){
		for (int k = 1; k < 4; ++k) tmp.push_back(matrix[i-k][j-k]);
		if (PATTERN == tmp) ++count;
		tmp.clear(); 
	}
	
	// left down 
	if (j >= 3 && i + 3 < matrix.size()){
		for (int k = 1; k < 4; ++k) tmp.push_back(matrix[i+k][j-k]);
		if (PATTERN == tmp) ++count;
		tmp.clear(); 
	}
	
	// right up
	if (j + 3 < matrix[i].size() && i >= 3){
		for (int k = 1; k < 4; ++k) tmp.push_back(matrix[i-k][j+k]);
		if (PATTERN == tmp) ++count;
		tmp.clear(); 
	}
	
	// right
	if (j + 3 < matrix[i].size() && i + 3 < matrix.size()){
		for (int k = 1; k < 4; ++k) tmp.push_back(matrix[i+k][j+k]);
		if (PATTERN == tmp) ++count;
		tmp.clear(); 
	}
	
	return count; 
}


int main (){
         
    std::ifstream inputFile("input.txt"); // Open the input file
    if (!inputFile) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1; // Exit with error code
    }
	
	 
    unsigned long long res = 0u; 
    std::string line;
	std::vector<std::vector<char>> matrix; // store chars
	
	// read from file 
	while (std::getline(inputFile, line)) {
        std::vector<char> row;
        for (char c : line) {
            row.push_back(c);
        }
        matrix.push_back(row);
    }
	
	for (int i = 0; i < matrix.size(); ++i) {
       for (int j = 0; j < matrix[i].size(); ++j) {
		   
			if (matrix[i][j] == 'X'){
				res += countXMAS(matrix, i, j); 
			}  
	   }
	}
	
    cout << res << endl; 
    inputFile.close(); // Close the file
    return 0;
}