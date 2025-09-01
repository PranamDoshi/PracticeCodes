#include<iostream>
#include<vector>
#include<random>
#include<limits>

using std::vector;
using std::cout;

void printArray(vector<int> arr){
    for(int a:arr){
        cout << a << ", ";
    }
    cout << std::endl;
}

vector<int> generateRandomNumsArray(int size, int min = 0, int max = std::numeric_limits<int>::max()){
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::uniform_int_distribution<> dis(min, max);

    vector<int> randomVector(size);
    for(int i=0;i<size;i++){
        randomVector[i] = dis(gen);
    }
    return randomVector;
}

void mergeSortMerge(vector<int>& arr, int left, int mid, int right){
    int a1 = mid - left + 1, a2 = right - mid;

    vector<int> L(a1), R(a2);

    for(int i=0;i< a1; i++){
        L[i] = arr[left+i];
    }
    for(int j=0;j< a2; j++){
        R[j] = arr[mid+j+1];
    }

    int i=0, j=0, k=left;

    while(i<a1 && j<a2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<a1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j<a2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right){
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    mergeSortMerge(arr, left, mid, right);
}

int generateRandomNumber(int min = 0, int max = std::numeric_limits<int>::max()){
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
