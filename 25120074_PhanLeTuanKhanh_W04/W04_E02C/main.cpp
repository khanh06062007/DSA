#include <iostream>
#include <fstream>
using namespace std;

void countingSortSubroutine(unsigned int arr[], int n, int shift);
void radixSortIPv4(unsigned int ips[], int n);

int main() {
    int n;
    cin >> n;
    
    unsigned int* ips = new unsigned int[n];
    for (int i = 0; i < n; i++) {
        cin >> ips[i];
    }
    
    radixSortIPv4(ips, n);
    
    for (int i = 0; i < n; i++) {
        cout << ips[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    delete[] ips;
    
    return 0;
}
