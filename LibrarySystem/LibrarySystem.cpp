#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "LibrarySystem.h"
#include <ctime>
#include <vector>
#include <Windows.h>
using namespace std;


//The Entry default constructor prompts the user to input data into the entry class
Entry::Entry() {
	//loadInfo();
	borrowed = false;
	borrowedBy = "N/a";
	IssuedOn = "N/a";
	cout << "Entry name: "; cin.ignore(); getline(cin, name);
	cout << "Year: "; getline(cin, year);
	}

//Load info get called by the Entry default constructo
void Entry::loadInfo() {

	//borrowed = false;
	//borrowedBy = "N/a";
	//IssuedOn = "N/a";
	//cout << "Entry name: "; cin.ignore(); getline(cin, name);
	//cout << "Year: "; getline(cin, year);
	
}

void Entry::entryBorrowed(string entryName) {
	cout << "Would you like to issue an item? (yes/no): ";
	string choice;
	cin >> choice;
	//while (choice != "q") {
		if (choice == "yes") {
			name = entryName;
			int memberID{ 0 };
			int date{ 0 };
			if (borrowed == true) { cout << "Item is already issued"; return; }
			else {
				borrowed = true;
				cout << "Library membership ID: "; cin >> memberID;
				cout << "Date (DDMMYYYY): "; cin >> date;
				cout << name << " issued to " << memberID << " on " << date << endl;
			}
		}
		else if (choice == "no") return;
		else {
			cout << "Invalid input " << endl;
			cin >> choice;
		}
	//}
}

void Entry::entryReturned(string entryName) {
	cout << "Would you like to return an item? (yes/no) ";
	string choice;
	cin >> choice;
		if (choice == "yes") {
			name = entryName;
			if (borrowed == false) { cout << "Item is already returned"; return; }
			else {
				borrowed = false;
			}
		}
		else if (choice == "no") return;
		else {
			cout << "Invalid input " << endl;
			cin >> choice;
		}
}


void Entry::printBaseDetails() const {
	cout << "\n\nEntry name: " << name << "\nCurrently issued: " << boolalpha << borrowed << "\nIssue to: " << borrowedBy
		<< "\nIssued on: "<< IssuedOn << endl;
}

Film::Film() {
	//loadInfo();
	cout << "Entry type: Film" << endl;
	cout << "Who was the director?: "; cin.ignore(); getline(cin, director);
	cout << "What language was the film in?: "; getline(cin, language);
}

void Film::printDetails() const {
	
	cout <<"Entry type: Film\n" << "Director: " << director << "\nLanguage: " << language << endl;
	Film::printBaseDetails();
	}

Book::Book(){
	//loadInfo();
	cout << "Who was the author?: "; cin.ignore(); getline(cin, author);
	cout << "Who was the publisher?: "; getline(cin, publisher);
	cout << "What edition is the book?: "; getline(cin, edition);
	
}


void Book::printDetails() const {
	
	cout << "Entry Type: Book\n" << "Author: " << author << "\n" << "Publisher: " << publisher << "\n" << "Edition: " << edition << endl;
	Book::printBaseDetails();
}

MusicAlbum::MusicAlbum(){
	cout << "Who was the artist?: "; cin.ignore(); getline(cin, artist);
	cout << "Who was the record label?: "; getline(cin, recordLabel);
}

void MusicAlbum::printDetails() const {
	
	cout << " Entry type: Music Album\n" << "Artist: " << artist << "\n" <<"Record Label: " << recordLabel << endl;
	MusicAlbum::printBaseDetails();
}

Catalogue::Catalogue() {

	totalNumberOfItems = 0; totalAlbums = 0; totalBooks = 0; totalFilms = 0; numberOfLoanedAlbums = 0; 
	numberOfLoanedFilms = 0; numberOfLoanedBooks = 0; numberOfLoanedItems = 0, loanDuration = 21;
}

string Entry::getName() const{
	return name;
}

void Entry::setName(string newName) const {
	name == newName;
}

