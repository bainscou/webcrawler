/*
 *  page.cpp
 *  
 *
 *  Created by Benjamin John Ainscough on 3/7/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "page.h"


page::page(){}

page ::page(string urlToAdd ) : URL(urlToAdd) {
	return;
}

page::page(const page & other){
	URL = other.URL;
	description= other.description;
	//cout<<" page copy constructor works"<<endl;
}

page::page(string absoluteURL, string relativeURL){
	URL=resolveURL(absoluteURL, relativeURL);
}


page :: ~page(){
	
}


string page:: getURL(){
	return URL;
}


string page::getDescription(){
	return description;
}

void page:: setDescription(string s){
	description = s;
}


string page::resolveURL(string absoluteURL, string relativeURL){
	char * relURL = &relativeURL[0];
	char * absURL = &absoluteURL[0];

			

	
	return urlParser(relURL, absURL);
}

string page::urlParser(char * relURL, char * absURL){
		string absoluteURL= "";
		
		if(relURL[0]=='#')
		{
			absoluteURL= absURL;
			
			
		}
		else
		{
			char * pound = strrchr(relURL, '#');
			if(pound!=NULL ){
				*pound = '\0';			
			}
			int BufferLength= strlen(absURL)+strlen(relURL)+1;
			int relLength=strlen(relURL)+1;
			char relArray[relLength];
			strcpy(relArray, relURL);
			//cout<<"Relative URL: "<<relArray<<endl;
			
			//This is a string array to put the final output in. 
			//It starts with the absolute url and modifies it then 
			//the resolved url will be added in.
			
			char BufferArray[BufferLength]; 											
			// This copies the absolute URL to the Buffer.
	
			strcpy(BufferArray,absURL);												
			// searches for the first slash, what if there are no slashes in the argument
			char* slash1= strchr(BufferArray, '/');	
			char* slash2= strchr(slash1+1, '/');
			char* slash3= strchr(slash2+1, '/');
			if(slash3==NULL){
				slash3=strrchr(BufferArray, 0);
				*slash3='/';
				*(slash3+1)=0;
			}
			char* cur=&relArray[0];
			char* rcur=strrchr(BufferArray,'/');
			*rcur=0;
			//if( isalnum(*cur)!=0){
				//cout << "relative: " << cur << endl;
				
				//*slash3=0;
			//}
			while(*cur=='.'||*cur=='/'){
				
				if(*cur=='.'){
					if(*(cur+1)=='.'&& rcur>slash3){
						rcur=strrchr(BufferArray,'/');
						*rcur=0;
						cur+=3;
					}
					else if(*(cur+1)=='/'){
						cur+=2;
					}
					else{
						cur+=3;
					}
				}
				else if(*cur=='/'){
					cur++;
					*slash3=0;
					
				}
				
				
			}
			
			strcat(BufferArray,"/");
			strcat(BufferArray,cur);
			absoluteURL= BufferArray;
			
		}
	
	return absoluteURL;	
}

bool page :: testPage(ostream & os){
		cout<<"Testing Page class.................";
		bool success = true;
		
		
		page * test1 = new page("http://www.byu.edu/BenRocksMySocks");
		TEST(test1->getURL().compare("http://www.byu.edu/BenRocksMySocks")==0);
		
		
		page * test2 = new page("http://www.test.com/adga/sdgadg/sdgasdg/sdgadgs/dgsasdg/asgdasdg/", 
							".//fdsf");
		TEST(test2->getURL().compare("http://www.test.com/fdsf")==0); 
		
		page * test3 = new page("http://www.test.com/adga/sdgadg/sdgasdg/sdgadgs/dgsasdg/asgdasdg/", 
							  ".././../fdsf");
		TEST(test3->getURL().compare("http://www.test.com/adga/sdgadg/sdgasdg/sdgadgs/fdsf")==0);
		
		page * test4 = new page("http://www.test.com/adga/sdgadg/sdgasdg/sdgadgs/dgsasdg/asgdasdg/", 
							  ".././../../../../../../../../../../../../../fdsf");
		TEST(test4->getURL().compare("http://www.test.com/fdsf")==0);
		
		page * test5 = new page("http://www.test.com/adga/sdgadg/sdgasdg/sdgadgs/dgsasdg/", 
							  "fdsf");
		string test5str="http://www.test.com/adga/sdgadg/sdgasdg/sdgadgs/dgsasdg/fdsf";
		TEST(test5->getURL().compare(test5str)==0);
		page * test6 = new page("http://www.test.com/adga/sdgadg/sdgasdg/sdgadgs/dgsasdg/asgdasdg/", 
							  ".//fdsf");
		TEST(test6->getURL().compare("http://www.test.com/fdsf")==0);
		
		page * test7 = new page("http://www.test.com/sdgasdg/sdgadgs/dgsasdg/asgdasdg/", 
							  "#fdsf");
		TEST(test7->getURL().compare("http://www.test.com/sdgasdg/sdgadgs/dgsasdg/asgdasdg/")==0);
		
		page * test8 = new page("http://www.test.com/sdgasdg/sdgadgs/dgsasdg/asgdasdg/", 
							  "fdsa#fdsf");
		TEST(test8->getURL().compare("http://www.test.com/sdgasdg/sdgadgs/dgsasdg/asgdasdg/fdsa")==0);
					     
		page * test9 = new page("http://www.test.com/sdgasdg/sdgadgs/dgsasdg/asgdasdg/", 
							  "fdsa?fdsf");
		//cout<<test8->getURL()<<endl;
		//cout<<test9->getURL()<<endl;
		TEST(test9->getURL().compare("http://www.test.com/sdgasdg/sdgadgs/dgsasdg/asgdasdg/fdsa?fdsf")==0);
					     
		page newTest("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/scale.php?sec=","scale.php?sec=tortoise");
		//cout<<newTest.getURL()<<endl;
		
		page newTest1("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawler/testFive.html","scale.php?sec=");
		//cout<<newTest1.getURL()<<endl;
		
		delete test1;
		delete test2;
		delete test3;
		delete test4;
		delete test5;
		delete test6;
		delete test7;
		
		if (success) {
			cout << "PASSED"<<endl;
		}
		return success;
	}
