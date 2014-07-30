/*
 ß	Map: Word->Occurence Set 
 ß	Add(word, page)
 ß	Iteration Capability
 */
 
 #ifndef CS240_KW_I
#define CS240_KW_I




#include <iostream>
#include <string>
#include "unit_test.h"
#include "keyword.h"
#include "occurrence.h"
#include "occurrence_set.h"




	using namespace std; 
	
	//!  keyword_index_node implements a binary search tree node
	class keyword_index_node {
		friend class keyword_index;   //!< keyword_index can access private members of keyword_index_node
		
	public:
		
		//!  Constructor
		keyword_index_node(string word, page & URL) :
		 left(NULL), right(NULL){
			value=new keyword(word, URL);
		}
		
				
		~keyword_index_node(){
		  		        delete value;
		}
		
		keyword_index_node(keyword k) :
		left(NULL), right(NULL){
			value =&k;
		}
		
		//! Copy Constructor
		keyword_index_node(const keyword_index_node & other) : 
		value(other.value),left(other.left),right(other.right){
		}
		
		
		//!  Read-only public methods for use by clients of the keyword_index class
		const std::string  GetValue() {
			
			return  value->getWord();
		}
		
		
		
		
		
		keyword_index_node * GetLeft()const{
			return left;
		}
		
		void traverse(string & output){
			
		  
			if(left!=NULL)
				left->traverse(output);
			
			output+="Node: ";
			output+=this->value->getWord();
			output+="\n";

			output+="\t";
			output+=value->get_Occurrence_set_output();
			

			
			if(right!=NULL)
				right->traverse(output);
			

		}
		
		void toXML(string & output){
			if(left!=NULL)
				left->toXML(output);
			
			output+="<word>\n";
			output+="<value>";
			output+=this->value->getWord();
			output+="</value>\n";
			
			
			output+=value->get_occurrence_set_XML_output();
			
			output+="</word>\n";
			
			if(right!=NULL)
				right->toXML(output);
		}
		
		
		keyword_index_node * GetRight()const{
			return right;
		}
		
		//! Assignment operator 
		keyword_index_node & operator=(const keyword_index_node & other){
			if(this!=&other){
				value=other.value;
				left=other.left;
				right=other.right;
			}
			
			return *this;
		}
		
	private:
		keyword * value;  //!< value stored in the node
		keyword_index_node * left;     //!< pointer to the node's left child
		keyword_index_node * right;    //!< pointer to the node's right child
	};
	
	
	//!  keyword_index implements a binary search tree
	class keyword_index {
		
	public:
		
		//!  No-arg constructor.  Initializes an empty keyword_index
		keyword_index();
		
		
		//!  Copy constructor.  Makes a complete copy of its argument
		keyword_index(const keyword_index & other);
		
		
		//!  Destructor
		~keyword_index();
		
		
		//!  Assignment operator.  Makes a complete copy of its argument
		//!  @return Reference to oneself
		keyword_index& operator =(const keyword_index & other);
		
		
		//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
		//!  @note This is useful for keyword_index clients that need to traverse the tree.)
		keyword_index_node * GetRoot()const;
		
		
		//!  @return true if the keyword_index is empty, or false if the keyword_index is not empty
		bool IsEmpty() const;
		
		
		//!  Removes all values from the keyword_index
		void Clear();
		
		void recursiveClear(keyword_index_node * me);
		
		
		//!  @return the number of values in the keyword_index
		int GetSize() const;
		
		
		//!  Inserts value v into the keyword_index
		//!  
		//!  @param v The new value being inserted
		//!
		//!  @return a pointer to the newly inserted node, or a pointer to the node where the
		//!	 count was incremented
		keyword_index_node * Insert(string word,  page & url);
		
		
		//!  Searches the tree for value v
		//!  
		//!  @param v The new value being searched for
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not in the tree
		keyword_index_node * Find(keyword & v) const;
		
		
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
		
		static bool  testKeyword_index(ostream & os);
		
	private:
		int count;
		keyword_index_node * root;
		keyword_index_node * recursiveInsert(keyword_index_node * current, string word,  page & url);
		keyword_index_node * recursiveFind(keyword_index_node * current, keyword & v)const  ;
		void copy(const keyword_index & other);
		void copyHelper(keyword_index_node*& copy, const keyword_index_node* originalTree);
		
	};




#endif
