#include <bits/stdc++.h>
#include <math.h>

using namespace std;

int m[1000000][20], n, a[1000000], mPair, pairI[1000000], pairJ[1000000], sum = 0;

void process() {	
	// Khoi tao gia tri M[i][0]
	for (int i = 0; i < n; i++) {
		m[i][0] = a[i];
	}
	
	// Tinh M[i][j]
	for (int j = 1; pow(2,j) <= n; j++) {
		for (int i = 0; i + pow(2,j) <= n; i++) {
			int  exp = i+pow(2,j-1)-1;
			if (m[i][j-1] < m[exp][j-1]) {
				m[i][j] = m[i][j-1];
			}
			else m[i][j] = m[exp][j-1];

		}
	}
	
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; i + pow(2,j) <= n; j++) {
//			cout << m[i][j] << ' ';
//		}
//		cout << endl;
//	}
	
	
}

void RMQ() {
	for (int i = 0; i < mPair; i++) {
		int k = log2(pairJ[i]-pairI[i]+1);
		int exp = pairJ[i]-pow(2,k)+1;
		if (m[pairI[i]][k] < m[exp][k]) {
			sum += m[pairI[i]][k];
		}
		else sum += m[exp][k]; 
	}
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> mPair;
    for (int i = 0; i < mPair; i++) cin >> pairI[i] >> pairJ[i];
    
	process();
	
	RMQ();
	
	cout << sum;
	
    return 0;
}
