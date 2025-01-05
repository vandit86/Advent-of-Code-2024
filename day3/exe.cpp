#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <cstdlib>
#include <sstream>
#include <cctype> // For std::isdigit


using namespace std; 

bool allDigits(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

int main (){
         
    std::ifstream inputFile("input.txt"); // Open the input file
    if (!inputFile) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1; // Exit with error code
    }
    
    unsigned long long res = 0u; 
    std::string line;
      
    while (getline(inputFile, line)) { 
        
      
        const string pattern ("mul(");
        size_t pos = line.find(pattern); // Find first occurrence
        while (pos != string::npos && (pos + pattern.size() + 1 < line.size())) {
        
            string a{}, b{}; 
            int numA{}, numB{}; 
            
            pos = pos + pattern.size();
            
            // find first num 
            size_t a_pos = line.find(',' , pos);
            if (a_pos != string::npos){
               a = line.substr (pos , a_pos-pos); 
                
            }
            else {
                break;
            }
            
            if (a_pos + 1 < line.size()){
                a_pos ++ ; 
            }
            else break; 
            
            // get second num 
            size_t b_pos = line.find(')', a_pos);
            if (a_pos != string::npos){
               b = line.substr (a_pos , b_pos - a_pos); 
                
            }
            else {
                break;
            }
            
            cout << "pos = " << pos << " : " << a << " : " << b << endl; 
            
            if (allDigits(a) && allDigits(b)){
                numA = std::stoi(a);
                numB = std::stoi(b);
                res = res + numA * numB;  
            }   
            
            pos = line.find(pattern, pos+1); // Find next occurrence
        }      
    }
    
    cout << res << endl; 
    inputFile.close(); // Close the file
    return 0;
}