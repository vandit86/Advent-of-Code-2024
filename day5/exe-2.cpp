#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm> 
#include <cstdlib>
#include <sstream>
#include <cctype> // For std::isdigit


/*
result part 1: 4959 
result part 2: 9614 (to hight)
*/

using namespace std; 

void parsePages (vector<int>& numbers, string line){
	
    std::stringstream ss(line);
    std::string temp;

    while (std::getline(ss, temp, ',')) {
        numbers.push_back(std::stoi(temp)); // Convert the substring to an integer
    }
}

void parseRule (unordered_map<int, vector<int>>& myRules, string& line){
	
	int first, second; 
	// Replace the delimiter '|' with a space or split directly
    std::replace(line.begin(), line.end(), '|', ' ');

    // Use a stringstream to extract the two integers
    std::stringstream ss(line);
    ss >> first;  
	ss >> second;
	
	auto key = first; 
	// count the weight of first number 
	if (myRules.find(key) == myRules.end()) {
		vector<int> v{};
		v.push_back(second); 
		myRules.emplace(key, v);
	}
	else {
		myRules[key].push_back(second); 
	}
	
}

void printVec(vector<int> vec){
	for (auto& i : vec){
		cout << i << " " ; 
	}
	cout << endl ; 
}

void orderPage (unordered_map<int, vector<int>>& rules, vector<int>& page){
	
	vector<int> newPage{};  
	
	// cout << "beore " << endl; 
	// printVec (page); 
	// cout << "after" << endl;
	
	// Iterating through the vector
    for (auto it = page.begin(); it != page.end(); ) {
		bool erase = true; 
		for (int i = 0; i < page.size() ; ++i){
			if (*it == i) continue;
			auto vec = rules[page[i]]; 
			if (std::find(vec.begin(), vec.end(), *it) != vec.end()) {
				erase = false; 
				break;
			}
		}
		if (erase){
			newPage.push_back(*it); 
			// Erase the current element and update the iterator
			page.erase(it); 
			it = page.begin(); 
		}
		else {
			++it; 
		}
    }
	
	page = newPage;
	//printVec (page); 
}

int main (){
         
    std::ifstream inputFile("input.txt"); // Open the input file
    if (!inputFile) {
        return 1; // Exit with error code
    }
	
    unsigned long long res = 0u; 
    std::string line;
	
	unordered_map<int, vector<int>> myRules; // store rules 
	
	// read page ordering rules
	while (std::getline(inputFile, line) && line.size()>1) {	
		parseRule (myRules , line); 		
	}
		
	// read pages to produce in each update
	while (std::getline(inputFile, line) && !line.empty()) {	
		vector<int> pages{};
		parsePages( pages, line); 
		
		bool rightOrder {true}; 
		for (int i = 0 ; i+1 < pages.size() ; ++i){
			
			auto key = pages[i];
			
			if (myRules.find(key) == myRules.end()) {
				rightOrder = false;
				cout<< "key not in map "<< endl; 
			}
			
			auto& vec = myRules[key]; // rules for one page
			auto it = std::find(vec.begin(), vec.end(), pages[i+1]);
			if (it == vec.end()) {
				rightOrder = false;  
			}				
		}
		
		if (!rightOrder) {
			orderPage (myRules, pages);
		}
		//printVec (pages);
		// should be ordered here 
		res += pages[pages.size()/2];
    }
	
	// for (auto& i : myRules){
		// cout << i.first << " : " ;
		// for (auto& j : i.second){
			// cout << j << " " ; 
		// }
		// cout << endl; 
	// }
	
    cout << res << endl; 
    inputFile.close(); // Close the file
    return 0;
}