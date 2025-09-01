#ifndef UTILS_H
#define UTILS_H

#include <vector>

std::vector<int> generateRandomNumsArray(int size, int min = 0, int max = std::numeric_limits<int>::max());
int generateRandomNumber(int min = 0, int max = std::numeric_limits<int>::max());
void mergeSort(std::vector<int>& arr, int left, int right);
void printArray(std::vector<int> arr);

#endif
