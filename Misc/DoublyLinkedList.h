/***************************************************************************************************************:')

DoublyLinkedList.h

Doubly Linked list. DOUBLY_LINKED_LIST_DATA must be defined to the desired type.

Fabrice Le Bars

Created : 2013-10-27

***************************************************************************************************************:)*/

// Prevent Visual Studio Intellisense from defining _WIN32 and _MSC_VER when we use 
// Visual Studio to edit Linux or Borland C++ code.
#ifdef __linux__
#	undef _WIN32
#endif // __linux__
#if defined(__GNUC__) || defined(__BORLANDC__)
#	undef _MSC_VER
#endif // defined(__GNUC__) || defined(__BORLANDC__)

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "OSCore.h"

/*
Debug macros specific to DoublyLinkedList.
*/
#ifdef _DEBUG_MESSAGES
#	define _DEBUG_MESSAGES_DOUBLYLINKEDLIST
#endif // _DEBUG_MESSAGES

#ifdef _DEBUG_WARNINGS
#	define _DEBUG_WARNINGS_DOUBLYLINKEDLIST
#endif // _DEBUG_WARNINGS

#ifdef _DEBUG_ERRORS
#	define _DEBUG_ERRORS_DOUBLYLINKEDLIST
#endif // _DEBUG_ERRORS

#ifdef _DEBUG_MESSAGES_DOUBLYLINKEDLIST
#	define PRINT_DEBUG_MESSAGE_DOUBLYLINKEDLIST(params) PRINT_DEBUG_MESSAGE(params)
#else
#	define PRINT_DEBUG_MESSAGE_DOUBLYLINKEDLIST(params)
#endif // _DEBUG_MESSAGES_DOUBLYLINKEDLIST

#ifdef _DEBUG_WARNINGS_DOUBLYLINKEDLIST
#	define PRINT_DEBUG_WARNING_DOUBLYLINKEDLIST(params) PRINT_DEBUG_WARNING(params)
#else
#	define PRINT_DEBUG_WARNING_DOUBLYLINKEDLIST(params)
#endif // _DEBUG_WARNINGS_DOUBLYLINKEDLIST

#ifdef _DEBUG_ERRORS_DOUBLYLINKEDLIST
#	define PRINT_DEBUG_ERROR_DOUBLYLINKEDLIST(params) PRINT_DEBUG_ERROR(params)
#else
#	define PRINT_DEBUG_ERROR_DOUBLYLINKEDLIST(params)
#endif // _DEBUG_ERRORS_DOUBLYLINKEDLIST

// Node of a DOUBLY_LINKED_LIST.
struct _DOUBLY_LINKED_LIST_NODE	
{
	DOUBLY_LINKED_LIST_DATA data;
	struct _DOUBLY_LINKED_LIST_NODE* prev; // Previous node in the list.
	struct _DOUBLY_LINKED_LIST_NODE* next; // Next node in the list.
};
typedef struct _DOUBLY_LINKED_LIST_NODE DOUBLY_LINKED_LIST_NODE;

// Linked list. 
struct _DOUBLY_LINKED_LIST	
{
	DOUBLY_LINKED_LIST_NODE* first; // First node of the list.
	unsigned int count; // Number of nodes in the list.
};
typedef struct _DOUBLY_LINKED_LIST DOUBLY_LINKED_LIST;

/*
Initialize the first list node.
*/
inline int DOUBLY_LINKED_LIST_INIT(DOUBLY_LINKED_LIST_DATA data, DOUBLY_LINKED_LIST* list)	
{
	// Initialize the first node of the list.
	list->first = (DOUBLY_LINKED_LIST_NODE*)calloc(1, sizeof(DOUBLY_LINKED_LIST_NODE));

	if (list->first == NULL)
	{
		PRINT_DEBUG_ERROR_DOUBLYLINKEDLIST(("DOUBLY_LINKED_LIST_INIT error (%s) : %s"
			"(data=%#x, list=%#x)\n", 
			strtime_m(), 
			szOSUtilsErrMsgs[EXIT_OUT_OF_MEMORY], 
			data, list));
		return EXIT_OUT_OF_MEMORY;
	}

	list->first->data = data;
	list->first->prev = NULL;
	list->first->next = NULL;

	// Update the number of nodes in the list.
	list->count = 1;

	return EXIT_SUCCESS;
}

inline int DOUBLY_LINKED_LIST_CLEAR(DOUBLY_LINKED_LIST* list)	
{
	DOUBLY_LINKED_LIST_NODE* node_tmp = NULL;
	DOUBLY_LINKED_LIST_NODE* node = list->first; 

	list->count = 0;

	while (node)	
	{
		node_tmp = node->next;

		// Remove the node from the list.
		if (node->prev != NULL)	
		{
			node->prev->next = node->next;
		} 
		if (node->next != NULL)	
		{
			node->next->prev = node->prev;
		} 

		free(node);

		node = node_tmp;
	}

	return EXIT_SUCCESS;
}

