#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
using namespace std;

std::vector<std::string> split(std::string str,std::string pattern){

    std::string::size_type pos;
    std::vector<std::string> result;

    str+=pattern;
    int size=str.size();

    for(int i=0; i<size; i++){

        pos=str.find(pattern,i);
        if(pos<size){
            std::string s=str.substr(i,pos-i);

            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}

void readEpitopeF(std::string hla_e_file, std::string& res, map<int, std::string>& fragments_AA){
    std::stringstream epitopes_stream;
    std::ifstream data(hla_e_file.c_str());

    std::string line;
    int pep_start = 0;
    int key_of_pep;
    std::string tmp_peptide;
    while(getline(data, line)){
        if (line.substr(0,7) != "Epitope"){
            std::vector<std::string> columns = split(line, "\t"); 
            epitopes_stream << columns[1] + "|";
            
            if (columns[1].length() <=6){
            
                tmp_peptide = columns[1]  + '-' + columns[2];
                key_of_pep = pep_start ;
                fragments_AA.insert(pair<int, std::string>(key_of_pep, tmp_peptide ));
            } else {
            
                for (int i=0 ; i<= columns[1].length()-6; i++ ) {
                    tmp_peptide = columns[1].substr(i, 6) + '-' + columns[2];
                    key_of_pep = pep_start + i;
                    fragments_AA.insert(pair<int, std::string>(key_of_pep, tmp_peptide ));   

                }
            }
            pep_start += columns[1].length() + 1;
        }
    }
    res = epitopes_stream.str();
    data.close();
}

std::vector<std::string> cutPeptide(std::string pep, int aa_len){
    std::vector<std::string> result;
    int size = pep.size();

    for(int i=0; i <= size - aa_len; i++){

        std::string s = pep.substr(i, aa_len);
        result.push_back(s);
    }
    return result;
}

int main(int argc, char *argv[]){
    void readEpitopeF(std::string hla_e_file, std::string& res, map<int, std::string>& fragments_AA);
    std::vector<std::string> split(std::string str,std::string pattern);
    std::vector<std::string> cutPeptide(std::string pep, int aa_len);

    if (argc == 1){
        cout << "Missing input File to read" << endl;
        return 1;
    }

    std::string filepath = argv[1];
    std::string epistring ;
    map<int, std::string> map_of_allPeps;

    readEpitopeF(filepath, epistring, map_of_allPeps);
    cout << "Epitopes total length is " << epistring.length() << endl;

    std::string::size_type position;
    map<int, std::string>::iterator pep_search;
    //   ---------------------------
    //
    std::string mut_line; 
    
    ifstream srcFile("../mutation_AA.xls",ios::in); 
    if(!srcFile) { 
        cout << "error opening cosmic mutation file." << endl;
        return 0;
    }

    std::vector<std::string> peps;
    while (getline(srcFile, mut_line)) {
        std::vector<std::string> cols = split(mut_line, "\t");

        std::string pep_9  = cols[5];

        peps = cutPeptide(pep_9, 8);
        for (int i=0;  i < peps.size(); i++){
            std::string test_pep1 = peps[i];     
            position = epistring.find(test_pep1);
            pep_search = map_of_allPeps.find(position);
            if (pep_search != map_of_allPeps.end()){
                cout << cols[3] << "\t";
                cout << test_pep1 << " Found " << pep_search->first << " " ;
                cout << pep_search->second << endl;
            }
        }
    }
    return 0;
}

