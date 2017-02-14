#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
class IntervalTree
{
    struct node
    {   int low,high,max;
        char color;
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
            root->color='B';
            root->parent=NULL;
            root->left = NULL;
            root->right = NULL;
        }
        else
        {
		cout<<"came to else root "<<endl;
		node *p=root;
        node *pp=NULL;
        while(p){
        	pp=p;
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
        nnode->color='R';
        nnode->max=h;
        
        if(l>=pp->low)
        {pp->right=nnode;
        //-----------
        if((pp->max)<nnode->max)
        pp->max=nnode->max;
        //------------
        cout<<"came here right"<<endl;
        bool b=(pp->parent!=NULL)&(pp->color=='R');
        if(b){
        
        if(((pp->parent)->left)->color=='R'){
		    //uncle red case 
		    cout<<"calling insertfix_uncleRed(nnode)"<<endl;
        	insertfix_uncleRed(nnode);
        }
         if(((pp->parent)->left)->color=='B'&((pp->parent)->left!=NULL)){//uncle black case
        		cout<<"calling insertfix_uncleBlack(nnode)"<<endl;
				insertfix_uncleBlack(nnode);
        }
    }
        }
        
        
        else{
        	pp->left=nnode;
        	//---------------
        	if((pp->max)<nnode->max)
        pp->max=nnode->max;
           //-------------------
        
		
		 cout<<"came here left"<<endl;
		 if(pp->parent){
		 cout<<"pp has parent"<<endl;
		 bool b=(pp->parent!=NULL);
		 if(b){
		 
        	if(((pp->parent)->right)->color=='R'){//uncle red case
			     cout<<"--"<<endl;
        		insertfix_uncleRed(nnode);
        		cout<<"------------------"<<endl;
        		
        }
        else{
		//uncle black case
		
        		insertfix_uncleBlack(nnode);
        }
		}
    }
        else
        cout<<"pp is root "<<endl;
        }
        
           
        }
        
    }
    //fix insertion when uncle is red
    void insertfix_uncleRed(node *currentnode){
    	node *papa= currentnode->parent;
    	node *grandpa=papa->parent;
    	node *uncle;
    	if(grandpa->left==papa){
    		uncle=grandpa->right;	
    	}else
    	uncle=grandpa->left;
    	
    	// Step1--color parent and uncle black
    	papa->color='B';
   		uncle->color='B';
   		// step--2 color grandparent black
   		if(grandpa!=root)
		grandpa->color='R';
	
		bool b=(grandpa->parent!=NULL);
		if(b){
		cout<<"ppp"<<endl;
		if((grandpa->parent)->color=='R'){
			if(((grandpa->parent)->parent)->left==(grandpa->parent)){
				//uncle in right
				node *newUncle=((grandpa->parent)->parent)->right;
				if(newUncle){
				
				if(newUncle->color=='R')
				insertfix_uncleRed(grandpa);
				else
				insertfix_uncleBlack(grandpa);}
			}
			else{
				//uncle in left
				node *newUncle=((grandpa->parent)->parent)->left;
				if(newUncle){
				
				if(newUncle->color=='R')
				insertfix_uncleRed(grandpa);
				else
				insertfix_uncleBlack(grandpa);
				}
			}
		}
	}
	else
	cout<<"out fixed"<<endl;	 //fixed
    	
    	
    }
    //fix insertion when uncle is black
    void insertfix_uncleBlack(node *currentnode){
    	node *papa=currentnode->parent;
    	node *grandpa=papa->parent;
    	node *uncle;
    	if(papa->left==currentnode){
    		
    		if(grandpa->left==papa){
    			//Left left uncle black case;
    			leftleft(papa,grandpa);
  			
    		}else
    		{//right left uncle black case;
    		    RotateRight(papa);	
    		    rightright(currentnode,grandpa);
    		}
    	}
    	else{
    		if(grandpa->left==papa){
    			//Left right uncle black case;
    			RotateLeft(papa);
    			leftleft(currentnode,grandpa);
    			
    		}else
    		{//right right uncle black case;
    		rightright(papa,grandpa);
    			
    		}
    	}
    	
    }
    //roate right
    void RotateRight(node *x){
    	node *parent_x=x->parent;
    	node *left_x= x->left;
    	node *right_x=x->right;
    	node *Tl=right_x->left;
    	node *Tr=right_x->right;
    	
    	x->left=Tr;
    	left_x->right=x;
    	left_x->parent=parent_x;
    	
    	//changing value overaal max of subtree
    	int ml,mx;
    	left_x->max= ml;
    	x->max=mx;
    	if(ml<mx)
    		left_x->max=mx;
    		
    	if(mx<Tr->max)
    	x->max=Tr->max;
    	
    	
    }
     //roate right
    void RotateLeft(node *x){
    	node *parent_x=x->parent;
    	node *left_x= x->left;
    	node *right_x=x->right;
    	node *Tl=right_x->left;
    	node *Tr=right_x->right;
    	
    	x->right=Tl;
    	right_x->left=x;
    	right_x->parent=parent_x;
    	//changing value overaal max of subtree
    	int mr,mx;
    	right_x->max= mr;
    	x->max=mx;
    	if(mr<mx)
    		right_x->max=mx;
    		
    	if(mx<Tl->max)
    	x->max=Tl->max;
    	
    	
    }
     //right  right uncle black  case in insertion
    void rightright(node *papa,node *grandpa){
    	//left rotate grandparent
		RotateLeft(grandpa);
		//swap color of papa and grandparent
		char temp =papa->color;
		papa->color=grandpa->color;
		grandpa->color=temp;
    }
     //right  right uncle black  case in insertion
    void leftleft(node *papa,node *grandpa){
    	//right rotate grandparent
		RotateRight(grandpa);
		//swap color of papa and grandparent
		char temp =papa->color;
		papa->color=grandpa->color;
		grandpa->color=temp;
    }
    
    void display(node *ptr)
    {cout<<"displaying"<<endl;
        if(root==NULL)cout<<"interval tree is empty"<<endl;
        else
        {
            if(ptr->left)
                display(ptr->left);
                
            cout<<"("<<ptr->low<<","<<ptr->high<<" ) "<<ptr->max<<endl;   ///in-order traversal..
            if(ptr->right)
                display(ptr->right);
        }
    }
    
};
int main(){
	IntervalTree IT;
	
	IT.insert(15,20);
	IT.display(IT.root);
	IT.insert(10,30);
	IT.display(IT.root);
	
	IT.insert(17,19);
	IT.display(IT.root);
	IT.insert(5,20);
	IT.display(IT.root);
	IT.insert(12,15);
	IT.display(IT.root);
	IT.insert(30,40);
	
	
	IT.display(IT.root);
	return 0;
}
