# DSA Lab - Week 04
## Optimized Sorting

*TA: Hồ Lê Minh Quân & Lê Hình Nhựt Thanh*

*Date: April 7, 2026*

---

### Exercise 1C. Market Delta Analysis

#### 1. Problem Formulation
In High-Frequency Trading (HFT) systems, the server records millions of price fluctuations (deltas) every second. These deltas can be positive (price increased) or negative (price decreased).

The challenge is that traditional **Radix Sort (LSD)** cannot handle negative numbers directly because the modulo and division operators behave differently for negative integers. To solve this, you must:
1. Normalize the data by offsetting all values to be non-negative
2. Apply Radix Sort using a **Counting Sort subroutine**
3. Restore the original values by reversing the offset

#### 2. Your Task
Sort an array of $N$ price deltas in ascending order using **Radix Sort** to achieve a linear time complexity of $O(d \cdot (N + k))$. Instead of using an array of queues for buckets, implement a **Counting Sort subroutine** to sort the digits at each positional place.

Implement the following functions:
``` cpp
void countingSortSubroutine(int arr[], int n, long long exp);
void radixSortHFT(int deltas[], int n);
```

Parameter explanation:
- `deltas`: array of price deltas to be sorted.
- `n`: number of deltas in the array.
- `arr`: array being sorted in the Counting Sort subroutine.
- `exp`: the current exponent/place value (1, 10, 100, etc.).

#### 3. Input & Output Format
**Input file:**
- Line 1: integer `N` (`1 <= N <= 100000`) - number of recorded deltas.
- Line 2: `N` integers `deltas[i]` (`-1000000 <= deltas[i] <= 1000000`) - price deltas.

**Output file:**
- One line containing the sorted array values, separated by one space.

**Examples:**
- Input:
  ```
  6
  150 -20 5 -150 0 42
  ```
- Output:
  ```
  -150 -20 0 5 42 150
  ```

#### 4. Hints
- **Handling Negative Numbers:** Find the minimum value in the array and subtract it from all elements to make them non-negative. After sorting, add the minimum back to restore original values.
- **Counting Sort Subroutine:** 
  - Create a `count` array of size 10 (for base-10 digits).
  - Count the frequencies of each digit at the current `exp` place.
  - Calculate the prefix sums of the count array so `count[i]` stores the exact position of this digit in the output array.
  - To maintain stability (mandatory for Radix Sort), build the output array by looping through the original array **backwards** (from $N-1$ down to 0).

#### 5. Submission & Setup Requirements
- Directory structure: inside `W04_E01C`, submit exactly one source file `main.cpp`.
- Allowed libraries: `<iostream>`, `<fstream>`.
- Program must accept exactly two CLI arguments: input path and output path.

#### 6. Template for `main.cpp`
See `W04_E01C/main.cpp`.

---

### Exercise 2C. Network Packet Sequencer

#### 1. Problem Formulation
A cybersecurity firewall at Yeah1 Corporation is analyzing millions of incoming network packets. To identify DDoS attack patterns, the system needs to group packets originating from the same source by sorting their IPv4 addresses in ascending order.

Each IPv4 address is represented as a 32-bit unsigned integer. The key insight is that IPv4 addresses are exactly 32 bits (4 bytes), so a **Base-256 Radix Sort** will guarantee exactly 4 passes regardless of the array size. This approach processes the data byte by byte, making it ideal for high-throughput network analysis.

#### 2. Your Task
Sort an array of $N$ IPv4 addresses using **Radix Sort** in Base-256. For IP addresses consisting of 4 bytes (octets), you will process it byte by byte, implementing a **Counting Sort subroutine** to sort the array at each byte position.

Implement the following functions:
``` cpp
void countingSortSubroutine(unsigned int arr[], int n, int shift);
void radixSortIPv4(unsigned int ips[], int n);
```

Parameter explanation:
- `ips`: array of IPv4 addresses (as 32-bit unsigned integers) to be sorted.
- `n`: number of IP addresses in the array.
- `arr`: array being sorted in the Counting Sort subroutine.
- `shift`: bit shift amount to extract the current byte (0, 8, 16, 24).

#### 3. Input & Output Format
**Input file:**
- Line 1: integer `N` (`1 <= N <= 100000`) - number of recorded IP addresses.
- Line 2: `N` unsigned integers `ips[i]` (`0 <= ips[i] <= 4294967295`) - IPv4 addresses as 32-bit integers.

**Output file:**
- One line containing the sorted array values, separated by one space.

**Constraints:**
- $N \le 10^5$ (Number of recorded IP addresses).
- Time Limit: 0.5 seconds.
- Memory Limit: 32 MB.

**Examples:**
- Input:
  ```
  4
  3232235778 167772161 3232235777 4294967295
  ```
- Output:
  ```
  167772161 3232235777 3232235778 4294967295
  ```
- Explanation:
  - Addresses correspond to: 192.168.1.2, 10.0.0.1, 192.168.1.1, 255.255.255.255
  - The array is sorted in ascending order based on their 32-bit unsigned integer representations.

#### 4. Hints
- **Base-256 Extraction:** In base-10, you extract a digit using `(number / exp) % 10`. In base-256 (byte-level), extract the $i$-th byte using bitwise operations: `(ip >> shift) & 255`, where shift = 0, 8, 16, 24 for the 1st, 2nd, 3rd, and 4th bytes respectively.
- **Counting Sort Subroutine:** 
  - Since we operate in Base-256, your `count` array must be of size 256 (representing values 0 through 255).
  - Count the frequencies of each byte at the current `shift` position.
  - Calculate the prefix sums of the count array so `count[i]` indicates the exact position of this byte in the output array.
  - To maintain stability (mandatory for Radix Sort), build the output array by looping through the original array **backwards** (from $N-1$ down to 0).

