#include <iostream>
#include <string>
#define MAX 100000

using namespace std;

int n, m = 0;
int a[MAX];
int b[MAX];

void deleteMax();
void output();
void stringInput(string str);

int main() 
{
    cin >> n;
    for (int i=0; i<n; i++) 
    {
        cin >> a[i];
    }

    while (1) 
    {
        string strInput;
        cin >> strInput;

        if (strInput[0] != '*') 
        {
            stringInput(strInput);
            continue;
        }
        else break;
    }
    
    output();
    return 0;
}

void deleteMax() 
{
    int max = -999991, index = 0;
    for (int i=0; i< n; i++) 
    {
        if (a[i] > max) 
        {
            max = a[i];
            index = i;
        }
    }
    a[index] = -999991;
    b[m] = max;
    m++;
}

void output() 
{
    for (int i=0; i< m; i++) 
    {
        cout << b[i] << endl;
    }
}

void stringInput(string str) {
    if (str.find("insert") != -1) 
    {
        int inputNumber;
        cin >> inputNumber;
        a[n] = inputNumber;
        n++;
    }
    
    if (str.find("delete-max") != -1) 
    {
        deleteMax();
    }
}