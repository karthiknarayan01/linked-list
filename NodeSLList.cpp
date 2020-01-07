///////////////////////////////////////////////////////////////////////
//File name - NodeSLList.cpp
//Name - Karthik Narayan
//Course Number - CPS 400
// Class NodeSLList Implementation
//
// Description - This file implements a singly linked list.
///////////////////////////////////////////////////////////////////////
#include "NodeSLList.h"


///////////////////////////////////////////////////////////////////////
// default constructor
///////////////////////////////////////////////////////////////////////
NodeSLList::NodeSLList()
{
	head = tail = 0;
}

///////////////////////////////////////////////////////////////////////
// copy constructor
///////////////////////////////////////////////////////////////////////
NodeSLList::NodeSLList(NodeSLList& list)
{
	*this = list;
}

///////////////////////////////////////////////////////////////////////
// destructor
///////////////////////////////////////////////////////////////////////
NodeSLList::~NodeSLList()
{
	// call destroyList() to remove all nodes
	// and reset linked list
	DestroyList();
}

///////////////////////////////////////////////////////////////////////
// IsEmpty
///////////////////////////////////////////////////////////////////////
bool NodeSLList::IsEmpty()
{
	// if head is NULL, then the list is empty, and we will return true
	// otherwise, we will return false
	return (head == 0);
}

///////////////////////////////////////////////////////////////////////
// GetSize
///////////////////////////////////////////////////////////////////////
int NodeSLList::GetSize()
{
	// check to see if the list is empty. if 
	// so, just return 0
	if (IsEmpty()) return 0;

	int size = 1;
	IntNode* p = head;
	// compute the number of nodes and return
	while (p != tail)
	{
		// until we reach the tail, keep counting
		size++;
		p = p->next;
	}
	return size;
}

///////////////////////////////////////////////////////////////////////
// AddToHead
///////////////////////////////////////////////////////////////////////
void NodeSLList::AddToHead(const IntNode& node)
{
	// create a new node, and make it the head. the 
	// previous head will become head->next
	IntNode* next = head;
	head = new IntNode;
	head->next = next;
	head->data = node.data;

	// if this is the first node, make the tail the 
	// same as the head
	if (tail == 0)
		tail = head;
}

///////////////////////////////////////////////////////////////////////
// DeleteFromHead
///////////////////////////////////////////////////////////////////////
IntNode NodeSLList::DeleteFromHead()
{
	IntNode temp;
	temp.data = 0;
	temp.next = NULL;
	if (IsEmpty())
	{
		cout << "*****ERROR: Can't delete from head. List is Empty" << endl;
		return temp;
	}

	// get current value of node we are about to delete, 
	// so we can return it.
	temp.data = head->data;

	IntNode* tmp = head;

	// if there is only one node, set the head and pointer tails
	// to NULL (0)
	if (head == tail)
		head = tail = 0;

	// otherwise, move the head pointer to the next node 
	// in the list
	else
		head = head->next;

	// delete head node
	delete tmp;

	// return value of node that was deleted
	return temp;
}

///////////////////////////////////////////////////////////////////////
// AddToTail
///////////////////////////////////////////////////////////////////////
void NodeSLList::AddToTail(const IntNode& node)
{
	// if there are no elements in the list then tail will be 0 and therefore just execute the addtohead procedure
	if (tail == 0) {
		AddToHead(node);
	}
	// Else allocate memory for a new node and assign the contents for this newly allocated node using the contents of the node parameter sent to the function.
	// make the current tail node point to this new node and assign the memory of this new node to the tail variable
	else {
		IntNode * currentEndNode = tail;
		tail = new IntNode;
		currentEndNode->next = tail;
		(*tail).data = node.data;
		(*tail).next = 0;
	}
}

///////////////////////////////////////////////////////////////////////
// DeleteFromTail
///////////////////////////////////////////////////////////////////////
IntNode NodeSLList::DeleteFromTail()
{
	IntNode nodeData;

	// get the current data at the tail
	nodeData.data = tail->data;


	// if there is only one node, delete the only node, and set the 
	// head and tail pointers to NULL (0) 
	if (head == tail)
	{
		delete head;
		head = tail = 0;
	}

	// otherwise, traverse to the tail node and delete it
	else
	{
		IntNode* temp;
		// traverse to tail pointer
		for (temp = head; temp->next != tail; temp = temp->next);
		delete tail;
		tail = temp;
		tail->next = 0;
	}

	return nodeData;
}


