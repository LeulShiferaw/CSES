#include <bits/stdc++.h>

using namespace std;

int main()
{
	ifstream fileOut("out");
	ifstream fileIn("in");
	ifstream fileCorrect("corr_out");

	long long temp;
	fileIn >> temp;
	fileIn >> temp;
	for(int i = 0; i<200000; ++i) {
		fileIn >> temp;
	}
	vector<long long> in, out, corr_out;
	while(fileOut >> temp) out.push_back(temp);
	while(fileCorrect >> temp) corr_out.push_back(temp);
	while(fileIn >> temp) in.push_back(temp);
	for(int i = 0; i<out.size(); ++i) {
		if(out[i] != corr_out[i]) {
			cout << i << endl;
			cout << in.size() << endl;
			cout << "in: " << in[i] << endl;
			cout << "out: " << out[i] << endl;
		    cout << "correct: " << corr_out[i] << endl;
			return 0;
		}
	}
	return 0;
}
