#include <bits/stdc++.h>

using namespace std;

bool is_valid(int x, int y, int n)
{
	if(x>=0 && x<n && y<n && y>=0) return true;
	return false;
}

int num_taken(int n, int i, int j)
{
	int res = is_valid(i-2, j-1, n) + is_valid(i-2, j+1, n) + is_valid(i-1, j-2, n)
			  + is_valid(i-1, j+2, n) + is_valid(i+1, j+2, n) + is_valid(i+1, j-2, n)
			  + is_valid(i+2, j-1, n) + is_valid(i+2, j+1, n);
	
	return res;
}

long long soln[10000 + 5];

long long num_two_knights(int n)
{
	if(n==1)
		return 0LL;
	if(soln[n] != 0)
		return soln[n];
		
	long long res = num_two_knights(n-1);
	for(int i = 0; i<n; ++i)
	{
		res += ((long long)n*n) - (long long)num_taken(n, n-1, i) - (long long)i -1;
	}
	
	for(int i = 1; i<n; ++i)
	{
		res += ((long long)n*n) - n - (i-1) - (long long)num_taken(n, i, n-1) + (i == 1 && n >= 3) + (i == 2 && n >= 3) - 1;
	}
	soln[n] = res;
	return res;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	for(int i = 1; i<=n; ++i)
	{
		cout << num_two_knights(i) << endl;
	}
	return 0;
}
