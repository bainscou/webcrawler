/*
 ß 	IsStopWord(word);	
 ß 	Load stopwords
 */
 
 #ifndef CS240_S_W
#define CS240_S_W

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <typeinfo>
#include "unit_test.h"

using namespace std; 

class stop_word
{
public:
	
	stop_word(string textFile);
	
	~stop_word();
	
	bool contains(string query);
	
	static bool test_stop_word(ostream & os);
	
private:
	
	void fileReader(string textFile);
	
	int  fileLineCounter(string textFile);
	
	string * stop_word_list;
	
	//int cmp(const void * a, const void * b);
	
	int lineCount;
	
};



#endif
