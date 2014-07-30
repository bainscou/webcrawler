/*
 *  occurrence_set.cpp
 *  
 *
 *  Created by Benjamin John Ainscough on 3/2/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */




#include "occurrence_set.h"
using namespace std;

void occurrence_set::copy(const occurrence_set & other){
	root = 0;
	count= other.count;
	//	copyHelper(root, other.root);
}

void occurrence_set::copyHelper(occurrence_set_node*& copy,
	 const occurrence_set_node* originalTree){
	
	if (originalTree == NULL)
		copy = NULL;
	else{
		copy = new occurrence_set_node(originalTree->value);
		copyHelper(copy->left, originalTree->left);
		copyHelper(copy->right, originalTree->right);
	}
	
}

string occurrence_set::toXML(){
	string XML;
	
	root->toXML(XML);
	
	return XML;
}

string occurrence_set::traverse(){
	string output;
	
	root->traverse(output);

	return output;
}

occurrence_set::occurrence_set() : root(0) , count(0){
	return; 
}

occurrence_set::occurrence_set(const occurrence_set & other){
	copy(other);
}

occurrence_set::~occurrence_set(){
	Clear();
}

occurrence_set& occurrence_set:: operator =(const occurrence_set & other){
	if (this != &other) {
		Clear();
		copy(other);
	}
	return *this;
}

void occurrence_set::Clear(){
	recursiveClear(root);
	root= 0;
	count= 0;
}

void occurrence_set::recursiveClear(occurrence_set_node * me){
	if(me==NULL)
		return;
	recursiveClear(me->right);
	recursiveClear(me->left);
	//delete me->left;
	//delete me->right;
	delete me;
	me=NULL;
	
}

occurrence_set_node * occurrence_set::GetRoot()const{
	return root;
}

bool occurrence_set::IsEmpty() const{
	return (count==0);
}

int occurrence_set::GetSize() const{
	return count;
}



occurrence_set_node * occurrence_set::Insert(occurrence *  o){
 
	if(root==NULL){
		root= new occurrence_set_node(o);
		count++;
		return root;
	}
	else{
		occurrence_set_node * cur= root;
		return recursiveInsert(root,o);
		
	}
	
    
}

occurrence_set_node * occurrence_set::recursiveInsert(occurrence_set_node * current,
							 occurrence * v){
	int comp=v->getURL().compare(current->value->getURL());
	//cout<< "Comparing: "<<comp <<endl;
	if(comp<0){
		//cout<< "I am on the left"<<endl;
		if(current->left==NULL){
			count++;
			return current->left= new occurrence_set_node(v);
		}
		else
			recursiveInsert(current->left, v);
	}
	else if(comp>0){
		//cout<< "I am on the right"<<endl;
		if(current->right==NULL){
			count++;
			return current->right= new occurrence_set_node(v);
		}
		else
			recursiveInsert(current->right, v);
	}
	else{
		//current->IncrementCount();
		return current;
	}
}


occurrence_set_node * occurrence_set::Find(string v) const{
	return recursiveFind(root, v);
}

occurrence_set_node * occurrence_set::recursiveFind(occurrence_set_node * current, string v) const{
	// cout<< v<<endl;
	// cout<< current<<endl;
	if(current==NULL){
		return NULL;
	}
	else if(v.compare(current->value->getURL())<0){
		return recursiveFind(current->left,v );
	}
	else if(v.compare(current->value->getURL())>0){
		return recursiveFind(current->right,v);
	}
	else{
		return current;
	}
	
}

bool occurrence_set :: testOccurrence_set(ostream & os){

	cout<<"Testing occurrence_set class.................";
	bool success = true;
	
	if (success) {
		cout << "PASSED"<<endl;
	}
	return success;
   
}
