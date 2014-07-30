/*
 ß 	Tracks pages to be processed
 ß		Push and pop method
 ß 		IsEmpty method
 */
 
 
 #ifndef CS240_P_Q
#define CS240_P_Q

#include <iostream>
#include <string>
#include "page.h"
using namespace std; 


//! page_queue_node implements a doubly-linked list node
class page_queue_node {
	friend class page_queue;  //!< page_queue can access private members of page_queue_node
public:
	
	//!  Constructor
	page_queue_node(page & v, page_queue_node * p, page_queue_node * n) :
	value(v), prev(p), next(n){
	}
	
	//! Copy Constructor 
	page_queue_node(const page_queue_node & other) : 
	value(other.value),prev(other.prev),next(other.next){
	}
	
	~page_queue_node(){
		
		//delete value;
	}

	//!  Read-only public methods for use by clients of the page_queue class
	const std::string  getURL() {
		
		return  value.getURL();
	}
	
	page getPage(){
		return value;
	}
	
	
	page_queue_node * GetPrevious()const{
		return prev;
	}
	
	
	page_queue_node * GetNext()const{
		return next;
	}
	
	bool hasNext(){
		return this->next!=NULL;
	}
	bool hasPrev(){
		return this->prev!=NULL;
	}
	
	//! Assignment operator 
	page_queue_node & operator=(const page_queue_node & other){
		if(this!=&other){
			value=other.value;
			prev=other.prev;
			next=other.next;
		}
		return *this;
	}
	
private:
	page  value;        //!< value stored in the node
	page_queue_node * prev;            //!< pointer to previous node in the list
	page_queue_node * next;            //!< pointer to next node in the list
};


//! page_queue implements a doubly-linked list
class page_queue{

public:
	
	//!  No-arg constructor.  Initializes an empty linked list
	page_queue();
	
	
	//!  Copy constructor.  Makes a complete copy of its argument
	page_queue(const page_queue & other);
	
	
	//!  Destructor
	~page_queue();
	
	
	//! Assignment operator.  Makes a complete copy of its argument
	//! @return A reference to oneself
	page_queue& operator =(const page_queue & other);
	
	
	//!  @return true if the list is empty, or false if the list is not empty
	bool IsEmpty() const;
	
	
	//!  Removes all values from the list
	void Clear();
	
	
	//!  @return the number of values in the list
	int GetSize() const;
	
	
	
	//!  @return a pointer to the first node in the list, or NULL if the list is empty
	page_queue_node * GetFirst()const;
	
	
	
	//!  @returns a pointer to the last node in the list, or NULL if the list is empty
	page_queue_node * GetLast()const;
	
	
	//!  Inserts value v into the list after node n
	//!  
	//!  @param v The new value being inserted
	//!  @param n A node that is already in the list after which the new node should 
	//!      be inserted.
	//!      If n is NULL, the new node should be inserted at the beginning of the list.
	//!
	//!  @return a pointer to the newly inserted node
	page_queue_node * Insert(page & Url, page_queue_node * n);
	
	
	//! Searches for the first occurrence of value v that appears in the list 
	//!   after node n
	//!   end
	//!  @param v The value being searched for
	//!  @param n The node in the list after which the search should begin.
	//!      If n is NULL, the list should be searched from the beginning.
	//!
	//!  @return a pointer to the node containing v, or NULL if v is not found
	page_queue_node * Find(page & url, page_queue_node * n) const;
	
	
	//!  Removes node n from the list
	//!  
	//!  @param n The node being removed from the list
	void Remove(page_queue_node * n);
	
	// pops the first node off the list
	page  pop();
	
	static bool test_page_queue(ostream & os);
	
	void printer();
	

	page_queue_node * start;
	page_queue_node * end;
private:
	int count;
	
	
	void copy(const page_queue & other);
};


#endif
