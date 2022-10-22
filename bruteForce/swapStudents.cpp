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

void allswap(vector<int> index, int group[102], int max){
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
}

void go(int offset, int k, vector<int> &people, vector<int> &combination, vector< vector<int> > &result) {
	if (k == 0) {
		result.push_back(combination);
    	return;
  	}
	for (int i = offset; i <= people.size() - k; ++i) {
    	combination.push_back(people[i]);
    	go(i+1, k-1, people, combination, result);
    	combination.pop_back();
  	}
}

int main() {

  	int n = 101, k = 2;
  	vector<int> people;
	vector<int> combination;
	vector< vector<int> > result;


  	for (int i = 0; i < n; ++i) { 
		people.push_back(i); 
	}
  	go(0, k, people, combination, result);


	for(int i=0;i<result.size();++i){
		for(int j=0;j<result[i].size();++j)
			cout << result[i][j] << " " ;
		cout << endl;
	}
  	return 0;
}
