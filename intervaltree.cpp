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
        void search(node *,interval *);
        void display( node *,int);
        
};

//--------------------------------------------insert function--------------------------------------------------
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
                  //--------
                  if(Tnode->left->max>Tnode->max)
                  {if(Tnode->right!=NULL)
                  Tnode->max=(Tnode->I->high>Tnode->right->max)?Tnode->I->high:Tnode->right->max;
				  else
				  Tnode->max=Tnode->I->high;
				  }
                    //------------       
           }
           else
                  {
                  currentnode->right=NULL;
                  //-------------
				  if(Tnode->max>currentnode->max){
				  	if(currentnode->left!=NULL)
				  	currentnode->max=(currentnode->I->high>currentnode->left->max)?currentnode->I->high:currentnode->left->max;
				  	else
				  	currentnode->max=currentnode->I->high;
				  }
				  //------
				  }
				  
				  
           if(currentnode->parent!=NULL)
                {
                Tnode->parent=currentnode->parent;
				//-----
				if(Tnode->max>currentnode->max){
					if(Tnode->max>currentnode->parent->max)
					currentnode->parent->max=Tnode->max;
				}
				//----
				}
           if(currentnode->parent==NULL)
                {
                root=Tnode;
				}
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
                  
                  //--------
                  if(Tnode->right->max>Tnode->max)
                  {if(Tnode->left!=NULL)
                  Tnode->max=(Tnode->I->high>Tnode->left->max)?Tnode->I->high:Tnode->left->max;
				  else
				  Tnode->max=Tnode->I->high;
				  }
                    //------------  
         }
         else
               {
                 currentnode->left=NULL;
                 //-------------
				  if(Tnode->max>currentnode->max){
				  	if(currentnode->right!=NULL)
				  	currentnode->max=(currentnode->I->high>currentnode->right->max)?currentnode->I->high:currentnode->right->max;
				  	else
				  	currentnode->max=currentnode->I->high;
				  }
				  //------
				 
				 }
         if(currentnode->parent!=NULL)
                 {
                 Tnode->parent=currentnode->parent;
				 //-----
				if(Tnode->max>currentnode->max){
					if(Tnode->max>currentnode->parent->max)
					currentnode->parent->max=Tnode->max;
				}
				//----
				}
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

///----------------------------------------------------------------------------------------------------------
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

//-------------------------------SEARCH (NODE, INTERVAL)---------------------------------------
void IntervalTree::search(node *nnode,interval *searchI){
	//cout<<searchI->low<<","<<searchI->high<<endl;
	 interval *i=new interval();
     i->low=searchI->low;
     i->high=searchI->high;
	if(nnode==NULL)
	{
	cout<<"No overlapping interval found"<<endl;
	return;}
	else{if(nnode->left!=NULL){
	     // node in left
		if(nnode->left->max<i->low){
			//not overlap  in left of subtree
			if(i->low<=nnode->I->high&&i->high>=nnode->I->low){
				cout<<"overlap with interval ("<<nnode->I->low<<","<<nnode->I->high<<")"<<endl;
			}
			else
			search(nnode->right,i);//go to right of tree
		}
		else{
			//go to left of tree
			search(nnode->left,i);
		}
	}else{
		//no left subtree
		if(i->low<=nnode->I->high&&i->high>=nnode->I->low){
				cout<<"overlap with interval ("<<nnode->I->low<<","<<nnode->I->high<<")"<<endl;
			}
			else
			search(nnode->right,i);//go to right of tree
	}
	
	}
}


//------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------
int main(){
	IntervalTree IT;
	
	for(int i=0;i<6;i++){
		int l,h;
		cin>>l>>h;
		interval *inter=newinterval(l,h);
		//inter->low=l;
		//inter->high=h;
		node *n=new node();
		IT.insert(n,inter);
	}
	IT.display(IT.root,0);
	interval *i1,*i2,*i3,*i4;
	i1=newinterval(14,16);
	i2=newinterval(21,23);
	i3=newinterval(0,4);
	i4=newinterval(100 ,200);
	IT.search(IT.root,i1);
	IT.search(IT.root,i2);
	IT.search(IT.root,i3);
	IT.search(IT.root,i4);
	
	return 0;
}
