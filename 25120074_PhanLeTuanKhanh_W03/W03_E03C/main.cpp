#include <iostream>
#include <fstream>

using namespace std;

// --- YOUR CODE HERE ---
void sortColors(int nums[], int n) {
    int low = 0;        
    int mid = 0;        
    int high = n - 1;  
    while (mid <= high) {
        if (nums[mid] == 0) {
            int temp = nums[low];
            nums[low] = nums[mid];
            nums[mid] = temp;
            low++;
            mid++;
        } 
        else if (nums[mid] == 1) 
            mid++;
        else {
            int temp = nums[mid];
            nums[mid] = nums[high];
            nums[high] = temp;
            high--;
        }
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

    if (!infile.is_open() || !outfile.is_open()) {
        return 1;
    }

    int n;
    if (!(infile >> n)) {
        return 0;
    }

    int* nums = new int[n];
    for (int i = 0; i < n; i++) {
        infile >> nums[i];
    }

    sortColors(nums, n);

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            outfile << " ";
        }
        outfile << nums[i];
    }
    outfile << "\n";

    delete[] nums;
    infile.close();
    outfile.close();
    return 0;
}
