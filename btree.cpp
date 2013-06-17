#include <iostream>
#include <string>

using namespace std;

typedef char datatype;

struct node{
	datatype data;
	int llink, rlink;
};

void preorder ( node* tree, int p);
void inorder  ( node* tree, int p);
void postorder( node* tree, int p);

int main() {
	const int n = 6;

	node tree[n+1];
	int root = 1;


	tree[1].data = 'a';
	tree[2].data = 'b';
	tree[3].data = 'c';
	tree[4].data = 'd';
	tree[5].data = 'e';
	tree[6].data = 'f';

	tree[1].llink = 2;	
	tree[1].rlink = 3;

	tree[2].llink = 0;	
	tree[2].rlink = 4;

	tree[3].llink = 5;	
	tree[3].rlink = 6;

	tree[4].llink = 0;	
	tree[4].rlink = 0;

	tree[5].llink = 0;	
	tree[5].rlink = 0;

	tree[6].llink = 0;	
	tree[6].rlink = 0;

	
	preorder(tree, root);
	cout << endl;

	inorder(tree, root);
	cout << endl;

	postorder(tree, root);
	cout << endl;
}

void preorder( node* tree, int p) {
	if ( p > 0 ) {
		cout << tree[p].data << " ";
		preorder(tree, tree[p].llink);
		preorder(tree, tree[p].rlink);
	}
}

void inorder( node* tree, int p) {
	if ( p > 0 ) {
		inorder(tree, tree[p].llink);
		cout << tree[p].data << " ";
		inorder(tree, tree[p].rlink);
	}	
}

void postorder( node* tree, int p) {
	if ( p > 0 ) {
		postorder(tree, tree[p].llink);
		postorder(tree, tree[p].rlink);
		cout << tree[p].data << " ";
	}		
}