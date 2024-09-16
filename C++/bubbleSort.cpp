#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
#include <chrono>

using std::cout;
using std::endl;
using std::vector;

int takeUserInput(int size){
    cout << "Array size is selected as " << size << ", Please provide a different if you want:";
    std::string input;
    std::getline(std::cin, input);

    if(!input.empty()){
        return std::stoi(input);
    }
    else{
        return size;
    }
}

vector<int> generateAsampleArray(int size){
    vector<int> sampleArray(size);
    for(int i=0;i<size;i++){
        sampleArray[i] = (rand()%size) +1;
    }
    return sampleArray;
}

int getSizeOfArray(vector<int> array){
    // cout << sizeof(array) << endl;
    return array.size();
}

vector<int> swapIndexes(vector<int> array, int index1, int index2){
    int temp = array[index2];
    array[index2] = array[index1];
    array[index1] = temp;
    return array;
}

void printArray(vector<int> array){
    for(int value:array){
        cout << value << " ";
    }
    cout << endl;
}

vector<int> bubbleSort(vector<int> sampleArray){
    int index1, index2, temp;
    int arraySize = getSizeOfArray(sampleArray);

    for(index1=0;index1<arraySize;index1++){
        for(index2=0;index2<arraySize-index1-1;index2++){
            if(sampleArray[index2] > sampleArray[index2+1]){
                // sampleArray = swapIndexes(sampleArray, index2, index2+1);
                int temp = sampleArray[index2];
                sampleArray[index2] = sampleArray[index2+1];
                sampleArray[index2+1] = temp;
                // printArray(sampleArray);
            }
        }
    }

    return sampleArray;
}

int main(){
    srand(time(0));
    int size = takeUserInput(10000);

    vector<int> sampleArray = generateAsampleArray(size);

    // printArray(sampleArray);
    cout << "Size of the generated array is: " << getSizeOfArray(sampleArray) << endl;

    // float sorting_start = time(0);
    auto sorting_start = std::chrono::high_resolution_clock::now();
    sampleArray = bubbleSort(sampleArray);
    // float sorting_end = time(0);
    auto sorting_end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> sorting_time = sorting_end-sorting_start;

    // printArray(sampleArray);
    cout << "Time taken to sort the array of size " << size << ": " << std::setprecision(10) << std::fixed << sorting_time.count() << " seconds!" << endl;

    return 0;
}
