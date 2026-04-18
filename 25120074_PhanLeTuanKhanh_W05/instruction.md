# DSA Lab - Week 05
## Tree Data Structure

*TA: Ho Le Minh Quan & Le Hinh Nhut Thanh*

*Date: April 14, 2026*

---

### Exercise 3A. K-th Largest Element in a BST

#### 1. Problem Formulation
Given the root of a Binary Search Tree (BST) and an integer `k`, return the $k$-th largest value (1-indexed) among all node values.

This exercise is equivalent to Problem 1E/2E from Week 05 lecture material.

#### 2. Your Task
Implement the following function:
``` cpp
struct Node {
    int val;
    Node* left;
    Node* right;
};

int kthLargest(Node* root, int k);
```

#### 3. Input & Output Format
**Input file:**
- Line 1: integer `N` (`1 <= N <= 100000`) - number of level-order tokens.
- Line 2: `N` tokens representing the binary tree in level-order. Use `null` for missing nodes.
- Line 3: integer `k`.

**Output file:**
- One line containing the $k$-th largest value.

**Example:**
- Input:
  ```
  11
  5 3 6 2 4 null null 1 null null null
  3
  ```
- Output:
  ```
  4
  ```

#### 4. Constraints
- Time Complexity: $\mathcal{O}(H + k)$, where $H$ is the height of the tree. (You must stop traversing as soon as you find the answer).
- Space Complexity: $\mathcal{O}(H)$
- Rule: You are not allowed to flatten the tree or storing the node values in an array, vector, or list. You must find the answer during the traversal itself.

#### 5. Hints
- An in-order traversal (Left $\rightarrow$ Root $\rightarrow$ Right) visits values in ascending order. How can you modify this to visit values in strictly descending order?
- If you only need the $k$-th largest element, it is a waste of time to visit all $N$ nodes. What should your recursive function do the exact moment it processes the $k$-th node?
- Think about how to keep track of how many nodes you have visited so far. Since recursion creates multiple separate function calls, a standard local variable won't work. Consider passing a counter by reference (e.g., int& count) or using a class-member variable.

#### 6. Submission & Setup Requirements
- Directory structure: inside `W05_E03A`, submit exactly one source file `main.cpp`.
- Allowed libraries: `<iostream>`, `<fstream>`, `<string>`.
- Program must accept exactly two CLI arguments: input path and output path.

#### 7. Template for `main.cpp`
See `W05_E03A/main.cpp`.

---

### Exercise 3B. Two Sum IV - Input is a BST

#### 1. Problem Formulation
Given the root of a Binary Search Tree and an integer `target`, determine whether there exist two distinct nodes in the tree such that their values sum to `target`.

#### 2. Your Task
Implement the following function:
``` cpp
struct Node {
    int val;
    Node* left;
    Node* right;
};

bool findTarget(Node* root, int target);
```

#### 3. Input & Output Format
**Input file:**
- Line 1: integer `N` (`1 <= N <= 100000`) - number of level-order tokens.
- Line 2: `N` tokens representing the BST in level-order. Use `null` for missing nodes.
- Line 3: integer `target`.

**Output file:**
- One line containing `true` or `false`.

**Example:**
- Input:
  ```
  7
  5 3 6 2 4 null 7
  9
  ```
- Output:
  ```
  true
  ```

#### 4. Constraints
- Time Complexity: $\mathcal{O}(N)$
- Space Complexity: $\mathcal{O}(H)$, where $H$ is the height of the tree.

#### 5. Hints
- If you had a sorted array, you could solve this in $\mathcal{O}(1)$ space using the Two Pointers technique. How can you simulate moving a "left pointer" and a "right pointer" on a BST?
- An in-order traversal yields elements in ascending order. A reverse in-order traversal yields them in descending order.
- To achieve $\mathcal{O}(H)$ space without fully traversing the tree upfront, you need a way to pause and resume your traversals on demand. What underlying data structure does recursion use, and how can you manually simulate it?

#### 6. Submission & Setup Requirements
- Directory structure: inside `W05_E03B`, submit exactly one source file `main.cpp`.
- Allowed libraries: `<iostream>`, `<fstream>`, `<string>`, `<stack>`.
- Program must accept exactly two CLI arguments: input path and output path.

#### 7. Template for `main.cpp`
See `W05_E03B/main.cpp`.

---

### Exercise 3C. All Nodes Distance K in Binary Tree

#### 1. Problem Formulation
Given the root of a binary tree, a target node value, and an integer `k`, return all node values whose distance from the target node is exactly `k`.

#### 2. Your Task
Implement the following functions:
``` cpp
struct Node {
    int val;
    Node* left;
    Node* right;
};

Node* findNode(Node* root, int targetVal);
int distanceK(Node* root, Node* target, int k, int output[]);
```

Note: `distanceK` should populate the output array and return the total number of nodes found.

#### 3. Input & Output Format
**Input file:**
- Line 1: integer `N` (`1 <= N <= 100000`) - number of level-order tokens.
- Line 2: `N` tokens representing the binary tree in level-order. Use `null` for missing nodes.
- Line 3: integer `targetVal`.
- Line 4: integer `k`.

**Output file:**
- One line containing all values at distance `k`, sorted in ascending order and separated by one space.
- If no such node exists, output an empty line.

**Example:**
- Input:
  ```
  13
  3 5 1 6 2 0 8 null null 7 4 null null
  5
  2
  ```
- Output: One line containing all values at distance `k`, separated by one space, sorted in ascending order
  ```
  1 4 7
  ```

#### 4. Constraints
- Time Complexity: $\mathcal{O}(N \log N)$ in the worst case if you sort the final answer array; the recursive traversal itself is $\mathcal{O}(N)$.
- Space Complexity: $\mathcal{O}(H)$ for the recursive call stack. (Note: Storing the final answer array does not count toward this limit).
- Rule: You are not allowed to alter the Node structure to add a `parent` pointer. Solve this problem using pure tree recursion.

#### 5. Hints
- In a standard binary tree, you can only traverse downward. To find nodes at distance K that are "above" or in completely different branches than the target, you must figure out a way to send information back up the tree.
- Think about what a recursive function returns. If a child node finds the target, what single integer value should it return to its parent so the parent knows exactly what to do?
- You will likely need two distinct behaviors in your code:
  - A way to find nodes exactly $D$ steps strictly downward from any given node.
  - A way to bubble information upward from the target, calculating the remaining distance needed in the opposite branches.
- If the output must be ascending, sort the collected answers before printing them.

#### 6. Submission & Setup Requirements
- Directory structure: inside `W05_E03C`, submit exactly one source file `main.cpp`.
- Allowed libraries: `<iostream>`, `<fstream>`, `<string>`.
- Program must accept exactly two CLI arguments: input path and output path.

#### 7. Template for `main.cpp`
See `W05_E03C/main.cpp`.

