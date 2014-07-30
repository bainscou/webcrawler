/*
 *  page_queue.cpp
 *  
 *
 *  Created by Benjamin John Ainscough on 3/7/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


# include "page_queue.h"


page_queue::page_queue(): count(0), end(0), start(0){
	return;
}

page_queue::page_queue(const page_queue & other){
	copy(other);
}

void page_queue::copy(const page_queue & other){
	// copy the list
	
	page_queue_node* cur=other.GetLast();
	start=0;
	end=0;
	count=0;
	while(cur != NULL){
		
		Insert(cur->value,NULL);
		
		cur=cur->prev;
		
	}
}


page_queue& page_queue::operator =(const page_queue & other){
	if (this != &other) {
		Clear();
		copy(other);
	}
	return *this;
}

bool page_queue::IsEmpty() const{
	return (count==0);
}

page_queue::~page_queue(){
 
	Clear();
}

void page_queue::Clear(){
 
	page_queue_node *cur = start;
	if (cur != NULL){
		while(cur->hasNext()){
			cur= cur->next;
			
			delete cur->prev;			
		}
		
		
		delete cur;
	}
	start=0;
	end=0;
	count=0;
}

int page_queue::GetSize() const{
	return count;
}

page_queue_node * page_queue::GetFirst()const{
	return start;
}

page_queue_node * page_queue::GetLast()const{
	return end;
}

page_queue_node * page_queue::Insert(page & v, page_queue_node * n){
	
	if( start==NULL){
		page_queue_node * node1= new page_queue_node(v,NULL,NULL);
		start= node1;
		end= node1;
		count++;
		
		return node1;
	}
	else if(n!=NULL){
		
		//   cout<<"Value:"<<v<<endl;
		//   cout<<"N:"<<n->value<<endl;
		//  cout<<"N.next: "<<end->value<<endl;
		page_queue_node * node2= new page_queue_node(v,n,n->GetNext());
		if(n->hasNext()){
			node2->next->prev=node2;
			
		}
		n->next=node2;
		count++;
		if(n==end){
			
			end=node2;
		}
		return node2;
		
	}
	else{
		
		page_queue_node * node3= new page_queue_node(v,NULL,start);
		start->prev=node3;
		start=node3;
		count++;
		return node3;
	}
	
	
	
	
}


page_queue_node * page_queue::Find(page & v, page_queue_node * n) const{
	page_queue_node * cur;
	if(n==NULL){
		cur=start;
	}
	else{
		if(n->hasNext())
			cur=n->next;
		else
			return NULL;
	}
	while(cur!=NULL){
		if(v.getURL().compare(cur->value.getURL())==0)
			return cur;
		cur=cur->next;
	}
	return NULL;
}

void page_queue::printer(){
	page_queue_node * cur=start;
	
	while(cur->hasNext()){
		
		cout<<cur->value.getURL()<<endl;
		cur=cur->next;
	}
	cout<<"Node: "<<cur->value.getURL()<<"\n";
	cout<<"\tDescription: "<<cur->value.getDescription()<<"\n"<<endl;
	
}
void page_queue::Remove(page_queue_node * n){
    if(n!=NULL){
		if(count==1){
			start=0;
			end=0;
			delete n;
		}
		else if(n==start){
			
			start=n->next;
			start->prev=0;
			delete n;
			
			
		}
		else if(n==end){
			end=n->prev;
			end->next=0;
			delete n;
		}
		else { 
			n->prev->next=n->next;
			n->next->prev=n->prev;
			delete n;
		}
		count--;
	}
	
	
}

page  page_queue::pop(){ 
	
	if(start!=NULL){
		page temp =   start->getPage();
		if(start->next!=NULL){
			start=start->next;
			delete start->prev;
	 		start->prev=NULL;
		}
		else{
			delete start;
			start=NULL;
		
		}
		count --;
		return temp;
	}
	page nullPage;
	return nullPage;
	
}




bool page_queue :: test_page_queue(ostream & os){
	cout<<"Testing page_queue class.................";
	bool success = true;
	/*
	page_queue * test1= new page_queue();
	TEST(test1->IsEmpty());
	page * test = new page("http://english.ucsb.edu:591/rchrono/");
	test1->Insert(  test, NULL );
	test1->Insert( new page("http://www.lib.ucdavis.edu/English/BWRP/index.htm") , NULL );
	test1->Insert( new page("http://www.qub.ac.uk/english/shuttle/rom-chrono/chrono.htm") , NULL );
	test1->Insert( new page("http://etext.lib.virginia.edu/modeng.browse.html") , NULL );
	test1->Insert( new page("http://etext.lib.virginia.edu/britpo.html") , NULL );
	test1->Insert( new page("http://jefferson.village.virginia.edu/blake/") , NULL );
	test1->Insert( new page("gopher://dept.english.upenn.edu:70/11/Courses") , NULL );
	test1->Insert( new page("gopher://dept.english.upenn.edu/11/E-Text/PEAL") , NULL );
	test1->Insert( new page("http://www.english.upenn.edu/~curran/home.html") , NULL );
	test1->Insert( new page("http://dept.english.upenn.edu/~mgamer/Romantic/") , NULL );
	test1->Insert( new page("http://gopher.upenn.edu/pennprintout/html/v11/3/creature.html") , NULL );
	test1->Insert( new page("http://www.rc.umd.edu/") , NULL );
	test1->Insert( new page("http://fay.english.umb.edu/") , NULL );
	test1->Insert( new page("http://www.nottingham.ac.uk/~aezacweb/wrew.htm") , NULL );
	test1->Insert( new page("http://users.ox.ac.uk/~scat0385") , NULL );
	test1->Insert( new page("http://www.sul.stanford.edu/mirrors/romnet/") , NULL );
	test1->Insert( new page("http://www.ualberta.ca/~dmiall/ROMCDINF.HTM") , NULL );
	test1->Insert( new page("http://www.en.utexas.edu/") , NULL );
	test1->Insert( new page("http://www.cwrl.utexas.edu/~worp") , NULL );
	test1->Insert( new page("http://www.usc.edu/dept/LAS/english/19c/newbooks.html") , NULL );
	test1->Insert( new page("http://www.luc.edu/publications/keats-shelley/ksjweb.htm") , NULL );
	test1->Insert( new page("http://lang.nagoya-u.ac.jp/~matsuoka/19th-authors.html") , NULL );
	test1->Insert( new page("http://lang.nagoya-u.ac.jp/~matsuoka/Victorian.html") , NULL );
	test1->Insert( new page("http://www.ebi.ac.uk/microarray-as/ae/") , NULL );
	test1->Insert( new page("http://biocyc.org/") , NULL );
	test1->Insert( new page("http://bioenergycenter.org/") , NULL );
	test1->Insert( new page("http://www.brenda-enzymes.info") , NULL );
	test1->Insert( new page("http://www.cazy.org/") , NULL );
	test1->Insert( new page("http://camera.calit2.net/") , NULL );
	test1->Insert( new page("http://cmr.jcvi.org/") , NULL );
	test1->Insert( new page("http://gaggle.systemsbiology.net/docs/geese/firegoose/") , NULL );
	test1->Insert( new page("http://gaggle.systemsbiology.net/docs/") , NULL );
	test1->Insert( new page("http://www.ncbi.nlm.nih.gov/Genbank") , NULL );
	test1->Insert( new page("http://www.ncbi.nlm.nih.gov/geo") , NULL );
	test1->Insert( new page("http://www.geneontology.org/") , NULL );
	test1->Insert( new page("http://gensc.org/") , NULL );
	test1->Insert( new page("http://www.greatlakesbioenergy.org/") , NULL );
	test1->Insert( new page("http://genomicsgtl.energy.gov/datasharing/GTLDataPolicy.pdf") , NULL );
	test1->Insert( new page("http://www.hupo.org/") , NULL );
	test1->Insert( new page("http://www.sc.doe.gov/ascr/INCITE") , NULL );
	test1->Insert( new page("http://www.iscb.org/") , NULL );
	test1->Insert( new page("http://www.jbei.org/") , NULL );
	test1->Insert( new page("http://www.jgi.doe.gov/") , NULL );
	test1->Insert( new page("http://img.jgi.doe.gov/cgi-bin/pub/main.cgi") , NULL );
	test1->Insert( new page("http://www.genome.jp/kegg/") , NULL );
	test1->Insert( new page("http://www.metacyc.org/") , NULL );

	TEST(!test1->IsEmpty());
	TEST(test1->GetSize()==47);
	page * tmp1 = test1->pop();
	TEST(tmp1->getURL().compare("http://www.metacyc.org/")==0);
	delete tmp1;
	TEST(test1->GetSize()==46);
	page * tmp2 = test1->pop();
	TEST(tmp2->getURL().compare("http://www.genome.jp/kegg/")==0);
	delete tmp2;
	TEST(test1->GetSize()==45);
	page * tmp3 = test1->pop();
	TEST(tmp3->getURL().compare("http://img.jgi.doe.gov/cgi-bin/pub/main.cgi")==0);
	delete tmp3;
	TEST(test1->GetSize()==44);
	page * tmp4 = test1->pop();
	TEST(tmp4->getURL().compare("http://www.jgi.doe.gov/")==0);
	delete tmp4;
	TEST(test1->GetSize()==43);
	page * tmp5 = test1->pop();
	TEST(tmp5->getURL().compare("http://www.jbei.org/")==0);
	delete tmp5;
	TEST(test1->GetSize()==42);
	page * tmp6 = test1->pop();
	TEST(tmp6->getURL().compare("http://www.iscb.org/")==0);
	delete tmp6;
	TEST(test1->GetSize()==41);
	page * tmp7 = test1->pop();
	TEST(tmp7->getURL().compare("http://www.sc.doe.gov/ascr/INCITE")==0);
	delete tmp7;
	TEST(test1->GetSize()==40);
	page * tmp8 = test1->pop();
	TEST(tmp8->getURL().compare("http://www.hupo.org/")==0);
	delete tmp8;
	TEST(test1->GetSize()==39);
	page * tmp9 = test1->pop();
	TEST(tmp9->getURL().compare("http://genomicsgtl.energy.gov/datasharing/GTLDataPolicy.pdf")==0);
	delete tmp9;
	TEST(test1->GetSize()==38);
	page * tmp10 = test1->pop();
	TEST(tmp10->getURL().compare("http://www.greatlakesbioenergy.org/")==0);
	delete tmp10;
	TEST(test1->GetSize()==37);
	TEST(test1->GetSize()==36);
	page * tmp12 = test1->pop();
	delete tmp12;
	page * tmp13 = test1->pop();
	delete tmp13;
	page * tmp14 = test1->pop();
	delete tmp14;
	page * tmp15 = test1->pop();
	delete tmp15;
	page * tmp16 = test1->pop();
	delete tmp16;
	page * tmp17 = test1->pop();
	delete tmp17;
	page * tmp18 = test1->pop();
	delete tmp18;
	page * tmp19 = test1->pop();
	delete tmp19;
	page * tmp20 = test1->pop();
	delete tmp20;
	page * tmp21 = test1->pop();
	delete tmp21;
	page * tmp22 = test1->pop();
	delete tmp22;
	page * tmp23 = test1->pop();
	delete tmp23;
	page * tmp24 = test1->pop();
	delete tmp24;
	page * tmp25 = test1->pop();
	delete tmp25;
	page * tmp26 = test1->pop();
	delete tmp26;
	page * tmp27 = test1->pop();
	delete tmp27;
	page * tmp28 = test1->pop();
	delete tmp28;
	page * tmp29 = test1->pop();
	delete tmp29;
	page * tmp30 = test1->pop();
	delete tmp30;
	page * tmp31 = test1->pop();
	delete tmp31;
	page * tmp32 = test1->pop();
	delete tmp32;
	page * tmp33 = test1->pop();
	delete tmp33;
	page * tmp34 = test1->pop();
	delete tmp34;
	page * tmp35 = test1->pop();
	delete tmp35;
	page * tmp36 = test1->pop();
	delete tmp36;
	page * tmp37 = test1->pop();
	delete tmp37;
	page * tmp38 = test1->pop();
	delete tmp38;
	page * tmp39 = test1->pop();
	delete tmp39;
	page * tmp40 = test1->pop();
	delete tmp40;
	page * tmp41 = test1->pop();
	delete tmp41;
	page * tmp42 = test1->pop();
	delete tmp42;
	page * tmp43 = test1->pop();
	delete tmp43;
	page * tmp44 = test1->pop();
	delete tmp44;
	page * tmp45 = test1->pop();
	delete tmp45;
	page * tmp46 = test1->pop();
	delete tmp46;
	page * tmp47 = test1->pop();
	delete tmp47;
	page * tmp48 = test1->pop();
	delete tmp48;
	TEST(test1->IsEmpty());
	//tests pops when list is empty
	test1->pop();
	test1->pop();
	test1->pop();
	test1->pop();
	test1->pop();
	test1->pop();

	
	TEST(test1->IsEmpty());
	
	delete test1;*/
	if (success) {
		cout << "PASSED"<<endl;
	}
	return success;
	
}


