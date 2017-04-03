/***************************************************************************************************************:')

DoublyLinkedList.c

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

#include "DoublyLinkedList.h"
