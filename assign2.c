#include<stdio.h>
#include<stdlib.h>
#define SIZE 6
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
		
	

status UnionOfSet(int val1,int val2,disjoint_set * pointer_array[])
{
	status sc=success;
	int i,j,flag1=0,flag2=0;
	int findindex1,findindex2;
	for(i=0;i<SIZE;i++)
	{
		if(pointer_array[i]->data==val1)
		{
			findindex1=i;
			flag1=1;
		}
		if(pointer_array[i]->data==val2)
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
		
void CreateUnion(int list[],disjoint_set * pointer_array[])
{
	
	int helper_array[SIZE],i;	
	for(i=0;i<SIZE;i++)
	{
		pointer_array[i]=makeset(list[i]);
	}			
	for(i=0;i<SIZE-1;i++)
	{
		UnionOfSet(list[i],list[i+1],pointer_array);
		
	}
}	

int main()
{

	disjoint_set * pointer_array[SIZE]; //store pointer to struct type
	disjoint_set *ptr=NULL,*ptr1,*ptr2;	
	int n,i,ch,rep;
	disjoint_set * pointer_arrayList1[SIZE];
	disjoint_set * pointer_arrayList2[SIZE];
	int list1[SIZE],list2[SIZE];
	do
	{
		printf("1.implementation of union and find operations:\n");
		printf("2. check two elements belongs to same set:\n");
		printf("3.create two sets:\n");
		printf("4.exit:\n");
		printf("enter your choice:\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("enter elemnts in disjoint set :");
				for(i=0;i<SIZE;i++)
				{
					scanf("%d",&n);
					pointer_array[i]=makeset(n);
				}
				/* two set {0,1,2} {3,4,5}*/
				UnionOfSet(pointer_array[0]->data,pointer_array[1]->data, pointer_array);  																					
				UnionOfSet(pointer_array[1]->data,pointer_array[2]->data, pointer_array);
				UnionOfSet(pointer_array[3]->data,pointer_array[4]->data, pointer_array);
				UnionOfSet(pointer_array[3]->data,pointer_array[5]->data, pointer_array);
				//UnionOfSet(0,3, pointer_array);
				
				for(i=0;i<SIZE;i++)
				{
					ptr=pointer_array[i];
					ptr1=ptr->parent;
					printf("element=%d ",ptr->data);
					printf("set representive=%d\n",ptr1->data);
				}
				printf("enter representative element of set:");
				scanf("%d",&rep);
				printf("elements in set:\n");
				for(i=0;i<SIZE;i++)
				{
					ptr2=pointer_array[i];
					ptr=FindParent(ptr2);
					if(ptr->data==rep)
					{
						printf("%d ",ptr2->data);
					}
		

				}
				break;
			case 2:
				/*printf("enter two elements of set:"); //set created in case 1
				scanf("%d %d",&num1,&num2);
				for(i=0;i<SIZE;i++)
				{
					ptr2=pointer_array[i];
					parent1=FindParent(ptr2);
					parent2=FindParent(ptr2)
					if(ptr->data==rep)
					{
						printf("%d ",ptr2->data);
					}
		

				}*/
	
				break;
			case 3:

					printf("enter elements for list1:");
					for(i=0;i<SIZE;i++)
					{
						scanf("%d",&(list1[i]));

					}
					printf("enter elements for list2:");
					for(i=0;i<SIZE;i++)
					{
						scanf("%d",&(list2[i]));
					}
					CreateUnion( list1, pointer_arrayList1);
					CreateUnion( list2, pointer_arrayList2);
					
					for(i=0;i<SIZE;i++)
					{
						ptr=pointer_arrayList1[i];
						ptr1=ptr->parent;
						printf("element=%d ",ptr->data);
						printf("set representive=%d\n",ptr1->data);
					}
					printf("enter representative element of set:");
					scanf("%d",&rep);

					for(i=0;i<SIZE;i++)
					{
						ptr2=pointer_arrayList1[i];
						ptr=FindParent(ptr2);
						if(ptr->data==rep)
						{
							printf("%d ",ptr2->data);
						}
		

					}
				break;
			case 4:
				exit(0);
			default :
					printf("not valid choice:");
					break;
		}
	}while(1);
					

	

	
}
