#include "linked.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

/**********************************************************************
***  FUNCTION insertNode *** **********************************************
***  DESCRIPTION  :  inserts a node into the list based on the name	 ***
***  INPUT ARGS     : string name, string value, int len, int address     ***
***  OUTPUT ARGS :  N/A												 ***
***  IN/OUT ARGS   :  N/A											  ***
***  RETURN :  void													   ***
***********************************************************************/
void list::insertNode(int pageNum, int count, int pid)
{
	ListNode* nodePtr;
	ListNode* newNode;
	ListNode* prevNode = nullptr;

	newNode = new ListNode;
	newNode->pageNum = pageNum;
	newNode->count = count;
    newNode->pid = pid;


	if (!head)
	{
		head = newNode;
		newNode->next = nullptr;
	}
	else
	{
		nodePtr = head;
		prevNode = nullptr;

		while (nodePtr != nullptr && nodePtr->count <= count)
		{
			prevNode->count++;
            prevNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		if (prevNode == nullptr)
		{
			head = newNode;
			newNode->next = nodePtr;
		}
		else
		{
			prevNode->next = newNode;
			newNode->next = nullptr;
		}
	}
}

/**********************************************************************
***  FUNCTION deleteNode *** **********************************************
***  DESCRIPTION  :  deletes a node from the list based on the value***
***  INPUT ARGS     :  string value					                ***
***  OUTPUT ARGS :  N/A												 ***
***  IN/OUT ARGS   :  N/A											  ***
***  RETURN :  	void												   ***
***********************************************************************/
void list::deleteNode(int pageNum)
{
	ListNode* nodePtr;
	ListNode* prevNode = nullptr;

	if (!head)
		return;
	if (head->pageNum == pageNum)
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;
	}
	else
	{
		nodePtr = head;

		while (nodePtr->pageNum != pageNum && nodePtr != nullptr)
		{
			prevNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		if (nodePtr)
		{
			prevNode->next = nodePtr->next;
			delete nodePtr;
		}
	}
}

/**********************************************************************
***  FUNCTION searchList *** **********************************************
***  DESCRIPTION  : searches for a node in the list based on name    ***
***		and returns true if found									***
***  INPUT ARGS     :  string name							           ***
***  OUTPUT ARGS :  N/A												 ***
***  IN/OUT ARGS   :  N/A											  ***
***  RETURN :  	bool												   ***
***********************************************************************/
int list::searchList()
{
	ListNode* nodePtr;
    nodePtr = head;
	return nodePtr->pageNum;
}

int list::returnPID (int pageNum)
{
    ListNode* nodePtr;

	nodePtr = head;

	while (nodePtr)
	{
		if (nodePtr->pageNum == pageNum)				
            return nodePtr->pid;
		nodePtr = nodePtr->next;
	}
}

/**********************************************************************
***  FUNCTION destructor *** **********************************************
***  DESCRIPTION  : destory the enitre list							 ***
***  INPUT ARGS     :  N/A							                ***
***  OUTPUT ARGS :  N/A												 ***
***  IN/OUT ARGS   :  N/A											  ***
***  RETURN :  	void												   ***
***********************************************************************/
list::~list()
{
	ListNode* nodePtr;
	ListNode* nextNode;

	nodePtr = head;

	while (nodePtr != nullptr)
	{
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}
