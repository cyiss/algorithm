
#include<iostream>
#include<string>

#include "List.h"

using namespace std;

int main( ) {
	List* myList = new List();
	List* myList2 = new List();
	List* myList3 = new List();
	List* myList4 = new List();
	List* myList5 = new List();

	int i = 10;

	cout << "list size: " << endl;
	myList->start();
	cin >> i;
	srand( time(NULL) );
	int j = i;
	while( j-- > 0 ) {
		int tmp = rand()%10000+1;
		myList->insert(tmp);
		myList2->insert(tmp);
		myList3->insert(tmp);
		myList4->insert(tmp);
		myList5->insert(tmp);
	}
	myList->print();

	myList->time_spend();

	myList->start();
	// myList->sort(SORT_SELECTION);
	myList->sort(SORT_MERGE);
	// myList->print();
	cout << "merge: ";
	myList->time_spend();
	myList->print();

	myList2->start();
	myList2->sort(SORT_BUBBLE);
	cout << "bubble: ";
	myList2->time_spend();
	myList2->print();

	myList3->start();
	cout << "selection: ";
	myList3->sort(SORT_SELECTION);
	myList3->time_spend();
	myList3->print();

	myList4->start();
	myList4->sort(SORT_QUICK);
	cout << "quick: ";
	myList4->time_spend();
	myList4->print();

	myList5->start();
	myList5->sort(SORT_INSERTION);
	cout << "insertion: ";
	myList5->time_spend();
	myList5->print();

	return 0;
}

