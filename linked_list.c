#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Node of linked list
typedef struct node Node;
struct node
{
    int vertex;
    int weight;
    Node* next;
};

//Head of linked list
typedef struct list_head
{
    Node* head;
}Lhead;

//Create new node
Node* node_new(int to_vertex, int weight)
{
	Node *newnode;
	newnode=(Node*)malloc(sizeof(Node));	
	newnode->vertex = to_vertex;
	newnode->weight = weight;
	newnode->next = NULL;
	
	return newnode;
}

//Create new list
Lhead* list_new()
{
	Lhead *newhead;
	newhead=(Lhead *)malloc(sizeof(Lhead));
	newhead->head = NULL;
	
	return newhead;
}

//Return size of list
int list_size( Lhead* lst )
{
	Node *current;
	current=(Node *)malloc(sizeof(Node));		
	current->next = lst->head;
	
	int length=0;
	while(current->next!=NULL)
	{
		length++;
		current = current->next;
	}
	return length;

}

//Print the list
void list_print( Lhead* lst )
{
	Node *current;
	current=(Node *)malloc(sizeof(Node));		
	current->next = lst->head;
	
	while(current->next!=NULL)
	{
		current = current->next;	
		printf("%d (%d)\t", current->vertex, current->weight);
	}
	printf("\n");
}


// int list_get_index( Lhead* lst, int value )
// {
// 	Node *current;
// 	current=(Node *)malloc(sizeof(Node));		
// 	current->next = lst->head;
// 	int i = -1, found = -1;
	
// 	while(current->next!=NULL)
// 	{
// 		current = current->next;	
// 		i += 1;
// 		if(current->vertex == value)
// 		{
// 			found = i;
// 			break;
// 		} 
// 	}
// 	return found;
// }



// int list_get( Lhead* lst, int idx )
// {
// 	Node *current;
// 	current=(Node *)malloc(sizeof(Node));		
// 	current->next = lst->head;
	
// 	if(current->next == NULL || idx>(Lhead_size(lst)-1))
// 		return INT_MIN;
		
// 	int i;
// 	for(i=0; i<=idx; i++)
// 		current = current->next;		
// 	return current->data;
// }


// void list_append( Lhead* lst, int data )
// {
// 	Node *current;
// 	current=(Node *)malloc(sizeof(Node));		
// 	current->next = lst->head;
// 	Node *newnode;
// 	newnode=(Node *)malloc(sizeof(Node));	
// 	newnode->data = data;
// 	newnode->next = NULL;
	
// 	if(lst->head==NULL)
// 		lst->head = newnode;
// 	else
// 	{
// 		while(current->next!=NULL)
// 			current = current->next;
// 		current->next = newnode;
// 	}
// }


// void list_prepend( Lhead* lst, int data )
// {
// 	Node *newnode;
// 	newnode=(Node *)malloc(sizeof(Node));		
// 	newnode->data = data;
// 	newnode->next = lst->head;	
// 	lst->head = newnode;
// }


// void list_insert( Lhead* lst, int idx, int data )
// {
// 	Node *current;
// 	current=(Node *)malloc(sizeof(Node));		
// 	current->next = lst->head;	
// 	Node *newnode;
// 	newnode=(Node *)malloc(sizeof(Node));		
// 	newnode->data = data;
	
// 	int i;
// 	if(idx==0)
// 	{
// 		if(lst->head==NULL)
// 			lst->head=newnode;
// 		else
// 		{
// 			newnode->next=lst->head;
// 			lst->head=newnode;
// 		}
// 	}
// 	else if(lst->head!=NULL)
// 	{
// 		for(i=0; i<idx; i++)
// 			current = current->next;
// 		newnode->next = current->next;
// 		current->next= newnode;
// 	}
// }


// void list_remove_last( Lhead* lst )
// {
// 	Node *current;
// 	current=(Node *)malloc(sizeof(Node));		
// 	current->next = lst->head;
	
// 	if(lst->head!=NULL)
// 	{
		
// 		if(current->next->next==NULL)
// 			lst->head=NULL;
// 		else
// 		{
// 			while(current->next->next!=NULL)
// 				current = current->next;
// 			current->next=NULL;
// 		}
// 	}
// }


// void list_remove_first( Lhead* lst )
// {
// 	lst->head=lst->head->next;
// }


// void list_remove( Lhead* lst, int idx )
// {
// 	Node *current;
// 	current=(Node *)malloc(sizeof(Node));		
// 	current->next = lst->head;
	
// 	int i;
// 	if(lst->head!=NULL)
// 	{
		
// 		if(idx==0)
// 			lst->head=lst->head->next;	
// 		else
// 		{
// 			for(i=0; i<idx; i++)
// 				current = current->next;
// 			current->next = current->next->next;
// 		}
// 	}
// }
	
		
	
	










			
	
	
