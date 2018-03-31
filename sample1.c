#include<stdio.h>
#include<stdlib.h>
#define SIZE 7
typedef enum {FAILURE,SUCCESS} statuscode;


typedef struct disjoint_tag
{
	int data;
	int rank;
	struct disjoint_tag *parent;
}disjoint_set;

//Array node ; It is the array where every node has the number and pointer to the disjoint_set node containing that number;
typedef struct arraynode_tag
{
    int data;
    disjoint_set *node;
}arraynode;

// Creating a node and initialising it 
disjoint_set * makeset(int data)
{
	disjoint_set *ptr;
	ptr=(disjoint_set*)malloc(sizeof(disjoint_set));
	ptr->data=data;
	ptr->rank=0;
	ptr->parent=NULL;
return ptr;
}

disjoint_set * FindParent(disjoint_set *node)
{
	
	if(node->parent == NULL)
	return node;
	else
	{
		FindParent(node->parent);
	}
}
		
	

statuscode UnionOfSet(int val1,int val2,arraynode array[])
{
	statuscode sc=SUCCESS;
	int i,flag1=0,flag2=0;
	disjoint_set *node1,*node2;
	
	for(i=0;i<SIZE && (flag1==0 || flag2==0) ;i++)
	{
		if(array[i].data==val1)
		{
			node1 = array[i].node;
			flag1=1;
		}
		if(array[i].data==val2)
		{
			node2 = array[i].node;
			flag2=1;
		}
	}
	

	disjoint_set *parent1,*parent2;
	parent1=FindParent(node1);
	parent2=FindParent(node2);
	
	
	if(parent1->data==parent2->data)
	{
		sc=FAILURE;
	}
	
	if(parent1->rank >= parent2->rank)
	{
		if(parent1->rank == parent2->rank)
		{
			parent1->rank = (parent1->rank)+1;
			
		}
		parent2->parent = parent1;
	}
	else
	{
		parent1->parent = parent2;
	}

return sc;
}
		
			
// Heap sort Algo follows:

void InsertHeap(arraynode array[],int low,int high,arraynode key)
{
    int large;
    large=2*low+1;done=0;
    while((large<high)&&(done==0))
    {
        if((large<high)&&(array[large].data<array[large+1].data))
        {
            large++;
        }
        if (array[large].data < key.data)
        {
            done =1;
        }
        else
        {
            array[low]=array[large];
            low=large;
            large =2*low+1;
        }
        array[low]=key;
    }
    
    
}
void BuildHeap (arraynode array[],int n)
{
    int low;
    for(low= (n/2)-1;low>=0; low--)
    {
        InsertHeap(array,low,n-1,array[low]);
    }
}
void Sort(arraynode array[],int n)
   {
       int pos; 
       arraynode current;
       BuildHeap(array,n);
       for(pos =n-1;pos>=1;pos--)
       {
           current=array[pos];
           array[pos]=array[0];
           InsertHeap(array,0,pos-1,current);
           
       }
   }


disjoint_set * BinSearch(arraynode array[], int n , int x)
{
    int low,high,mid,found;
    disjoint_set *retval;
    low=0;high=n-1;found=0;
    while(low <= high && found == 0)
    {
        mid =(low+high)/2;
        if (x==array[mid].data)
        {
            found =1;
            retval = array[mid].node ;
        }
        else if (x<array[mid].data)
        {
            high=mid-1;    
        }
        else
        {
            low = mid+1;
        }
    }
    return retval;
}
int main()
{

	statuscode sc;
	disjoint_set *ptr,*node,*ptr1,*ptr2;
	arraynode array[SIZE];	
	int n,option,i,val1,val2,data;
	printf("enter the number of elements to be read\n");
	scanf("%d",&n);
	printf("enter elemnts in disjoint set");
	for(i=0;i<n;i++)
	{
		scanf("%d",&data);
		array[i].node=makeset(data);
	    array[i].data=data;
	}
	Sort(array,n);
	option = 0;
	while(option != -1)
	{
	    printf("1.Union\n2.Find Parent of Element\n3.Find if 2 Elements Present in same set\n4.Give 2nd list and implement set operations\n5.Exit\n");
    	scanf("%d",&option);
    	switch(option)
    	{
    	    case 1:printf("Enter 2 numbers\n");
    	            scanf("%d %d",&val1,&val2);
    	            sc = UnionOfSet(val1,val2,array);
    	            if(sc==0)
    	                printf("Elements are already in same set\n");
    	            else
    	                printf("Union operation successful\n");
    	            break;
    	   case 2:printf("Enter a number\n");
    	            scanf("%d",&val1);
    	            node = BinSearch(array,n,val1);
    	            ptr=FindParent(node);
    	            printf("%d\n",ptr->data);
    	            break;
    	   case 3:printf("Enter 2 numbers\n");
    	          scanf("%d %d",&val1,&val2);
    	          node = BinSearch(array,n,val1);
    	          ptr1 = FindParent(node);
    	          node = BinSearch(array,n,val2);
    	          ptr2 = FindParent(node);
    	           if(ptr1->data == ptr2->data)
    	                printf("They are in same set \n");
    	           else
    	                printf("They are in different set\n");
    	           break;
    	   case 4://Coming shortly 
    	            break;
    	   default: option=-1;
    	}
	}

}
