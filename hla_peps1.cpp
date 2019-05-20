#include <iostream>
#include <fstream>
#include <list>
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

void pepMap_FromFile( std::string infile , map< std::string, list<std::string> >& result_map ){
 
    std::ifstream data(infile.c_str());
    std::string line;
    map< std::string, list<std::string> >::iterator it;

    while (getline(data, line)){

        std::vector<std::string> columns = split(line, "\t");
        it = result_map.find(columns[1]);
        if (it == result_map.end()){
            list<std::string> list1 = {};
            list1.push_back(columns[2]); 
            result_map.insert(pair<std::string, list<std::string>>(columns[1], list1));
            
        } else {
            list<std::string>& list2 = it->second;
            list2.push_back(columns[2]);
            result_map.insert(pair<std::string, list<std::string>>(columns[1], list2));
        }
 
    }
}
 
int main(int argc, char *argv[]){
    if (argc == 1){
        cout << "Missing input File to read" << endl;
        return 1;
    }
    
    // Compile  :  cl hla_peps1.cpp
    // Usage    :  hla_peps1.exe test_d1.txt

    std::string filepath = argv[1];
    map< std::string, list<std::string> > TestMap_out;
    pepMap_FromFile( filepath,   TestMap_out );
 
    map< std::string, list<std::string> >::iterator it = TestMap_out.begin();
    for (it = TestMap_out.begin(); it != TestMap_out.end(); ++it) {
        // list<std::string>& hlaList = it ->second;
        list<std::string> hlaList = (*it).second;
        cout << it->first;
        for(list<std::string>::iterator hla_it=hlaList.begin(); hla_it!=hlaList.end();hla_it++)  {
            cout<< '\t' << *hla_it << " "; 
        }
        cout  << endl;
    } 
    cout << endl; 
}
 
