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
            last=first;
            
            
        }
        else{node *nnode=new node();
            nnode->data=d;
            last->link=nnode;
            
            last=last->link;
            
        }
        cout<<"--inserted"<<last->data<<"."<<endl;
    }
    bool checkBad(string s1,string s2){
        node *p=first;
        bool b=true;
        while(p){
            if((p->data==s1)||(p->data==s2))
            {
                b=false;
                cout<<"equal"<<endl;
                break;
                
            }
            else
            p=p->link;
        }
        
        return b;
    }
};

class AvoidRoads{
    private :
    
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
            string s;
            int x1,y1,x2,y2;
            cin>>x1>>y1>>x2>>y2;
            s=change_to_string(x1,y1,x2,y2);
            Badroad.insert(s); 
            cout<<endl;
        }
    }
   
     string change_to_string(int ,int,int,int);
     long long checkpoint();
     

};
 string AvoidRoads::change_to_string(int x1,int y1,int x2,int y2){
    string Result;         
   ostringstream convert;  
   convert <<x1<<" "<<y1<<" "<<x2<<" "<<y2;     
    Result = convert.str();
     return Result;
   }
   
   
long long AvoidRoads:: checkpoint(){
long long T[height+2][width+2];
for(int i=0;i<height+2;i++)
T[i][width+1]=0;
for(int j=0;j<width+2;j++)
T[height+1][j]=0;

for(int i=height;i>=0;i--){
for(int j=width;j>=0;j--){
    //at point where we have to reach
	if(i==height&&j==width)
	T[width][height]=1;
	//at other points
	if((i==height) &&(j!=width)){
	string B1=change_to_string(i,j,i,j+1);
      string B2=change_to_string(i,j+1,i,j);
	bool b=Badroad.checkBad(B1,B2);
	if(b){
	T[i][j]=T[i][j+1];
	}
	else
	T[i][j]=0;
	
	}
	//---------
	if(j==width && (i!=height)){
	string A1= change_to_string(i,j,i+1,j) ;
    string A2= change_to_string(i+1,j,i,j) ;
	bool a=Badroad.checkBad(A1,A2);
	if(a){
	T[i][j]=T[i+1][j];
	}
	else
	T[i][j]=0;
}
	//----
	
if(i<height && j<width){
      string A1= change_to_string(i,j,i+1,j) ;
      string A2= change_to_string(i+1,j,i,j) ;
      string B1=change_to_string(i,j,i,j+1);
      string B2=change_to_string(i,j+1,i,j);
      bool a=Badroad.checkBad(A1,A2); // for T[i+1][j]
      bool b=Badroad.checkBad(B1,B2);  // for T[i][j+1]
	  //both roads are open
	  if(a&&b){
	  T[i][j]=T[i][j+1]+T[i+1][j];
	  }
	  //if one road is block
	  if(a==true&&b==false){
	  T[i][j]=T[i+1][j];
	  }
	  if(a==false&&b==true){
	  T[i][j]=T[i][j+1];
	  }
	  if(a==false && b==false)
	  T[i][j]=0;

}
	
	
	}
}

return T[0][0];  // max distinct road to reach
}


int main(){
    AvoidRoads A;
    long max_Road=A.checkpoint();
    cout<<max_Road<<endl;
    return 0;
}
