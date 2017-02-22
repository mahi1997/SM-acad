#include <iostream>

using namespace std;
int longestZigZag(int *Array,int N){
    
    int n=N-1;
    int *A=new int[n];
    for(int i=0;i<n;i++)
    A[i]=Array[i+1]-Array[i];
    
    int *C=new int[n];
    for(int i=0;i<n;i++)
    C[i]=1;
    int max_index=0;
    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++){
            if(A[j]*A[i]<0){
                if(C[j]+1>C[i])
                C[i]=C[j]+1;
            }
        }
        max_index=(C[max_index]>C[i])?max_index:i;
        
    }
    int previous_number;
    
   /* cout<<"Longest zigzag sequence is :";
    for(int i=0;i<= max_index;i++){
        if(A[i]*A[max_index]<0){
                if(C[i]+1>C[max_index])
                {
                    cout<<Array[i]<<" ";
                    previous_number=Array[i+1];
                }
            }
    }
    cout<<previous_number<<endl;
    */
    return C[max_index]+1;
    
    
}
int main()
{
   int N;
   cout<<"enter N"<<endl;
   cin>>N;
   int Array[N];
   for(int i=0;i<N;i++)
   cin>>Array[i];
   int legth_longestZigzag= longestZigZag(Array,N);
   cout<<"Length of longest zigzag subsequence is:"<<legth_longestZigzag<<endl;
   
   return 0;
}