/* 
Create a new DOUBLY_LINKED_LIST_NODE based on new_data and add it to the beginning of the list.
*/
inline int DOUBLY_LINKED_LIST_ADD_FIRST(DOUBLY_LINKED_LIST_DATA new_data, DOUBLY_LINKED_LIST* list)	
{
	DOUBLY_LINKED_LIST_NODE* new_node = NULL;
	DOUBLY_LINKED_LIST_NODE* node = NULL;

	// Create a new DOUBLY_LINKED_LIST_NODE structure that will contain the new data.
	new_node = (DOUBLY_LINKED_LIST_NODE*)calloc(1, sizeof(DOUBLY_LINKED_LIST_NODE));

	if (new_node == NULL)
	{
		PRINT_DEBUG_ERROR_DOUBLYLINKEDLIST(("DOUBLY_LINKED_LIST_ADD_FIST error (%s) : %s"
			"(new_data=%#x, list=%#x)\n", 
			strtime_m(), 
			szOSUtilsErrMsgs[EXIT_OUT_OF_MEMORY], 
			new_data, list));
		return EXIT_OUT_OF_MEMORY;
	}

	// Initialize it with the new data.
	new_node->data = new_data;

	// Add it to the beginning of the list.
	if (list->first == NULL)
	{
		new_node->prev = NULL;
		new_node->next = NULL;
		list->first = new_node;
	}
	else
	{
		new_node->prev = NULL;
		new_node->next = list->first; 
		list->first->prev = new_node;
		list->first = new_node;
	}

	// Update the number of nodes in the list.
	list->count++;

	return EXIT_SUCCESS;
}

/* 
Create a new DOUBLY_LINKED_LIST_NODE based on new_data and add it to the end of the list.
*/
inline int DOUBLY_LINKED_LIST_ADD_LAST(DOUBLY_LINKED_LIST_DATA new_data, DOUBLY_LINKED_LIST* list)	
{
	DOUBLY_LINKED_LIST_NODE* new_node = NULL;
	DOUBLY_LINKED_LIST_NODE* node = NULL;

	// Create a new DOUBLY_LINKED_LIST_NODE structure that will contain the new data.
	new_node = (DOUBLY_LINKED_LIST_NODE*)calloc(1, sizeof(DOUBLY_LINKED_LIST_NODE));

	if (new_node == NULL)
	{
		PRINT_DEBUG_ERROR_DOUBLYLINKEDLIST(("DOUBLY_LINKED_LIST_ADD_LAST error (%s) : %s"
			"(new_data=%#x, list=%#x)\n", 
			strtime_m(), 
			szOSUtilsErrMsgs[EXIT_OUT_OF_MEMORY], 
			new_data, list));
		return EXIT_OUT_OF_MEMORY;
	}

	// Initialize it with the new data.
	new_node->data = new_data;

	// Look for the last node of the list.
	if (list->first == NULL)
	{
		new_node->prev = NULL;
		new_node->next = NULL;
		list->first = new_node;
	}
	else
	{
		node = list->first;
		while (node->next)	
		{
			node = node->next;
		} // node is now the last element.

		// Add the new node at the end of the list.
		new_node->prev = node;
		new_node->next = NULL;
		node->next = new_node;
	}

	// Update the number of nodes in the list.
	list->count++;

	return EXIT_SUCCESS;
}

/* 
Remove the first node from the list.
*/
inline int DOUBLY_LINKED_LIST_REMOVE_FIRST(DOUBLY_LINKED_LIST* list)	
{
	DOUBLY_LINKED_LIST_NODE* node = list->first;

	// Update the number of nodes in the list.
	list->count--;

	// Remove the node from the list.
	//if (node->prev != NULL)	
	//{
	//	node->prev->next = node->next;
	//} 
	if (node->next != NULL)	
	{
		node->next->prev = NULL;
	} 
	list->first = node->next;

	free(node); node = NULL;

	return EXIT_SUCCESS;
}

/* 
Remove a node from the list.
*/
inline int DOUBLY_LINKED_LIST_REMOVE(DOUBLY_LINKED_LIST_NODE* node, DOUBLY_LINKED_LIST* list)	
{
	// Update the number of nodes in the list.
	list->count--;

	if (node == list->first)
	{
		// Remove the node from the list.
		//if (node->prev != NULL)	
		//{
		//	node->prev->next = node->next;
		//} 
		if (node->next != NULL)	
		{
			node->next->prev = NULL;
		} 
		list->first = node->next;
	}
	else
	{
		// Remove the node from the list.
		if (node->prev != NULL)	
		{
			node->prev->next = node->next;
		} 
		if (node->next != NULL)	
		{
			node->next->prev = node->prev;
		} 
	}

	free(node); node = NULL;

	return EXIT_SUCCESS;
}

#endif // DOUBLYLINKEDLIST_H
