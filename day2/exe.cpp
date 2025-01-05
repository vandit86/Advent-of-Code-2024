#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // For std::sort
#include <cstdlib>
#include <sstream>


using namespace std; 

int main (){
         
    std::ifstream inputFile("input.txt"); // Open the input file
    if (!inputFile) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1; // Exit with error code
    }
    
    unsigned long long res = 0u; 
    std::string line;
    int a, b; 
    
    while (getline(inputFile, line)) { 
        vector<int> row;
        stringstream ss(line);   
        while (ss >> a) {
            row.push_back(a);
        }
        int mul = (row[0] < row[1])? -1 : 1;
        bool safe = true; 
        for (int i = 0 ; i < row.size()-1; ++i){
            if (row[i] - row[i+1] != 1*mul  && row[i] - row[i+1] != 2*mul && row[i] - row[i+1] != 3*mul){
                safe = false; 
                break; 
            } 
        }
        if (safe) res ++;      
    }
    
    cout << res << endl; 
    inputFile.close(); // Close the file
    return 0;
}