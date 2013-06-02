#include <mach/mach.h>
#include <mach/mach_time.h>
#include <unistd.h>
#include <CoreServices/CoreServices.h>

enum sort_type {
	SORT_BUBBLE,
	SORT_SELECTION,
	SORT_QUICK,
	SORT_INSERTION,
	SORT_MERGE,
	SORT_HEAP,
	SORT_SHELL
};

struct node {
	node *prev;
	node *next;
	
	int number;
};

class List {
	private:
		node *first;
		node *last;
		int count;

		uint64_t start_time;
		node* merge_helper(node* start, int length);

	protected:
		void sort_bubble();
		void sort_selection();
		void sort_quick();
		void sort_insertion();
		void sort_merge();
		void sort_heap();
		void sort_shell();
		
	public:
		List();
		~List();
		
		void insert(int number);
		void insert(int number, int index);
		
		void sort();
		void sort(sort_type sorttype);
		
		void remove(int index);
		
		node* find(int index);

		void print();
		void print(int index);

		int size();

		void start();
		void time_spend();
};