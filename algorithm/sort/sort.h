#ifndef ALGORITHM_SORT_H
#define ALGORITHM_SORT_H

#include <vector>
using namespace std;

/*
排序算法的分类如下：
1.插入排序（直接插入排序、折半插入排序、希尔排序）
2.交换排序（冒泡泡排序、快速排序）
3.选择排序（直接选择排序、堆排序）
4.归并排序；
5.分配排序（基数排序、箱排序）
*/

namespace algorithm{
    namespace sort{
        /*
        * 快速排序:
        * (1)选择基准：在待排序列中，按照某种方式挑出一个元素，作为 "基准"（pivot）；
        * (2)分割操作：以该基准在序列中的实际位置，把序列分成两个子序列。此时，在基准左边的元素都比该基准小，在基准右边的元素都比基准大；
        * (3)递归地对两个序列进行快速排序，直到序列为空或者只有一个元素。
        */
        template<typename type>
        void quick_sort(vector<type>& v,int left,int right){
            if(left < right){
                type key = v[left];
                int low = left;
                int high = right;

                while(low < high){
                    while(low < high && v[high] >= key){
                        high--;
                    }
                    swap(v[low],v[high]);

                    while(low < high && v[low] <= key){
                        low++;
                    }
                    swap(v[low],v[high]);
                }

                quick_sort(v,left,low-1);
                quick_sort(v,low+1,right);
            }
        }

        /*
        //排序思路：每次将一个待排序的元素与已排序的元素进行逐一比较，直到找到合适的位置按大小插入
        */
        template<typename type>
        void insert_sort(type arr[], const int & length)
        {
            for (size_t i = 1; i < length; i++)
            {
                //从小到大排序，如果需要从大到小排序，可以改下面的为大于号
                if (arr[i] < arr[i-1]) {
                    type temp = arr[i];
                    int j = 0;
                    //把比temp元素大或相等的元素都往后移位
                    for (j = i - 1;j>=0&&arr[j]>temp;j--) {
                        arr[j + 1] = arr[j];
                    }
                    //把待排序的元素放到j+1处
                    arr[j+1] = temp;
                }
            }
        }
    }
}

#endif