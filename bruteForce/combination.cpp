#include <iostream>
#include <vector>

using namespace std;



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
		people.push_back(i+1); 
	}
  	go(0, k, people, combination, result);


	for(int i=0;i<result.size();++i){
		for(int j=0;j<result[i].size();++j)
			cout << result[i][j] << " " ;
		cout << endl;
	}
  	return 0;
}
