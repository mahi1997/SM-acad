#include <iostream>

using namespace std;
class IntervalTree{
  private: 
   struct node{
        int low;
        int high;
        int max;
        node* left; node* right;
    };
    public :
     node *root ;
     IntervalTree(){
        
        root=NULL;
    }
    void insert(node* nnode,int i,int h){
        if(root==NULL){
            
            root->left=NULL;
            root->right=NULL;
            root->max=h;
            root->low=i;
            root->high=h;
            
        }
        else{
            if(nnode!=NULL){
            nnode->max=(nnode->max>h)?nnode->max:h;
            if(nnode->low>i)
            insert(nnode->left,i,h);
            else
            insert(nnode->right,i,h);}
            else{
                nnode->low=i;
                nnode->high=h;
                nnode->max=h;
                nnode->left=NULL;
                nnode->right=NULL;
            }
            
        }
    }
    void display(node* nnode){
    	if(nnode!=NULL){
    	
        cout<<"("<<nnode->low<<","<<nnode->right<<")  "<<nnode->max<<endl;
        display(nnode->left);
        display(nnode->right);}
        else 
        return;
        
    }
};
int main()
{
   IntervalTree IT;
   IT.insert(IT.root,15,20);
    IT.insert(IT.root,10,30);
    IT.insert(IT.root,10,15);
     IT.insert(IT.root,17,19);
      IT.insert(IT.root,5,20);
       IT.display(IT.root);
   return 0;
}


