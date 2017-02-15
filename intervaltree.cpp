#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
class IntervalTree
{
    struct node
    {   int low,high,max;
        
        node *parent;
        node *right;
        node *left;
    };
public:
    node *root;
    IntervalTree()
    {
        root=NULL;  
    }

    void insert(int l,int h)
    {
        if(root==NULL)
        {
            root = new node;
            root->low =l;
            root->high=h;
            root->max=h;
        
            root->parent=NULL;
            root->left = NULL;
            root->right = NULL;
        }
        else
        {
		//cout<<"came to else root "<<endl;
		node *p=root;
        node *pp=NULL;
        while(p){
        	pp=p;
        	if(p->max<h)
        	p->max=h;
        	if(l<p->low)
        		p=p->left;
        		
        	
        	else
        	p=p->right;
        }
        node *nnode=new node;
        nnode->low=l;
        nnode->high=h;
        nnode->parent=pp;
        nnode->left=NULL;
        nnode->right=NULL;
  
        nnode->max=h;
        
        if(l>=pp->low)
        {pp->right=nnode;
        }
        else{
        	pp->left=nnode;
        }
       
    }
}
    void display(node *ptr,int level)
    {//cout<<"displaying"<<endl;
        if(root==NULL)
		cout<<"interval tree is empty"<<endl;
        else
        {
            if(ptr->left)
                display(ptr->left,level+1);
                
            cout<<"("<<ptr->low<<","<<ptr->high<<" )  :"<< ptr->max<<" level:"<<level<<endl;   ///in-order traversal..
            if(ptr->right)
                display(ptr->right,level+1);
        }
    }
    
};
int main(){
	IntervalTree IT;
	
	IT.insert(15,20);
	IT.insert(10,30);
	IT.insert(17,19);
	IT.insert(5,20);
	IT.insert(12,15);
	IT.insert(30,40);
	IT.display(IT.root,0);
	return 0;
}
