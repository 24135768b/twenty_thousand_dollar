#include<iostream>
#include <iomanip>
#include<vector>
using namespace std; 
int main(){

    int student [46][102];
    float probabilityMatrix [102][102] = {0};

    for(int i=0;i<46;++i){
        for(int j=0;j<=101;++j){
            cin >> student[i][j];
        }
    }
    
    for(int i=1;i<=101;++i){
        for(int j=1;j<=101;++j){

            double count = 0;
            for(int k=0;k<46;++k){
                if(student[k][i] == student[k][j] )
                    count++;
            }
            probabilityMatrix[i][j] = count/46.0;

        }
    }
/*
    // write probability matrix to file

    for(int i=1;i<=101;++i){
        for(int j=1;j<=101;++j){
            cout << fixed << setprecision(2) <<  probabilityMatrix[i][j] << " ";
        }
        cout << endl;
    }
*/


    for(int i=1;i<=101;++i){
        int count = 0;
        vector<int> friends;
        for(int j=1;j<=101;++j){
            
            if(probabilityMatrix[i][j] > 0.75){
                count++;
                friends.push_back(j);
            }
        }
        if(count < 15){
            cout << "orphan: " << i << " count: " << count << endl;
            
        }else if (count < 30) {
            cout << "small group: " << i << " count: " << count << endl;
        }else{
            cout << "big group: " << i << " count: " << count << endl;
        }

        cout << "friends: " ;
        for(int i=0;i<friends.size();++i){
            cout << friends[i] << " ";
        }
        cout << endl;
    }
    


    return 0;

}