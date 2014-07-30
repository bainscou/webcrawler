/*
 ß 	Set of occurrences 
 ß 	occurrence_set Map
 */
 
 #ifndef CS240_O_S
#define CS240_O_S

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "unit_test.h"
#include "occurrence.h"

using namespace std; 

//!  occurrence_set_node implements a binary search tree node
class occurrence_set_node {
	friend class occurrence_set; //!< occurrence_set can access private members of occurrence_set_node
	
public:
	
	//!  Constructor
	occurrence_set_node( occurrence * o) :
	value(o), left(NULL), right(NULL){
	}
	
	~occurrence_set_node(){
		
		delete value;
	}
	
	//! Copy Constructor
	occurrence_set_node(const occurrence_set_node & other) : 
	value(other.value),left(other.left),right(other.right){
	}
	
	
	//!  Read-only public methods for use by clients of the occurrence_set class
	const std::string  GetValue() {
		
		return  value->getURL();
	}
	
	void IncrementCount(){
		value->incrementCount();
	}
	
	
	
	occurrence_set_node * GetLeft()const{
		return left;
	}
	
	void traverse(string & output){
	
		
		//		cout << this << endl << this->left << endl;
		
		if(this->left != NULL){
		 
		  this->left->traverse(output);
		}

		
		output+="Node: "+this->value->getURL()+"\n"+"\tCount: ";
		output+=(char)(((int)'0')+this->value->getCount())+"\n";
	  
		if(this->right!=NULL){
		  
		    this->right->traverse(output);
		}
		
	}
	string convertInt(int number){
	   stringstream ss;//create a stringstream
	   ss << number;//add number to the stream
	   return ss.str();//return a string with the contents of the stream
	}
	
	void toXML(string & output){
		if(this->left != NULL){
			this->left->toXML(output);
		}

		output+="<occurrence>\n";
		output+="<url>\n"+this->value->getURL()+"\n"+"</url>\n";
		output+="<count>"+convertInt(this->value->getCount())+"</count>\n";
	  	output+="</occurrence>\n";
	  	
		if(this->right!=NULL){
			this->right->toXML(output);
		}
	}
	
	
	occurrence_set_node * GetRight()const{
		return right;
	}
	
	//! Assignment operator 
	occurrence_set_node & operator=(const occurrence_set_node & other){
		if(this!=&other){
			value=other.value;
			left=other.left;
			right=other.right;
		}
		
		return *this;
	}
	
private:
	occurrence * value;  //!< value stored in the node
	occurrence_set_node * left;     //!< pointer to the node's left child
	occurrence_set_node * right;    //!< pointer to the node's right child
};


//!  occurrence_set implements a binary search tree
class occurrence_set {
	
public:
	
	//!  No-arg constructor.  Initializes an empty occurrence_set
	occurrence_set();
	
	
	//!  Copy constructor.  Makes a complete copy of its argument
	occurrence_set(const occurrence_set & other);
	
	
	//!  Destructor
	~occurrence_set();
	
	
	//!  Assignment operator.  Makes a complete copy of its argument
	//!  @return Reference to oneself
	occurrence_set& operator =(const occurrence_set & other);
	
	
	//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
	//!  @note This is useful for occurrence_set clients that need to traverse the tree.)
	occurrence_set_node * GetRoot()const;
	
	
	//!  @return true if the occurrence_set is empty, or false if the occurrence_set is not empty
	bool IsEmpty() const;
	
	
	//!  Removes all values from the occurrence_set
	void Clear();
	
	void recursiveClear(occurrence_set_node * me);
	
	
	//!  @return the number of values in the occurrence_set
	int GetSize() const;
	
	
	//!  Inserts value v into the occurrence_set
	//!  
	//!  @param v The new value being inserted
	//!
	//!  @return a pointer to the newly inserted node, or a pointer to the node where the
	//!	 count was incremented
	occurrence_set_node * Insert(occurrence *  o);
	
	
	//!  Searches the tree for value v
	//!  
	//!  @param v The new value being searched for
	//!
	//!  @return a pointer to the node containing v, or NULL if v is not in the tree
	occurrence_set_node * Find(string v) const;
	
	
	//! @NOTE: YOU ARE NOT REQUIRED TO IMPLEMENT THE Remove METHOD BELOW
	//!        (BUT YOU CAN IF YOU WANT TO)
	//!
	//!  Removes value v from the tree
	//!  
	//!  @param v The value being removed from the tree
	//!
	//!  @return true if v was removed from the tree, or false if v was not in the tree
	//bool Remove(const std::string & v);
	
	void addOccurrence(string url);
	
	string traverse();
	
	string toXML();
	
	static bool  testOccurrence_set(ostream & os);
	
private:
	int count;
	occurrence_set_node * root;
	occurrence_set_node * recursiveInsert(occurrence_set_node * current, occurrence * v);
	occurrence_set_node * recursiveFind(occurrence_set_node * current, string v)const  ;
	void copy(const occurrence_set & other);
	void copyHelper(occurrence_set_node*& copy, const occurrence_set_node* originalTree);
	
};



#endif
