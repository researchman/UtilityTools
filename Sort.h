#ifndef UTILITY_TOOL_SORT_H
#define UTILITY_TOOL_SORT_H

/*
排序算法的分类如下：
1.插入排序（直接插入排序、折半插入排序、希尔排序）
2.交换排序（冒泡泡排序、快速排序）
3.选择排序（直接选择排序、堆排序）
4.归并排序；
5.分配排序（基数排序、箱排序）
*/

namespace Sort {
	//排序思路：每次将一个待排序的元素与已排序的元素进行逐一比较，直到找到合适的位置按大小插入
	template<class Typename>
	void InsertSort(Typename arr[], const int& length);



	template<class Typename>
	void InsertSort(Typename arr[], const int & length)
	{
		for (size_t i = 1; i < length; i++)
		{
			//从小到大排序，如果需要从大到小排序，可以改下面的为大于号
			if (arr[i] < arr[i-1]) {
				Typename temp = arr[i];
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

#endif // !UTILITY_TOOL_SORT
