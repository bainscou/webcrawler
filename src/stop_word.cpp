/*
 *  stop_word.cpp
 *  
 *
 *  Created by Benjamin John Ainscough on 3/8/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "stop_word.h"

stop_word :: stop_word(string textFile){
	lineCount= fileLineCounter(textFile);	
	stop_word_list = new string[lineCount] ;
	fileReader(textFile);
}

stop_word :: ~stop_word(){
  // free heap data
  delete [] stop_word_list;
}

int cmp(const void * a, const void * b){
	return ((*(string*)a).compare(*(string *)b));
}

bool  stop_word :: contains(string query){
	string * result = (string *) bsearch(&query, stop_word_list, lineCount, sizeof(string*), cmp);
	if(result!=NULL)
		return true;
	else
		return false;
}


void stop_word :: fileReader(string textFile){
	// open file
	//
	ifstream file;
	file.open(textFile.c_str());

	if (!file.is_open()){
	  //TODO throw exception
	}

	// read lines from file
	//

	char curLine[1024];
	for ( int i =0; i < lineCount; ++i){
		file.getline(curLine, sizeof(curLine));
		string  temp =  string(curLine);
		//cout<< *temp<<endl;
		stop_word_list[i] = temp;
	}
	
	// close file
	//
	file.close();

	// print lines
	//
	/*cout<<"linecount: "<<lineCount<<endl;
	for (int i = 0; i < lineCount; ++i){
		cout<< "int i: "<<i<<endl;
		cout << *stop_word_list[i] << endl;
	}*/
  
}

int stop_word :: fileLineCounter(string textFile){
	// open file
	//
	ifstream file;
	file.open(textFile.c_str());

	if (!file.is_open()){
	//////////////////////Do some exception handling here
	}

	 // count lines from file
	 //

	lineCount = 0;
	char curLine[1024];
	while (file.getline(curLine, sizeof(curLine))){
		++lineCount;
	}

	// close file
	//
	file.close();

	return lineCount;
}

bool stop_word :: test_stop_word(ostream & os){
	cout<<"Testing stop_word class.................";
	bool success = true;
	
		stop_word * test1 = new stop_word("stopword.txt");
		TEST(!test1->contains("alright"));
		TEST(test1->contains("a"));
		TEST(test1->contains("z"));
		TEST(!test1->contains("zoo"));
		delete test1;
	if (success) {
		cout << "PASSED"<<endl;
	}
	return success;

}
