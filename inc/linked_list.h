/*
 ß	stores page objects
 ß
 */
 
 #ifndef CS240_LINKED_LIST_H
#define CS240_LINKED_LIST_H

#include <string>

//! LLNode implements a doubly-linked list node
class LLNode {
		friend class LinkedList;  //!< LinkedList can access private members of LLNode
	public:
	
		//!  Constructor
		LLNode(const std::string & v, LLNode * p, LLNode * n) :
		  page(v), prev(p), next(n){
		}
		
		//! Copy Constructor 
		LLNode(const LLNode & other) : 
		   page(other.page),prev(other.prev),next(other.next){
		}
	
		//!  Read-only public methods for use by clients of the LinkedList class
		const std::string & Getpage() const{
		  return page;
		}
	
	
		LLNode * GetPrevious()const{
		  return prev;
		}
	
	
		LLNode * GetNext()const{
		  return next;
		}
		
		bool hasNext(){
		  return this->next!=NULL;
		}
		bool hasPrev(){
		  return this->prev!=NULL;
		}
		
		//! Assignment operator 
		LLNode & operator=(const LLNode & other){
			if(this!=&other){
				page=other.page;
				prev=other.prev;
				next=other.next;
			}
			return *this;
		}
	
	private:
		std::string page;        //!< page stored in the node
		LLNode * prev;            //!< pointer to previous node in the list
		LLNode * next;            //!< pointer to next node in the list
};


//! LinkedList implements a doubly-linked list
class LinkedList{
	public:
	
		//!  No-arg constructor.  Initializes an empty linked list
		LinkedList();
	
	
		//!  Copy constructor.  Makes a complete copy of its argument
		LinkedList(const LinkedList & other);
	
	
		//!  Destructor
		~LinkedList();
	
	
		//! Assignment operator.  Makes a complete copy of its argument
		//! @return A reference to oneself
		LinkedList& operator =(const LinkedList & other);
	
	
		//!  @return true if the list is empty, or false if the list is not empty
		bool IsEmpty() const;
	
	
		//!  Removes all pages from the list
		void Clear();
	
	
		//!  @return the number of pages in the list
		int GetSize() const;
	
	
	
		//!  @return a pointer to the first node in the list, or NULL if the list is empty
		LLNode * GetFirst()const;
	
	
	
		//!  @returns a pointer to the last node in the list, or NULL if the list is empty
		LLNode * GetLast()const;
	
	
		//!  Inserts page v into the list after node n
		//!  
		//!  @param v The new page being inserted
		//!  @param n A node that is already in the list after which the new node should 
		//!      be inserted.
		//!      If n is NULL, the new node should be inserted at the beginning of the list.
		//!
		//!  @return a pointer to the newly inserted node
		LLNode * push(const std::string & v, LLNode * n);
	
	
		//! Searches for the first occurrence of page v that appears in the list 
		//!   after node n
		//!   end
		//!  @param v The page being searched for
		//!  @param n The node in the list after which the search should begin.
		//!      If n is NULL, the list should be searched from the beginning.
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not found
		LLNode * Find(const std::string & v, LLNode * n) const;
	
	
		//!  Removes node n from the list
		//!  
		//!  @param n The node being removed from the list
		void Remove(LLNode * n);
		
		//! pops the first page off the list
		page pop();
		
		 void printer();
	
		  LLNode * start;
		  LLNode * end;
	private:
	  int count;
	 
	 
	  void copy(const LinkedList & other);
};


#endif

