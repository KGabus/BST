/* Author:	Kaylee Gabus
*  Date:	2-14-17
*  Class:	EECS 2510 Non-Linear
*/


#pragma once
#include "stdafx.h";
#include <string>;
#include <iostream>;
#include "BinarySearchTree.h";

using namespace std;


#pragma region PublicFunctions

BinarySearchTree::BinarySearchTree()
{
	nodeCount = 0;
	treeRoot = nullptr;
}

int BinarySearchTree::insert(string key)
{	//inserts a key into the tree
	//if key is already present, increments node's counter
	//returns the count of the key in the tree
	int nodeCounter = insertKey(key);
	return nodeCounter;
}

int BinarySearchTree::remove(string key)
{	//removes a key from the tree
	//returns the count of the key in the tree
	//if node had count of 1, deletes node; otherwise decrements counter
	//if key is not in the set, returns -1
	int nodeCounter = deleteKey(key);
	return nodeCounter;
}

string BinarySearchTree::getMinumum()
{	//returns the smallest key
	//if tree is empty, returns empty string
	BSTNode *minNodePointer	= treeMin(treeRoot);

	if (minNodePointer == nullptr)
		return "";
	return minNodePointer->key;
}

string BinarySearchTree::getMaximum()
{	//returns the largest key
	//if tree is empty, returns empty string
	BSTNode *maxNodePointer = treeMax(treeRoot);

	if (maxNodePointer == nullptr)
		return "";
	return maxNodePointer->key;
}

int BinarySearchTree::searchKey(string key)
{	//returns count of key in the tree
	//returns 0 if key is not found
	BSTNode *locatedNodePointer = findNodePointer(key);

	if (locatedNodePointer != nullptr)
		return locatedNodePointer->count;
	else return 0;
}

string BinarySearchTree::next(string key)
{	//Finds the next key in the tree. If tree is empty or key is not found, returns empty string.
	BSTNode *nextPointer = nodePointerSucessor(findNodePointer(key));

	if (nextPointer == nullptr)
		return "";
	else return nextPointer->key;
}

string BinarySearchTree::previous(string key)
{	//Finds the previous key in the tree. If the tree is empty or key is not found, returns empty string.
	BSTNode *previousPointer = nodePointerPredecessor(findNodePointer(key));

	if (previousPointer == nullptr)
		return "";
	else return previousPointer->key;
}

void BinarySearchTree::listKeys()
{	//Performs an in order traversal and prints each key with it's count.
	traverseAndPrint(treeRoot);
}

int BinarySearchTree::getTotalNodeCount()
{	//returns the number of nodes in the tree
	return nodeCount;
}



#pragma endregion

#pragma region PrivateFunctions

int BinarySearchTree::insertKey(string key)
{	//Inserts a key into the tree. If the key is already present in the tree, increase that key's node's counter.
	int returnCount = 1;
	BSTNode *currentNodePointer;
	BSTNode *parentNodePointer;
	BSTNode *locatedNodePointer = findNodePointer(key);		//check to see if key os present in the tree

	if (locatedNodePointer == nullptr)					
	{	//if key isn't found, make and insert a new node
		currentNodePointer = treeRoot;
		parentNodePointer = nullptr;

		BSTNode *nodeToInsert = new BSTNode;
		nodeToInsert->count = 1;
		nodeToInsert->key = key;

		while (currentNodePointer != nullptr)
		{	//navigate the tree by comparing keys until a null pointer is followed
			parentNodePointer = currentNodePointer;
			if (key < currentNodePointer->key)
			{
				currentNodePointer = currentNodePointer->LeftChild;
			}
			else currentNodePointer = currentNodePointer->RightChild;
		}

		nodeToInsert->ParentNode = parentNodePointer;	//currentNodePointer is null at this point

		if (nodeToInsert->ParentNode == NULL)			
		{	//if the tree is empty, add node as root
			treeRoot = nodeToInsert;
		}
		else if (key < parentNodePointer->key)			//if the new node's key is less than the parent's, make it a left child
			parentNodePointer->LeftChild = nodeToInsert;
		else											//new node's key is greater than parents, make it a right child
			parentNodePointer->RightChild = nodeToInsert;

		nodeCount++;									//increment count of tree nodes
	}
	else												//if it is found, increment the counter
	{
		locatedNodePointer->count = locatedNodePointer->count++;
		returnCount = locatedNodePointer->count;
	}

	return returnCount;
}

