/* Test sorts
 * Used in realtime with cutom types
 * By: Mithun C
 */
#include "bubblesort.h"
#include "testmanuers.h"

#define QuickSortDefaultTest 0
#define QuickSortCustomTypeTest 1

void testTestmanuers(){
    TestManuers a(1, 0, 0);
    TestManuers a1(1, 0, 0);
    std::cout<< (a == a1 ? "a same" : "a1 not same") <<std::endl;

    TestManuers b(10, 0, 0);
    TestManuers b1(1, 0, 0);
    std::cout<< (b > b1 ? "bgreater" : "b1 not greater") <<std::endl;

    TestManuers c(1, 0, 0);
    TestManuers c1(10, 0, 0);
    std::cout<< (c > c1 ? "C greater" : "C not greater") <<std::endl;
    std::cout<< (c < c1 ? "C lesser" : "C not lesser") <<std::endl;
}

int main()
{
#if QuickSortDefaultTest
    int arr[] = {7, 10, 8, 9, 1, 11};
    quicksort::n = sizeof(arr) / sizeof(arr[0]);
    quicksort::dsorts::quickSort(arr, 0, quicksort::n - 1);
    quicksort::dsorts::printArray(arr, quicksort::n);

    std::cout<<"*****************************"<<std::endl;

    std::vector<int> testarr {64, 25, 12, 22, 11};
    quicksort::tsorts::quickSort(testarr, 0, testarr.size()-1);
    std::cout<<testarr<<std::endl;
#endif

#if QuickSortCustomTypeTest
    std::vector<TestManuers> manuerArr{ TestManuers(7, 0, 0),
                                        TestManuers(10, 0, 0),
                                        TestManuers(8, 0, 0),
                                        TestManuers(9, 0, 0),
                                        TestManuers(1, 0, 0),
                                        TestManuers(11, 0, 0)
                                      };

    quicksort::tsorts::quickSort(manuerArr, 0, manuerArr.size()-1);
    std::cout<<manuerArr<<std::endl; // Expected output [1, 0, 0] [7, 0, 0] [8, 0, 0] [9, 0, 0] [10, 0, 0] [11, 0, 0]

 #endif
    return 0;
}
