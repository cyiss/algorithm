
#include<iostream>
#include<string>

#include "List.h"

using namespace std;

int main( ) {
	List* myList = new List();

	int i = 10;

	cout << "list size: " << endl;
	myList->start();
	cin >> i;
	srand( time(NULL) );
	while( i-- > 0 ) {
		myList->insert(rand()%10000+1);
	}
	myList->print();
	myList->time_spend();


	myList->start();
	// myList->sort(SORT_SELECTION);
	myList->sort(SORT_MERGE);
	myList->print();

	myList->time_spend();

	return 0;
}

