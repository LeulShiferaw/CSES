#include <bits/stdc++.h>

using namespace std;

/*
	the sum of the first xi and the sum of the second set xj are equal
	therefore xi = xj = x
	xi + xj = n(n+1)/2
	2x = n(n+1)/2
	therefore for x to be an int (n*(n+1)) % 4 == 0

	Case 1: n%4 == 0
	this is easy just take the two polar sides: first element and last element, second element and second last element and add them to different sets

	Case 2: (n+1) % 4 == 0
	Just remove three element and the sets can be used like before
	The three elements are m(middle element), x1, and x2
	x1 + x2 must equal (n+1)
	x1 + x2 = n+1
	x1 + m  = x2

	therefore find x1, x2 from sim equation above
	then add x1, m to one set and x2 to another
	Now that you have removed the three elements just do the steps of Case 1 to Case 2. Watch out for x1 don't accidentally add it to.
*/

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	if(n % 4 ==0)
	{
		cout << "YES" << endl;
		vector<int> set1, set2;
		bool set1_turn = true;
		for(int i = 1; i<= (n/2); ++i)
		{
			if(set1_turn)
			{
				set1.push_back(i);
				set1.push_back(n-(i-1));
			}
			else
			{
				set2.push_back(i);
				set2.push_back(n-(i-1));
			}
			set1_turn = !set1_turn;
		}
		cout << set1.size() << endl;
		cout << set1[0];
		for(int i = 1; i<(int)set1.size(); ++i)
			cout << " " << set1[i];
		cout << endl;
		
		cout << set2.size() << endl;
		cout << set2[0];
		for(int i = 1; i<(int)set2.size(); ++i)
			cout << " " << set2[i];
		cout << endl;
		return 0;
	}
	else if((n+1)%4==0)
	{
		
		cout << "YES" << endl;
		/*
		 * x1 + x2 = (n+1)
		 * x1 + m  = x2
		 * 2x2 = (n+1) + m
		 * x2 = ((n+1) + m)/2
		 * x1 = (n+1) - x2
		 * */
		int c = n+1;
		int m = ceil((n)/2.0);
		int x2 = (c+m)/2;
		int x1 = c - x2;
		
		vector<int> set1, set2;
		set1.push_back(x1);
		set1.push_back(m);
		set2.push_back(x2);
		
		bool set1_turn = true;
		for(int i = 1; i<= (n/2); ++i)
		{
			if(i == x1)
				continue;
				
			if(set1_turn)
			{
				set1.push_back(i);
				set1.push_back(n-(i-1));
			}
			else
			{
				set2.push_back(i);
				set2.push_back(n-(i-1));
			}
			set1_turn = !set1_turn;
		}
		
		cout << set1.size() << endl;
		cout << set1[0];
		for(int i = 1; i<set1.size(); ++i)
			cout << " " << set1[i];
		cout << endl;
		
		cout << set2.size() << endl;
		cout << set2[0];
		for(int i = 1; i<set2.size(); ++i)
			cout << " " << set2[i];
		cout << endl;
		return 0;
	}
	else
		cout << "NO" << endl;
	return 0;
}
