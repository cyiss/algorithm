#include "List.h"
#include <cstddef>
#include <iostream>

using namespace std;

List::List() {
	count = 0;
}

List::~List() {
	node* tmpNode = first;
	while (first != NULL)
	{	
		tmpNode = first;
		first = tmpNode->next;
		delete tmpNode;
	}
}

void List::insert(int number) {
	
	node *newNode = new node;
	newNode->number = number;

	if ( first )
	{
		last->next = newNode;
		newNode->prev = last;
		last = newNode;
	} else {
		first = newNode;
		last = newNode;
	}

	count++;
}

node* List::find(int index) {
	node *resultNode = NULL;

	if ( index > count || index <= 0 )
	{
		cout << "you want node " << index
			 << ". But current size is : " << count << endl;
	} else {
		resultNode = first;

		while(--index > 0) {
			resultNode = resultNode->next;
		}
	}

	return resultNode;
}

void List::remove(int index) {
	node* targetNode = find(index);
	
	if (targetNode != NULL) {
		node* prev = targetNode->prev;
		node* next = targetNode->next;

		prev->next = next;
		if (next != NULL) {
			next->prev = prev;
		}
		count--;
		delete targetNode;
	}
}

int List::size() {
	return count;
}

void List::print() {
	node* tmpNode = first;

	cout << "Print List:" << endl;
	while( tmpNode != NULL) {
		cout << tmpNode->number << " ";
		tmpNode = tmpNode->next;
	}
	cout << endl;
}

void List::print(int index) {
	
	node* tmpNode = find(index);

	if (tmpNode != NULL)
	{
		cout << tmpNode->number << endl;
	}
}

void List::start() {
	start_time = mach_absolute_time();
}

void List::time_spend() {
	uint64_t end_time;
	uint64_t elapsed;

	end_time = mach_absolute_time();
	elapsed = end_time - start_time;

	Nanoseconds elapsedNano = AbsoluteToNanoseconds( *(AbsoluteTime *) &elapsed);
	
	uint64_t nanosec = *(uint64_t *)&elapsedNano;

	mach_timebase_info_data_t base;
	mach_timebase_info(&base);



	cout << nanosec/10e9 << endl;
}

void List::sort_bubble() {
	if (count > 0) {
		for ( int i = 0; i < count; i++ ) {
			node *tmpNode = first;
			while ( tmpNode != NULL ) {
				node *tmpNextNode = tmpNode->next;
				if ( tmpNextNode != NULL ) {
					if ( tmpNode->number > tmpNextNode->number ) {
						int tmp = tmpNode->number;
						tmpNode->number = tmpNextNode->number;
						tmpNextNode->number = tmp;
					}
				}
				tmpNode = tmpNextNode;
			}
		}
	}
}

void List::sort_selection() {
	if ( count > 0 ) {
		node *startNode = first;
		while ( startNode != NULL ) {
			node *minNode = startNode;
			node *seekingNode = startNode->next; 
			while ( seekingNode != NULL ) {
				if ( minNode->number > seekingNode->number ) {
					minNode = seekingNode;
				}
				seekingNode = seekingNode->next;
			}
			int tmp = minNode->number;
			minNode->number = startNode->number;
			startNode->number = tmp;

			startNode = startNode->next;
		}
	}
}

void List::sort_quick() {
	if ( count > 0 ) {
		quick_helper(first, last, count);
	}
}

void List::quick_helper( node* start, node* last, int nodeCount ) {

	node* left = start;
	int leftCount = 1;
	node* right = last;
	int rightCount = 1;

	int halfCount = nodeCount/2;
	// cout <<  nodeCount << " " << halfCount << endl;
	node* pivot = start;
	while( halfCount-- > 0 ) {
		pivot = pivot->next;
	}

	while(leftCount + rightCount <= nodeCount) {
		while( left->number < pivot->number ) {
			left = left->next;
			leftCount++;
		}
		while( right->number > pivot->number ) {
			right = right->prev;
			rightCount++;
		}

		if ( leftCount + rightCount <= nodeCount ) {
			int tmp = left->number;
			left->number  = right->number;
			right->number = tmp;
			left = left->next;
			right = right->prev;
			leftCount++;
			rightCount++;
		}
	}
	// this->print();
	if ( leftCount < nodeCount ) {
		quick_helper( start, left, leftCount );
	}
	if ( rightCount < nodeCount ) {
		quick_helper( right, last, rightCount );
	}

}

void List::sort_insertion() {
	if ( count > 0 ) {
		node* tmpNode = first->next;
		while ( tmpNode != NULL ) {
			node* prevNode = tmpNode->prev;
			while ( prevNode != NULL ) {
				if ( tmpNode->number < prevNode->number ) {
					prevNode = prevNode->prev;
				} else {
					break;
				}
			}
			node* nextNode = tmpNode->next;
			
			if ( tmpNode->prev != prevNode ) {
				tmpNode->prev->next = tmpNode->next;
				if ( tmpNode->next != NULL ) {
					tmpNode->next->prev = tmpNode->prev;
				}

				if ( prevNode != NULL ) {
					tmpNode->next = prevNode->next;
					tmpNode->prev = prevNode;
					tmpNode->next->prev = tmpNode;
					prevNode->next = tmpNode;
				} else {
					tmpNode->prev = NULL;
					first->prev = tmpNode;
					tmpNode->next = first;
					first = tmpNode;
				}
			}

			tmpNode = nextNode;
		}
	}
}

void List::sort_merge() {
	if ( count > 0 ) {
		first = merge_helper( first, count );
		node* tmpNode = first;
		while( tmpNode ) {
			last = tmpNode;
			tmpNode = tmpNode->next;
		}
	}
}

node* List::merge_helper( node* start, int length ) {
	if ( length == 1 ) {
		start->next = NULL;
		start->prev = NULL;

	} else {
		int llength = length / 2;

		int i = llength;
		node *halfStart = start;
		while( i-- > 0 ) {
			halfStart = halfStart->next;
		}

		node* left	= merge_helper( start, llength );
		node* right = merge_helper( halfStart , length - llength );

		if ( left->number < right->number ) {
			start = left;
			left = left->next;
		} else {
			start = right;
			right = right->next;
		}

		node* currentNode = start;

		while ( left || right ) {
			if ( left && right ) {
				if ( left->number < right->number ) {
					currentNode->next = left;
					left->prev = currentNode;
					currentNode = left;
					left = left->next;
				} else {
					currentNode->next = right;
					right->prev = currentNode;
					currentNode = right;
					right = right->next;
				}
			} else if ( left ) {
				currentNode->next = left;
				left->prev = currentNode;
				currentNode = left;
				left = left->next;
			} else if ( right ) {
				currentNode->next = right;
				right->prev = currentNode;
				currentNode = right;
				right = right->next;
			}
		}
	}

	return start;
}

void List::sort_heap() {
	cout << "sort_heap" << endl;
}

void List::sort_shell() {
	cout << "sort_shell" << endl;
}

void List::sort() {
	sort_quick();
}

void List::sort(sort_type sorttype) {
	switch(sorttype) {
		case SORT_BUBBLE:
			sort_bubble();
			break;
		case SORT_SELECTION:
			sort_selection();
			break;
		case SORT_QUICK:
			sort_quick();
			break;
		case SORT_INSERTION:
			sort_insertion();
			break;
		case SORT_MERGE:
			sort_merge();
			break;
		case SORT_HEAP:
			sort_heap();
			break;
		case SORT_SHELL:
			sort_shell();
			break;
		default:
			sort_quick();
			break;
	}
}