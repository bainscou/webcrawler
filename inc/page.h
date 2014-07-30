/*
 ß 	Contains
 ß  	URL
 ß 		Words
 ß		Links
 ß		Description
 ß	This class stores the URL and a description for a page
 ß 	The page
 */
 
 
 
 #ifndef CS240_P
#define CS240_P

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "unit_test.h"
using namespace std; 

class page
{

public:
	
	page();
	
	page(string  urlToAdd );
	
	page(string absoluteURL, string relativeURL);
	
	page(const page & other);
	
	~page();
	
	//TODO copy constructor
	
	string  getURL();
	
	string getDescription();
	
	void setDescription(string s);
	
	static bool testPage(ostream & os);
	
private:
	string URL;
	string description;
	
	string resolveURL(string absoluteURL, string relativeURL);
	string urlParser(char * relURL, char * absURL);
};



#endif
