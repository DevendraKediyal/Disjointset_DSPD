#include<stdio.h>
#include<stdlib.h>
#define SIZE 8
typedef enum {failure,success} status;
typedef struct disjoint_tag
{
	int data;
	int rank;
	struct disjoint_tag *parent;
}disjoint_set;

struct node{
    int key;
    disjoint_set * pointer_array;
    struct node *next;
};
struct table{
    int size;
    struct node **list;
};
disjoint_set * makeset(int data)
{
	disjoint_set *ptr;
	ptr=(disjoint_set*)malloc(sizeof(disjoint_set));
	ptr->rank=0;
	ptr->data=data;
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
		
	
disjoint_set * search(struct table *t,int key){
    int pos = hashCode(t,key);
    struct node *list = t->list[pos];
    struct node *temp = list;
    while(temp!=NULL){
        if(temp->key==key){
            return temp->pointer_array;
        }
        temp = temp->next;
    }
    return NULL;
}
status UnionOfSet(int val1,int val2,struct table *t)
{
	status sc=success;
	int i,j,flag1=0,flag2=0;
	int findindex1,findindex2;
	disjoint_set *node1,*node2;
	node1=	search(t,val1);
	node2=	search(t,val2);

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
		
void CreateUnion(int list[],struct table *t)
{	
	int i;		
	for(i=0;i<SIZE-1;i++)
	{
		UnionOfSet(list[i],list[i+1],t);
		
	}
}	
struct table *createTable(int size){
    struct table *t = (struct table*)malloc(sizeof(struct table));
    t->size = size;
    t->list = (struct node**)malloc(sizeof(struct node*)*size);
    int i;
    for(i=0;i<size;i++)
        t->list[i] = NULL;
    return t;
}
int hashCode(struct table *t,int key){
    if(key<0)
        return -(key%t->size);
    return key%t->size;
}
void insert(struct table *t,int key,disjoint_set *pointer_array){
    int pos = hashCode(t,key);
    struct node *list = t->list[pos];
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    struct node *temp = list;
    while(temp!=NULL){
        if(temp->key==key){
            temp->pointer_array =makeset(key);
            return;
        }
        temp = temp->next;
    }
    newNode->key = key;
    newNode->pointer_array = makeset(key);
    newNode->next = list;
    t->list[pos] = newNode;
}

int main()
{
  struct table *t = createTable(8);
//	disjoint_set * pointer_array[SIZE]; //store pointer to struct type
	disjoint_set *ptr=NULL,*ptr1,*ptr2,*ptr_num1,*parent_num1,*ptr_num2,*parent_num2;	
	int n,i,ch,rep;
	int num1,num2;
	disjoint_set * pointer_arrayList1[SIZE];
	disjoint_set * pointer_arrayList2[SIZE];
	int list1[SIZE],list2[SIZE],list[SIZE];
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
							list[i]=n;
							insert(t,n,makeset(n));
					
					
						}
						/* two set {0,1,2} {3,4,5} */
						UnionOfSet(list[0],list[1],t);
						UnionOfSet(list[1],list[2],t);
						UnionOfSet(list[3],list[4],t);	
						UnionOfSet(list[4],list[5],t);
						for(i=0;i<SIZE;i++)
						{
							ptr=search(t,list[i]); // search for given elements in hash table
							ptr1=FindParent(ptr); // find parent of given elements
							printf("element=%d ",ptr->data);
							printf("set representive=%d\n",ptr1->data);
						}
						break;
			case 2:
						printf("enter two elements of set:"); 
						scanf("%d %d",&num1,&num2);
						ptr_num1=search(t,num1); // search for given elements in hash table
						parent_num1=FindParent(ptr_num1);
						ptr_num2=search(t,num2); // search for given elements in hash table
						parent_num2=FindParent(ptr_num2);
						if((parent_num1!=NULL && parent_num2!=NULL) && (parent_num1==parent_num2))
						{
							printf("elements belongs to same set:\n");
						}
						else
						{
							printf("elements does not belongs to same set\n");
						}
			
						break;
			case 3:

					printf("enter elements for list1:\n");
					for(i=0;i<SIZE;i++)
					{
						scanf("%d",&(list1[i]));
						insert(t,list1[i],makeset(list1[i]));

					}
					printf("enter elements for list2:\n");
					for(i=0;i<SIZE;i++)
					{
						scanf("%d",&(list2[i]));
						insert(t,list2[i],makeset(list2[i]));
					}
					CreateUnion( list1,t);
					CreateUnion( list2, t);
					
					for(i=0;i<SIZE;i++)
					{
							ptr=search(t,list1[i]); // search for given elements in hash table
							ptr1=FindParent(ptr); // find parent of given elements
							printf("element=%d ",ptr->data);
							printf("set representive=%d\n",ptr1->data);
					}
					/*printf("enter representative element of set:");
					scanf("%d",&rep);

					for(i=0;i<SIZE;i++)
					{
						ptr2=pointer_arrayList1[i];
						ptr=FindParent(ptr2);
						if(ptr->data==rep)
						{
							printf("%d ",ptr2->data);
						}
		

					}*/
				break;
			case 4:
				exit(0);
			default :
					printf("not valid choice:");
					break;
		}
	}while(1);
					

	

	
}

