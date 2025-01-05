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

bool doOperation (const string str, bool doOp){
    const string dontStr ("don't()"); 
    const string doStr  ("do()"); 
     // Find the last occurrence of the pattern
    auto last_pos_do = str.rfind(doStr);
    auto last_pos_dont = str.rfind(dontStr);
    
    if (last_pos_do != std::string::npos && last_pos_dont != std::string::npos )
        return last_pos_do > last_pos_dont;
    else if (last_pos_do == std::string::npos && last_pos_dont != std::string::npos)
        return false;
    else if (last_pos_do != std::string::npos && last_pos_dont == std::string::npos)
        return true;
    else return doOp;   // don't change current operation 
}

/* 

result part 1 : 166357705 
result part 2 : 88811886

*/

int main (){
         
    std::ifstream inputFile("input.txt"); // Open the input file
    if (!inputFile) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1; // Exit with error code
    }
    
    unsigned long long res = 0u; 
    std::string line;
    
    bool doOp = true; 
    const string pattern ("mul(");
      
    while (getline(inputFile, line)) { 
        
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
            
            if (allDigits(a) && allDigits(b)){
                numA = std::stoi(a);
                numB = std::stoi(b);
                
                string opStr = line.substr(0, pos);
                doOp = doOperation(opStr, doOp);  
                if (doOp){
                    res = res + numA * numB;  
                } 
            }   
            
            pos = line.find(pattern, pos+1); // Find next occurrence
        }      
    }
    
    cout << res << endl; 
    inputFile.close(); // Close the file
    return 0;
}