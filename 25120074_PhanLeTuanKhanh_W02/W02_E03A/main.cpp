#include <iostream>
#include <fstream>

using namespace std;

// --- YOUR CODE HERE ---
bool backtrack(int* nums, int N, int index, long long prodA, long long prodB) {
    // 1. Base Case: Reached the end of the array
    if (index == N) 
        return prodA == prodB;
    // 2. Recursive Step: Make a choice (Put in A OR Put in B)
    bool choiceA = backtrack(nums, N, index + 1, prodA * nums[index], prodB);
    if (choiceA) return true;
    bool choiceB = backtrack(nums, N, index + 1, prodA, prodB * nums[index]);
    return choiceB;
}

bool canPartitionProduct(int* nums, int N) {
    return backtrack(nums, N, 0, 1, 1);
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

    int N;
    if (!(infile >> N)) return 0;

    int* nums = new int[N];
    for (int i = 0; i < N; i++) {
        infile >> nums[i];
    }

    if (canPartitionProduct(nums, N)) {
        outfile << "YES\n";
    } else {
        outfile << "NO\n";
    }

    delete[] nums; // Prevent memory leak

    infile.close();
    outfile.close();
    return 0;
}