#include "cTree.h"


string cTree::getObjectFileName()
{
	return filename;
}

cTree::cTree()
{
	filename = "BigTree";//BigTree
	this->width = 109;
	this->height = 100;
	
}
cTree::cTree(int x, int y)
{
	this->filename = "BigTree";
	this->width = 109;
	this->height = 100;
	this->x = x;
	this->y = y;
}