///////////////////////////////////////////////////////////////////////
// DeleteNode
///////////////////////////////////////////////////////////////////////
IntNode NodeSLList::DeleteNode(int nodeNum)
{
	if (nodeNum <= 0) nodeNum = 1;
	IntNode* prev = head, * temp = head;
	IntNode current;

	// traverse to the node
	for (int loop = 1; loop < nodeNum; loop++)
	{
		prev = temp, temp = temp->next;
		// check for case where nodeNum is > the number of 
		// nodes in the list. if we reach the tail before
		// we traverse to the node, delete the tail 
		if (temp == tail)
			return DeleteFromTail();
	}

	// if deleting the head just call 
	// the appropriate member function 
	// and don't repeat that logic here
	if (temp == head) return DeleteFromHead();

	// otherwise, delete the node we traversed to
	prev->next = temp->next;
	current.data = temp->data;

	delete temp;

	return current;
}

///////////////////////////////////////////////////////////////////////
// InsertNode
///////////////////////////////////////////////////////////////////////
void NodeSLList::InsertNode(int nodeNum, const IntNode& node)
{
	IntNode* tempHead = head, * newNode = new IntNode;
	int i = 0;
	newNode->data = node.data;
	newNode->next = 0;

	//if the list is empty then insert the new node at the head of the list
	if (head == 0)
		AddToHead(node);

	// if you want to insert the node at the head then point the head to the newnode and change the next pointer of newnode to point to the second element
	else if (nodeNum <= 0)
	{
		newNode->next = head->next;
		head = newNode;
	}
	// traverse till u either reach the end of the list or an element that appears before the position at which you want to insert the new node.
	else {
		while (tempHead != 0 && i < nodeNum - 1) {
			tempHead = tempHead->next;
			i += 1;
		}

		// if you reach the end of the list then just add the node to tail

		if (tempHead == 0) {

			AddToTail(node);
		}

		// else point the next pointer of the nodeNum-1th element to the newnode and assign newNode.next to the node which was previously in nodeNum position
		else {
			newNode->next = tempHead->next;
			tempHead->next = newNode;
		}
	}
}


///////////////////////////////////////////////////////////////////////
// UpdateNode
///////////////////////////////////////////////////////////////////////
void NodeSLList::UpdateNode(int nodeNum, const IntNode& node)
{
	IntNode* tmp = head;

	// traverse to the node, or to the last node, whichever comes
	// first. if the last node is reached, then that is the node
	// that is updated
	for (int i = 1; i < nodeNum && tmp != tail; i++)
		tmp = tmp->next;

	tmp->data = node.data;
}

// it compares the contents of node1 and node2 and you are sorting asc then return -1 if node1 < node2, return 1 if node1 > node2 if order = 2 i.e. you want to sort it desc then 
// return -1 if node1 > node2, return 1 if node1 < node2 and 0 otherwise
int compare(int order, IntNode* node1, IntNode* node2) {
	if (node1->data == node2->data) {
		return 0;
	}
	else if (node1->data < node2->data) {
		return (order == 1) ? -1 : 1;
	}

	return (order == 1) ? 1 : -1;
}

///////////////////////////////////////////////////////////////////////
// SortList
///////////////////////////////////////////////////////////////////////
void NodeSLList::SortList(unsigned int order)
{
	// At each ith iteration, the loop finds the appropriate node that needs to be available at ith position and it uses previouspointers and a temproary variable to swap the node at ith position with another
	//node that is identified as its correct replacement according to asc or desc order
	// lastly head and tail pointers are also updated at i = 0 and i = n-1 steps
	IntNode* tempHeadNodei = head, *previousHeadNodei = new IntNode, * tempHeadNodej, * previousHeadNodej,* nodeToBeInsertedAtIAccordingToOrder, * previousNodeToBeInsertedAtIAccordingToOrder;
	IntNode* temp;
	previousHeadNodei->next = tempHeadNodei;
	int i = 0, size = GetSize();
	while (i<size-1) {
		tempHeadNodej = tempHeadNodei->next;
		previousHeadNodej = tempHeadNodei;
		nodeToBeInsertedAtIAccordingToOrder = tempHeadNodei;
		previousNodeToBeInsertedAtIAccordingToOrder = previousHeadNodei;
		
		while (tempHeadNodej != 0) {
			if (compare(order,  tempHeadNodej, nodeToBeInsertedAtIAccordingToOrder) < 0)
			{
				nodeToBeInsertedAtIAccordingToOrder = tempHeadNodej;
				previousNodeToBeInsertedAtIAccordingToOrder = previousHeadNodej;
			}
			previousHeadNodej = tempHeadNodej;
			tempHeadNodej = tempHeadNodej->next;
		}
		
		if (previousHeadNodei != previousNodeToBeInsertedAtIAccordingToOrder) {
			previousHeadNodei->next = nodeToBeInsertedAtIAccordingToOrder;
			previousNodeToBeInsertedAtIAccordingToOrder->next = tempHeadNodei;
			temp = tempHeadNodei->next;
			tempHeadNodei->next = nodeToBeInsertedAtIAccordingToOrder->next;
			nodeToBeInsertedAtIAccordingToOrder->next = temp;
		}
		if (i == 0)
			head = previousHeadNodei->next;

		previousHeadNodei = previousHeadNodei->next;
		tempHeadNodei = previousHeadNodei->next;
		i += 1;
		if (i == size - 1)
			tail = previousHeadNodei->next;
	}
}

