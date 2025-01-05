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

 11728063527  - low 
result part 1:

result part 2: 

*/

using ull=unsigned long long; 

// [out] res -> first int in line, expected value
vector<int> extractIntsFromString(const std::string& input, ull& res) {
    std::vector<int> numbers; 
	std::stringstream ss(input); 
    int number;
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


bool checkEquation (vector<int> nums, ull testVal){
	std::vector<ull> vec1;
	vec1.push_back(nums[0]); 
	for (int i = 1; i < nums.size(); ++i){
		std::vector<ull> tmp; 					// temp vec
		ull num = nums[i]; 						// next num  
		for (int j = 0; j < vec1.size(); ++j){
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

ull concatTwoNums (ull num1, ull num2){
	// Convert integers to strings
	std::string str1 = std::to_string(num1);
	std::string str2 = std::to_string(num2);

	  // Concatenate strings
	std::string str = str1 + str2;

	return std::stoull(str); 
}

// now we have concatenetion 
bool checkVectors (vector<int> nums, ull testVal){
	
	for (int i = 0; i < nums.size(); ++i){
		
		vector<ull> tmp{}; 
		
		for (int j = 0; j < nums.size(); ++j){
			ull num = nums[j]; 
			if (j > 0 && j == i){
				tmp.pop_back(); // remove
				num = concatTwoNums (nums[j-1], nums[j]);
			}
			tmp.push_back(num); 
		}
		
		if (checkEquation(tmp,testVal))
			return true; 
	}
	return false; 
}

void printVector(vector<int>& v){
	cout << endl; 
	for(const auto& i : v){
		cout << i << " "; 
	}
	cout << endl; 
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
		vector<int> nums = extractIntsFromString (line,testVal); 
		
		if (checkEquation(nums, testVal)){
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