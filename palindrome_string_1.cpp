#include <iostream>
#include <map> 
using namespace std; 

void reverseString(std::string s , std::string& s1_out) {
    s1_out = s;
    int l=s.size();
    int lo=0;
    int hi=l-1;
    for(int i=lo,j=hi;i<j;i++,j--){
        char c=s[j];
        s1_out[j]=s[i];
        s1_out[i]=c;
    }
}

// Function to return the number of distinct palindromic sub-strings 
// in given string s 
int palindromeSubStrs(std::string s) 
{ 
  
    // To store the positions of palindromic sub-strings 
    int ss = s.size();
    int st, end, i, j, len; 
  
    // Map to store the sub-strings 
    map<string, bool> m; 

    // Find palindromic sub-strings of length>=3 
    for (len = 1; len <= ss; len++) { 
        for (st = 0; st <= ss - len; st++) { 
            std::string s1 = s.substr(st, len);
            std::string s2 = s.substr(st, len);
            // reverse string s2
            std::string str_rev ;
            reverseString(s2, str_rev);
            
            if (s1 == str_rev) { 
                m[s1] = 1; 
            } 
        } 
    } 
    // Return the count of distinct palindromes 
    return m.size(); 
} 
  
// Driver code 
int main() { 
    string s = "abaaa"; 
    cout << palindromeSubStrs(s); 
  
    return 0; 
} 
