#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <cstdlib>
#include <sstream>
#include <cctype> // For std::isdigit


/*
result part 1: 2406
result part 2: 1807
*/

using namespace std; 


int countXMAS (std::vector<std::vector<char>>& matrix, int i, int j){
	
	int count {}; 
	const string MAS {"MAS"};
	const string SAM {"SAM"};
	string tmp1 {};
	string tmp2 {};
	// tmp.push_back();  
	// tmp.clear()
	
	// check bounds
	if (j > 0 && j + 1 < matrix[i].size() && i > 0 && i + 1 < matrix.size()){
		
		// word 1 
		tmp1.push_back(matrix[i-1][j-1]);
		tmp1.push_back('A');
		tmp1.push_back(matrix[i+1][j+1]);
		
		// word 2
		tmp2.push_back(matrix[i-1][j+1]);
		tmp2.push_back('A');
		tmp2.push_back(matrix[i+1][j-1]);
		
		if (tmp1 == MAS || tmp1 == SAM){
			if (tmp2 == MAS || tmp2 == SAM){
				++count; 
			}
		}
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
		   
			if (matrix[i][j] == 'A'){
				res += countXMAS(matrix, i, j); 
			}  
	   }
	}
	
    cout << res << endl; 
    inputFile.close(); // Close the file
    return 0;
}