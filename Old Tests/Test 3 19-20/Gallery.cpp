#include "Gallery.h"
#include <ostream>
#include <algorithm>
using namespace std;

Gallery::Gallery(vector<Paint*> c): catalog(PaintCatalogItem("", "", 0, 0.00)), collection(c) {

}

vector<Paint*> Gallery::getCollection() const {
    return collection;
}

void Gallery::setCollection(vector<Paint*> c) {
    collection = c;
}

priority_queue<ExhibitionItem> Gallery::getPaintsToShow() const {
    return paintsToShow;
}
HashTableAuthorRecord Gallery::getAuthorRecords () const {
    return  authorRecords;
}

void Gallery::addAuthorRecord(AuthorRecord ar) {
    authorRecords.insert(ar);
}

void Gallery::generateCatalog() {
    catalog.makeEmpty();
    for(int i = 0; i < collection.size(); i++) {
        catalog.insert(collection[i]);
    }
}

BST<PaintCatalogItem> Gallery::getCatalog() const {
    return catalog;
}


void Gallery::prepareExhibition() {
    while( !paintsToShow.empty())
        paintsToShow.pop();
    for(int i = 0; i < collection.size(); i++) {
        ExhibitionItem ei(collection[i]);
        paintsToShow.push(ei);
    }
}

//-------------------------------------------------------------------------------

//TODO

vector<Paint*> Gallery::getPaintsBy(string a) const {
    vector<Paint*> tmp;
    BSTItrIn<PaintCatalogItem> it(catalog);
    while (!it.isAtEnd()) {
        if (it.retrieve().getAuthor() == a) {
            tmp.push_back(it.retrieve().getPaint());
        }
        it.advance();
    }
    return tmp;
}

//TODO
vector<Paint*> Gallery::getPaintsBetween(int y1, int y2) const {
    vector<Paint*> tmp;
    BSTItrIn<PaintCatalogItem> it(catalog);
    while(!it.isAtEnd()) {
        if (it.retrieve().getYear() >= y1 && it.retrieve().getYear() <= y2) {
            tmp.push_back(it.retrieve().getPaint());
        }
        it.advance();
    }
    return tmp;
}

//TODO
bool Gallery::updateTitle(Paint* p, string tnew) {
    PaintCatalogItem paint(p);
    auto it = catalog.find(paint);
    if (it.getAuthor().empty() && it.getTitle().empty()) return false;
    catalog.remove(it);
    Paint *temp = new Paint(p->getAuthor(), tnew, p->getYear(), p->getPrice());
    PaintCatalogItem new_(temp);
    catalog.insert(new_);
    return true;
}


//TODO
int Gallery::recordAvailablePainters() { //carrega a tabela de dispersao com AuthorRecords
    for (auto it = collection.begin(); it != collection.end(); it++) {
        if(authorRecords.find((*it)->getAuthor()) != authorRecords.end()) {
            auto it1 = authorRecords.find((*it)->getAuthor());
            AuthorRecord temp(it1->getAuthor(), it1->getAvailablePaints() + 1, it1->getTotalSells());
            authorRecords.erase(it1);
            authorRecords.insert(temp);
        }
        else {
            authorRecords.insert((*it)->getAuthor());
        }
    }
    return authorRecords.size();
}

//TODO
double Gallery::totalSells() const {
    double count;
    for (auto it = authorRecords.begin(); it != authorRecords.end(); it++) {
        count += it->getTotalSells();
    }
    return count;
}

//TODO
double Gallery::sellPaint(string a, string t) {
    double price = 0;
    for (auto it = collection.begin(); it != collection.end(); it++) {
        if ((*it)->getAuthor() == a && (*it)->getTitle() == t) {
            price = (*it)->getPrice();
            collection.erase(it);
            break;
        }
    }
    if(price == 0) return price;
    auto it = authorRecords.find(AuthorRecord(a, 0, 0));
    AuthorRecord temp(a, it->getAvailablePaints() - 1, it->getTotalSells() + price);
    authorRecords.erase(it);
    authorRecords.insert(temp);
    return price;
}

//TODO
vector<Paint*> Gallery::nBestExibition(int n, int maxPerYear) {  //escolhe as N mais caras pinturas, dos anos mais antigos, para realizar uma exposição
    vector<Paint*> tmp;
    priority_queue<ExhibitionItem> temp;
    int year = paintsToShow.top().getYear();
    int counter = 0;
    while (!paintsToShow.empty()) {
        ExhibitionItem aux = paintsToShow.top();
        if (maxPerYear == counter && year == aux.getYear()) {
            temp.push(aux);
        }
        else {
            if (year != aux.getYear()) {
                counter = 1;
                year = aux.getYear();
            }
            else {
                counter++;
            }
            tmp.push_back(aux.getPaint());
        }
        paintsToShow.pop();
        if (n == tmp.size()) {
            break;
        }
    }
    while (!temp.empty()) {
        paintsToShow.push(temp.top());
        temp.pop();
    }
    return tmp;
}

//TODO
int Gallery::itemExibitionOrder(string a, string t) {
    priority_queue<ExhibitionItem> temp = paintsToShow;
    int count = 0;
    while (!temp.empty()) {
        count++;
        if (temp.top().getAuthor() == a && temp.top().getTitle() == t) {
            return count;
        }
        temp.pop();
    }
    return 0;
}

