/*
 ß 	string download(URL);
 ß 	
 */
 
 
 #ifndef CS240_P_D
#define CS240_P_D

#include <iostream>
#include <string>

using namespace std; 


// downloads the page for the html parser to use
class page_downloader
{
public:
	page_downloader();
	
	~page_downloader();
	
	//download method returns a stream and handles all the exceptions that may occur
	// Parameters : string url - url of page to download
	//		
	// returns : string of the htmlCode
	const string & download(string url);


private:


};



#endif
