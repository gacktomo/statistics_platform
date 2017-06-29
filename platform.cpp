#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>

int main()
{
    std::ifstream ifs("weights.txt");
    if (ifs.fail())
    {
        std::cerr << "fail" << std::endl;
        return -1;
    }

    std::string str;
    std::vector< std::vector<std::string> > table; 
    while (getline(ifs, str))
    {
        std::string token;
        std::istringstream stream(str);
        std::vector<std::string> line;
        while(getline(stream,token,'\t')){
            if(token!=""){
                line.push_back(token);
            }
        }
        table.push_back(line);
    }

    //output
    for(int j=0; j<table[0].size(); j++){
        float temp = 0;
        for(int i=1; i<table.size(); i++){
            temp += stof(table[i][j]); 
        }

        if(j==7){
            std::cout<<table[0][j] << "\t" << temp/(table.size()-1)<<"%"<<std::endl;
        }else{
            std::cout<<table[0][j] << "\t" << temp/(table.size()-1)<<std::endl;
        }
    }
    return 0;
}