#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<math.h>

using namespace std;

float calc_average(vector<float> list)
{
    float sum = 0.0;
    for(int i=0; i<list.size(); i++){
        sum += list[i]; 
    }

    return sum/list.size();
}

float calc_SD(vector<float> list)
{
    float sum = 0.0;
    float average = calc_average(list);
    for(int i=0; i<list.size(); i++){
        sum += pow((list[i] - average),2); 
    }

    return sqrt(sum/list.size());
}

int main()
{
    ifstream ifs("weights.txt");
    if (ifs.fail()) {
        cerr << "fail" << endl;
        return -1;
    }

    //load text to array
    string str;
    vector< vector<string> > table; 
    while (getline(ifs, str))
    {
        string token;
        istringstream stream(str);
        vector<string> line;
        while(getline(stream,token,'\t')){
            if(token!=""){
                line.push_back(token);
            }
        }
        table.push_back(line);
    }

    //calc & output
    cout<< "\t average\t S.D\t "<<endl;
    for(int j=0; j<table[0].size(); j++){
        string label = table[0][j];

        //export column
        vector<float> array;
        for(int i=1; i<table.size(); i++){
            array.push_back(stof(table[i][j]));
        }

        float average = calc_average(array);
        float SD      = calc_SD(array);

        cout<< label << "\t" << average << "\t" << SD << endl;
    }
    return 0;
}