int BinarySearchTree::deleteKey(string key)
{
	BSTNode *nodeToDeletePointer = findNodePointer(key);

	if (nodeToDeletePointer == nullptr)					//if the key wasn't found, return -1
		return -1;
	else if (nodeToDeletePointer->count > 1)			//if the key was found and had more than 1 as it's count, decrement count
	{
		nodeToDeletePointer->count--;
		return nodeToDeletePointer->count;
	}
	else
	{
		if (nodeToDeletePointer->LeftChild == nullptr && nodeToDeletePointer->RightChild == nullptr)
		{	//if the node has no children
			if (nodeToDeletePointer == treeRoot)	//if the node is the root of the tree
			{
				treeRoot = nullptr;
				delete nodeToDeletePointer;
				nodeCount--;
				return 0;
			}		
			
			if (nodeToDeletePointer == nodeToDeletePointer->ParentNode->LeftChild)	//if the node is a left child
				nodeToDeletePointer->ParentNode->LeftChild = nullptr;				// set it's parent's left pointer to nullptr
			else nodeToDeletePointer->ParentNode->RightChild = nullptr;
		}
		else if (nodeToDeletePointer->LeftChild == nullptr)	//if the node doesn't have a left child, switch with right child subtree
			transplantSubtree(nodeToDeletePointer, nodeToDeletePointer->RightChild);
		else if (nodeToDeletePointer->RightChild == nullptr)//switch node and left child subtree
			transplantSubtree(nodeToDeletePointer, nodeToDeletePointer->LeftChild);
		
		else											//node has both children
		{
			BSTNode *nodeSucessorPointer = nodePointerSucessor(nodeToDeletePointer);//find the next node

			if (nodeSucessorPointer->ParentNode != nodeToDeletePointer)//if the next node isn't an immediate child
			{
				transplantSubtree(nodeSucessorPointer, nodeSucessorPointer->RightChild);//swap the next node and it's right subtree
				nodeSucessorPointer->RightChild = nodeToDeletePointer->RightChild;	//set the next node's right child to the right child of the node being deleted
				nodeSucessorPointer->RightChild->ParentNode = nodeSucessorPointer;	
			}

			transplantSubtree(nodeToDeletePointer, nodeSucessorPointer);			//swap the node and its sucessor 
			nodeSucessorPointer->LeftChild = nodeToDeletePointer->LeftChild;		//set the left child of the successor to the right subtree of the node
			nodeSucessorPointer->LeftChild->ParentNode = nodeSucessorPointer;		
		}
		delete nodeToDeletePointer;													//garbage collect the node
		nodeCount--;																//decrement count of tree nodes
	}
	return 0;
}

BSTNode *BinarySearchTree::treeMin(BSTNode *node)
{	//Finds and returns the minimum value in the tree. Returns newline formatting if tree is empty.
	if (node != nullptr)
	{
		while (node->LeftChild != NULL)					//while the node has left children, go left
				node = node->LeftChild;
	}
	return node;
}

BSTNode *BinarySearchTree::treeMax(BSTNode *node)
{	//Finds and returns the maximum value in the tree. Returns newline formatting if tree is empty.
	if (node != nullptr)
	{
		while (node->RightChild != NULL)				//while the node has a right child, go right
			node = node->RightChild;
	}
	return node;
}

BSTNode *BinarySearchTree::findNodePointer(string key)
{
	BSTNode *currentNodePointer = treeRoot;			//starting at the tree's root node

	while (currentNodePointer != NULL)				//continue until a null pointer is reached
	{
		if (currentNodePointer->key.compare(key) == 0)		//if the keys match, return the node
			return currentNodePointer;
		if (currentNodePointer->key.compare(key) < 0)
		{//if the current key is greater than the search key, follow a right pointer
			currentNodePointer = currentNodePointer->RightChild;
			continue;
		}
		else currentNodePointer = currentNodePointer->LeftChild;			//the current key is less than the search key, follow a left pointer	
	}
	return nullptr;					//this statement will only execute if the key wasn't found
}

BSTNode *BinarySearchTree::nodePointerSucessor(BSTNode *currentNodePointer)
{
	BSTNode *parentNodePointer;

	if (currentNodePointer == nullptr)						//if the tree is empty, return null pointer
		return nullptr;

	if (currentNodePointer->RightChild != nullptr)
	{	//if the current node has a right child
		return treeMin(currentNodePointer->RightChild);		//continue moving right until a leaf is reached
	}

	parentNodePointer = currentNodePointer->ParentNode;

	while (parentNodePointer != nullptr && currentNodePointer == parentNodePointer->RightChild)
	{	//while the current node isn't the root and is the right child of it's parent
		currentNodePointer = parentNodePointer;				//move upwards one level in the tree
		parentNodePointer = parentNodePointer->ParentNode;
	}

	return parentNodePointer;
}

BSTNode *BinarySearchTree::nodePointerPredecessor(BSTNode *currentNodePointer)
{
	BSTNode *parentNodePointer;

	if (currentNodePointer == nullptr)						//if the tree is empty, return null pointer
		return nullptr;

	if (currentNodePointer->LeftChild != nullptr)
	{	//if the current node has a left child
		return treeMax(currentNodePointer->LeftChild);		//continue moving left until a leaf is reached
	}

	parentNodePointer = currentNodePointer->ParentNode;

	while (parentNodePointer != nullptr && currentNodePointer == parentNodePointer->LeftChild)
	{//while the current node isn't the root and is the right child of it's parent
		currentNodePointer = parentNodePointer;				//move upwards one level in the tree
		parentNodePointer = parentNodePointer->ParentNode;
	}

	return parentNodePointer;
}

void BinarySearchTree::traverseAndPrint(BSTNode *node)
{	//performs an in order traversal of the tree to print out keys and counts
 	if (node == nullptr)
		return;

	if (node->LeftChild != nullptr)
	{
		traverseAndPrint(node->LeftChild);
	}

	cout << "	" << node->key << "		" << node->count << endl;

	if (node->RightChild != nullptr)
	{
		traverseAndPrint(node->RightChild);
	}
}

void BinarySearchTree::transplantSubtree(BSTNode *nodeA, BSTNode *nodeB)
{
	if (nodeA->ParentNode == nullptr)				//if node A is the root, make node B the root
		treeRoot = nodeB;
	else if (nodeA == nodeA->ParentNode->LeftChild)	//if node A is a left child
		nodeA->ParentNode->LeftChild = nodeB;		//make B the new left child
	else nodeA->ParentNode->RightChild = nodeB;		//else B is the new right child

	if (nodeB != nullptr)
		nodeB->ParentNode = nodeA->ParentNode;		//make B's parent A's parent
}

#pragma endregion




