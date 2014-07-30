/*
 *  occurrence.cpp
 *  
 *
 *  Created by Benjamin John Ainscough on 2/22/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */




#include "occurrence.h"

occurrence:: occurrence() : Count(0), Page(NULL){

}

occurrence::occurrence(const occurrence & other){
	Count= other.Count;
	Page = other.Page;
	
}

occurrence:: occurrence(  page & PAGE, int count) : Count(count) , Page(PAGE){

}

occurrence:: ~occurrence(){

	
	//delete Page;

}

void occurrence:: incrementCount(){
	Count++;
}

string occurrence:: getURL(){
	return Page.getURL();
}

int occurrence:: getCount(){
	return Count;
}

bool occurrence :: testOccurrence(ostream & os){
	cout<<"Testing Occurrence class.................";
	bool success = true;
	page  page1("http://www.testthisstuff.com/");
	occurrence * test1= new occurrence(page1, 6);
	TEST(test1->getURL()=="http://www.testthisstuff.com/");
	TEST(test1->getCount()==6);
	
	delete test1;

	if (success) {
		cout << "PASSED"<<endl;
	}
	return success;
	
}






/*
test function template
 
 bool occurrence :: test(ostream & os)
 {
 cout<<"Testing ? class.................";
 bool success = true;
 
 TEST(condition);
 
 if (success) {
 cout << "PASSED"<<endl;
 }
 return success;
 
 }


*/
