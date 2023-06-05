#include <bits/stdc++.h>

using namespace std;

int main()
{
    ifstream fileIn("in");
    ofstream fileOut("out");

    string description, scope, prefix, body;
    cout << "Description: ";
    getline(cin, description);
    description = "\"" + description + "\"";

    cout << "Scope (usually c++): ";
    cin >> scope;
    scope = "\"scope\": \"" + scope + "\",";

    cout << "Prefix (the command for calling the snippet): ";
    cin >> prefix;
    prefix = "\"prefix\": \"" + prefix + "\",";

    string str;
    string result = "";
    result += description + ": {\n";
    result += scope + "\n";
    result += prefix + "\n";
    result += "\"body\"";
    result += ": [\n";
    while(getline(fileIn, str)) {
        str = "\"" + str + "\",\n";
        result += str;
    }
    result += "]\n}";

    fileOut << result;

    return 0;
}