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
        
        //void delet(node *,interval *);
        void deleteNode(node *,interval *);
        void deletefix(node *);
        node* nextbigAfterParentOf(node *);
        
        
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
///--------------------------DELETEION ---------------------------------------------------------------------

/*void IntervalTree::delet(node* r,interval *d){
	
	interval *i=new interval();
     i->low=d->low;
     i->high=d->high;
     
	if(r==NULL){
		cout<<"Sorry..No such interval found"<<endl;
		return;
	}else{
		if((i->low==r->I->low)&&(i->high==r->I->high)){
			deleteNode(r);
		}
		else{
			if(r->left->max<i->low)
			delet(r->right,i);
			else
			delet(r->left,i);
		}
		
	}
}
*/
//------------------------------------------------
//delete node and maintan interval tree
void IntervalTree::deleteNode(node *p,interval *d)
{   interval *i=new interval();
     i->low=d->low;
     i->high=d->high;
    //-----------------------------
    if(root==NULL)
     {
           cout<<"\nEmpty Tree." ;
           return ;
     }
     
    
     int found=0;
     while(p!=NULL&&found==0)
     {
           if(p->I->low==i->low &&p->I->high==i->high)
               {found=1;
               
               }
           if(found==0)
           {
                 if(p->left->max<i->low) p=p->right;
                 else
                    p=p->left;
           }
     }
     if(found==0)
     {
            cout<<"\nElement Not Found.";
            return ;
     }
	
	//------------------------ 
    else{
    	
    node *T1,*T2;
    cout<<"Deleted node interval: ("<<p->I->low<<","<<p->I->high<<") color: "<<p->color<<endl;
         
       if(p->left==NULL||p->right==NULL) //p has atmost one child      
		      T1=p;                                                       
         else
              { 
              T1=nextbigAfterParentOf(p);//two child case
			      //eigther biggest from left of subtree or smallest from right of subtree with node p                       
                   //this node will be swapped with deleting node in two child case
                   
				   }
		 if(T1->left!=NULL)
              T2=T1->left;
         else
         { 
              if(T1->right!=NULL)
                   T2=T1->right;
              else
                   T2=NULL;
         }
         
         if(T2!=NULL)              //only single chid case
             {
              T2->parent=T1->parent;
			  }
              
         if(T1->parent==NULL)   // deleting node is root
              {root=T2;
              //--------
              if(T2->left!=NULL){
              	T2->max=(T2->max>T2->left->max)?T2->max:T2->left->max;
              }
              if(T2->right!=NULL){
              	T2->max=(T2->max>T2->right->max)?T2->max:T2->right->max;
              }
              //--------
              }
         else
         {
             if(T1==T1->parent->left)
                {
                T1->parent->left=T2;}
             else
                T1->parent->right=T2;
         }
         if(T1!=p)  //in case of two child 
         {
             p->color=T1->color;
             p->I=T1->I;  //swaping nodes
             p->max=(p->left->max>p->right->max)?p->left->max:p->right->max;
             if(T1->parent->left==T1)
             T1->parent->left=NULL;
             T1->parent=NULL;
             
             
         }
         if(T1->color=='b')  
             {
             deletefix(T2);}
         }
    
}
//------------------------------------------------------------------------
node* IntervalTree::nextbigAfterParentOf(node *p)
{
      node *y=NULL;
     if(p->left!=NULL)
     { //get maximum of left subtree
         y=p->left;
         while(y->right!=NULL)
              y=y->right;
     }
     else
     {//get smallest of right subtree
         y=p->right;
         while(y->left!=NULL)
              y=y->left;
     }
     return y;
}
//-----------------------------------------------------------------------------
//delete fix
void IntervalTree::deletefix(node *p)
{
    node *s;
    while(p!=root&&p->color=='b')  //p is black
    {
          if(p->parent->left==p)  // p is in left of its parent
          {
                  s=p->parent->right;  //sibling
                  if(s->color=='r')     //red sibling
                  {
                         s->color='b';
                         p->parent->color='r';
                         leftrotate(p->parent);
                         s=p->parent->right;  //s is in right of prior s
                  }
                  if(s->right->color=='b'&&s->left->color=='b')
                  {
                         s->color='r';
                         p=p->parent;  //prior s
                  }
                  else
                  {
                      if(s->right->color=='b')
                      {
                             s->left->color=='b';
                             s->color='r';
                             rightrotate(s);
                             s=p->parent->right;
                      }
                      s->color=p->parent->color;
                      p->parent->color='b';
                      s->right->color='b';
                      leftrotate(p->parent);
                      p=root;
                  }
          }
          else
          {
                  s=p->parent->left;
                  if(s->color=='r')
                  {
                        s->color='b';
                        p->parent->color='r';
                        rightrotate(p->parent);
                        s=p->parent->left;
                  }
                  if(s->left->color=='b'&&s->right->color=='b')
                  {
                        s->color='r';
                        p=p->parent;
                  }
                  else
                  {
                        if(s->left->color=='b')
                        {
                              s->right->color='b';
                              s->color='r';
                              leftrotate(s);
                              s=p->parent->left;
                        }
                        s->color=p->parent->color;
                        p->parent->color='b';
                        s->left->color='b';
                        rightrotate(p->parent);
                        p=root;
                  }
          }
       p->color='b';
       root->color='b';
    }
}

