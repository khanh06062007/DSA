#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void customSort(string arr[], int left, int right){
    if (left >= right)
        return;
    int i = left, j = right;
    string mid = arr[i + (j - i) / 2];
    while (i < j){
        while (arr[i]+mid > mid+arr[i])
            i++;
        while (arr[j]+mid < mid+arr[j])
            j--;
        if (i <= j){
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j)
        customSort(arr, left, j);
    if (i < right)
        customSort(arr, i, right);
}
void assembleLargestHash(string arr[], int n){
    customSort(arr, 0, n - 1);
    if (arr[0][0] == '0'){
        cout << '0';
        return;
    }
    for (int i = 0; i < n; i++)
        cout << arr[i];
}

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

    string* arr = new string[n];
    for (int i = 0; i < n; i++) {
        infile >> arr[i];
    }

    assembleLargestHash(arr, n);

    for (int i = 0; i < n; i++) {
        if (arr[i] != "0") {
            for (int j = 0; j < n; j++) {
                outfile << arr[j];
            }
            outfile << "\n";
            delete[] arr;
            infile.close();
            outfile.close();
            return 0;
        }
    }

    outfile << "0\n";

    delete[] arr;
    infile.close();
    outfile.close();
    return 0;
}
