#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include "LibrarySystem.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <Windows.h>

using namespace std;


void displayItemDetail(vector <Entry> vec, Catalogue lib);

int main() {

	Catalogue library;

	//library.readFromFiles(library.Albums, library.Books, library.films, library);

	library.currentDate(library.date, "0");
	cout << "\n\n******* LIBRARY MANAGEMENT SYSTEM *******\n\n\n";
	cout << "Enter the number of the action would you like to take? \n\n1) Add a new entry \n\n2) Delete an entry \n\n3) Search Item \n\n"
		"4) View library inventory \n\n5) View available items \n\n6) View loaned items \n\n7) Issue an item \n\n8) Return an item \n\n9) Set loan duration \n\n10) Quit" << endl;
	int choice = 1;
	cout << "\n\nSelection: "; cin >> choice;

	while (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7 || choice == 8 || choice == 9 || choice == 10) {

	

		switch (choice) {
		case 1:	system("CLS");
			library.addEntry(library.totalItems, library.availableItems, library, library.Books, library.films, library.Albums);
			break;
		case 2: { cout << "Enter the name of the item you would like to delete: "; string name; cin.ignore(); getline(cin, name);
			library.deleteVectorObj(library.availableItems, name); library.deleteVectorObj(library.totalItems, name);
			break; }
		case 3: {system("CLS"); {if (library.totalItems.size() == 0) {
			cout << "There are currently zero items in the library inventory - Type any key to return to the menu\n";
			string x; cin >> x;
			break;
		}
			  cout << "What is the name of the item you would like to see?: ";
			  string search; cin.ignore(); getline(cin, search); library.searchItem(library.totalItems, search);
			  if (library.searchItem(library.totalItems, search).borrowed == false) cout << "This item is available for issue" << endl; break;
			  cout << "This item is currently loaned out to: " << library.searchItem(library.totalItems, search).borrowedBy << endl;
			  cout << "It will be returned on: " << library.searchItem(library.totalItems, search).returnDate << endl;
			  cout << "Type any key to return to the menu \n";
			  string x; cin >> x;

		}
		case 4: system("CLS"); if (library.totalItems.size() == 0) {
			cout << "There are currently zero items in the library inventory - Type any key to return to the menu\n";
			string x; cin >> x;
			break;
		}
			  else library.showItems(library.totalItems); break;
		case 5: system("CLS"); if (library.availableItems.size() == 0) {
			cout << "There are currently zero available items in the library inventory - Type any key to return to the menu\n";
			string x; cin >> x;
			break;
		}
			  else library.showItems(library.availableItems); break;
		case 6: system("CLS"); if (library.loanedItems.size() == 0) {
			cout << "There are currently zero loaned items in the library inventory - Type any key to return to the menu\n";
			string x; cin >> x;
			break;
		}
			  else library.showItems(library.loanedItems); break;
		case 7: system("CLS"); if (library.availableItems.size() == 0) {
			cout << "There are currently zero available items in the library inventory - Type any key to return to the menu\n";
			string x; cin >> x;
		}
			  else library.issueItem(library.availableItems, library.loanedItems); break;
		case 8: system("CLS"); if (library.loanedItems.size() == 0) {
			cout << "There are mo items currently on loan - Type any key to return to the menu\n"; string x; cin >> x; break;
		}
			  else library.returnItem(library.availableItems, library.loanedItems); break;
		case 9: system("CLS"); library.setLoanDuration(); break;
		case 10: cout << "Exiting Library Management System";  return 0;
		}
			  

		}
		system("CLS");
		cout << "Enter the number of the action would you like to take? \n\n1) Add a new entry \n\n2) Delete an entry \n\n 3) Search Item \n\n"
		"4) View library inventory \n\n5) View available items \n\n6) View loaned items \n\n7) Issue an item \n\n8) Return an item \n\n9) Set loan duration \n\n10) Quit" << endl;
		cout << "\nSelection: "; cin >> choice;
		
	}
return 0;
}

