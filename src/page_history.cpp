/*
 *  page_history.cpp
 *  
 *
 *  Created by Benjamin John Ainscough on 3/7/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include "page_history.h"





using namespace std;

void page_history::copy(const page_history & other){
	
	// recursive method to copy the tree
	root = 0;
	count= other.count;
	
	copyHelper(root, other.root);
	
	
}

void page_history::copyHelper(page_history_node*& copy, const page_history_node* originalTree){
	
	if (originalTree == NULL)
		copy = NULL;
	else{
		page tempPage = originalTree->value;
		copy = new page_history_node(tempPage);
		copyHelper(copy->left, originalTree->left);
		copyHelper(copy->right, originalTree->right);
	}
	
}

string page_history::traverse(){
	string output;
	root->traverse(output);
	return output;
}

string page_history::toXML(){
	string XML;
	XML += "<pages>\n";
	root->toXML(XML);
	XML +="</pages>\n";
	return XML;
}

page_history::page_history() : root(0) , count(0){
	return; 
}

page_history::page_history(const page_history & other){
	copy(other);
}

page_history::~page_history(){
	Clear();
}

page_history& page_history:: operator =(const page_history & other){
	if (this != &other) {
		Clear();
		copy(other);
	}
	return *this;
}

void page_history::Clear(){
	recursiveClear(root);
	root= 0;
	count= 0;
}

void page_history::recursiveClear(page_history_node * me){
	if(me==NULL)
		return;
	recursiveClear(me->right);
	recursiveClear(me->left);
	//delete me->left;
	//delete me->right;
	delete me;
	me=NULL;
	
}

page_history_node * page_history::GetRoot()const{
	return root;
}

bool page_history::IsEmpty() const{
	return (count==0);
}

int page_history::GetSize() const{
	return count;
}

page_history_node * page_history::Insert(page &  o){
	
	if(root==NULL){
		root= new page_history_node(o);
		count++;
		return root;
	}
	else{
		page_history_node * cur= root;
		return recursiveInsert(root,o);
		
	}
	
    
}

page_history_node * page_history::recursiveInsert(page_history_node * current, page & v){
	int comp=v.getURL().compare(current->value.getURL());
	//cout<< "Comparing: "<<comp <<endl;
	if(comp<0){
		//cout<< "I am on the left"<<endl;
		if(current->left==NULL){
			count++;
			return current->left= new page_history_node(v);
		}
		else
			recursiveInsert(current->left, v);
	}
	else if(comp>0){
		//cout<< "I am on the right"<<endl;
		if(current->right==NULL){
			count++;
			return current->right= new page_history_node(v);
		}
		else
			recursiveInsert(current->right, v);
	}
	else{
		
		return NULL;
	}
}


bool page_history::contains(page & query){
	page_history_node * result = Find(query);
	if(result!=NULL){
		return true;
	}else
		return false;
}

page_history_node * page_history::Find(page & v) const{
	return recursiveFind(root, v);
}

page_history_node * page_history::recursiveFind(page_history_node * current, page & v) const{
	// cout<< v<<endl;
	// cout<< current<<endl;
	if(current==NULL)
		return NULL;
	if(v.getURL().compare(current->value.getURL())<0){
		recursiveFind(current->left,v );
	}
	else if(v.getURL().compare(current->value.getURL())>0){
		recursiveFind(current->right,v);
	}
	else
		return current;
	
    
	
}

bool page_history :: testpage_history(ostream & os){

	cout<<"Testing page_history class.................";
	bool success = true;
	/*
	page_history * test1= new page_history();
	page * testURL = new page("http://www.bnn.com/");
	
	test1->Insert(testURL);
	test1->Insert(new page("http://www.cnn.com/"));
	test1->Insert(new page("http://www.ann.com/"));
	test1->Insert(new page("http://english.ucsb.edu:591/rchrono/"));
	test1->Insert(new page("http://www.lib.ucdavis.edu/English/BWRP/index.htm"));
	test1->Insert(new page("http://www.qub.ac.uk/english/shuttle/rom-chrono/chrono.htm"));
	test1->Insert(new page("http://etext.lib.virginia.edu/modeng.browse.html"));
	test1->Insert(new page("http://etext.lib.virginia.edu/britpo.html"));
	test1->Insert(new page("http://jefferson.village.virginia.edu/blake/"));
	test1->Insert(new page("gopher://dept.english.upenn.edu:70/11/Courses"));
	test1->Insert(new page("gopher://dept.english.upenn.edu/11/E-Text/PEAL"));
	test1->Insert(new page("http://www.english.upenn.edu/~curran/home.html"));
	test1->Insert(new page("http://dept.english.upenn.edu/~mgamer/Romantic/"));
	test1->Insert(new page("http://gopher.upenn.edu/pennprintout/html/v11/3/creature.html"));
	test1->Insert(new page("http://www.rc.umd.edu/"));
	test1->Insert(new page("http://fay.english.umb.edu/"));
	test1->Insert(new page("http://www.nottingham.ac.uk/~aezacweb/wrew.htm"));
	test1->Insert(new page("http://users.ox.ac.uk/~scat0385"));
	test1->Insert(new page("http://www.sul.stanford.edu/mirrors/romnet/"));
	test1->Insert(new page("http://www.ualberta.ca/~dmiall/ROMCDINF.HTM"));
	test1->Insert(new page("http://www.en.utexas.edu/"));
	test1->Insert(new page("http://www.cwrl.utexas.edu/~worp"));
	test1->Insert(new page("http://www.usc.edu/dept/LAS/english/19c/newbooks.html"));
	test1->Insert(new page("http://www.luc.edu/publications/keats-shelley/ksjweb.htm"));
	test1->Insert(new page("http://lang.nagoya-u.ac.jp/~matsuoka/19th-authors.html"));
	test1->Insert(new page("http://lang.nagoya-u.ac.jp/~matsuoka/Victorian.html"));
	test1->Insert(new page("http://www.ebi.ac.uk/microarray-as/ae/"));
	test1->Insert(new page("http://biocyc.org/"));
	test1->Insert(new page("http://bioenergycenter.org/"));
	test1->Insert(new page("http://www.brenda-enzymes.info"));
	test1->Insert(new page("http://www.cazy.org/"));
	test1->Insert(new page("http://camera.calit2.net/"));
	test1->Insert(new page("http://cmr.jcvi.org/"));
	test1->Insert(new page("http://gaggle.systemsbiology.net/docs/geese/firegoose/"));
	test1->Insert(new page("http://gaggle.systemsbiology.net/docs/"));
	test1->Insert(new page("http://www.ncbi.nlm.nih.gov/Genbank"));
	test1->Insert(new page("http://www.ncbi.nlm.nih.gov/geo"));
	test1->Insert(new page("http://www.geneontology.org/"));
	test1->Insert(new page("http://gensc.org/"));
	test1->Insert(new page("http://collections.plos.org/plosbiology/gos-2007.php"));
	test1->Insert(new page("http://www.greatlakesbioenergy.org/"));
	test1->Insert(new page("http://genomicsgtl.energy.gov/datasharing/GTLDataPolicy.pdf"));
	test1->Insert(new page("http://www.hupo.org/"));
	test1->Insert(new page("http://www.sc.doe.gov/ascr/INCITE"));
	test1->Insert(new page("http://www.iscb.org/"));
	test1->Insert(new page("http://www.jbei.org/"));
	test1->Insert(new page("http://www.jgi.doe.gov/"));
	test1->Insert(new page("http://img.jgi.doe.gov/cgi-bin/pub/main.cgi"));
	test1->Insert(new page("http://www.genome.jp/kegg/"));
	test1->Insert(new page("http://www.metacyc.org/"));
	test1->Insert(new page("http://www.microbesonline.org/"));
	test1->Insert(new page("http://nihroadmap.nih.gov/hmp"));
	test1->Insert(new page("http://www.obofoundry.org/"));
	test1->Insert(new page("http://www.opensource.org/"));
	test1->Insert(new page("http://pathema.jcvi.org/"));
	test1->Insert(new page("http://www.phytozome.net/"));
	test1->Insert(new page("http://ncrr.pnl.gov/"));
	test1->Insert(new page("http://ober-proteomics.pnl.gov/"));
	test1->Insert(new page("http://omics.pnl.gov/"));
	test1->Insert(new page("http://www.promscan.uklinux.net/"));
	test1->Insert(new page("http://ncrr.pnl.gov/about/process.stm"));
	test1->Insert(new page("http://www.rcsb.org/pdb/home/home.do"));
	test1->Insert(new page("http://regtransbase.lbl.gov/cgi-bin/regtransbase?page=main"));
	test1->Insert(new page("http://rfam.sanger.ac.uk/"));
	test1->Insert(new page("http://132.248.32.45:8080/cgi-bin/ribex.cgi/"));
	test1->Insert(new page("http://robetta.org/"));
	test1->Insert(new page("http://www.scidac.gov/"));
	test1->Insert(new page("http://www.theseed.org/"));
	test1->Insert(new page("http://www.shewanella.org/"));
	test1->Insert(new page("http://sourceforge.net/"));
	test1->Insert(new page("http://sbml.org/"));
	test1->Insert(new page("http://www.taverna.org.uk/"));
	test1->Insert(new page("http://www.ccg.unam.mx/Computational_Genomics/tractorDB/"));
	test1->Insert(new page("http://www.ebi.ac.uk/swissprot/"));
	test1->Insert(new page("http://www.ccrc.uga.edu/"));
	test1->Insert(new page("http://genome.lbl.gov/vista/"));
	TEST(test1->contains(testURL));
	
	
	page_history * test2= new page_history();
	test2->Insert(new page("http://www.bnn.com/"));
	test2->Insert(new page("http://www.cnn.com/"));
	test2->Insert(new page("http://www.ann.com/"));
	test2->Insert(new page("http://english.ucsb.edu:591/rchrono/"));
	test2->Insert(new page("http://www.lib.ucdavis.edu/English/BWRP/index.htm"));
	test2->Insert(new page("http://www.qub.ac.uk/english/shuttle/rom-chrono/chrono.htm"));
	test2->Insert(new page("http://etext.lib.virginia.edu/modeng.browse.html"));
	test2->Insert(new page("http://etext.lib.virginia.edu/britpo.html"));
	test2->Insert(new page("http://jefferson.village.virginia.edu/blake/"));
	test2->Insert(new page("gopher://dept.english.upenn.edu:70/11/Courses"));
	test2->Insert(new page("gopher://dept.english.upenn.edu/11/E-Text/PEAL"));
	test2->Insert(new page("http://www.english.upenn.edu/~curran/home.html"));
	test2->Insert(new page("http://dept.english.upenn.edu/~mgamer/Romantic/"));
	test2->Insert(new page("http://gopher.upenn.edu/pennprintout/html/v11/3/creature.html"));
	test2->Insert(new page("http://www.rc.umd.edu/"));
	test2->Insert(new page("http://fay.english.umb.edu/"));
	test2->Insert(new page("http://www.nottingham.ac.uk/~aezacweb/wrew.htm"));
	test2->Insert(new page("http://users.ox.ac.uk/~scat0385"));
	test2->Insert(new page("http://www.sul.stanford.edu/mirrors/romnet/"));
	test2->Insert(new page("http://www.ualberta.ca/~dmiall/ROMCDINF.HTM"));
	test2->Insert(new page("http://www.en.utexas.edu/"));
	test2->Insert(new page("http://www.cwrl.utexas.edu/~worp"));
	test2->Insert(new page("http://www.usc.edu/dept/LAS/english/19c/newbooks.html"));
	test2->Insert(new page("http://www.luc.edu/publications/keats-shelley/ksjweb.htm"));
	test2->Insert(new page("http://lang.nagoya-u.ac.jp/~matsuoka/19th-authors.html"));
	test2->Insert(new page("http://lang.nagoya-u.ac.jp/~matsuoka/Victorian.html"));
	test2->Insert(new page("http://www.ebi.ac.uk/microarray-as/ae/"));
	test2->Insert(new page("http://biocyc.org/"));
	test2->Insert(new page("http://bioenergycenter.org/"));
	test2->Insert(new page("http://www.brenda-enzymes.info"));
	test2->Insert(new page("http://www.cazy.org/"));
	test2->Insert(new page("http://camera.calit2.net/"));
	test2->Insert(new page("http://cmr.jcvi.org/"));
	test2->Insert(new page("http://gaggle.systemsbiology.net/docs/geese/firegoose/"));
	test2->Insert(new page("http://gaggle.systemsbiology.net/docs/"));
	test2->Insert(new page("http://www.ncbi.nlm.nih.gov/Genbank"));
	test2->Insert(new page("http://www.ncbi.nlm.nih.gov/geo"));
	test2->Insert(new page("http://www.geneontology.org/"));
	test2->Insert(new page("http://gensc.org/"));
	test2->Insert(new page("http://collections.plos.org/plosbiology/gos-2007.php"));
	test2->Insert(new page("http://www.greatlakesbioenergy.org/"));
	test2->Insert(new page("http://genomicsgtl.energy.gov/datasharing/GTLDataPolicy.pdf"));
	test2->Insert(new page("http://www.hupo.org/"));
	test2->Insert(new page("http://www.sc.doe.gov/ascr/INCITE"));
	test2->Insert(new page("http://www.iscb.org/"));
	test2->Insert(new page("http://www.jbei.org/"));
	test2->Insert(new page("http://www.jgi.doe.gov/"));
	test2->Insert(new page("http://img.jgi.doe.gov/cgi-bin/pub/main.cgi"));
	test2->Insert(new page("http://www.genome.jp/kegg/"));
	test2->Insert(new page("http://www.metacyc.org/"));
	test2->Insert(new page("http://www.microbesonline.org/"));
	test2->Insert(new page("http://nihroadmap.nih.gov/hmp"));
	test2->Insert(new page("http://www.obofoundry.org/"));
	test2->Insert(new page("http://www.opensource.org/"));
	test2->Insert(new page("http://pathema.jcvi.org/"));
	test2->Insert(new page("http://www.phytozome.net/"));
	test2->Insert(new page("http://ncrr.pnl.gov/"));
	test2->Insert(new page("http://ober-proteomics.pnl.gov/"));
	test2->Insert(new page("http://omics.pnl.gov/"));
	test2->Insert(new page("http://www.promscan.uklinux.net/"));
	test2->Insert(new page("http://ncrr.pnl.gov/about/process.stm"));
	test2->Insert(new page("http://www.rcsb.org/pdb/home/home.do"));
	test2->Insert(new page("http://regtransbase.lbl.gov/cgi-bin/regtransbase?page=main"));
	test2->Insert(new page("http://rfam.sanger.ac.uk/"));
	test2->Insert(new page("http://132.248.32.45:8080/cgi-bin/ribex.cgi/"));
	test2->Insert(new page("http://robetta.org/"));
	test2->Insert(new page("http://www.scidac.gov/"));
	test2->Insert(new page("http://www.theseed.org/"));
	test2->Insert(new page("http://www.shewanella.org/"));
	test2->Insert(new page("http://sourceforge.net/"));
	test2->Insert(new page("http://sbml.org/"));
	test2->Insert(new page("http://www.taverna.org.uk/"));
	test2->Insert(new page("http://www.ccg.unam.mx/Computational_Genomics/tractorDB/"));
	test2->Insert(new page("http://www.ebi.ac.uk/swissprot/"));
	test2->Insert(new page("http://www.ccrc.uga.edu/"));
	test2->Insert(new page("http://genome.lbl.gov/vista/"));
	
	
	
	page_history * test3= new page_history();
	test3->Insert(new page("http://www.bnn.com/"));
	test3->Insert(new page("http://www.cnn.com/"));
	test3->Insert(new page("http://www.ann.com/"));
	test3->Insert(new page("http://english.ucsb.edu:591/rchrono/"));
	test3->Insert(new page("http://www.lib.ucdavis.edu/English/BWRP/index.htm"));
	test3->Insert(new page("http://www.qub.ac.uk/english/shuttle/rom-chrono/chrono.htm"));
	test3->Insert(new page("http://etext.lib.virginia.edu/modeng.browse.html"));
	test3->Insert(new page("http://etext.lib.virginia.edu/britpo.html"));
	test3->Insert(new page("http://jefferson.village.virginia.edu/blake/"));
	test3->Insert(new page("gopher://dept.english.upenn.edu:70/11/Courses"));
	test3->Insert(new page("gopher://dept.english.upenn.edu/11/E-Text/PEAL"));
	test3->Insert(new page("http://www.english.upenn.edu/~curran/home.html"));
	test3->Insert(new page("http://dept.english.upenn.edu/~mgamer/Romantic/"));
	test3->Insert(new page("http://gopher.upenn.edu/pennprintout/html/v11/3/creature.html"));
	test3->Insert(new page("http://www.rc.umd.edu/"));
	test3->Insert(new page("http://fay.english.umb.edu/"));
	test3->Insert(new page("http://www.nottingham.ac.uk/~aezacweb/wrew.htm"));
	test3->Insert(new page("http://users.ox.ac.uk/~scat0385"));
	test3->Insert(new page("http://www.sul.stanford.edu/mirrors/romnet/"));
	test3->Insert(new page("http://www.ualberta.ca/~dmiall/ROMCDINF.HTM"));
	test3->Insert(new page("http://www.en.utexas.edu/"));
	test3->Insert(new page("http://www.cwrl.utexas.edu/~worp"));
	test3->Insert(new page("http://www.usc.edu/dept/LAS/english/19c/newbooks.html"));
	test3->Insert(new page("http://www.luc.edu/publications/keats-shelley/ksjweb.htm"));
	test3->Insert(new page("http://lang.nagoya-u.ac.jp/~matsuoka/19th-authors.html"));
	test3->Insert(new page("http://lang.nagoya-u.ac.jp/~matsuoka/Victorian.html"));
	test3->Insert(new page("http://www.ebi.ac.uk/microarray-as/ae/"));
	test3->Insert(new page("http://biocyc.org/"));
	test3->Insert(new page("http://bioenergycenter.org/"));
	test3->Insert(new page("http://www.brenda-enzymes.info"));
	test3->Insert(new page("http://www.cazy.org/"));
	test3->Insert(new page("http://camera.calit2.net/"));
	test3->Insert(new page("http://cmr.jcvi.org/"));
	test3->Insert(new page("http://gaggle.systemsbiology.net/docs/geese/firegoose/"));
	test3->Insert(new page("http://gaggle.systemsbiology.net/docs/"));
	test3->Insert(new page("http://www.ncbi.nlm.nih.gov/Genbank"));
	test3->Insert(new page("http://www.ncbi.nlm.nih.gov/geo"));
	test3->Insert(new page("http://www.geneontology.org/"));
	test3->Insert(new page("http://gensc.org/"));
	test3->Insert(new page("http://collections.plos.org/plosbiology/gos-2007.php"));
	test3->Insert(new page("http://www.greatlakesbioenergy.org/"));
	test3->Insert(new page("http://genomicsgtl.energy.gov/datasharing/GTLDataPolicy.pdf"));
	test3->Insert(new page("http://www.hupo.org/"));
	test3->Insert(new page("http://www.sc.doe.gov/ascr/INCITE"));
	test3->Insert(new page("http://www.iscb.org/"));
	test3->Insert(new page("http://www.jbei.org/"));
	test3->Insert(new page("http://www.jgi.doe.gov/"));
	test3->Insert(new page("http://img.jgi.doe.gov/cgi-bin/pub/main.cgi"));
	test3->Insert(new page("http://www.genome.jp/kegg/"));
	test3->Insert(new page("http://www.metacyc.org/"));
	test3->Insert(new page("http://www.microbesonline.org/"));
	test3->Insert(new page("http://nihroadmap.nih.gov/hmp"));
	test3->Insert(new page("http://www.obofoundry.org/"));
	test3->Insert(new page("http://www.opensource.org/"));
	test3->Insert(new page("http://pathema.jcvi.org/"));
	test3->Insert(new page("http://www.phytozome.net/"));
	test3->Insert(new page("http://ncrr.pnl.gov/"));
	test3->Insert(new page("http://ober-proteomics.pnl.gov/"));
	test3->Insert(new page("http://omics.pnl.gov/"));
	test3->Insert(new page("http://www.promscan.uklinux.net/"));
	test3->Insert(new page("http://ncrr.pnl.gov/about/process.stm"));
	test3->Insert(new page("http://www.rcsb.org/pdb/home/home.do"));
	test3->Insert(new page("http://regtransbase.lbl.gov/cgi-bin/regtransbase?page=main"));
	test3->Insert(new page("http://rfam.sanger.ac.uk/"));
	test3->Insert(new page("http://132.248.32.45:8080/cgi-bin/ribex.cgi/"));
	test3->Insert(new page("http://robetta.org/"));
	test3->Insert(new page("http://www.scidac.gov/"));
	test3->Insert(new page("http://www.theseed.org/"));
	test3->Insert(new page("http://www.shewanella.org/"));
	test3->Insert(new page("http://sourceforge.net/"));
	test3->Insert(new page("http://sbml.org/"));
	test3->Insert(new page("http://www.taverna.org.uk/"));
	test3->Insert(new page("http://www.ccg.unam.mx/Computational_Genomics/tractorDB/"));
	test3->Insert(new page("http://www.ebi.ac.uk/swissprot/"));
	test3->Insert(new page("http://www.ccrc.uga.edu/"));
	test3->Insert(new page("http://genome.lbl.gov/vista/"));
	
	test3->Insert(testURL);
	test3->Insert( testURL);
	test3->Insert(testURL);
	test3->Insert(testURL);
	test3->Insert(testURL);
	test3->Insert(testURL);
	test3->Insert(testURL);
	test3->Insert(testURL);
	
	
	
	
	TEST(!test3->IsEmpty());	
	
	test3->Clear();
	
	TEST(test3->IsEmpty());
	
	TEST(test2->GetSize()==76);
		
	delete test1;
	delete test2;
	delete test3;
	*/
	if (success) {
		cout << "PASSED"<<endl;
	}
	return success;
	
}
