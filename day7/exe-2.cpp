#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm> 
#include <cstdlib>
#include <sstream>
#include <cctype> // For std::isdigit
#include <cassert>

using namespace std; 
/*

https://adventofcode.com/2024/day/7

for debug print : g++ -DDEBUG -o exe exe.cpp
for GDB 		: g++ -DDEBUG -g -o exe exe-2.cpp
run GDB 		: gdb ./exe
optimization 	: g++ -O2 -o exe exe-2.cpp

result part 1: 303876485655
result part 2: 146111650210682  

*/

using ull=unsigned long long; 

void printVector(vector<int>& v){
	cout << endl; 
	for(const auto& i : v){
		cout << i << " "; 
	}
	cout << endl; 
}

// [out] res -> first int in line, expected value
vector<ull> extractIntsFromString(const std::string& input, ull& res) {
    std::vector<ull> numbers; 
	std::stringstream ss(input); 
    ull number;
    char delimiter; 

    // Extract the first integer (before the colon)
    ss >> res; 
    ss >> delimiter; // Skip the colon

    // Extract the remaining integers after the colon
    while (ss >> number) {
        numbers.push_back(number);
    }

    return numbers;
}



ull concatTwoNums (ull num1, ull num2){
	// Convert integers to strings
	std::string str1 = std::to_string(num1);
	std::string str2 = std::to_string(num2);

	  // Concatenate strings
	std::string str = str1 + str2;

	return std::stoull(str); 
}

bool checkEquation (vector<ull> nums, ull testVal, bool concat){
	std::vector<ull> vec1;
	vec1.push_back(nums[0]); 
	for (int i = 1; i < nums.size(); ++i){
		std::vector<ull> tmp; 					// temp vec
		ull num = nums[i]; 						// next num  
		
		for (int j = 0; j < vec1.size(); ++j){
			
			// concatenation Part 2 
			if (concat){
				vector<ull> tmp2;
				auto tmpNum = concatTwoNums(vec1[j], num); 
				tmp2.push_back(tmpNum); 
				for (int k = i+1; k < nums.size(); k++){
					tmp2.push_back(nums[k]); 
				}
				if (checkEquation (tmp2, testVal, true)) return true; 
			}
			
			tmp.push_back(vec1[j] + num);		// '+'
			tmp.push_back(vec1[j] * num);		// '*'
		}
		vec1 = tmp; 
	}
	for (const auto& i : vec1){
		if (i == testVal) return true; 
	}
	return false; 
}



int main (){
         
    //std::ifstream inputFile("input.txt"); // Open the input file
    std::ifstream inputFile("input-big.txt"); // Open the input file
    
	if (!inputFile) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1; // Exit with error code
    }
	
    std::string line;
	ull result{};
	int linesCount{};  
	
	// read page ordering rules
	while (std::getline(inputFile, line)) {
		ull testVal {}; 
		linesCount++; 
		vector<ull> nums = extractIntsFromString (line,testVal); 
		
		if (checkEquation(nums, testVal, true)){
			if (result + testVal <= std::numeric_limits<unsigned long long>::max()){
				result += testVal;
				cout << result << endl; 
			}
			else {
				cout << "very lasge val"<< endl; 
			}
		}
		//printVector(nums); 
	}
	
	cout << "Lines:" << linesCount << endl;
	cout << "Final:" << result << endl;
	// 18446744073709551615
	cout << std::numeric_limits<unsigned long long>::max() << endl; 
	
}