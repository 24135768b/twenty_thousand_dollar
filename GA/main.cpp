#include <bits/stdc++.h>
using namespace std;

mt19937 r(time(NULL));
vector<vector<double>> wij;

class ClassOfStudents
{
public:
    vector<bool> student;
    double score = 0;
    ClassOfStudents()
    {
        student = vector<bool>();
    }
    ClassOfStudents(vector<bool> &initStudent)
    {
        int size = initStudent.size();
        student.resize(size);
        for (int i = 1; i <= size; i++)
        {
            student[i] = initStudent[i];
        }
        calcE();
    }

    void calcE()
    {
        int size = student.size();
        score = 0;
        for (int i = 1; i < size; i++)
        {
            for (int j = i + 1; j <= size; j++)
            {
                score += wij[i][j] * (student[i] ? 1 : -1) * (student[j] ? 1 : -1);
            }
        }
    }
    void printResult()
    {
        int size = student.size();
        for (int i = 1; i < size; i++)
        {
            cout << (student[i] ? "A" : "B") << " ";
        }
        cout << endl;
        cout << score << endl;
    }
};

int cmp(ClassOfStudents const &a, ClassOfStudents const &b)
{
    return a.score > b.score;
}

class GA
{
private:
    int populationSize = 100;
    double pm = 0.15, pc = 0.95;
    // Crossover from population last parent and parent - cnt
    int crossoverCnt;
    ClassOfStudents *population;

public:
    GA(int n)
    {
        population = new ClassOfStudents[n];
        crossoverCnt = sqrt(populationSize);
        for (int i = 0; i < populationSize; i++)
        {
            vector<bool> temp = randomGenStud(n);
            population[i] = ClassOfStudents(temp);
            // population[i].calcE();
            // population[i].printResult();
        }
    }
    vector<bool> randomGenStud(int n)
    {
        vector<bool> result(n + 1);
        for (int i = 1; i <= n; i++)
        {
            result[i] = r() % 2;
        }
        return result;
    }
    void nextGen()
    {
        sort(population, population + populationSize, cmp);
        int top = populationSize * 0.2;
        for (int i = crossoverCnt; i < populationSize; i++)
        {
            population[i] = crossOver(population[r() % crossoverCnt], population[r() % crossoverCnt]);
        }
    }
    void print()
    {
        for (int i = 0; i < populationSize; i++)
        {
            population[i].printResult();
        }
    }
    void run(int gen)
    {
        for (int i = 0; i < gen; i++)
        {
            nextGen();
            population[0].printResult();
        }
    }
    ClassOfStudents crossOver(ClassOfStudents &a, ClassOfStudents &b)
    {
        vector<bool> tmp = a.student;
        int size = a.student.size();
        vector<bool> b_students = b.student;
        for (int i = 1; i < size; i++)
        {
            if (b_students[i] != a.student[i])
            {
                if ((rand() & 1) || tmp[i] != a.student[i])
                    tmp[i] = !a.student[i];
            }
        }
        // if pm
        if (((double)rand()) / (RAND_MAX + 1) < pm)
        {
            int t = r() % size - 1;
            tmp[t] = !a.student[t];
        }
        ClassOfStudents c = ClassOfStudents(tmp);
        return c;
    }
};

int main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n = atoi(argv[1]);
    int size = n * (n - 1) / 2;

    cout << "n= " << n << "\nsize= " << size << endl;

    wij.resize(n + 1);
    for (int i = 0; i <= n; i++)
    {
        wij[i].resize(n + 1);
    }
    cout << "initialize successful" << endl;
    for (int i = 0; i < size; i++)
    {
        int n, m;
        double w;
        cin >> n >> m >> w;
        wij[n][m] = w;
        wij[m][n] = w;
    }
    cout << "read success" << endl;
    GA ga(n);
    ga.run(10000);
    return 0;
}