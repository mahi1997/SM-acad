#include<iostream>
#include<string> 
using namespace std;
 
int binarySearch(long long A[], int left, int right, long long key) 
{
  	while(left + 1 < right) 
		{
  	 	 	int mid = left + (right - left) / 2;
			if(A[mid]<key) 
  	   		 left = mid;
  	  		else 
  	    		right = mid;
  	 	 }
 	 return right;
}
 
int LongIncreasingSubsequence(long long A[], int length) 
{
	  long long *temp = new long long[length];
	  for(int i = 0; i < length; i++)
  	  temp[i] = 0;
	  int max_len;
	  temp[0] = A[0];  //put starting as number at choosen  seat
  	  max_len = 1;      //min length is only 1
  	  for(int i = 0; i < length; ++i) 
		{     
		// if A[i] is less than starting number of sequence then make it smallest 
		//smallest=temp[0]
		//highest in sequence=temp[max-len-1]
	    	 if(A[i] < temp[0])
      				temp[0] = A[i];
	    	 else if (A[i] > temp[max_len-1])  //if A[i] is greater than highest number in sequence than add it as highest and increase subsequence length
      			{	
				temp[max_len] = A[i];
      				max_len++;
			}
    		 else
			{   //arrange
      				long long key = A[i];
     				temp[binarySearch(temp, -1, max_len - 1, key)] = A[i];
   		 	}
		}
	 delete[] temp;
  	 return max_len;
}
 
int main() 
{
  	
	int T;
	cin>>T;
	int ans[T];
	for(int i=0;i<T;i++){
			int N;
   		    cin>>N;
    		long long Array[2*N]; // 2*n so that we can choose any person from 1 to ..N
 		for(int j = 0; j < N; j++)
		{
      			cin>>Array[j];
      			Array[j+N] = Array[j];
   		}
   	 int max = 0;
   	 for(int j = 0; j< N; j++) 
	{
    	 	int a = LongIncreasingSubsequence(Array+j, N);
      	 	if(a > max) 
         	max = a;
        }
		ans[i]=max;
	}
	for(int i=0;i<T;i++)
	cout<<ans[i]<<endl;
	return 0;
}
 
