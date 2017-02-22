#include <iostream>

using namespace std;
class CircularList{
    struct node{
        node *link;
        int data;
        
    };
    public:
    node *head,*last;
    CircularList(){
        head=NULL;
        last=NULL;
    }
    void insert(int d){
        if(head==NULL){
            node *nnode=new node();
            nnode->data=d;
            head=nnode;
            last=nnode;
            head->link=last;
        }
        else{node *nnode=new node();
            nnode->data=d;
            last->link=nnode;
            nnode->link=head;
            last=nnode;
            
        }
    }
    void display(){
        cout<<head->data<<" ";
        node* p=head->link;
        while(p!=head){
            cout<<p->data<<" ";
            p=p->link;
        }
        cout<<endl;
    }
    
};


int longestIS(CircularList C){
    
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
   cout<<"Length of zigzag sequence is:"<<legth_longestZigzag<<endl;
   
   return 0;
}
*/
//------------
int main(){
    int N;
    cin>>N;
    CircularList C;
    for(int i=0;i<N;i++){
        int a;
        cin>>a;
        C.insert(a);
    }
    C.display();
}


