/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>


using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked list
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
	~L1List() {}

    void    clean();
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    T&      at(int i);// give the reference to the element i-th in the list
    T&      operator[](int i);// give the reference to the element i-th in the list

    bool    find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
    int     insert(int i, T& a);// insert an element into the list at location i. Return 0 if success, -1 otherwise
    int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.

    int     push_back(T& a);// insert to the end of the list
    int     insertHead(T& a);// insert to the beginning of the list

    int     removeHead();// remove the beginning element of the list
    int     removeLast();// remove the last element of the list

    void    reverse();

    void    traverse(void (*op)(T&)) {
        // TODO: Your code goes here
		L1Item<T> *p = this->_pHead;
		while (p != NULL) {
			(*op)(p->data);
			p = p->pNext;
		}
    }
	void    traverse(void(*op)(T&, string, int&), string pParam, int &n) {
		// TODO: Your code goes here
		L1Item<T> *p = this->_pHead;
		while (p != NULL) {
			(*op)(p->data, pParam, n);
			p = p->pNext;
		}
	}
	void    traverse(void(*op)(T&, string, int&, bool&), string pParam, int &n, bool &b) {
		// TODO: Your code goes here
		L1Item<T> *p = this->_pHead;
		while (p != NULL && b) {
			(*op)(p->data, pParam, n, b);
			p = p->pNext;
		}
	}
	void    traverse(void(*op)(T&, string &, int), string &pParam, int n) {
		// TODO: Your code goes here
		L1Item<T> *p = this->_pHead;
		while (p != NULL) {
			(*op)(p->data, pParam, n);
			p = p->pNext;
		}
	}
	void    traverse(void(*op)(T&, int&, int), int &n, int m) {
		// TODO: Your code goes here
		L1Item<T> *p = this->_pHead;
		while (p != NULL) {
			(*op)(p->data, n, m);
			p = p->pNext;
		}
	}
	void    traverse(void(*op)(T&, int, int*, int&), int n, int* m, int &q) {
		// TODO: Your code goes here
		L1Item<T> *p = this->_pHead;
		while (p != NULL) {
			(*op)(p->data, n, m, q);
			p = p->pNext;
		}
	}
	void    traverse(void(*op)(T&, int&), int &q) {
		// TODO: Your code goes here
		L1Item<T> *p = this->_pHead;
		while (p != NULL) {
			(*op)(p->data, q);
			p = p->pNext;
		}
	}
	void    traverse(void(*op)(T&, int, bool& , int&), int n, bool &b ,int &a) {
		// TODO: Your code goes here
		L1Item<T> *p = this->_pHead;
		while (p != NULL && b) {
			(*op)(p->data, n, b, a);
			p = p->pNext;
		}
	}
	void    traverse(void(*op)(T&, int, int, bool&, int&), int n, int m, bool &b, int &a) {
		// TODO: Your code goes here
		L1Item<T> *p = this->_pHead;
		while (p != NULL && b) {
			(*op)(p->data, n, m, b, a);
			p = p->pNext;
		}
	}
};

/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T &a) {
    // TODO: Your code goes here
	L1Item<T>* pNew = new L1Item<T>;
	pNew->data = a;
	pNew->pNext = NULL;
	if (this->_pHead == NULL) this->_pHead = pNew;	
	else
	{
		L1Item<T>* pTemp = this->_pHead;
		while (pTemp->pNext != NULL)
		{
			pTemp = pTemp->pNext;
		}
		pTemp->pNext = pNew;
	}
	this->_size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T &a) {
    // TODO: Your code goes here
	L1Item<T>* pNew = new L1Item<T>;
	pNew->data = a;
	pNew->pNext = NULL;
	if (this->_pHead == NULL) this->_pHead = pNew;
	else
	{
		pNew->pNext = this->_pHead;
		this->_pHead = pNew;
	}
	this->_size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
    // TODO: Your code goes here
	if (this->_pHead == NULL) return -1;	
	if (this->_size == 1) delete this->_pHead;
	else
	{
		L1Item<T>* p = this->_pHead;
		this->_pHead = p->pNext;
		delete p;
	}
	this->_size--;
	return 0;
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
    // TODO: Your code goes here
	if (this->_pHead == NULL) return -1;
	if (this->_size == 1) delete this->_pHead;
	else
	{
		L1Item<T>* pPre = this->_pHead;
		L1Item<T>* pLoc = this->_pHead;
		while (pLoc->pNext != NULL)
		{
			pPre = pLoc;
			pLoc = pLoc->pNext;
		}
		pPre->pNext = NULL;
		delete pLoc;
	}
	this->_size--;
	return 0;
}
template <class T>
T& L1List<T>::at(int i)
{
	L1Item<T> *p = this->_pHead;
	int pos = 0;
	while (pos != i)
	{
		p = p->pNext;
		pos++;
	}
	return p->data;
}
template <class T>
bool L1List<T>::find(T& a, int &idx)
{
	if (this->_pHead == NULL) return false;
	L1Item<T> *p = this->_pHead;
	int i = 0;
	while (p->pNext != NULL && p->data!=a)
	{
		p = p->pNext;
		i++;
	}
	if (p->pNext != NULL) idx = i;
	else idx = -1;
	return (p->pNext != NULL);
}
template <class T>
int L1List<T>::remove(int i) {
	if (this->_pHead == NULL) return -1;	
	if (i == 0) return removeHead();
	if (i == 0) return removeLast();
	L1Item<T> *pPre = this->_pHead;
	L1Item<T> *pLoc = this->_pHead;
	int pos = 0;
	while (pLoc->pNext != NULL && pos != i)
	{
		pPre = pLoc;
		pLoc = pLoc->pNext;
		pos++;
	}
	pPre->pNext = pLoc->pNext;
	pLoc->pNext = NULL;
	delete pLoc;
	this->_size--;
	return 0;
}
template <class T>
int L1List<T>::insert(int i, T &a) {
	L1Item<T>* pNew = new L1Item<T>;
	pNew->data = a;
	pNew->pNext = NULL;	
	if (this->_pHead == NULL) {
		this->_pHead = pNew;
		return 0;
	}
	if (i == 0) return insertHead(a);
	if (i == this->_size - 1) return push_back(a);
	L1Item<T> *pPre = this->_pHead;
	L1Item<T> *pLoc = this->_pHead;
	int pos = 0;
	while (pLoc->pNext != NULL && pos != i)
	{
		pPre = pLoc;
		pLoc = pLoc->pNext;
		pos++;
	}
	pNew->pNext = pLoc;
	pPre->pNext = pNew;
	this->_size++;
	return 0;
}
#endif //DSA191_A1_DSALIB_H
