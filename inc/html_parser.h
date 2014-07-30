/*
 ß	Finds words, links and descriptions
 */
 
 
 
#ifndef CS240_HTML_P
#define CS240_HTML_P

#include <iostream>
#include <string>
#include<boost/regex.hpp>
#include "StringUtil.h"
#include "HTMLTokenizer.h"
#include "HTMLToken.h"
#include "page.h"
#include "stop_word.h"
#include "page_queue.h"
#include "keyword_index.h"
#include "CS240Exception.h"

using namespace std; 

class html_parser
{
public:

	html_parser(string stopwordFile, string startingURL);
	
	~html_parser();
	
	
	// parses through the page and creates occurence objects adds links to the 
	// queue and finds a description. all to be ready for the page object to be
	// created
	void parse(page & curPage, page_queue * PagesToCrawl, keyword_index * KeyWordIndex);
	
	bool isInScope(string URL);
	
	static bool test_html_parser(ostream & os);

private:
	stop_word * stopwords;

	bool inTitleOrBody;
	bool inScript;
	bool foundDescription;
	bool inHeader;
	bool inTitle;
	string description;
	string scope;
	int charCounter;
	
	
	//this is used only to test the class
	string getDescription();
	
	
	void parseText(string curString, page & Page, keyword_index * kwIndex);
	void parseStartTag(string tokenValueLowerCase, HTMLToken curTok,
				 page & curPage, page_queue * PagesToCrawl);
	void parseEndTag(string tokenValueLowerCase);
	void processLinks(HTMLToken curTok, page & curPage, page_queue * PagesToCrawl);
	void saveDescription(page & curPage, string desc);
	void getHundredCharacters(string desc);
	string domainToLower(string URL);

	


};



#endif
