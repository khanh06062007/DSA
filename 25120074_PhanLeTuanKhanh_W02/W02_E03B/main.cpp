#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// --- YOUR CODE HERE ---
void backtrack(string s, int index, int partCount, string currentIP, string* result, int& resultCount) {
    // Implement the backtracking logic here
    if (partCount == 4 && index == s.length()) {
        result[resultCount++] = currentIP.substr(0, currentIP.length() - 1);
        return;
    }
    if (partCount == 4 || index == s.length()) return;
    for (int len = 1; len <= 3 && index + len <= s.length(); len++) {
        string part = s.substr(index, len); 
        if (len > 1 && part[0] == '0') continue;
        int val = stoi(part);
        if (val >= 0 && val <= 255)
            backtrack(s, index + len, partCount + 1, currentIP + part + ".", result, resultCount);
    }
}

// --- MAIN FUNCTION (DO NOT MODIFY) ---
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./main.exe <input_path> <output_path>\n";
        return 1;
    }

    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);

    if (!infile.is_open() || !outfile.is_open()) return 1;

    string s;
    infile >> s;

    string results[200]; // Max valid IP combinations for length 12 is less than 200
    int resultCount = 0;

    backtrack(s, 0, 0, "", results, resultCount);
    
    for (int i = 0; i < resultCount; i++) {
        outfile << results[i] << "\n";
    }

    infile.close();
    outfile.close();
    return 0;
}