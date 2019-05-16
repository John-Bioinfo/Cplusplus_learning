#include <iostream>
#include <vector>
#include <string>

using namespace std;

std::vector<std::string> cutPeptide(std::string pep, int aa_len){
    std::vector<std::string> result;
    int size = pep.size();

    for(int i=0; i <= size - aa_len; i++){

        std::string s = pep.substr(i, aa_len);
        result.push_back(s);
    }
    return result;
}

int main(){
    
    std::vector<std::string> cutPeptide(std::string pep, int aa_len);

    std::string test_pep1 = "KVYGTVLSR";
    std::vector<std::string> peptides = cutPeptide(test_pep1, 8);

    for (std::vector<std::string>::iterator p = peptides.begin(); p != peptides.end(); ++p){
        std::string p_str = *p;
        cout << p_str << endl;
    }
    
    for(int i=0;i<peptides.size();i++)  {    
        cout<< peptides[i]<<"\t";    
    }    
    cout<<endl; 
}
