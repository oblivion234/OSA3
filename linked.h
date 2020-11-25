#pragma once
#ifndef linked_H
#define linked_H
#include <string>

using namespace std;

class list
{
private:
	struct ListNode
	{
		int pageNum;
        int count;
        int pid;
		struct ListNode* next;
	};

	ListNode* head;
public:
	//constructor
	list()
	{
		head = nullptr;
	}

	//destructor
	~list();


	//list operations
	void appendNode(int, int);
	int searchList();
	void insertNode(int, int);
	void deleteNode(int);
	void displayList();
	


};
#endif