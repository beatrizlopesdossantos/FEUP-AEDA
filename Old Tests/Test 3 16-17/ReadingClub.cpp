/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {
	
	for (auto it = books.begin(); it != books.end(); it++) {
		BookCatalogItem aux((*it)->getTitle(), (*it)->getAuthor(), (*it)->getYear);
		auto it1 = catalogItems.find(aux);
		if (it1.getAuthor().empty() && it1.getTitle().empty()) {
			aux.addItems(it);
			catalogItems.insert(aux);
		}
		else {
			aux = it1;
			aux.addItems(it);
			catalogItems.remove(it1);
			catalogItems.insert(aux);
		}
	}

}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
	BookCatalogItem aux(book->getTitle(), book->getAuthor(), book->getYear());
	auto it = catalogItems.find(aux);
	if (!it.getAuthor().empty() && !it.getTitle().empty()) {
		for (auto it1 = it.getItems().begin(); it1 != it.getItems().end(); it1++) {
			if ((*it1)->getReader()) {
				continue;
			}
			else {
				temp.push_back(it1);
			}
		}
	}
	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	BookCatalogItem aux(book->getTitle(), book->getAuthor(), book->getYear());
	auto it = catalogItems.find(aux);
	if (it.getAuthor().empty() && it.getTitle().empty()) {
		return false;
	}
	else {
		for (auto it1 = it.getItems().begin(); it1 != it.getItems().end; it1++) {
			if ((*it1)->getReader) {
				continue;
			}
			else {
				(*it1)->setReader(reader);
				reader->addReading(book->getTitle, book->getAuthor);
				return true;
			}
			
		}
	}
	return false;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
	userRecords.insert(user);
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	for (auto it = userRecords.begin(); it != userRecords.end(); it++) {
		if (it.getEmail() == user->getEMail()) {
			UserRecord aux(user);
			aux.setEMail(newEMail);
			userRecords.erase(it);
			userRecords.insert(it);
		}
	}
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	for (auto it = candidates.begin(); it != candidates.end(); it++) {
		if ((*it).getReading()) {
			if ((*it).getReadings.size() + 1 >= min) {
				readerCandidates.push(*it);
			}
		}
		else if ((*it).getReadings.size() >= min) {
			readerCandidates.push(*it);
		}
	}
}

int ReadingClub::awardReaderChampion(User& champion) {
	priority_queue<User> aux = readerCandidates;
	User tem = aux.top();
	aux.pop();
	if (tem.getReadings().size() > aux.top().getReadings().size()) {
		champion = tem;
		return readerCandidates.size();
	}
	else {
		return 0;
	}
}
























