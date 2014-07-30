/*
 ß 	Main Driver	
 ß 		Creates Page Queue
 ß		Creates Page History
 ß		Puts start page in page Queue
 ß		While(!PageQueue.IsEmpty)
 ß	This with main.h Drives the overall crawling process 
 */
 
#include <iostream>
#include <string>
#include <fstream>
#include "page_queue.h"
#include "page_history.h"
#include "keyword_index.h"
#include "page.h"
#include "html_parser.h"


using namespace std;

class webcrawler
{
 
 public: 
 	// Default construtor 
 	webcrawler();
 
 	// Creates a webcrawler object with all necessary variables
 	// 
 	//	Paramaters: 
 	//  	
 	//		XMLOutputFileName- Name of the XML output file to be writen to given by 
 	//			user
 	//		stopwordsFileName- Name of the user's chosen stopwords file to be used 
 	//			in the crawl method.
 	webcrawler( string stopwordsFileName);
 	
 	// Destructor
 	~webcrawler();
 	
 	//Downloads the web pages within the scope and creates associated data structures
 	// of keywords to be searched.
 	//	startPage- The starting Page given by the user
 	void crawl(string startPage);
 	
 	// Writes the data structures into a XML output file 
 	void writeXMLOutput(string startPage, string XMLFile);
 
 	page_history * getPageHistory();
 	
 	keyword_index * getKeywordIndex();
 	
 	 	
 private:

	string stopwordsFile;
	page_queue * PagesToCrawl;
 	page_history * PageHistory;
 	keyword_index * KeyWordIndex;
 	html_parser * html;
 
 };	
