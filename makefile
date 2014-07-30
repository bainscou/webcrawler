
OBJS_MAIN=  obj/main.o obj/webcrawler.o obj/html_parser.o obj/occurrence.o obj/occurrence_set.o obj/keyword_index.o obj/keyword.o obj/page.o obj/page_history.o obj/page_queue.o obj/stop_word.o
OBJS_TEST = obj/test.o obj/html_parser.o obj/occurrence.o obj/occurrence_set.o obj/keyword_index.o obj/keyword.o obj/page.o obj/page_history.o obj/page_queue.o obj/stop_word.o

bin:bin/crawler 
#	./bin/main http://students.cs.byu.edu/~cs240ta/crawler_tests/crawlindex.html xmlOut.xml stopword.txt



bin/crawler: $(OBJS_MAIN) lib/libcs240utils.a
	g++ -o bin/crawler $(OBJS_MAIN) lib/libcs240utils.a -lboost_regex
 
obj/main.o : src/main.cpp inc/main.h lib/libcs240utils.a
	g++ -o obj/main.o -c -I inc -I utils/include/  src/main.cpp 

test: bin/test 
	./bin/test
	
testMem: bin/test
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes --suppressions=string.supp bin/test

bin/test: $(OBJS_TEST) lib/libcs240utils.a
	g++ -g -o bin/test $(OBJS_TEST) lib/libcs240utils.a -lboost_regex

obj/test.o:  src/test.cpp inc/test.h  inc/occurrence.h inc/occurrence_set.h inc/keyword_index.h inc/page.h inc/page_history.h inc/page_queue.h inc/stop_word.h src/test.cpp
	g++ -g -o obj/test.o  -c -I inc -I utils/include/  src/test.cpp 

obj/webcrawler.o: src/webcrawler.cpp inc/webcrawler.h inc/unit_test.h 
	g++ -g -c -o obj/webcrawler.o src/webcrawler.cpp -I inc -I utils/include/ 
	
	
obj/occurrence.o: src/occurrence.cpp inc/occurrence.h inc/unit_test.h src/occurrence.cpp
	g++ -g -c -o obj/occurrence.o src/occurrence.cpp -I inc -I utils/include/ 
	
obj/occurrence_set.o : inc/occurrence_set.h inc/occurrence.h inc/unit_test.h src/occurrence_set.cpp
	g++ -g -c -o obj/occurrence_set.o src/occurrence_set.cpp -I inc -I utils/include/ 

obj/keyword_index.o : inc/keyword_index.h src/keyword_index.cpp inc/occurrence_set.h inc/occurrence.h inc/unit_test.h inc/
	g++ -g -c -o obj/keyword_index.o src/keyword_index.cpp -I inc -I utils/include/ 

obj/keyword.o : inc/keyword.h src/keyword.cpp inc/occurrence_set.h inc/occurrence.h inc/unit_test.h 
	g++ -g -c -o obj/keyword.o src/keyword.cpp -I inc -I utils/include/ 
	
obj/page_history.o : inc/page_history.h inc/page.h inc/unit_test.h src/page_history.cpp
	g++ -g -c -o obj/page_history.o src/page_history.cpp -I inc -I utils/include/ 

obj/page.o: src/page.cpp inc/page.h inc/unit_test.h 
	g++ -g -c -o obj/page.o src/page.cpp -I inc -I utils/include/ 
	
obj/page_queue.o : src/page_queue.cpp inc/page_queue.h 
	g++ -g -c -o obj/page_queue.o src/page_queue.cpp -I inc -I utils/include/ 
	
obj/stop_word.o : src/stop_word.cpp inc/stop_word.h inc/unit_test.h
	g++ -g -c -o obj/stop_word.o src/stop_word.cpp -I inc -I utils/include/ 

obj/html_parser.o: obj/page.o obj/stop_word.o obj/page_queue.o obj/keyword_index.o inc/html_parser.h src/html_parser.cpp lib/libcs240utils.a
	g++ -g -c -o obj/html_parser.o  src/html_parser.cpp -I inc -I utils/include/ 
	
lib: lib/libcs240utils.a


lib/libcs240utils.a : utils/obj/CommandRunner.o  utils/obj/FileInputStream.o  utils/obj/FileSystem.o utils/obj/HTMLToken.o utils/obj/HTMLTokenizer.o utils/obj/HTTPInputStream.o utils/obj/StringUtil.o  utils/obj/URLInputStream.o
	ar r lib/libcs240utils.a utils/obj/CommandRunner.o  utils/obj/FileInputStream.o  utils/obj/FileSystem.o utils/obj/HTMLToken.o utils/obj/HTMLTokenizer.o utils/obj/HTTPInputStream.o utils/obj/StringUtil.o  utils/obj/URLInputStream.o



utils/obj/CommandRunner.o: utils/src/CommandRunner.cpp utils/include/CommandRunner.h  utils/include/StringUtil.h utils/include/CS240Exception.h
	g++ -o utils/obj/CommandRunner.o -c -I utils/include utils/src/CommandRunner.cpp

utils/obj/FileInputStream.o: utils/src/FileInputStream.cpp utils/include/FileInputStream.h utils/include/CS240Exception.h
	g++ -o utils/obj/FileInputStream.o -c -I utils/include utils/src/FileInputStream.cpp

utils/obj/FileSystem.o: utils/src/FileSystem.cpp utils/include/FileSystem.h  utils/include/UnitTest.h utils/include/CS240Exception.h
	g++ -o utils/obj/FileSystem.o -c -I utils/include utils/src/FileSystem.cpp

utils/obj/HTMLToken.o: utils/src/HTMLToken.cpp utils/include/HTMLToken.h   
	g++ -o utils/obj/HTMLToken.o -c -I utils/include utils/src/HTMLToken.cpp

utils/obj/HTMLTokenizer.o: utils/src/HTMLTokenizer.cpp utils/include/HTMLTokenizer.h   
	g++ -o utils/obj/HTMLTokenizer.o -c -I utils/include utils/src/HTMLTokenizer.cpp

utils/obj/HTTPInputStream.o: utils/src/HTTPInputStream.cpp utils/include/HTTPInputStream.h  utils/include/StringUtil.h utils/include/CS240Exception.h
	g++ -o utils/obj/HTTPInputStream.o -c -I utils/include utils/src/HTTPInputStream.cpp

utils/obj/StringUtil.o: utils/src/StringUtil.cpp utils/include/StringUtil.h   
	g++ -o utils/obj/StringUtil.o -c -I utils/include utils/src/StringUtil.cpp

utils/obj/URLInputStream.o: utils/src/URLInputStream.cpp utils/include/URLInputStream.h  utils/include/StringUtil.h utils/include/CS240Exception.h utils/include/HTTPInputStream.h utils/include/FileInputStream.h utils/include/InputStream.h
	g++ -o utils/obj/URLInputStream.o -c -I utils/include utils/src/URLInputStream.cpp


clean :
	@- rm -f bin/crawler
	@- rm -f bin/test
	@- rm -f obj/*.o
	@- rm -f lib/*.a
	@- rm -f utils/obj/*.o
	

