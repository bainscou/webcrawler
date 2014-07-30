/*
 *  keyword.h
 *  
 *
 *  Created by Benjamin John Ainscough on 3/6/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef CS240_KW
#define CS240_KW

#include <iostream>
#include <string>
#include "occurrence_set.h"
#include "occurrence.h"



class keyword 
{
	
public:

	
	keyword(string WordToAdd, page & url );
	
	
	~keyword();
	
	string getWord();
	
	string get_Occurrence_set_output();
	
	string get_occurrence_set_XML_output();
	
	occurrence_set getOccurrence_set();
	
	void addOccurrence(page & url);
	
	
private:
	occurrence_set * occurrences;
	string word;
	
};


#endif
