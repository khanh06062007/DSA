#include<iostream>
#include<vector>
using namespace std;

void print(int a[], int n){
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << '\n';
}
void selection_sort(int a[], int n){
    for (int i = 0; i < n; i++){
        int min_idx = i;
        for (int j = i + 1; j < n; j++){
            if(a[min_idx] > a[j])
                min_idx = j;
        }
        swap(a[min_idx], a[i]);
    }
}
void bubble_sort(int a[], int n){
    bool swapped;
    for (int i = 0; i < n; i++){
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]){
                swap(a[j], a[j+1]);
                swapped = true;
            }
        if(!swapped)
            break;
    }
}
void weird_sort(int a[],int n){
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if(a[i]>a[j])
                swap(a[j], a[i]);
}
void insertion_sort(int a[],int n){
    for (int i = 1; i < n; i++){
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}
void heapify(int a[], int n, int i){
    int best = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && a[l] > a[best])
        best = l;
    if (r < n && a[r] > a[best])
        best = r;
    if (best != i){
        swap(a[best],a[i]);
        heapify(a, n, best);
    }
}
void heap_sort(int a[], int n){
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    for (int i = n - 1; i > 0; i--){
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}
void merge(int a[], int l, int mid, int r){
    int nleft = mid - l + 1;
    int nright = r - mid;
    int *left = new int[nleft];
    int *right = new int[nright];
    for (int i = 0; i < nleft; i++)
        left[i] = a[l + i];
    for (int i = 0; i < nright;i++)
        right[i] = a[mid + i + 1];

    int i = 0, j = 0, k = l;
    while (i < nleft && j < nright){
        if (left[i] <= right[j]){
            a[k] = left[i];
            i++;
        }
        else{
            a[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < nleft)
        a[k] = left[i], i++, k++;
    while (j < nright)
        a[k] = right[j], j++, k++;
    delete[] left;
    delete[] right;
}
void merge_sort(int a[], int l, int r){
    if (l >= r)
        return;
    int mid = l + (r - l) / 2;
    merge_sort(a, l, mid);
    merge_sort(a, mid + 1, r);
    merge(a, l, mid, r);
}
void quick_sort(int a[], int l, int r){
    if(l>=r)
        return;
    int i = l, j = r, mid = a[l + (r - l) / 2];
    while(i < j){
        while (a[i] < mid)
            i++;
        while (a[j] > mid)
            j--;
        if (i <= j){
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if(l < j)
        quick_sort(a, l, j);
    if(i < r)
        quick_sort(a, i, r);
}
void counting_sort_subroutine(int a[], int n, long long exp){
    int count[10] = {0};
    int *output = new int[n];
    for (int i = 0; i < n; i++){
        int digit = (a[i] / exp) % 10;
        count[digit]++;
    }
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--){
        int digit = (a[i] / exp) % 10;
        output[count[digit] - 1] = a[i];
        count[digit]--;
    }
    for (int i = 0; i < n; i++)
        a[i] = output[i];
    delete[] output;
}
void radix_sort(int a[], int n){
    if (n <= 1)
        return;
    int minval = a[0], maxval = 0;
    for (int i = 1; i < n; i++)
        minval = min(minval, a[i]);
    for (int i = 0; i < n; i++)
        a[i] += (minval < 0 ? -minval : 0), maxval = max(maxval, a[i]);
    for (long long exp = 1; exp<=maxval; exp *= 10)
        counting_sort_subroutine(a, n, exp);
    for (int i = 0; i < n; i++)
        a[i] -= (minval < 0 ? -minval : 0);
}
int main(){
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    
    // selection_sort(a, n);
    // bubble_sort(a, n);
    // insertion_sort(a, n);
    // heap_sort(a, n);
    // merge_sort(a, 0, n-1);
    // quick_sort(a, 0, n - 1);
    // radix_sort(a, n);

    print(a, n);
}