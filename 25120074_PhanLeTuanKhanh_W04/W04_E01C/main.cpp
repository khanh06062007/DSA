#include <iostream>
#include <fstream>
using namespace std;

void countingSortSubroutine(int arr[], int n, long long exp){
    int output[n];
    int count[10] = {0};
    for (int i = 0; i < n; i++) 
        count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) 
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) 
        arr[i] = output[i];
}
void radixSortHFT(int deltas[], int n){
    int maxVal = abs(deltas[0]);
    for (int i = 1; i < n; i++) 
        maxVal = max(maxVal,abs(deltas[i]));
    for (int i = 0; i < n; i++) 
        deltas[i] += maxVal;
    for (long long exp = 1; maxVal*2 / exp > 0; exp *= 10) {
        countingSortSubroutine(deltas, n, exp);
    }
    for (int i = 0; i < n; i++) 
        deltas[i] -= maxVal;
}

int main() {
    int n;
    cin >> n;
    
    int* deltas = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> deltas[i];
    }
    
    radixSortHFT(deltas, n);
    
    for (int i = 0; i < n; i++) {
        cout << deltas[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    delete[] deltas;
    
    return 0;
}
