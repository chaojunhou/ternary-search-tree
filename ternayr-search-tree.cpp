// Cpp program to demonstrate Ternary Search Tree (TST) insert, travese
// and search operations
#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#include <vector>
# include<string>
#include <iostream>
using namespace std;
// A node of ternary search tree
struct Node
{
	char data;

	// True if this character is last character of one of the words
	unsigned isEndOfString : 1;

	struct Node *left, *eq, *right;
};

// A utility function to create a new ternary search tree node
struct Node* newNode(char data)
{
	auto *temp = new Node();
	//	 struct Node* temp =  (struct Node*) malloc(sizeof( struct Node ));
	temp->data = data;
	temp->isEndOfString = 0;
	temp->left = temp->eq = temp->right = NULL;
	return temp;
}

// Function to insert a new word in a Ternary Search Tree
void insert(struct Node** root, char *word)
{
	// Base Case: Tree is empty
	if (!(*root))
		*root = newNode(*word);

	// If current character of word is smaller than root's character,
	// then insert this word in left subtree of root
	if ((*word) < (*root)->data)
		insert(&((*root)->left), word);

	// If current character of word is greate than root's character,
	// then insert this word in right subtree of root
	else if ((*word) > (*root)->data)
		insert(&((*root)->right), word);

	// If current character of word is same as root's character,
	else
	{
		if (*(word + 1))
			insert(&((*root)->eq), word + 1);

		// the last character of the word
		else
			(*root)->isEndOfString = 1;
	}
}

// A recursive function to traverse Ternary Search Tree
void   traverseTSTUtil(struct Node* root,vector<string> & vec, string buffer, int depth)
{
	if (root)
	{
		// First traverse the left subtree
		traverseTSTUtil(root->left,vec, buffer, depth);

		// Store the character of this node
		buffer += root->data;
		if (root->isEndOfString)
		{
			vec.push_back(buffer);
			//buffer=" ";
		}

		// Traverse the subtree using equal pointer (middle subtree)
		traverseTSTUtil(root->eq, vec,buffer, depth + 1);

		// Finally Traverse the right subtree
		traverseTSTUtil(root->right,vec, buffer, depth);
	}
}

// The main function to traverse a Ternary Search Tree.
// It mainly uses traverseTSTUtil()
vector<string> traverseTST(struct Node* root)
{
	string buffer;
	vector<string> vec;

	traverseTSTUtil(root,vec, buffer, 0);
	return vec;
}

// Function to search a given word in TST
int searchTST(struct Node *root, char *word)
{
	if (!root)
		return 0;

	if (*word < (root)->data)
		return searchTST(root->left, word);

	else if (*word >(root)->data)
		return searchTST(root->right, word);

	else
	{
		if (*(word + 1) == '\0')
			return root->isEndOfString;
			 
		return searchTST(root->eq, word + 1);
	}
}

// Driver program to test above functions
int main()
{
	struct Node *root = NULL;

	insert(&root, "cat");
	insert(&root, "cats");
	insert(&root, "up");
	insert(&root, "bug");

	printf("Following is traversal of ternary search tree\n");

	for (auto ss:traverseTST(root))
	{
		cout << ss << endl;
	}
	printf("\nFollowing are search results for cats, bu and cat respectively\n");
	searchTST(root, "cats") ? printf("Found\n") : printf("Not Found\n");
	searchTST(root, "bu") ? printf("Found\n") : printf("Not Found\n");
	searchTST(root, "cat") ? printf("Found\n") : printf("Not Found\n");
	cin.get();
	return 0;
}
