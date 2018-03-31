#include<stdio.h>
#include<stdlib.h>
#define SIZE 7
typedef enum {failure,success} status;
typedef struct disjoint_tag
{
	int data;
	int rank;
	struct disjoint_tag *parent;
}disjoint_set;
disjoint_set * makeset(int data)
{
	disjoint_set *ptr;
	ptr=(disjoint_set*)malloc(sizeof(disjoint_set));
	ptr->data=data;
	ptr->rank=0;
	ptr->parent=ptr;
return ptr;
}
disjoint_set * FindParent(disjoint_set *node)
{
	disjoint_set *parent=node->parent;
	if(parent==node)
	return node;
	else
	{
		FindParent(node->parent);
	}
}
		
	

status UnionOfSet(int val1,int val2,int intial_array[],disjoint_set * pointer_array[])
{
	status sc=success;
	int i,j,flag1=0,flag2=0;
	int findindex1,findindex2;
	for(i=0;i<SIZE;i++)
	{
		if(intial_array[i]==val1)
		{
			findindex1=i;
			flag1=1;
		}
		if(intial_array[i]==val2)
		{
			findindex2=i;
			flag1=2;
		}
	}
	disjoint_set *node1,*node2;
	node1=pointer_array[findindex1];
	node2=pointer_array[findindex2];

	disjoint_set *parent1,*parent2;
	parent1=FindParent(node1);
	parent2=FindParent(node2);
	if(parent1==parent2)
	{
		sc=failure;
		return sc;
	}
	if(parent1->rank>=parent2->rank)
	{
		if(parent1->rank==parent2->rank)
		{
			parent1->rank=parent1->rank+1;
			
		}
		parent2->parent=parent1;
	}
	else
	{
		parent1->parent=parent2;
	}

return sc;
}
		
			
		

int main()
{

	disjoint_set * pointer_array[SIZE]; //store pointer to struct type
	disjoint_set *ptr,*ptr1;
	int intial_array[SIZE];	
	int n,i;
	printf("enter elemnts in disjoint set");
	for(i=0;i<SIZE;i++)
	{
		scanf("%d",&n);
		pointer_array[i]=makeset(n);
		intial_array[i]=n;
	}
	UnionOfSet(0,1,intial_array, pointer_array);
	UnionOfSet(1,2,intial_array, pointer_array);
	UnionOfSet(3,4,intial_array, pointer_array);
	UnionOfSet(3,5,intial_array, pointer_array);
	//UnionOfSet(0,3,intial_array, pointer_array);
	ptr=FindParent(pointer_array[3]);
	printf("%d",ptr->data);


	/*for(i=0;i<SIZE;i++)
	{
		ptr=pointer_array[i];
		ptr1=ptr->parent;
		printf("%d",ptr1->data);
	}*/
}
