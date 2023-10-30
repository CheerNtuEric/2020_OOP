#include"LinkedList.h"

LinkedList::LinkedList()
{
	//Constructor
	Tail = new ListNode;
	Head = NULL;
	Tail = NULL;
}
void LinkedList::Push_back(int x)
{
	//TODO : Insert a node to the end of the linked list, the node¡¦s value is x.

	//ListNode *current = Head;
	ListNode *current ;
	current = new ListNode;
	/*current = Head;
	while(current != NULL){
		current = current->next;
	}*/
	current -> val = x;
	if(Head == NULL){
		Head = Tail = current;
		Tail -> next = NULL;
		return;
	}
	//cout << current->val << " ";
	Tail -> next = current;
	Tail = current;
	Tail -> next = NULL;
	
}

void LinkedList::Push_front(int x)
{
	//TODO : Insert a node to the front of the linked list, the node¡¦s value is x.

	ListNode *current;
	current = new ListNode;
	//newnode -> next = new ListNode;
	current -> val = x;
	if(Head == NULL ){
		Head = Tail = current;
		Tail -> next = NULL;
		return;
	}
	
	current -> next = Head ;
	//Head -> next = current;
	Head = current;

}

void LinkedList::Insert(int index,int x)
{
	//TODO : Insert a node to the linked list at position ¡§index¡¨, the node's value is x.
	//The index of the first node in the linked list is 0.
	ListNode *newnode;
	ListNode *current;
	//current = new ListNode;
	

	newnode = new ListNode;
	newnode ->val = x;
	current = Head;
	//cout<< newnode ->val<<" ";
	if(Head == NULL){
		Head = Tail = newnode;
		Tail -> next = NULL;
		return;
	}
	else if (index == 0){          //add_to_front
		//newnode->next = Head;
		newnode -> next = current -> next;
		Head = newnode;
	}
	else{
		while(--index){
			current = current->next;
		}//find the previous node's index;
		newnode -> next = current -> next;
		current-> next = newnode;
	}
}

void LinkedList::Delete(int index)
{
	//TODO : Remove the node with index ¡§index¡¨ in the linked list.
	ListNode *current,*temp;
	temp = current = Head;
	if(index == 0){
		current = current-> next;
		Head = current;
	}
	else {
		while(--index){
		current = current->next;
		}
	temp = current -> next;
	current -> next = temp -> next;
	}
	delete temp;
}

void LinkedList::Reverse()
{
	//TODO : Reverse the linked list.
	/*Test
	ListNode *current,*prev, *next;
	current = new ListNode;
	current = Head;
	*/
	ListNode *current,*prev, *next;
	prev = new ListNode;
	next = new ListNode;
	current = new ListNode;
	current = Head;
	prev = next = NULL;
	while(current != NULL){
		next = current -> next;
		current -> next = prev;
		prev = current;
		current = next;
	}
	Head = prev;
}

void LinkedList::Print()
{
	cout << "List: ";
	//TODO : Print all the elements in the linked list in order.
	ListNode *current =Head;
	/*
	current = new ListNode;
	current = Head;*/
	while(current != NULL){
		cout << current->val << " ";
		current = current-> next;
	}
		//printf("\n");
}

LinkedList::~LinkedList()
{
	//Destructor
}
