#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Queue data structure
typedef struct queue
{
	Lhead* front;
	Lhead* rear;
}Queue;

//Create new queue
Queue* queue_new()
{
	Queue *new_queue;
	new_queue = (Queue *)malloc(sizeof(Queue));
	new_queue->front = (Lhead *)malloc(sizeof(Lhead));
	new_queue->front->head = NULL;
	new_queue->rear = (Lhead *)malloc(sizeof(Lhead));
	new_queue->rear->head = NULL;
	return new_queue;
}

//Check if queue is empty
int queue_is_empty(Queue *q)
{
	if(q->front->head == NULL)
		return 1;
	else
		return 0;	
}

//Enqueue an element to queue
void enqueue(Queue *q, int ele)
{
	Node *newnode = node_new(ele, 0);
	if(queue_is_empty(q))
		q->front->head = newnode;
	else
	{
		Node *current;
		current=(Node *)malloc(sizeof(Node));		
		current->next = q->front->head;

		while(current != q->rear->head)
		{
			current = current->next;
		}
		current->next = newnode;
	}
	q->rear->head = newnode;
}

//Dequeue element from queue
int dequeue(Queue *q)
{
	if(queue_is_empty(q))
		return INT_MIN;
	else
	{
		int data = q->front->head->vertex;
		q->front->head = q->front->head->next;
		return data;
	}
}

//Return size of queue
int queue_size(Queue *q)
{
	return list_size(q->front);
}

//Print the queue
void queue_print(Queue *q)
{
	list_print(q->front);
}