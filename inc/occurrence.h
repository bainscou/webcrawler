/*
 ß 	Contains
 ß 		Page
 ß		Count
 */
 
 #ifndef CS240_Occ
#define CS240_Occ

#include <iostream>
#include <string>
#include "page.h"
#include "unit_test.h"


class occurrence
{
public:
	// is an object that stores the words and the number of times it appears on the 
	// page
	occurrence( page & PAGE, int count);
	
	occurrence(const occurrence & other);
	
	occurrence();
	
	~occurrence();

	void incrementCount();
	
	string getURL();
	
	int getCount();
	
	static bool testOccurrence(ostream & os);
	
private:
	page  Page;
	int Count;

};



#endif
