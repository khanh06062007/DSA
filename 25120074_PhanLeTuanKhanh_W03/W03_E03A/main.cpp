#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Submission {
    string teamCode;
    int score;
};

// --- YOUR CODE HERE ---
void sortLeaderboard(Submission subs[], int left, int right) {
    if(left >= right)return;
    sortLeaderboard(subs, left, left + (right - left) / 2);
    sortLeaderboard(subs, left + (right - left) / 2 + 1, right);
    int n1 = (left + (right - left) / 2) - left + 1;
    int n2 = right - (left + (right - left) / 2);
    Submission* L = new Submission[n1];
    Submission* R = new Submission[n2];
    for (int i = 0; i < n1; i++) L[i] = subs[left + i];
    for (int j = 0; j < n2; j++) R[j] = subs[(left + (right - left) / 2) + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].score >= R[j].score) 
            subs[k++] = L[i++];
        else 
            subs[k++] = R[j++];
    }
    while (i < n1) subs[k++] = L[i++];
    while (j < n2) subs[k++] = R[j++];
    delete[] L;
    delete[] R;
}

string queryScore(Submission subs[], int n, int target) {
    int l = 0, r = n - 1, res = -1;
    while (l <= r){
        int mid = l + (r - l) / 2;
        if(subs[mid].score <= target){
            res = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    return (res == -1 || subs[res].score != target ? "Not found" : subs[res].teamCode);
}

// --- MAIN FUNCTION (DO NOT MODIFY) ---
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: ./main.exe <input_path> <output_path>\n";
        return 1;
    }

    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);

    if (!infile.is_open() || !outfile.is_open()) {
        return 1;
    }

    int n;
    if (!(infile >> n)) {
        return 0;
    }

    Submission* subs = new Submission[n];
    for (int i = 0; i < n; i++) {
        infile >> subs[i].teamCode >> subs[i].score;
    }

    sortLeaderboard(subs, 0, n - 1);

    int q;
    infile >> q;
    for (int i = 0; i < q; i++) {
        int target;
        infile >> target;
        outfile << queryScore(subs, n, target) << "\n";
    }

    delete[] subs;
    infile.close();
    outfile.close();
    return 0;
}
