/*
 ß 	Main Driver	
 ß 		Creates Page Queue
 ß		Creates Page History
 ß		Puts start page in page Queue
 ß		
 */
 #include "webcrawler.h"
 
 	
// Creates a webcrawler object with all necessary variables
// 
//	Paramaters: 
//  	startPage- The starting Page given by the user
//		stopwordsFileName- Name of the user's chosen stopwords file to be used 
//			in the crawl method.
webcrawler::webcrawler( string stopwordsFileName)
	: stopwordsFile(stopwordsFileName){
	PagesToCrawl = new page_queue();
	PageHistory= new page_history();
	KeyWordIndex = new keyword_index();
	
}

// Destructor
webcrawler::~webcrawler(){
	delete PagesToCrawl;
	delete PageHistory;
	delete KeyWordIndex;
	delete html;
}

//This function instantiates an html_parser which downloads pages, parses the html
//and then populates the keyword_index.

void webcrawler::crawl(string startPage){
	page firstPage(startPage);
	PagesToCrawl->Insert(firstPage, NULL);
	string scope = firstPage.getURL();
	int index = scope.find_last_of("/");
	scope = scope.substr(0, index+1);
	//cout<<scope<<endl;
	html = new html_parser(stopwordsFile, scope );
	while(!PagesToCrawl->IsEmpty()){
		page curPage= PagesToCrawl->pop();
		if(!PageHistory->contains(curPage)){
			html->parse(curPage, PagesToCrawl, KeyWordIndex);
			PageHistory->Insert(curPage);
		}
		
	}
	

	
	
	//cout<<"finished"<<endl;
}

// Writes the data structures into a XML output file 
void webcrawler::writeXMLOutput(string startPage, string XMLFile){
	ofstream myfile;
  	myfile.open (XMLFile.c_str());
	
	string XML;
	XML+="<website>\n";
	XML+="<start-url>\n"+startPage+"\n</start-url>\n";
	XML+=PageHistory->toXML();
	XML+=KeyWordIndex->toXML();
	XML+="</website>\n";
	
	
	
  	myfile << XML;
  	myfile.close();
}

page_history * webcrawler::getPageHistory(){
	return PageHistory;
}
 	
 keyword_index * webcrawler::getKeywordIndex(){
 	return KeyWordIndex;
 }
 


