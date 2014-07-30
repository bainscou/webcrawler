#include "html_parser.h"

html_parser::html_parser(string stopwordFile, string startingURL): scope(startingURL){
	stopwords = new stop_word(stopwordFile);
	
}

html_parser::~html_parser(){
	delete stopwords;
}

void html_parser::parse(page & curPage, page_queue * PagesToCrawl, keyword_index * KeyWordIndex){
	//TODO ask ta's about xml entities and how they should be parsed
	
	cout<<"Parsing: "<<curPage.getURL()<<endl;
	//create tokenizer
	try{
		URLInputStream url(curPage.getURL());
		HTMLTokenizer tokenizer(&url);
	
		//find html token validates that is a html doc
		HTMLToken curTok = tokenizer.GetNextToken();
		//cout<<curTok.GetValue()<<endl;
		//cout<<strcasecmp(curTok.GetValue().c_str(), "html")<<endl;
		while(tokenizer.HasNextToken() && strcasecmp(curTok.GetValue().c_str(), "html")==0){
			curTok = tokenizer.GetNextToken();
		}
		//initialize boolean flags for parsing
		inTitleOrBody=false;
		inScript=false;
		foundDescription=false;
		inHeader=false;
		inTitle=false;
		
		description="";
		
		charCounter=0;
		
		
		
		while(tokenizer.HasNextToken()){
			curTok=tokenizer.GetNextToken();
			string tokenValue = curTok.GetValue();
			string tokenValueLowerCase = StringUtil::ToLowerCopy(tokenValue);
			StringUtil::Trim(tokenValue);	
			StringUtil::Trim(tokenValueLowerCase);
			//cout<<"Token Value: "<< tokenValue<<endl;
			//cout<<"inTitleOrBody: "<<inTitleOrBody<<endl;
			//cout<<"inScript: "<<inScript<<endl;
			//cout<<"foundDescription: "<<foundDescription<<endl;
			//cout<<"inHeader: "<<inHeader<<endl;
			//cout<<"inTitle: "<<inTitle<<endl;
			switch( curTok.GetType()){
				case TAG_START:
					parseStartTag(tokenValueLowerCase, curTok, curPage, PagesToCrawl);
					break;
					
				case TAG_END:
					parseEndTag( tokenValueLowerCase);
					break;
					
				case TEXT:
					if (inTitleOrBody && tokenValue!=""){
						
						//cout<<"just text:: "<<tokenValue<<endl;
						parseText(tokenValueLowerCase, 
							  curPage, KeyWordIndex );
						if(!foundDescription){
							saveDescription(curPage, tokenValue);
						}
					}
					break;
					
				case END:
					break;
				case COMMENT:
					break;
				default:
					cout << "ERROR!  Contact TA's about TypeToString() in HTMLToken.cpp."<<endl;
					break;
			}
			
		}
		//cout<<description<<endl;

		StringUtil::EncodeToXml(description);

		curPage.setDescription(description);
		//cout<<KeyWordIndex->toXML()<<endl;
	}catch(CS240Exception e){
		
		cout<<e.GetMessage()<<endl;
	}
}




void html_parser::parseStartTag(string tokenValueLowerCase, HTMLToken curTok,
				 page & curPage, page_queue * PagesToCrawl){
					//set bool to true based on case
					// check if in title or body 
					if(tokenValueLowerCase== "title"||
						tokenValueLowerCase== "body"){
						inTitleOrBody=true; 
					}
					// check if in title
					if(tokenValueLowerCase== "title"){
						inTitle=true;
					}
					// check if script
					if(tokenValueLowerCase== "script"){
						inScript=true;
					}
					// check if header
					if(tokenValueLowerCase[0]== 'h' 
					   && isdigit( tokenValueLowerCase[1])){
						inHeader=true;
					}
					if(tokenValueLowerCase=="a"&&curTok.AttributeExists("href")){
						processLinks(curTok, curPage, PagesToCrawl);
						
						
					}
}

void html_parser::processLinks(HTMLToken curTok, page & curPage, page_queue * PagesToCrawl){
						//cout<<tokenValueLowerCase<<endl;
						string href =curTok.GetAttribute("href");
						//StringUtil::ToLower(href);
						page newPage;
						if(StringUtil::IsPrefix(href, "http://")){
							newPage= page(href);
						}
						else if(StringUtil::IsPrefix(href, "file://")){
							newPage= page(href);
						}else{
							newPage= page(curPage.getURL(), href);
							//cout<<newPage.getURL()<<endl;
						}
						if(isInScope(newPage.getURL())){
							PagesToCrawl->Insert(newPage, NULL);
							cout<<"adding: "<<newPage.getURL()<<endl;
						}

}

