#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

typedef struct {
    int AA_length;
    std::string mol_name;
    std::string pepType;
} PeptidesStruct;
 
typedef  map< std::string , PeptidesStruct* > PEP_MAP; /* peptide descriptive of AA sequence and other information */

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


bool map_FromFile( std::string infile ,  PEP_MAP& result_map ){
 
    std::ifstream data(infile.c_str());

    std::string line;
    while (getline(data, line)){

        std::vector<std::string> columns = split(line, "\t");
        PeptidesStruct* pepData_s = new PeptidesStruct();
        pepData_s->pepType   = columns[0];
        pepData_s->mol_name  = columns[2];
        pepData_s->AA_length =  stoi(columns[3]);
        
        result_map.insert( PEP_MAP::value_type( columns[1].c_str() , pepData_s ) );
 
    }
    return true;
}
 
int main(int argc, char *argv[]){

    // awk -F '\t' '{print $1"\t"$2"\t"$3"\t"length($2)}' human_hla_epis.xls > test_structure_map.txt  ;

    if (argc == 1){
        cout << "Missing input File to read" << endl;
        return 1;
    }

    std::string filepath = argv[1];

    PEP_MAP TestMap_out;
    map_FromFile( filepath,   TestMap_out );
 
    PEP_MAP::iterator it = TestMap_out.begin();
    for (it = TestMap_out.begin(); it != TestMap_out.end(); ++it) {
        PeptidesStruct *ps = it->second;
        cout << it->first << '\t' << ps->mol_name << '\t' << ps->AA_length << endl; 
        
        delete ps;
    } 
    cout << endl; 
}
 
