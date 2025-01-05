#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // For std::sort
#include <cstdlib>


using namespace std; 

int main (){
         
    std::ifstream inputFile("input.txt"); // Open the input file
    if (!inputFile) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1; // Exit with error code
    }
    
    vector<int> first; 
    vector<int> second; 
     
    int a, b; 
    while (inputFile >> a >> b) {
        first.push_back(a);
        second.push_back(b);     
    }
   
   std::sort (first.begin(), first.end());
   std::sort (second.begin(), second.end());
   
   unsigned long long res = 0u; 
   
   for (int i = 0 ; i < second.size(); i++){
        res+=std::abs(first[i] - second[i]); 
   }
     
    cout << res << endl; 
    inputFile.close(); // Close the file
    return 0;
}