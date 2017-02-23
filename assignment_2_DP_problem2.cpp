#include<iostream>
#include <sstream>
#include <string>
using namespace std;

struct node{
    node *link;
    string data;
};

class Bad{
      public:
    node *first,*last;
    Bad(){
        first=NULL;
        
    }
    void insert(string d){
        if(first==NULL){
            node *nnode=new node();
            nnode->data=d;
            nnode->link=NULL;
            first=nnode;
            last=first->link;
            
        }
        else{node *nnode=new node();
            nnode->data=d;
            last->link=nnode;
            
            last=last->link;
            
        }
    }
    bool checkBad(string s1,string s2){
        node *p=first;
        bool b=false;
        while(p){
            if((p->data==s1)||(p->data==s2))
            {
                b=true;
                return b;
            }
            else
            p=p->link;
        }
        
        return b;
    }
};

class AvoidRoads{
    private :
    long long count=1;
    Bad Badroad;
    int width,height;
    public:
    AvoidRoads(){
        cin>>width;
        cin>>height;
        int badNum;
        cout<<"Enter number of bad road block"<<endl;
        cin>>badNum;
        for(int i=0;i<badNum;i++){
            int x1,y1,x2,y2;
            cin>>x1>>y1>>x2>>y2;
            string s=change_to_string( x1, y1,x2,y2);
            
            Badroad.insert(s); 
        }
    }
    string change_to_string(int x1,int y1,int x2,int y2){
    string Result;         
   ostringstream convert;  
   convert <<x1<<" "<<y1<<" "<<x2<<" "<<y2;     
    Result = convert.str();
     return Result;
   }
     void checkpoint(int i,int j){
    if((i<=width)&&(j<=height)){
      string A1= change_to_string(i,j,i+1,j) ;
      string A2= change_to_string(i+1,j,i,j) ;
      string B1=change_to_string(i,j,i,j+1);
      string B2=change_to_string(i,j+1,i,j);
      bool a=~Badroad.checkBad(A1,A2);
      bool b=~Badroad.checkBad(B1,B2);
      int fork=0;
      int first_count,second_count;
      if(a&&(i+1<=height)){
          fork++;
          checkpoint(i+1,j);
      }
      if(b&&(j+1<=width)){
          if(fork==1)
          count++;
          checkpoint(i,j+1);
      }
     
      
    }
    
}
long long ReturnCount(){
    return count;
}

};

int main(){
    AvoidRoads A;
    A.checkpoint(0,0);
    long long max_Road=A.ReturnCount();
    
    cout<<max_Road<<endl;
    return 0;
}
