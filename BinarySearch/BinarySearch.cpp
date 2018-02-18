/*	Author:	Kaylee Gabus
	Date:	2-14-17
	Class:	EECS 2510 Non-Linear
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include "BinarySearchTree.h";


using namespace std;


void printHelp();
BinarySearchTree BSTree = BinarySearchTree();


int main()
{
	int keyOccuranceCount = 0;
	string commandString = "";
	string enteredKeyString = "";
	string outputString;

	cout << "Please Enter A Command: \n";
	printHelp();

	do
	{
		cout << "\n>";							//output a new line and > for formatting purposes
		cin >> commandString;

		for (int counter = 0; counter < commandString.length(); counter++)
		{	//set commands to lower case
			commandString[counter] = tolower(commandString[counter]);
		}

		if (commandString == "exit")
			break;
		if (commandString == "min")
		{
			cout << "	" << BSTree.getMinumum();
			continue;
		}	
		else if (commandString == "max")
		{
			cout << "	" << BSTree.getMaximum();
			continue;
		}
		else if (commandString == "list")
		{
			BSTree.listKeys();
			continue;
		}
		else if (commandString == "help")
		{
			cout << "The following commands are available:\n";
			printHelp();
			continue;
		}
		else if (commandString == "nodes")
		{
			cout << "	" << BSTree.getTotalNodeCount();
			continue;
		}
		else cin >> enteredKeyString;			//get the key 
		cout << "	";							//offset the output for visual reference 
			
		if (commandString == "insert")
		{
			keyOccuranceCount = BSTree.insert(enteredKeyString);
			cout << enteredKeyString << "	" << keyOccuranceCount;
			continue;
		}	
		else if (commandString == "delete")
		{
			keyOccuranceCount = BSTree.remove(enteredKeyString);
			cout << enteredKeyString << "	" << keyOccuranceCount;
			continue;
		}
		else if (commandString == "search")
		{
			keyOccuranceCount = BSTree.searchKey(enteredKeyString);
			cout << enteredKeyString << "	" << keyOccuranceCount;
			continue;
		}
		else if (commandString == "next")
		{
			cout << BSTree.next(enteredKeyString);
			continue;
		}
		else if (commandString == "prev")
		{
			cout << BSTree.previous(enteredKeyString);
			continue;
		}
		else cout << "The command you entered is not reconized. Enter help for a list of accepted commands.";

	} 
	while (commandString != "exit");

	cout << "Closing KGabus BinarySearch";
    return 0;	
}

void printHelp()
{
	cout << "insert (string) \t Insert a string into the tree. \n";
	cout << "delete (string) \t Remove a string from the tree. \n";
	cout << "search (string) \t Find the number of occurances of a string in the tree. \n";
	cout << "next (string) \t\t Find the sucessor of the entered string. \n";
	cout << "prev(string) \t\t Find the predecessor of the entered string. \n";
	cout << "min \t\t\t Find the minimum value. \n";
	cout << "max \t\t\t Find the maximum value. \n";
	cout << "help \t\t\t Print this list of commands. \n";
	cout << "exit \t\t\t Exit the program. \n";
}

