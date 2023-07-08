/* testing selection sorts
 * Used in realtime with cutom types
 * By: Mithun C
 */

#include "common.h"

using namespace common;

namespace selectionsort{
typedef unsigned long size_k;

template <typename T>
void sort(std::vector<T> &arr, size_k length){

    size_k minValIndex = 0;
    for (size_k i = 0; i<=length-1; i++){
        minValIndex = i;
        for(size_k j = i+1; j<length; j++){
            if(arr[j] < arr[minValIndex] ){
                minValIndex = j;
            }
        }
        if(minValIndex != i)
            swap(arr[minValIndex], arr[i]);
    }
}
}