void html_parser::parseEndTag(string tokenValueLowerCase){
					//set bool to false based on case
					// check if in title or body 
					if(tokenValueLowerCase== "title"||
						tokenValueLowerCase== "body"){
						inTitleOrBody=false; 
					}
					// check if in title
					if(tokenValueLowerCase== "title"){
						inTitle=false;
					}
					// check if script
					if(tokenValueLowerCase== "script"){
						inScript=false;
					}
					// check if header
					if(tokenValueLowerCase[0]== 'h' 
					   && isdigit( tokenValueLowerCase[1])){
						inHeader=false;
					}
}

void html_parser::parseText(string curString, page & curPage, keyword_index * kwIndex){

	//regualr expression that finds words
	const int MATCH = 0;
	
	boost::regex re("[a-z|\\d|_|-]+");
	boost::sregex_token_iterator finder(curString.begin(), curString.end(), re, MATCH);
	boost::sregex_token_iterator no_match;
	
	while(finder != no_match){	
		// gets the word
		string curWord(*finder);

		if(!stopwords->contains(curWord)&& isalpha(curWord[0])){
			//cout<< "curWord FILTERED: "<<curWord<<endl;
			kwIndex->Insert(curWord, curPage);
		}
		
		
		// increments the regualr expression
		*finder++;			
	}
}


void html_parser::saveDescription(page & curPage, string desc){
	// check w/ ta for case of <title></title>
	if(inTitle || inHeader){
		description=desc;
		
		foundDescription=true;	
	}else{
		getHundredCharacters(desc);
		if(charCounter>100){
			foundDescription=true;
			
		}
	}
	
}

void html_parser::getHundredCharacters(string desc){
	
	// Add characters (+=) to description until charcounter = 100 OR string is done 
	while(desc.length()!=0 &&charCounter<100){
		description+=desc[0];
		if(!isspace(desc[0])){		
			charCounter++;
		}
		desc = desc.substr(1);

	}
}


bool html_parser::isInScope(string URL){
	//Possible error do not parse http://www.cnn.com/dsfsd/dfsdfs/sdfsdf
	cout<<"inscope URL: "<<URL<<endl;
	string extensions = ".html .htm .shtml .cgi .jsp .asp .aspx .php .pl .cfm";
	
	int indexQuestionMark = URL.find_last_of("?");
	if(indexQuestionMark!= -1){
		URL=URL.substr(0,indexQuestionMark);
	}
	int indexPeriod =URL.find_last_of(".");
	//cout<<URL[URL.length()-1]<<endl;
	string urlExtension;
	if(indexPeriod != -1)
		urlExtension =URL.substr(indexPeriod, URL.length());
	bool validExtension = false;
	bool containsScope= false;
	if(extensions.find(urlExtension,0)!=string::npos){
		validExtension=true;
	}
	
		
		
	


	URL = domainToLower(URL);
	
	

	
	if(URL.find(scope,0)!=string::npos)
		containsScope = true;
	return containsScope&&validExtension;
	
}

string html_parser::domainToLower(string URL){
	int slash1 =URL.find("/");
	string subSlash1 =URL.substr(0,slash1+1);
	string remaining =URL.substr(slash1+1, URL.length());

	int slash2 =remaining.find("/");
	string subSlash2 =remaining.substr(0,slash2+1);
	string remaining2 =remaining.substr(slash2+1, URL.length());

	int slash3 =remaining2.find("/");
	string subSlash3 =remaining2.substr(0,slash3+1);
	string remaining3 =remaining2.substr(slash3+1, URL.length());

	
	string domain = subSlash1+subSlash2+subSlash3;
	StringUtil::ToLower(domain);
	return domain+remaining3;
}


string html_parser::getDescription(){
	return description;
}

bool html_parser :: test_html_parser(ostream & os){
	cout<<"Testing html_parser class.................";
	bool success = true;
	
	keyword_index * kw_index = new keyword_index();
	
	
	page firstPage("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawlindex.html");
	string scope = firstPage.getURL();
	int index = scope.find_last_of("/");
	scope = scope.substr(0, index+1);
	html_parser * html = new html_parser("stopword.txt", scope );
	html->parse(firstPage, NULL, kw_index);
	delete html;
	delete kw_index;
	
	
	if (success) {
	cout << "PASSED"<<endl;
	}
	return success;

}

