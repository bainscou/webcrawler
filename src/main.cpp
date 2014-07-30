
/*
* This is the main driver of the webcrawler program. It checks for command line 
* line ussage and then creates a webcrawler object and execute the webcrawler's
* crawl method. It then executes the writeOutput method.
*/

#include "main.h"

int  main (int argc, char * argv[]){

	//cout << "hello make"<<endl;
	
	// validates command line arguments
	if(argc != 4){
		cout<< "USAGE: webcrawler <starting URL> <XML Output File> <Stopwords File>"
		<< endl;
		return 0;
	}
	// instantiates a webcrawler object which contains the methods to crawl web pages
	webcrawler * myCrawler= new webcrawler( argv[3]);
	myCrawler->crawl(argv[1]);
	
	myCrawler->writeXMLOutput(argv[1], argv[2]);
	
	delete myCrawler;
	
	return 0;
}
