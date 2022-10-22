#include <iostream>
using namespace std;
  
class Combination {
private:
    // Data array for combination
    int* Indices;
  
    // Length of the data array
    int N;
  
    // Number of elements in the combination
    int R;
  
    // The boolean array
    bool* Flags;
  
    // Starting index of the 1st tract of trues
    int Start;
  
    // Ending index of the 1st tract of trues
    int End;
  
public:
    // Constructor
    Combination(int* arr, int n, int r)
    {
        this->Indices = arr;
        this->N = n;
        this->R = r;
        this->Flags = nullptr;
    }
    ~Combination()
    {
        if (this->Flags != nullptr) {
            delete[] this->Flags;
        }
    }
  
    // Set the 1st r Booleans to true,
    // initialize Start and End
    void GetFirst()
    {
        this->Flags = new bool[N];
  
        // Generate the very first combination
        for (int i = 0; i < this->N; ++i) {
            if (i < this->R) {
                Flags[i] = true;
            }
            else {
                Flags[i] = false;
            }
        }
  
        // Update the starting ending indices
        // of trues in the boolean array
        this->Start = 0;
        this->End = this->R - 1;
        this->Output();
    }
  
    // Function that returns true if another
    // combination can still be generated
    bool HasNext()
    {
        return End < (this->N - 1);
    }
  
    // Function to generate the next combination
    void Next()
    {
  
        // Only one true in the tract
        if (this->Start == this->End) {
            this->Flags[this->End] = false;
            this->Flags[this->End + 1] = true;
            this->Start += 1;
            this->End += 1;
            while (this->End + 1 < this->N
                   && this->Flags[this->End + 1]) {
                ++this->End;
            }
        }
        else {
  
            // Move the End and reset the End
            if (this->Start == 0) {
                Flags[this->End] = false;
                Flags[this->End + 1] = true;
                this->End -= 1;
            }
            else {
                Flags[this->End + 1] = true;
  
                // Set all the values to false starting from
                // index Start and ending at index End
                // in the boolean array
                for (int i = this->Start; i <= this->End; ++i) {
                    Flags[i] = false;
                }
  
                // Set the beginning elements to true
                for (int i = 0; i < this->End - this->Start; ++i) {
                    Flags[i] = true;
                }
  
                // Reset the End
                this->End = this->End - this->Start - 1;
                this->Start = 0;
            }
        }
        this->Output();
    }
  
private:
    // Function to print the combination generated previouslt
    void Output()
    {
        for (int i = 0, count = 0; i < this->N
                                   && count < this->R;
             ++i) {
  
            // If current index is set to true in the boolean array
            // then element at current index in the original array
            // is part of the combination generated previously
            if (Flags[i]) {
                cout << Indices[i] << " ";
                ++count;
            }
        }
        cout << endl;
    }
};
  
// Driver code
int main()
{
    int arr[] = { 0, 1, 2, 3 };
    int n = sizeof(arr) / sizeof(int);
    int r = 2;
    Combination com(arr, n, r);
    com.GetFirst();
    while (com.HasNext()) {
        com.Next();
    }
    return 0;
}