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

float t_test(vector<float> list1, vector<float> list2)
{
    float avr1 = calc_average(list1);
    float avr2 = calc_average(list2);
    float SD1  = calc_SD(list1);
    float SD2  = calc_SD(list2);
    float n1   = list1.size();
    float n2   = list2.size();

    float poolV = ( (n1-1)*pow(SD1,2) + (n2-1)*pow(SD2,2) ) / (n1+n2-2); 
    float t = (avr1 - avr2) / sqrt(poolV * (1/n1 + 1/n2));
    return t;
}

int main(int argc, char *argv[])
{
    ifstream ifs(argv[1]);
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

        cout<< label << "\t" << average << "\t\t" << SD << endl;
    }
    cout << endl;

    if(table[0].size()==2){
        //export 2column
        vector<float> array1;
        vector<float> array2;
        for(int i=1; i<table.size(); i++){
            array1.push_back(stof(table[i][0]));
            array2.push_back(stof(table[i][1]));
        }
        cout<< "t = " << "\t" << t_test(array1,array2) << "\t" << endl;
        cout << endl;
    }
    return 0;
}