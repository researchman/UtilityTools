#ifndef ALGORITHM_SORT_H
#define ALGORITHM_SORT_H

#include <vector>
using namespace std;

namespace algorithm{
    namespace sort{
        /*
        * 快速排序:
        * 1.select
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
        */
        template<typename type>
        void insert_sort(Typename arr[], const int & length)
        {
            for (size_t i = 1; i < length; i++)
            {
                //´ÓÐ¡µ½´óÅÅÐò£¬Èç¹ûÐèÒª´Ó´óµ½Ð¡ÅÅÐò£¬¿ÉÒÔ¸ÄÏÂÃæµÄÎª´óÓÚºÅ
                if (arr[i] < arr[i-1]) {
                    Typename temp = arr[i];
                    int j = 0;
                    //°Ñ±ÈtempÔªËØ´ó»òÏàµÈµÄÔªËØ¶¼ÍùºóÒÆÎ»
                    for (j = i - 1;j>=0&&arr[j]>temp;j--) {
                        arr[j + 1] = arr[j];
                    }
                    //°Ñ´ýÅÅÐòµÄÔªËØ·Åµ½j+1´¦
                    arr[j+1] = temp;
                }
            }
        }
    }
}

#endif