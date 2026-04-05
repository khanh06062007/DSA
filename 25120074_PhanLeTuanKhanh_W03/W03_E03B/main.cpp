#include <iostream>
#include <fstream>

using namespace std;

// --- YOUR CODE HERE ---
int minimumCapacityPerDay(int weights[], int n, int days) {
    // Use binary search on capacity.
    int l = 1, r = 0, res = -1;
    for (int i = 0; i < n; i++)
        r = r + weights[i];
    while(l <= r){
        int mid = l + (r - l) / 2, d = 1, capacity = 0;
        for (int i = 0; i < n; i++){
            if(weights[i] > mid){
                d = n+1;
                break;
            }
            if (capacity + weights[i] > mid){
                d++;
                capacity = weights[i];
            }
            else
                capacity += weights[i];
        }
        if (d <= days){
            res = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    return res;
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

    int n, days;
    if (!(infile >> n >> days)) {
        return 0;
    }

    int* weights = new int[n];
    for (int i = 0; i < n; i++) {
        infile >> weights[i];
    }

    outfile << minimumCapacityPerDay(weights, n, days) << "\n";
    
    delete[] weights;
    infile.close();
    outfile.close();
    return 0;
}
