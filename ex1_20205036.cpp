#include <iostream>
using namespace std;

int n, k, m;

int a[100000];
int sum[1000000];
int count = 0;

void sumK();
void checkSumEqualM();

int main() 
{
    cin >> n >> k >> m;
    for (int i=0; i<n; i++) 
    {
        cin >> a[i];
    }

    sumK();
    checkSumEqualM();

    cout << count;

    return 0;
}


void sumK() 
{
    sum[0] = 0;
    for (int i = 0; i < n; i++) 
    {
        sum[i+1] = sum[i] + a[i];
    }
}

void checkSumEqualM() 
{
    for (int i = 0; i < n - k + 1; i++) 
    {
        int checkSum;
        checkSum = sum[i+k] - sum[i];
        if (checkSum == m) count++;
    }
}