// A add method that gets called every time the user wants to enter a new item into the library system. It creates the mew object directly into the available vector
//and copies the object into the totalItems vector
void Catalogue::addEntry(vector <Entry>& total, vector<Entry>& available, Catalogue& library, vector <Book> &bookList, vector<Film>&filmList, vector<MusicAlbum> &albumList) {

	string loop;
	while (loop != "m") {
		cout << "Choose the number of the option you would like to add (1, 2 or 3): \n\n 1) Book \n\n 2) Film \n\n 3) Album \n\n Answer: ";
		int choice; cin >> choice;

		switch (choice)
		{
		case 1:
		{
			
			bookList.emplace_back(Book());
			available.push_back(bookList.back());
			//available.emplace_back(Book());
			//booklist.push_back(available.back());
			library.totalBooks++;
			break;
		}
		case 2:
		{
			filmList.emplace_back(Film());
			available.push_back(filmList.back());
			//films.push_back(available.back());
			library.totalFilms++;
			break;
		}
		case 3:
		{
			albumList.emplace_back(MusicAlbum());
			available.push_back(albumList.back());
			//available.emplace_back(MusicAlbum());
			//Albums.push_back(available.back());
			library.totalAlbums++;
			break;
		}
		}

		library.totalNumberOfItems++;
		total.push_back(available.back());
		cout << "Type 'm' to return to the menu or type any other letter to continue adding items" << endl;
		cin >> loop;
	}
}

// This asks for the new loan duration in days and stores in to the catalogue attribute loanDuration
void Catalogue::setLoanDuration() {
	cout << "What would you like the new loan duration to be in days? \n";
	cin >> loanDuration;
}

Entry Catalogue::searchItem(vector <Entry>& list, string name) const {
	//cout << "What is the item you would like to search for?: " << endl;
	//string name; cin >> name;
	auto name_match_fn = [name](auto Entry) {
		return Entry.getName() == name;
	};
	auto entry_it = find_if(begin(list), end(list), name_match_fn);
	if (entry_it == end(list)) {
		// no match found
		cout << name << "was not found in the library records" << endl;
		Entry fail{ "0", 0, "0", "0", 0, "0"};
		return fail;
	}
	else {
		cout << name << " was found successfully in the library records" << endl;
		return *entry_it;
		
	}
}

template <class T>
T SearchItem(vector <T>& list, string name) {
	auto name_match_fn = [name](auto) {
		return T.getName() == name;
	};
	auto it = find_if(begin(list), end(list), name_match_fn);
	if (it == end(list)) {
		// no match found
		cout << name << "was not found in the library records" << endl;
		T fail{ "0", 0, "0", "0", 0, "0" };
		return fail;
	}
	else {
		cout << name << " was found successfully in the library records" << endl;
		return *it;
	}
}

void Catalogue::showNumbers() const {
	cout << "Total items: " << totalNumberOfItems << endl;
	cout << "Total albums: " << totalAlbums << endl;
	cout << "Total Books: " << totalBooks << endl;
	cout << "Total films: " << totalFilms << endl;
	cout << "Total albums loaned: " << numberOfLoanedAlbums << endl;
	cout << "Total films loaned: " << numberOfLoanedFilms << endl;
	cout << "Total Books loaned: " << numberOfLoanedBooks << endl;
	cout << "Total Loaned items: " << numberOfLoanedItems << endl;
}

//This method looks for the object within the inputed vector and uses the erase function to delete it. 
//This method has to get called very time you want to delete an object so that it doesnt delete multiple objects
//of the same name.

void Catalogue::deleteVectorObj(vector<Entry>& vec, string name) {

	vector<Entry>::iterator it;
	for (it = vec.begin(); it != vec.end(); ) {
		string entryname = (*it).getName();
		if (entryname == name) {
			it = vec.erase(it);
			break;
		}
		else
		{
			it++;
		}
	}
}


