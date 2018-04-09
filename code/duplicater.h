#ifndef DUPLICATER
#define DUPLICATER

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

void duplicater(string file){
    fstream input,duplicate;
    input.open(file , ios::in);
    duplicate.open(file + ".dup" , ios::out);
    string lines[1000][5];
    int len[1000]={0};

    while(!input.eof()){
        string temp;
        getline(input , temp);
        
        size_t n = temp.find("NET");
        size_t n2 = temp.find("Net");
        if( n2 != string::npos || n != string::npos){
            if(n2 != string::npos)
                temp.replace(n2 ,3 , "" );
            else
                temp.replace(n ,3 , "" );
            
            n = temp.find("Net");
            n2 = temp.find("NET");
            
            if( n2 != string::npos || n != string::npos){
                if(n2 != string::npos)
                    temp.replace(n2 ,3 , "" );
                else
                    temp.replace(n ,3 , "" );
                
            }        
        }

        n = temp.find(" ");

        if(n != string::npos && lines[stoi(temp.substr(1,n-1))][len[stoi(temp.substr(1,n-1))]] == "" ){
            lines[stoi(temp.substr(1,n-1))][len[stoi(temp.substr(1,n-1))]] = temp ;
            len[stoi(temp.substr(1,n-1))]++;        
        }
    }


    for(int i=0;i<100;i++){
        for(int j=0;j<len[i];j++){
            // cout<<lines.size()<<endl;
            // if(lines[i][j] != "")
            duplicate<<lines[i][j]<<endl;
        }
    }


    input.close();
    duplicate.close();
}


#endif
