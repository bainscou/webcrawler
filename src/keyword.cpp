/*
 *  keyword.cpp
 *  
 *
 *  Created by Benjamin John Ainscough on 3/6/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "keyword.h"



keyword :: keyword(string WordToAdd, page & url ){
	word=WordToAdd;
	occurrences=new occurrence_set();

	
	occurrences->Insert( new occurrence(url, 1));
	
}



keyword :: ~keyword(){
	delete occurrences;
}

string keyword :: getWord(){
	return word;
}

string keyword :: get_occurrence_set_XML_output(){
	return occurrences->toXML();
}


string keyword :: get_Occurrence_set_output(){
  return occurrences->traverse();
}

occurrence_set keyword :: getOccurrence_set(){
	return *occurrences;
}

void keyword :: addOccurrence(page & url){
	/////POSSIBLE MEMORY ERROR!!!!!!
	page p(url);
	occurrence_set_node * node =  occurrences->Find(url.getURL());
	occurrence_set_node * node1 =NULL;
	//cout<<"url: "<<url.getURL()<<endl;
	//cout<<node<<endl;
	if(occurrences->Find(url.getURL())!=NULL){
		//cout<<"dont go here"<<endl;
		node->IncrementCount();
		//cout<<"no seg"<<endl;
		
	}else{
		occurrences->Insert(new occurrence( p, 1));
	}
  

//delete temp;
}
