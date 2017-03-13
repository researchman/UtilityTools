#ifndef UTILITY_TOOL_SORT_H
#define UTILITY_TOOL_SORT_H

/*
�����㷨�ķ������£�
1.��������ֱ�Ӳ��������۰��������ϣ������
2.��������ð�������򡢿�������
3.ѡ������ֱ��ѡ�����򡢶�����
4.�鲢����
5.�������򣨻�������������
*/

namespace Sort {
	//����˼·��ÿ�ν�һ���������Ԫ�����������Ԫ�ؽ�����һ�Ƚϣ�ֱ���ҵ����ʵ�λ�ð���С����
	template<class Typename>
	void InsertSort(Typename arr[], const int& length);



	template<class Typename>
	void InsertSort(Typename arr[], const int & length)
	{
		for (size_t i = 1; i < length; i++)
		{
			//��С�������������Ҫ�Ӵ�С���򣬿��Ը������Ϊ���ں�
			if (arr[i] < arr[i-1]) {
				Typename temp = arr[i];
				int j = 0;
				//�ѱ�tempԪ�ش����ȵ�Ԫ�ض�������λ
				for (j = i - 1;j>=0&&arr[j]>temp;j--) {
					arr[j + 1] = arr[j];
				}
				//�Ѵ������Ԫ�طŵ�j+1��
				arr[j+1] = temp;
			}
		}
	}
}

#endif // !UTILITY_TOOL_SORT
