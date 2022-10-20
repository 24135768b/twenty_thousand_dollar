#include <bits/stdc++.h>
using namespace std;

mt19937 r(time(NULL));
vector<vector<double>> wij;

// Log file
ofstream log_file("log.txt");

double getRand()
{
    return (double)r() / (double)mt19937::max();
}

bool getRandBool()
{
    return getRand() < 0.5;
}
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
        if (score > 10000)
        {
            cout << "Error" << endl;
            cout << getResultString() << endl;
            int n = wij.size();
            for (int i = 1; i < n; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    cout << i << " " < < < j << " " << wij[i][j] << endl;
                }
            }
            exit(0);
        }
    }
    string getResultString()
    {
        int size = student.size();
        string result = "";
        for (int i = 1; i < size; i++)
        {
            result += string(student[i] ? "A" : "B") + string(" ");
        }
        result += string("\n") + to_string(score) + string("\n");
        return result;
    }
};

int cmp(ClassOfStudents *const &a, ClassOfStudents *const &b)
{
    return a->score > b->score;
}

class GA
{
public:
    int populationSize = 10000;
    double pm = 0.15, pc = 0.95;
    // Crossover from population last parent and parent - cnt
    int crossoverCnt;
    ClassOfStudents **population;

    GA(int n)
    {
        population = new ClassOfStudents *[populationSize];
        crossoverCnt = sqrt(populationSize);
        for (int i = 0; i < populationSize; i++)
        {
            vector<bool> temp = randomGenStud(n);
            ClassOfStudents *tempClass = new ClassOfStudents(temp);
            population[i] = tempClass;
            // population[i].calcE();
            // population[i].printResult();
        }
    }
    vector<bool> randomGenStud(int n)
    {
        vector<bool> result(n + 1);
        for (int i = 1; i <= n; i++)
        {
            result[i] = getRandBool();
        }
        return result;
    }
    void nextGen()
    {
        sort(population, population + populationSize, cmp);
        for (int i = crossoverCnt; i < populationSize; i++)
        {
            delete population[i];
            ClassOfStudents *tempClass = new ClassOfStudents();
            *tempClass = crossOver(*population[r() % crossoverCnt], *population[r() % crossoverCnt]);
            population[i] = tempClass;
            population[i]->calcE();
            if (tempClass->score > 10000)
            {
                cout << "Error" << endl;
                cout << tempClass->getResultString() << endl;
                exit(1);
            }
        }
    }
    void printHighest()
    {
        sort(population, population + populationSize, cmp);
        cout << population[0]->getResultString() << endl;
    }
    void run(int gen)
    {
        for (int i = 0; i < gen; i++)
        {
            nextGen();
            // Write log
            log_file << "Generation: " << i << endl;
            log_file << population[0]->getResultString() << endl;
        }
    }
    ClassOfStudents crossOver(ClassOfStudents &a, ClassOfStudents &b)
    {
        vector<bool> tmp = a.student;
        vector<bool> b_students = b.student;

        int size = tmp.size();
        for (int i = 1; i < size; i++)
        {
            if (tmp[i] != b_students[i])
            {
                if (getRand() < pc)
                {
                    tmp[i] = b_students[i];
                }
                else
                {
                    tmp[i] = tmp[i] ^ b_students[i];
                }
            }
        }
        // if pm
        if (getRand() < pm)
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

    int generation = atoi(argv[2]);

    int t = atoi(argv[3]);

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
    while (t--)
    {
        cout << t << " times last" << endl;
        GA ga(n);
        ga.run(generation);
        ga.printHighest();

        ifstream bestScoreFile("bestScore.txt");
        double bestScore;
        bestScoreFile >> bestScore;
        bestScoreFile.close();
        if (ga.population[0]->score > bestScore)
        {
            cout << "new best! ";
            ofstream newBest(string("bestScoreList/") + to_string(ga.population[0]->score));
            newBest << ga.population[0]->getResultString() << endl;
            ofstream bestScoreFile("bestScore.txt");
            bestScoreFile << ga.population[0]->score;
        }
        cout << ga.population[0]->score << endl;
    }
    return 0;
}