/*
 ß 	Tracks the pages that have been visited
 ß 	BST Map
 */
 
 
 
 #ifndef CS240_P_H
 #define CS240_P_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "unit_test.h"
#include "page.h"

using namespace std; 

//!  page_history_node implements a binary search tree node
class page_history_node {
	friend class page_history;   //!< page_history can access private members of page_history_node
	
public:
	
	//!  Constructor
	page_history_node(  page & p) :
	value(p), left(NULL), right(NULL){
	}
	
	//! Copy Constructor
	page_history_node(const page_history_node & other) : 
	value(other.value),left(other.left),right(other.right){
	}

	~page_history_node(){
		//delete value;
	}
	
	

	const std::string  GetValue() {
		
		return  value.getURL();
	}
	
	
	
	
	
	page_history_node * GetLeft()const{
		return left;
	}
	
	void traverse(string & output){
		
		if(this->left!=NULL)
		    left->traverse(output);
		output+="Node: "+this->value.getURL()+"\n"+"\tDescription: "+this->value.getDescription()+"\n";
		if(this->right!=NULL)
		    right->traverse(output);
		
	}
	
	void toXML(string & output){
		if(this->left!=NULL)
		    left->toXML(output);
		output+="<page>\n";
		output+="<url>\n"+this->value.getURL()+"\n"+"</url>\n";
		output+="<description>"+this->value.getDescription()+"</description>\n";
		output+="</page>\n";
		if(this->right!=NULL)
		    right->toXML(output);
	}
	
	
	page_history_node * GetRight()const{
		return right;
	}
	
	//! Assignment operator 
	page_history_node & operator=(const page_history_node & other){
		if(this!=&other){
			value=other.value;
			left=other.left;
			right=other.right;
		}
		
		return *this;
	}
	
private:
	page  value;  //!< value stored in the node
	page_history_node * left;     //!< pointer to the node's left child
	page_history_node * right;    //!< pointer to the node's right child
};


//!  page_history implements a binary search tree
class page_history {
	
public:
	
	//!  No-arg constructor.  Initializes an empty page_history
	page_history();
	
	
	//!  Copy constructor.  Makes a complete copy of its argument
	page_history(const page_history & other);
	
	
	//!  Destructor
	~page_history();
	
	
	//!  Assignment operator.  Makes a complete copy of its argument
	//!  @return Reference to oneself
	page_history& operator =(const page_history & other);
	
	
	//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
	//!  @note This is useful for page_history clients that need to traverse the tree.)
	page_history_node * GetRoot()const;
	
	
	//!  @return true if the page_history is empty, or false if the page_history is not empty
	bool IsEmpty() const;
	
	
	//!  Removes all values from the page_history
	void Clear();
	
	void recursiveClear(page_history_node * me);
	
	
	//!  @return the number of values in the page_history
	int GetSize() const;
	
	
	//!  Inserts value v into the page_history
	//!  
	//!  @param v The new value being inserted
	//!
	//!  @return a pointer to the newly inserted node, or a pointer to the node where the
	//!	 count was incremented
	page_history_node * Insert(page &  o);
	
	bool contains(page & query);
	
	//!  Searches the tree for value v
	//!  
	//!  @param v The new value being searched for
	//!
	//!  @return a pointer to the node containing v, or NULL if v is not in the tree
	page_history_node * Find(page & v) const;
	
	
	//! @NOTE: YOU ARE NOT REQUIRED TO IMPLEMENT THE Remove METHOD BELOW
	//!        (BUT YOU CAN IF YOU WANT TO)
	//!
	//!  Removes value v from the tree
	//!  
	//!  @param v The value being removed from the tree
	//!
	//!  @return true if v was removed from the tree, or false if v was not in the tree
	//bool Remove(const std::string & v);
	
	string traverse();
	
	string toXML();
	
	static bool  testpage_history(ostream & os);
	
private:
	int count;
	page_history_node * root;
	page_history_node * recursiveInsert(page_history_node * current, page & v);
	page_history_node * recursiveFind(page_history_node * current, page & v)const  ;
	void copy(const page_history & other);
	void copyHelper(page_history_node*& copy, const page_history_node* originalTree);
	
};






#endif
