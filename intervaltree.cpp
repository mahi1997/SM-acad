#include <iostream>
using namespace std;
struct interval{
	int low,high;
};
interval* newinterval(int l,int h){
	if(l<=h){
		interval *temp=new interval();
		temp->low=l;
		temp->high=h;
		return temp;
	}
}

struct node{
	node *parent;
	node *left;
	node *right;
	char color;
	int max;
	interval *I;
};
class IntervalTree{
	public:
	node *root;
		IntervalTree(){
			root=NULL;
			
		}
		void insert(node *,interval *);
		void search(interval *);
		void insertfix(node *);
        void leftrotate(node *);
        void rightrotate(node *);
        
        void display( node *,int);
};

//insert function
void IntervalTree::insert(node *nnode,interval *newI)
{  
   
   interval *i=new interval();
   i->low=newI->low;
   i->high=newI->high;
   nnode->I=i;
    
    nnode->left=NULL;
	nnode->right=NULL;
    nnode->max=(nnode->I)->high;
    
    nnode->color='r'; //color red first
    
     if(root==NULL)
     { 
           nnode->parent=NULL; 
		   root=nnode; 	   
     }
     else
     {node *p,*pp;
     p=root;
     pp=NULL;
         while(p!=NULL)
         {  
              pp=p;
              if(p->max<nnode->max)
              p->max=nnode->max;
              
              if((p->I)->low<(nnode->I)->low)
                  {
                  p=p->right;}
                   
              else
                  p=p->left;
         }
        
         nnode->parent=pp;
         if((pp->I)->low<(nnode->I)->low)
              pp->right=nnode;
         else
              pp->left=nnode;
     }
     
     insertfix(nnode);
}
//-------------
//insertion fix program
void IntervalTree::insertfix(node *currentnode)
{
     node *uncle;
     if(root==currentnode)
     { /// root node
         currentnode->color='b';
         return;
     }
     while(currentnode->parent!=NULL&&currentnode->parent->color=='r')
     {
           node *grandpa=currentnode->parent->parent;
           if(grandpa->left==currentnode->parent)
           {//parent is in left of grandparent
                        if(grandpa->right!=NULL)
                        {//uncle in right of grandparent
                              uncle=grandpa->right;
                              if(uncle->color=='r')
                              {//uncle color is red 
                                   currentnode->parent->color='b';
                                   uncle->color='b';
                                   grandpa->color='r';
                                  currentnode =grandpa;
                              }
                        }
                        else
                        {//no uncle case
                            if(currentnode->parent->right==currentnode)
                            {  //cureent node is in right of parent node
                                 currentnode=currentnode->parent;
                                 leftrotate(currentnode);
                            }
                            currentnode->parent->color='b';
                            grandpa->color='r';
                            rightrotate(grandpa);
                        }
           }
           else
           {
                        if(grandpa->left!=NULL)
                        {
                             uncle=grandpa->left;
                             if(uncle->color=='r')
                             {
                                  currentnode->parent->color='b';
                                  uncle->color='b';
                                  grandpa->color='r';
                                  currentnode=grandpa;
                             }
                        }
                        else
                        {
                            if(currentnode->parent->left==currentnode)
                            {
                                   currentnode=currentnode->parent;
                                   rightrotate(currentnode);
                            }
                            currentnode->parent->color='b';
                            grandpa->color='r';
                            leftrotate(grandpa);
                        }
           }
           root->color='b';
     }
}

//------------------
//left rotate
void IntervalTree::leftrotate(node *currentnode)
{
     if(currentnode->right==NULL)
           return ;
     else
     {
           node *Tnode=currentnode->right;
           if(Tnode->left!=NULL)
           {
                  currentnode->right=Tnode->left;
                  Tnode->left->parent=currentnode;
           }
           else
                  currentnode->right=NULL;
           if(currentnode->parent!=NULL)
                Tnode->parent=currentnode->parent;
           if(currentnode->parent==NULL)
                root=Tnode;
           else
           {
               if(currentnode==currentnode->parent->left)
                       currentnode->parent->left=Tnode;
               else
                       currentnode->parent->right=Tnode;
           }
           Tnode->left=currentnode;
           currentnode->parent=Tnode;
     }
}
//-----------------------
//right rotate
void IntervalTree::rightrotate(node *currentnode)
{
     if(currentnode->left==NULL)
          return ;
     else
     {
         node *Tnode=currentnode->left;
         if(Tnode->right!=NULL)
         {
                  currentnode->left=Tnode->right;
                  Tnode->right->parent=currentnode;
         }
         else
                 currentnode->left=NULL;
         if(currentnode->parent!=NULL)
                 Tnode->parent=currentnode->parent;
         if(currentnode->parent==NULL)
               root=Tnode;
         else
         {
             if(currentnode==currentnode->parent->left)
                   currentnode->parent->left=Tnode;
             else
                   currentnode->parent->right=Tnode;
         }
         Tnode->right=currentnode;
         currentnode->parent=Tnode;
     }
}

///-----------------
//display tree
void IntervalTree::display(node *r,int level)
{
     if(root==NULL)
     {
          cout<<"\nEmpty IntervalTree."<<endl;
          return ;
     }
     if(r!=NULL)
     {
	 //inorder traversal
	 display(r->left,level+1);
	 cout<<"("<<(r->I)->low<<","<<(r->I)->high<<")  :max="<<r->max<<" color="<<r->color<<"  level:"<<level<<endl;
	 display(r->right,level+1);
     }
}
//-------------
int main(){
	IntervalTree IT;
	
	for(int i=0;i<5;i++){
		int l,h;
		cin>>l>>h;
		interval *inter=newinterval(l,h);
		//inter->low=l;
		//inter->high=h;
		node *n=new node();
		IT.insert(n,inter);
	}
	IT.display(IT.root,0);
	return 0;
}
