#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

double wij[102][102] = {0};

double calcE(int student[102]){

    double score = 0;
    for (int i = 1; i < 102; i++)
    {
        for (int j = i + 1; j < 102; j++)
        {
            score += wij[i][j] * (student[i] ? 1 : -1) * (student[j] ? 1 : -1);
        }
    }
    return score;
}

int main(){
    // the first index is meaningless 

    // this is the 562000000th group
    // int group[102] = {4,0,0,0,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    // from GA/elite 727.528
    // int group[102] = {0,0,1,1,0,1,0,1,0,1,1,0,1,1,1,0,0,1,1,0,1,1,1,1,0,1,1,1,0,1,0,0,1,1,0,1,1,0,0,1,0,1,0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,0,1,1,1,1,0,0,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0};

    // from GA/bestScoreList/ 742
    int group[102] = {0,0,1,1,0,1,1,0,0,1,1,0,0,0,1,0,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,0,1,1,1,1,0,1,1,0,0,0,1,0,0,1,0,1,1,1,1,1,0,0,0,1,1,1,0};
    for (int i = 0; i < 5050; i++)
    {
        int n, m;
        double w;
        cin >> n >> m >> w;
        wij[n][m] = w;
        wij[m][n] = w;
    }

//    int student[102] = {0,0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0};
//    cout << calcE(student) << endl;

    int counter = 0;
    double max = calcE(group);
    cout << max << endl;
    while(true){
        // next group
        group[0]++;
        for(int i=0;i<101;i++){
            if(group[i] == 2){
                group[i] = 0;
                group[i+1]++;
            }
        }

        double currentE = calcE(group);
        if(currentE > max){
            // print group
            for(int i=1;i<102;i++){
                cout << group[i] ;
            }
            cout << endl;
            cout << currentE << endl;
            // write file
            ofstream MyFile("result.txt");
            for(int i=1;i<102;i++){
                MyFile << group[i];
            }
            MyFile.close();
        }
        if(counter % 1000000 == 0){
            cout << "current: " << counter << endl;
            cout << "Max value: " << max << endl;
            for(int i=1;i<102;i++){
                cout << group[i] << "," ;
            }
            cout << endl;
        }
        counter++;
    }
    
    return 0;
}