#include<iostream>
#include<vector>
#include<cmath>
#include <iomanip>
#include<fstream>
using namespace std;

void comb(int n, int m, int group[102]);
double calcE(int student[102]);

double wij[102][102] = {0};
float maximum = 742;
int counter = 0;

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

// n: number of swapping students 
// m: number of total students
void comb(int n, int m, int group[102]) {
    vector < int > list;
    for (int i = 0; i < n; ++i) {
        list.push_back(i);
    }
    --list[n - 1];

    // all combinations
    do {
        for (int i = n - 1; i >= 0; --i) {
            if (list[i] < m + i - n) {
                ++list[i];
                for (int j = i + 1; j < n; ++j) {
                    list[j] = list[i] + j - i;
                }
                break;
            }
        }
        // for each combination: 

		// print the current combination
        /*
        for (int i = 0; i < n; ++i) {
            cout << list[i] + 1 << ' ';
        }
        cout << endl;
        */
        
		// binary generator for every combination

        // save the state
        vector<int> temp;
        for(int j = 0; j < n; ++j) {
            temp.push_back(group[list[j]]);

        }

        // generate all binary strings

        // start from 000....0 to 111...1
        for(int j = 0; j < pow(2,n); ++j) {

            // mistyrious bitwise operation
            for(int i = 0; i < n; ++i) {
                group[list[i]] = (j >> i) & 1;
            }

            // calcE
            float currentValue = calcE(group);
            // cout << currentValue << endl;

            if (currentValue > maximum) {
                maximum = currentValue;
                cout << "New Maximum:"  << endl;
                cout << setprecision(10) << currentValue << endl;

                // print
                for(int i=0;i<m;++i){ // m = 101 or 102
                    cout << group[i] ;
                }
                cout << endl;

                // write file
                ofstream MyFile("result.txt");
                for(int i=1;i<102;i++){
                    MyFile << group[i];
                }
                MyFile << endl;
                MyFile << currentValue;
                MyFile.close();
            }
            if(counter % 100000 == 0)
                cout << counter << endl;
            counter++;
                
        }


        // restore the state
        for(int j = 0; j < n; ++j) {
            group[list[j]] = temp[j];
        }

    } while (list[0] < (m - n));
}

int main() {

    // input Wij
    for (int i = 0; i < 5050; i++){
        int n, m;
        double w;
        cin >> n >> m >> w;
        wij[n][m] = w;
        wij[m][n] = w;
    }

    int n = 4;
    int group[102] = {0,1,0,0,1,0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,0,0,0,0,1,0,0,1,1,1,0,1,1,0,1,0,0,0,0,0,1,1,1,0,0,0,1};
    // int group[102] = {0,0,1,1,0,1,1,0,0,1,1,0,0,0,1,0,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,0,1,1,1,1,0,1,1,0,0,0,1,0,0,1,0,1,1,1,1,1,0,0,0,1,1,1,0};
    comb(n, 102, group);
    cout << "result: " << maximum << endl;
    return 0;
}
/*
int main(){
    // the first index is meaningless 

    // this is the 562000000th group
    // int group[102] = {4,0,0,0,0,0,0,1,1,1,1,1,0,1,0,0,0,1,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    // from GA/elite 727.528 after 649000000
    int group[102] = {0,0,1,1,0,1,1,1,0,1,0,1,0,1,1,0,1,0,1,0,0,1,0,1,1,0,1,0,1,0,1,0,1,1,0,1,1,0,0,1,0,1,0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,0,1,1,1,1,0,0,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0};


    // from GA/bestScoreList/ 742
    // int group[102] = {0,0,1,1,0,1,1,0,0,1,1,0,0,0,1,0,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,0,1,1,1,1,0,1,1,0,0,0,1,0,0,1,0,1,1,1,1,1,0,0,0,1,1,1,0};
    current: -1098000000
    Max value: 742.61
    0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,0,1,1,1,0,1,0,1,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,0,1,1,1,1,0,1,1,0,0,0,1,0,0,1,0,1,1,1,1,1,0,0,0,1,1,1,0,
    
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
            max = currentE;
            // print group
            for(int i=1;i<102;i++){
                cout << group[i] ;
            }
            cout << endl;
            cout << currentE << endl;
            // write file
            ofstream MyFile("result.txt");
            for(int i=1;i<102;i++){
                MyFile << group[i] << " ";
            }
            MyFile << endl;
            MyFile << currentE << endl;
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
}*/