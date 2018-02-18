/* Author:	Kaylee Gabus
   Date:	2-14-17
   Class:	EECS 2510 Non-Linear
 */


#pragma once
#include <string>;

using namespace std;

struct BSTNode
{
	int count = 0;
	string key;
	BSTNode *LeftChild = nullptr;
	BSTNode *RightChild = nullptr;
	BSTNode *ParentNode = nullptr;
};

class BinarySearchTree
{
public:
	BSTNode *treeRoot;

	BinarySearchTree();
	int nodeCount;
	int insert(string key);
	int remove(string key);
	int searchKey(string key);
	int getTotalNodeCount();
	void listKeys();
	string next(string key);
	string previous(string key);
	string getMinumum();
	string getMaximum();

private:
	int insertKey(string key);
	int deleteKey(string key);
	void traverseAndPrint(BSTNode *node);
	void transplantSubtree(BSTNode *nodeA, BSTNode *nodeB);
	BSTNode *treeMin(BSTNode *node);
	BSTNode *treeMax(BSTNode *node);
	BSTNode *findNodePointer(string key);
	BSTNode *nodePointerSucessor(BSTNode *currentNodePointer);
	BSTNode *nodePointerPredecessor(BSTNode *currentNodePointer);
};