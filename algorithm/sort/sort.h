#ifndef ALGORITHM_SORT_H
#define ALGORITHM_SORT_H

#include <vector>
using namespace std;

namespace algorithm{
    namespace sort{
        /*
        * 快速排序
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
    }
}

#endif