#### 5. Submission & Setup Requirements
- Directory structure: inside `W04_E02C`, submit exactly one source file `main.cpp`.
- Allowed libraries: `<iostream>`, `<fstream>`.
- Program must accept exactly two CLI arguments: input path and output path.

#### 6. Template for `main.cpp`
See `W04_E02C/main.cpp`.

---

### Exercise 3A. Cryptographic Hash Assembly

#### 1. Problem Formulation
A blockchain node needs to construct a master signature by concatenating $N$ numeric string fragments. To ensure consensus, the network requires these fragments to be concatenated in a specific order: the arrangement that forms the strictly largest possible number (lexicographically and numerically).

For example, given the fragments `["9", "34", "3", "30", "5"]`, standard descending sort would yield `9, 5, 34, 30, 3` (concatenated: `9534303`). However, arranging them as `9, 5, 34, 3, 30` yields a larger overall value: `9534330`.

#### 2. Your Task
Sort an array of numeric strings such that their concatenation forms the largest possible string. This problem tests your sorting intuition by forcing you to design a custom comparison logic.

Furthermore, you are strictly prohibited from using built-in sorting libraries. You must implement your own $O(N \log N)$ sorting algorithm (such as Quick Sort or Merge Sort) from scratch to handle this data.

Implement the following functions:
``` cpp
#include <string>

void customSort(std::string arr[], int left, int right);
void assembleLargestHash(std::string arr[], int n);
```

#### 3. Input & Output Format
**Input file:**
- Line 1: integer `N` (1 <= `N` <= 50000).
- Line 2: `N` numeric strings `arr[i]` containing only digits.

**Output file:**
- One line containing the final concatenated maximum string. (Note: if the array is entirely zeroes, like `["0", "0"]`, output just `"0"`).

**Constraints:**
- $N \le 50,000$.
- Each string length $\le 100$.
- Time Limit: 0.5 seconds.
- Memory Limit: 16 MB.
- The use of `<algorithm>` and `std::sort` is strictly forbidden.

#### 4. Hints
- **Time Complexity**: Since $N = 50,000$, $O(N^2)$ approaches (like Bubble Sort or Insertion Sort) will result in a Time Limit Exceeded (TLE) error. You are required to implement a divide-and-conquer algorithm to achieve $O(N \log N)$ time.
- **Relational Transitivity (Quan hệ bắc cầu)**: Standard numerical comparison (`a > b`) or length comparison is invalid here. Your custom sorting logic must evaluate the *consequence of their arrangement* rather than their absolute individual values.

#### 5. Submission & Setup Requirements
- Directory structure: inside `W04_E03A`, submit exactly one source file `main.cpp`.
- Allowed libraries: `<iostream>`, `<fstream>`, `<string>`.
- Program must accept exactly two CLI arguments: input path and output path.

#### 6. Template for `main.cpp`
See `W04_E03A/main.cpp`.

---

### Exercise 3B. Downtime Consolidation

#### 1. Problem Formulation
What is a **"Maintenance Window"**? In cloud computing, backend servers are essentially physical computers. Just like your laptop, they occasionally need to be turned off for hardware upgrades, software patches, or security fixes. This period of scheduled downtime is called a **maintenance window**.

A cloud provider's infrastructure consists of thousands of these servers. When generating a monthly **SLA (Service Level Agreement)** report, the system aggregates the maintenance windows from all servers.

Because multiple servers might be turned off at the same time, their downtime windows often overlap. For example, if Server A is down from hour `1` to `3`, and Server B is down from hour `2` to `6`, the system as a whole was impaired from hour `1` to `6`. To calculate the true system downtime, you must consolidate these overlapping intervals into a set of disjoint (non-overlapping) intervals.

#### 2. Your Task
You are given an array of $N$ time intervals where `intervals[i] = [start_i, end_i]`. Implement a function to merge all overlapping intervals and return the new count of merged intervals.

Implement the following functions:
``` cpp
struct Interval {
    int start;
    int end;
};

// Modifies the array in-place and returns the new size of the merged array
int mergeDowntimes(Interval arr[], int n);
```

#### 3. Input & Output Format
**Input file:**
- Line 1: integer `N` (`1 <= N <= 100000`).
- Line 2 to $N+1$: Two integers start and end representing a downtime window.

**Output file:**
- Line 1: The new size of the array `K`.
- Line 2 to $K+1$: The merged intervals, ordered by start time.

**Constraints:**
- $N \le 10^5$.
- $0 \le start \le end \le 10^6$.
- Time Limit: 0.5 seconds.
- Memory Limit: 16 MB.
- The use of `<algorithm>` and `std::sort` is strictly forbidden.

#### 4. Hints
- **Time Complexity**: A naive brute-force approach to check every interval against every other interval takes $O(N^2)$ and will TLE. Pre-sorting the data reduces this so you can resolve all overlaps in a single linear pass, yielding an overall $O(N \log N)$ time.
- **Spatial Proximity (Tính chất lân cận trong không gian)**: If you establish a strict chronological baseline (e.g., sorting all items by their start times), any intervals that share a physical overlap are mathematically forced to sit adjacently in your array.

#### 5. Submission & Setup Requirements
- Directory structure: inside `W04_E03B`, submit exactly one source file `main.cpp`.
- Allowed libraries: `<iostream>`, `<fstream>`.
- Program must accept exactly two CLI arguments: input path and output path.

#### 6. Template for `main.cpp`
See `W04_E03B/main.cpp`.
