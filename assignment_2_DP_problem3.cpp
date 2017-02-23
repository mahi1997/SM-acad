#include <iostream>

using namespace std;
struct node{
        node *link;
        int data;
        
    };
class CircularList{
    
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


int longestIS(CircularList CList,int n){
    int overall_max=0;
    node* start=CList.head;
    for(int k=0;k<n;k++){
    //----
    int *C=new int[n];
    for(int i=0;i<n;i++)
    C[i]=1;
    int max=0;
    node *q=start->link;
    for(int i=1;i<n;i++){
        node *p=start;
        for(int j=0;j<i;j++){
            if(p->data<q->data){
                if(C[j]+1>C[i])
                C[i]=C[j]+1;
            }
             p=p->link;
            max=(max>C[i])?max:C[i];
        }
        q=q->link;
    }
    //----
    start=start->link;
    overall_max=(overall_max>max)?overall_max:max;
    }
    return overall_max;
    
    
}

int main(){
    int T;
    cin>>T;
    int list[T];
    for(int k=0;k<T;k++){
    int N;
    cin>>N;
    CircularList C;
    for(int i=0;i<N;i++){
        int a;
        cin>>a;
        C.insert(a);
    }
    list[k]=longestIS( C,N);
    }
    for(int k=0;k<T;k++)
    cout<<list[k]<<endl;
    return 0;
}