//----------------------------------------------------------------------------------------------------------
int main(){
	IntervalTree IT;
	cout<<"-----------------------WELCOME TO INTERVAL TREE ------------------"<<endl;
	
	//--------------------
	 while(true)
    {
        cout<<"Enter: \n1..Test Sample data set of problem \n Check randomly \n2..insert node\n3.search node \n4.delete \n5..print the interval tree\n6..exit\n";
        int option; 
		cin>>option;
        if(option==1)
        {cout<<"inserting {15, 20}, {10, 30}, {17, 19},{5, 20}, {12, 15}, {30, 40} -"<<endl;
        interval *i1=newinterval(15,20); node *n1=new node();
        interval *i2=newinterval(10,30); node *n2=new node();
        interval *i3=newinterval(17,19); node *n3=new node();
        interval *i4=newinterval(5,20);  node *n4=new node();
        interval *i5=newinterval(12,15); node *n5=new node();
        interval *i6=newinterval(30,40); node *n6=new node();
        
            IT.insert(n1,i1);
            IT.insert(n2,i2);
            IT.insert(n3,i3);
            IT.insert(n4,i4);
            IT.insert(n5,i5);
            IT.insert(n6,i6);
            IT.display(IT.root,0);
            cout<<"searching query {14,16}, {21,23}"<<endl;
            interval *i7=newinterval(14,16);
            interval *i8=newinterval(21,23);
            IT.search(IT.root,i7);
            IT.search(IT.root,i8);
            cout<<"deleting {5,20}"<<endl;
            IT.deleteNode(IT.root,i4);
            IT.display(IT.root,0);
            
            
        }
        else if(option==2)
        { int n;
           cout<<"Enter number of node that you have to insert"<<endl;
           cin>>n;
           cout<<"now enter your intervals"<<endl;
           for(int i=0;i<n;i++){
           	int l,h;
           	cin>>l>>h;
           	node *n=new node();
           	interval *inter=newinterval(l,h);
           	IT.insert(n,inter);
           }
        }
        else if(option==3)
        { int l,h;
		cout<<"Enter your query interval"<<endl;
        cin>>l>>h;
        interval *query=newinterval(l,h);
        IT.search(IT.root,query);
        }
        else if(option==4)
        { 
        IT.display(IT.root,0);
        }
        else if(option==5)
        { 	int l,h;
        cout<<"Enter your interval that has to be delted"<<endl;
           	cin>>l>>h;
           	interval *inter=newinterval(l,h);
        IT.deleteNode(IT.root,inter);
        }
        else     if(option==6)break;
    }
	//-----------------------
	return 0;
}