///////////////////////////////////////////////////////////////////////
// DestroyList
///////////////////////////////////////////////////////////////////////
void NodeSLList::DestroyList()
{
	// while the list is NOT empy
	// keep removing the head node and make
	// the next node the head node
	for (IntNode* p; !IsEmpty(); )
	{
		p = head->next;
		delete head;
		head = p;
	}
	head = tail = 0;
}

///////////////////////////////////////////////////////////////////////
// operator=
///////////////////////////////////////////////////////////////////////
NodeSLList& NodeSLList::operator=(NodeSLList& list)
{
	// first deallocate memory of all the elements in the list
	int i = 0, listSize = list.GetSize();
	DestroyList();
	// iterate through the list supplied as parameter to the function and add elements to the tail one by one
	while (i<listSize) {
		AddToTail(list.RetrieveNode(i+1));
		i += 1;
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////
// operator==
///////////////////////////////////////////////////////////////////////
bool NodeSLList::operator==(NodeSLList& list)
{
	int thisSize = GetSize(), lisSize = list.GetSize(), i = 0;
	// keep comparing the elements at each position using compare function
	while (i < thisSize && i < lisSize && compare(1,&RetrieveNode(i+1),&list.RetrieveNode(i+1)) == 0) {
		i += 1;		
	}
	// if the lists are equal i.e. all the elements are equal in both the lists then the loop would exit with the value in loop counter i = size +1 of a list.
	// now if the lists are of unequal size then the worst that can happen is that the loop counter would have the value min(thissize,lissize)
	// therefore we compare the loop counter value at the end of the loop and check if it is equal to the max(thissize,lissize) to know whether both lists are equal or not.
	
	if ((i != ((thisSize >= lisSize) ? thisSize : lisSize)))
		return false;

	return true;
}

///////////////////////////////////////////////////////////////////////
// operator!=
///////////////////////////////////////////////////////////////////////
bool NodeSLList::operator!=(NodeSLList& list)
{
	return !(*this == list);
}

///////////////////////////////////////////////////////////////////////
// operator+
///////////////////////////////////////////////////////////////////////
NodeSLList NodeSLList::operator+(NodeSLList& list)
{
	// copy all elements of this list into a new variable returnvalue
	// retrieve elements at each position from function parameter and invoke addtotail to append the retrieved element at the end of returnvalue list.
	NodeSLList *returnValue = new NodeSLList(*this);
	int lisSize = list.GetSize(), j = 0;

	while (j < lisSize) {
		returnValue->AddToTail(list.RetrieveNode(j + 1));
		j += 1;
	}

	return *returnValue;

}

///////////////////////////////////////////////////////////////////////
// RetrieveNode
// 
// Description: retrieve data from a node without removing it from 
//              the list
// Input: node number (1-N; not 0-N-1)
// Output: none
// Returns: reference to node data
///////////////////////////////////////////////////////////////////////
IntNode& NodeSLList::RetrieveNode(int nodeNum) const
{
	IntNode* tmp = head;

	// traverse to the node, or to the last node, whichever comes
	// first
	for (int i = 1; i < nodeNum && tmp != tail; i++)
		tmp = tmp->next;

	return *tmp;
}

ostream& operator<<(ostream& output, NodeSLList& list)
{
	// retrieve the elements from list one by one and use the output parameter to push the elements to the output stream
	int i = 0, lisSize = list.GetSize();
	output << "Values of the list are as below\n";
	while (i < lisSize) {
		output << list.RetrieveNode(i + 1).data << "\n";
		i += 1;
	}

	return output;
}

