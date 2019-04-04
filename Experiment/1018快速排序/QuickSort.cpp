#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string.h>
using namespace std;

#define maxsum 20000

int Partition(int L[maxsum], int low, int high) {  // 算法10.6(b)
   // 交换顺序表L中子序列L.r[low..high]的记录，使枢轴记录到位，
   // 并返回其所在位置，此时，在它之前（后）的记录均不大（小）于它
   int pivotkey;
   L[0] = L[low];            // 用子表的第一个记录作枢轴记录
   pivotkey = L[low];      // 枢轴记录关键字
   while (low<high) {            // 从表的两端交替地向中间扫描
      while (low<high && L[high]>=pivotkey) --high;
      L[low] = L[high];      // 将比枢轴记录小的记录移到低端
      while (low<high && L[low]<=pivotkey) ++low;
      L[high] = L[low];      // 将比枢轴记录大的记录移到高端
   }
   L[low] = L[0];            // 枢轴记录到位
   return low;                   // 返回枢轴位置
} // Partition

void QSort(int L[maxsum], int low, int high) {  //算法10.7
  // 对顺序表L中的子序列L.r[low..high]进行快速排序
  int pivotloc;
  if (low < high) {                      // 长度大于1
    pivotloc = Partition(L, low, high);  // 将L.r[low..high]一分为二
    QSort(L, low, pivotloc-1); // 对低子表递归排序，pivotloc是枢轴位置
    QSort(L, pivotloc+1, high);          // 对高子表递归排序
  }
} // QSort

int main(){
	int n;
    int L[maxsum];
    memset(L,0,sizeof(L));
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;i++){
			scanf("%d",&L[i]);
		}
		QSort(L,1,n);
		for(int i=1;i<=n;i++)
		{
			printf("%d ",L[i]);
		}
	} 
}
