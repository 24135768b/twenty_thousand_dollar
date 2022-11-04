#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

void comb(int n, int m, int group[102]);

int main() {
    int n = 2;
    int group[102] = {0};
    comb(n, 4, group);
    return 0;
}

void comb(int n, int m, int group[102]) {
    vector < int > list;
    for (int i = 0; i < n; ++i) {
        list.push_back(i);
    }
    --list[n - 1];
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
		// print
        for (int i = 0; i < n; ++i) {
            cout << list[i] + 1 << ' ';
        }
        cout << endl;
        


		// binary generator for every combination
        // init to zero and save the state
        vector<int> temp;
        for(int j = 0; j < n; ++j) {
            temp.push_back(group[list[j]]);
            group[list[j]] = 0;
        }

         // print
        for(int i=0;i<m;++i){ // m = 101 or 102
            cout << group[i] ;
        }
        cout << endl;

        for(int j = 0; j < pow(2,n); ++j) {

            // next
            // the bug is that the last one will overflow
            group[list[0]]++;
            for(int i=0;i<n;i++){
                if(group[list[i]] == 2){
                    group[list[i]] = 0;
                    group[list[i+1]]++;
                }
            }
            // print
            for(int i=0;i<m;++i){ // m = 101 or 102
                cout << group[i] ;
            }
            cout << endl;
        }
        // restore the state
        for(int j = 0; j < n; ++j) {
            group[list[j]] = temp[j];
        }

    } while (list[0] < (m - n));
}