void Catalogue::issueItem(vector <Entry>& available, vector <Entry>& loaned) {

	cout << "\nWhat type of item is it? Enter 1, 2 or 3. \n1) Book \n2) Film \n3) Album \n\n";
	int answer; cin >> answer;
	cout << "What is the name of item you would like to issue?: " << endl;
	string name; cin.ignore(); getline(cin, name);
	Entry Item = searchItem(available, name);
	if (Item.name == "0") return;
	//if (searchItem(available, name) == name)
	//delete searchItem(available, name);
	Item.borrowed = true;
	Item.IssuedOn = to_string(date[0]) + to_string(date[1]) + to_string(date[2]);
	cout << "Enter library membership number: "; cin >> Item.borrowedBy;
	cout << "\n" << name << " was issue successfully\n";
	cout << "Issued on : "; currentDate(date, "display");
	cout << "To: " << Item.borrowedBy << endl;
	returnDate(date, rtnDate);
	loaned.push_back(Item);


	switch (answer) {
	case 1: {numberOfLoanedBooks++; break; }
	case 2: {numberOfLoanedFilms++; break; }
	case 3: {numberOfLoanedAlbums++; break; }
	}
	deleteVectorObj(available, name);

	
}

void Catalogue::returnItem(vector <Entry>& loaned, vector <Entry>& available) {
	cout << "What is the item you would like to return?: " << endl;
	string name; cin >> name;
	Entry Item = searchItem(loaned, name);
	Item.borrowed = false;
	Item.IssuedOn, Item.returnDate = "N/a";
	Item.borrowedBy = "N/a";
	available.push_back(Item);
	cout << "What type of item is it? Enter 1, 2 or 3. \n 1) Book \n2) Film \n3) Album \n\n";
	int answer; cin >> answer;

	switch (answer) {
	case 1: {numberOfLoanedBooks--; break; }
	case 2: {numberOfLoanedFilms--; break; }
	case 3: {numberOfLoanedAlbums--; break; }
	}

	deleteVectorObj(loaned, name);

	cout << "Type any key to return to the menu" << endl;
	string x; cin >> x;
}

// A method that gets the current date and inserts it into the top of the initial display 
// and stores it in the vector date ready for use in other functions. 

void Catalogue::currentDate(vector<int>&date, string inDisplay) {
	string disp = "display";
	time_t t = time(0);
	tm* now = localtime(&t);
	int day = now->tm_mday;
	int month = (now->tm_mon + 1);
	int year = (now->tm_year + 1900);
	
	if (inDisplay == "display") {
		cout << now->tm_mday << '-' << (now->tm_mon + 1) << '-' << (now->tm_year + 1900) << "\n";

	}
	else cout << "Date: " << now->tm_mday << '-' << (now->tm_mon + 1) << '-' << (now->tm_year + 1900) << "\n";
	date.clear();
	date.push_back(day);
	date.push_back(month);
	date.push_back(year);



}

void Catalogue::returnDate(vector <int> date, vector <int>& rtn){

	int day = date[0];
	int month = date[1];
	int year = date[2];

	int daysInMonth;
	if (month == 2) daysInMonth = 28;
	else if (month == 4 || month == 6 || month == 9 || month == 11) daysInMonth = 30;
	else daysInMonth = 31;


	int newDay = day + loanDuration;
	if (newDay > daysInMonth) {
		int excess = newDay - daysInMonth;
		newDay = excess;
		month++;
		if (month == 13) { month = 1; year++; }
	}
	rtn.clear();
	rtn.push_back(newDay);
	rtn.push_back(month);
	rtn.push_back(year);
	cout << "Return date: " << newDay << "-" << month << "-" << year << endl;
}


/*
void Catalogue::readFromFiles(vector <Entry> Albums, vector <Entry> Books, vector <Entry> films, Catalogue library) {

	MusicAlbum album1{ "0", false, "0", "0", "0", "0", "0", "0" };
	ifstream File("Albums.txt");
	while (File >> album1.name >> album1.borrowed >> album1.borrowedBy >> album1.year >> album1.IssuedOn >> album1.returnDate){ //>> album1.artist >> album1.recordLabel) {
		//here you should create a Stock object and call push_back on the vector.
		
		library.Albums.push_back(album1);

	};
}

*/