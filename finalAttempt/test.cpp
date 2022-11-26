#include<iostream>
#include<iomanip>
#include<cmath>
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
    for (int i = 0; i < 5050; i++){
        int n, m;
        double w;
        cin >> n >> m >> w;
        wij[n][m] = w;
        wij[m][n] = w;
    }
    int group1[41] = {3,9,10,14,17,18,20,21,22,23,25,29,33,35,41,47,51,58,59,60,61,62,66,67,69,73,75,76,77,78,81,85,88,90,91,92,93,94,98,99,100};
    int group2[41] = {1,4,8,11,13,15,16,24,28,30,31,32,34,36,37,38,40,42,46,48,50,52,53,54,55,56,63,64,70,71,72,74,79,82,83,84,87,95,96,97,101};
    int orphans[19] = {2,5,6,7,12,19,26,27,39,43,44,45,49,57,65,68,80,86,89};
    int solution[102] = {0};
    for(int i=0;i<41;i++){
        solution[group1[i]] = 1;
        solution[group2[i]] = 0;
    }
    for(int i=0;i<19;i++){
        solution[orphans[i]] = 2;
        
    }
    for(int i=0;i<102;++i){
        cout << solution[i] << " ";
    }
    cout << endl;
    double score = calcE(solution);
    cout << setprecision(10) << score << endl;

    // generate all binary strings of length 19
    // for each string, calculate the score
    // keep track of the best score and the corresponding string
    // print the best string and its score

    double bestScore = 0;
    for(int i=0;i<pow(2,19);++i){

        for(int j = 0; j < 19; ++j) {
            solution[orphans[j]] = (i >> j) & 1;
        }
        double score = calcE(solution);
        if(score > bestScore){
            bestScore = score;
        }
        if(score > 700){
            for(int i=0;i<102;++i){
                cout << solution[i] << " ";
            }
            cout << endl;
            cout << setprecision(11) << "current score: " << score << "best score: "  << bestScore << endl;
        }
    }




    return 0;
}