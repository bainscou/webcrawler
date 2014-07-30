/*
 *  keyword_set.cpp
 *  
 *
 *  Created by Benjamin John Ainscough on 3/2/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */




#include "keyword_index.h"
using namespace std;

void keyword_index::copy(const keyword_index & other){
	
	// recursive method to copy the tree
	root = 0;
	count= other.count;
	
	copyHelper(root, other.root);
	
	
}

void keyword_index::copyHelper(keyword_index_node*& copy, const keyword_index_node* originalTree){
	
	if (originalTree == NULL)
		copy = NULL;
	else{
		copy = new keyword_index_node(*originalTree);
		copyHelper(copy->left, originalTree->left);
		copyHelper(copy->right, originalTree->right);
	}
	
}

string keyword_index::traverse(){
	string output;
	root->traverse(output);
	return output;
}

string keyword_index::toXML(){
	string XML;
	XML += "<index>\n";
	root->toXML(XML);
	XML += "</index>\n";
	return XML;
}


keyword_index::keyword_index() : root(0) , count(0){
	return; 
}

keyword_index::keyword_index(const keyword_index & other){
	copy(other);
}

keyword_index::~keyword_index(){
	Clear();
}

keyword_index& keyword_index:: operator =(const keyword_index & other){
	if (this != &other) {
		Clear();
		copy(other);
	}
	return *this;
}

void keyword_index::Clear(){
	recursiveClear(root);
	root= 0;
	count= 0;
}

void keyword_index::recursiveClear(keyword_index_node * me){
	if(me==NULL)
		return;
	recursiveClear(me->right);
	recursiveClear(me->left);
	//delete me->left;
	//delete me->right;
	delete me;
	me=NULL;
	
}

keyword_index_node * keyword_index::GetRoot()const{
	return root;
}

bool keyword_index::IsEmpty() const{
	return (count==0);
}

int keyword_index::GetSize() const{
	return count;
}

keyword_index_node * keyword_index::Insert(string word,  page & URL){
	
	if(root==NULL){
		root= new keyword_index_node( word,  URL);
		count++;
		return root;
	}
	else{
		keyword_index_node * cur= root;
		return recursiveInsert(root,word, URL);
		
	}
	
    
}

keyword_index_node * keyword_index::recursiveInsert(keyword_index_node * current,
							 string word,  page & url){
	//keyword * v = new keyword(word, url);
	int comp=word.compare(current->value->getWord());
	//cout<< "Comparing: "<<comp <<endl;
	if(comp<0){
		//cout<< "I am on the left"<<endl;
		if(current->left==NULL){
			count++;
			return current->left= new keyword_index_node(word, url);
		}
		else
			recursiveInsert(current->left, word, url);
	}
	else if(comp>0){
		//cout<< "I am on the right"<<endl;
		if(current->right==NULL){
			count++;
			return current->right= new keyword_index_node(word, url);
		}
		else
			recursiveInsert(current->right, word, url);
	}
	else{
		
	        current->value->addOccurrence(url);
		return current;
	}
}


keyword_index_node * keyword_index::Find(keyword & v) const{
	return recursiveFind(root, v);
}

keyword_index_node * keyword_index::recursiveFind(keyword_index_node * current, keyword & v) const{
	// cout<< v<<endl;
	// cout<< current<<endl;
	if(current==NULL)
		return NULL;
	if(v.getWord().compare(current->value->getWord())<0){
		recursiveFind(current->left,v );
	}
	else if(v.getWord().compare(current->value->getWord())>0){
		recursiveFind(current->right,v);
	}
	else
		return current;
	
    
	
}

bool keyword_index :: testKeyword_index(ostream & os){
        cout << "Testing keyword_index class................." ;
	bool success = true;
	keyword_index * test1 = new keyword_index();
	page crawlIndex("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawlindex.html");
	page frameTester("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/frame/testSix.html");
	page testFive("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/testFive.html");
	page scaleTest("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/scale.php");
	
	test1->Insert("test", crawlIndex);
	test1->Insert("test", crawlIndex);
	test1->Insert("test", crawlIndex);
	test1->Insert("test", crawlIndex);
	test1->Insert("test", crawlIndex);
	
	//cout<<"After crawlIndex: \n"<<test1->toXML()<<endl;
	
	test1->Insert("test", frameTester);
	
	//cout<<"After frameTester: \n"<<test1->toXML()<<endl;
	
	test1->Insert("test", testFive);
	
	test1->Insert("test", scaleTest);
	
	//cout<<test1->toXML()<<endl;
	
	delete test1;
	
	/*
	returns 
<index>
<word>
<value>test</value>
<occurrence>
<url>
http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/frame/testSix.html
</url>
<count>1</count>
</occurrence>
<occurrence>
<url>
http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/scale.php
</url>
<count>1</count>
</occurrence>
<occurrence>
<url>
http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/testFive.html
</url>
<count>1</count>
</occurrence>
<occurrence>
<url>
http://students.cs.byu.edu/~cs240ta/crawler_tests/crawlindex.html
</url>
<count>5</count>
</occurrence>
</word>
</index>

*/
	
	
	
if (success){
	cout << "PASSED"<<endl;
	}
	return success;
	
}
