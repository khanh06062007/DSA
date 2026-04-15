#include <iostream>
#include <fstream>

using namespace std;

struct Interval {
    int start;
    int end;
};

int mergeDowntimes(Interval arr[], int n);

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

    Interval* arr = new Interval[n];
    for (int i = 0; i < n; i++) {
        infile >> arr[i].start >> arr[i].end;
    }

    int mergedCount = mergeDowntimes(arr, n);
    outfile << mergedCount << "\n";
    for (int i = 0; i < mergedCount; i++) {
        outfile << arr[i].start << " " << arr[i].end << "\n";
    }

    delete[] arr;
    infile.close();
    outfile.close();
    return 0;
}
