#ifndef _LibrarySystem_H_
#define _LibrarySystem_H_
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>

using namespace std;

class Entry {
	friend class Catalogue;
public:
	string name;
	bool borrowed;
	string borrowedBy;
	string year;
	string IssuedOn;
	string returnDate;
	Entry();
	Entry(string nme, bool bor, string borBy, string yr, string iss, string rtn)
	{ name = nme; borrowed = bor; borrowedBy = borBy;  year = yr; IssuedOn = iss; returnDate = rtn; }
	string getName() const;
	void setName(string newName) const;
	virtual void entryBorrowed(string entryName);
	virtual void entryReturned(string entryName);
	virtual void loadInfo();
	virtual void printBaseDetails() const;

	virtual ~Entry() {};
};

class MusicAlbum : public Entry {
	friend class Catalogue;
private:
	string artist;
	string recordLabel;
public:
	MusicAlbum();
	MusicAlbum(string nme, bool bor, string borBy, string yr, string iss, string rtn, string art, string label)
	{
		name = nme; borrowed = bor; borrowedBy = borBy;  year = yr; IssuedOn = iss, returnDate = rtn; artist = art; recordLabel = label;
	}
	virtual void printDetails() const;
	virtual ~MusicAlbum() { "Album Entry Destroyed"; };
	//friend Catalogue;
};

class Book : public Entry {
	friend class Catalogue;
public:
	string author;
	string publisher;
	string edition;
public:
	Book();
	Book(bool bor, string borBy, string nme, string yr, string auth, string pub, string edit) 
		{ borrowed = bor; borrowedBy = borBy; name = nme; year = yr; author = auth; publisher = pub; edition = edit; }
	virtual void printDetails() const;
	virtual ~Book() {};

};

class Film : public Entry {
	friend class Catalogue;
private:
	string director;
	string language;
public:
	Film();
	Film(bool bor, string borBy, string nme, string yr, string dir, string lang) 
		{ borrowed = bor; borrowedBy = borBy; name = nme; year = yr; director = dir; language = lang; }
	// virtual void entryBorrowed(string entryName);
	//virtual void entryReturned(string entryName);
	virtual void printDetails() const;
	virtual ~Film() {};

};


class Catalogue {
public:
	int totalNumberOfItems;
	int totalBooks;
	int totalFilms;
	int totalAlbums;
	int numberOfLoanedItems;
	int numberOfLoanedBooks;
	int numberOfLoanedFilms;
	int numberOfLoanedAlbums;
	int loanDuration;
	

	Catalogue();
	Catalogue(int totnum, int totbooks, int totfilms, int totalbums, int loaned, int loanedbooks, int loanedfilms, int loanedalbums, int duration) {
		totalNumberOfItems = totnum; totalBooks = totbooks; totalFilms = totfilms; totalAlbums = totalbums; numberOfLoanedItems = loaned; numberOfLoanedBooks = loanedbooks;
		numberOfLoanedFilms = loanedfilms; numberOfLoanedAlbums = loanedalbums; loanDuration = duration;
	}
	void addEntry(vector <Entry>& list, vector <Entry>& available, Catalogue& library, vector <Book>& booklist, vector <Film>& filmlist, vector <MusicAlbum>& albumlist);	
	Entry searchItem(vector <Entry>& list, string name) const;
	void showItems(vector <Entry> list) const { for (auto n : list) n.printBaseDetails(); char m; cout << "Press m to return to the menu: "; cin >> m; }
	void issueItem(vector <Entry>& avail, vector <Entry>& loan);
	void currentDate(vector <int>& date, string display);
	void returnItem(vector <Entry>&loaned, vector <Entry> &available);
	void setLoanDuration();
	void returnDate(vector <int> date, vector <int>& rtn);
	void deleteVectorObj(vector <Entry>& a, string name);
	//void readFromFiles(vector <Entry> Albums, vector <Entry> Books, vector <Entry> films, Catalogue lib);
	//input from file
	//modify records
	//delete item
	//write to file
	//see overdue items
	vector <int> date{ 3 };
	vector <int> rtnDate{ 3 };
	void showNumbers() const;

	vector <MusicAlbum> Albums;
	vector <Book> Books;
	vector <Film> films;
	vector <Entry> totalItems; 
	vector <Entry> loanedItems;
	vector <Entry> availableItems;
};

#endif _LibrarySystem_H_

