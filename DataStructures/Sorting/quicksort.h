/* testing quick sorts
 * Used in realtime with cutom types
 * By: Mithun C
 */

#include <vector>
#include <iostream>
#include <ostream>
#include <algorithm>

std::ostream& operator<<(std::ostream& stream, const std::vector<int> &arr){
    for(auto e: arr){
        stream << e << " ";
    }
    return stream;
}

namespace quicksort{
static int n;
typedef unsigned long size_k;

template <typename T>
void swap(T &a, T&b){
    if(a == b){// there are chances with same values
        return;
    }
    auto temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}
namespace dsorts {

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        std::cout << arr[i] << " ";
}

/* To find the pivot, iterate from low to high
 * If finds, itr less than high, swap itr with adjecent,
 * increment the low
 * at last swap with the high by default and return pos of low
 */
int partition(int arr[], int low, int high)
{
    for (int j = low; j < high; j++) {
        if (arr[j] < arr[high]) {
            swap(arr[low], arr[j]);
            low++;
        }
    }
    swap(arr[low], arr[high]);
    return (low);
}

/* Use pivot finding to part the array
 * from min to pivot and pivot to max
 */
void quickSort(int arr[], int min, int max){
    if(min < max)
    {
        int pivot = partition(arr, min, max);
        quickSort(arr, min, pivot-1);
        quickSort(arr, pivot+1, max);
    }
}
}

namespace tsorts{
/*
 * If it is a custom defined type use
 *  < , > , == , = operators overloaded for that type
 */
template<typename T>
size_k partition(std::vector<T> &arr, size_k low, size_k high)
{
    for(auto j = low; j < high; j++){
        if(arr[j] < arr[high]){
            swap(arr[low], arr[j]);
            low++;
        }
    }
    swap(arr[low], arr[high]);
    return low;
}

template <typename T>
void quickSort(std::vector<T> &arr, size_k min, size_k max){
    if(min < max)
    {
        auto pivot = partition(arr, min, max);
        quickSort(arr, min, pivot == 0 ? 0 : pivot-1);
        quickSort(arr, pivot+1, max);
    }
}
}

}
