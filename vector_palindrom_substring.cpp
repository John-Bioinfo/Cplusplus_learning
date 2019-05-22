#include <iostream>
#include <vector>
#include <map> 
using namespace std; 

// Function to return the number of distinct palindromic sub-strings 
// in given string s 
int palindromeSubStrs(std::string s) { 
    // To store the positions of palindromic sub-strings 
    int ss = s.size();
    std::vector<std::vector<int>> dp(ss, std::vector<int>(ss));
    for (int i=0; i<ss;i++){
        std::fill( dp[i].begin(), dp[i].end(), 0 );
    }
    int st, end, i, j, len; 
  
    // Map to store the sub-strings 
    map<string, bool> m; 
    for (i = 0; i < s.size(); i++) { 
  
        // Sub-strings of length 1 are palindromes 
        dp.at(i).at(i) = 1; 
  
        // Store continuous palindromic sub-strings 
        m[string(s.begin() + i, s.begin() + i + 1)] = 1; 
    } 
  
    // Store palindromes of size 2 
    for (i = 0; i < s.size() - 1; i++) { 
        if (s[i] == s[i + 1]) { 
            dp.at(i).at(i + 1) = 1; 
            m[string(s.begin() + i, s.begin() + i + 2)] = 1; 
        } 
  
        // If str[i...(i+1)] is not a palindromic 
        // then set dp[i][i + 1] = 0 
        else { 
            dp.at(i).at(i + 1) = 0; 
        } 
    } 
  
    // Find palindromic sub-strings of length>=3 
    for (len = 3; len <= s.size(); len++) { 
        for (st = 0; st <= s.size() - len; st++) { 
  
            // End of palindromic substring 
            end = st + len - 1; 
  
            // If s[start] == s[end] and 
            // dp[start+1][end-1] is already palindrome 
            // then s[start....end] is also a palindrome 
            if (s[st] == s[end] && dp.at(st + 1).at(end - 1)) { 
  
                // Set dp[start][end] = 1 
                dp.at(st).at(end) = 1; 
                m[string(s.begin() + st, s.begin() + end + 1)] = 1; 
            } 
  
            // Not a palindrome 
            else
                dp.at(st).at(end) = 0; 
        } 
    } 
  
    // Return the count of distinct palindromes 
    return m.size(); 
} 
  
// Driver code 
int main() 
{ 
    string s = "abaaa"; 
    cout << palindromeSubStrs(s); 
  
    return 0; 
} 
