#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

struct Point {
    int r, c;
};

// --- HELPER FUNCTIONS (DO NOT MODIFY) ---
int** loadMatrix(ifstream& infile, int& M, int& N, int& sr, int& sc, int& newColor) {
    if (!(infile >> M >> N >> sr >> sc >> newColor)) return nullptr;

    int** image = new int*[M];
    for (int i = 0; i < M; i++) {
        image[i] = new int[N];
        for (int j = 0; j < N; j++) {
            infile >> image[i][j];
        }
    }
    return image;
}

void printMatrix(ofstream& outfile, int** image, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            outfile << image[i][j] << (j == N - 1 ? "" : " ");
        }
        outfile << "\n";
    }
}

void freeMatrix(int** image, int M) {
    for (int i = 0; i < M; i++) {
        delete[] image[i];
    }
    delete[] image;
}

// --- YOUR CODE HERE ---
void floodFillIterative(int** image, int M, int N, int sr, int sc, int newColor) {
    int oldColor = image[sr][sc];
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    queue<Point> q;
    q.push({sr, sc});
    while(!q.empty()){
        int l = q.front().r;
        int r = q.front().c;
        q.pop();
        image[l][r] = newColor;
        for (int i = 0; i < 4;i++){
            int x = l + dx[i], y = r + dy[i];
            if(x>=0 && x<=M && y>=0 && y<=N && image[x][y]==oldColor)
                q.push({x, y});
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
        cout << "Error opening files.\n";
        return 1;
    }

    int M, N, sr, sc, newColor;
    int** image = loadMatrix(infile, M, N, sr, sc, newColor);
    
    if (image == nullptr) {
        cout << "Invalid input format.\n";
        return 1;
    }

    floodFillIterative(image, M, N, sr, sc, newColor);

    printMatrix(outfile, image, M, N);
    freeMatrix(image, M);

    infile.close();
    outfile.close();

    return 0;
}