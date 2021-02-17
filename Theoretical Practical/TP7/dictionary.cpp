#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"
#include <sstream>

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return word < wm1.getWord();
}

bool WordMeaning::operator==(const WordMeaning &wm1) const {
    return word == wm1.getWord();
}

//TODO
void Dictionary::readDictionary(ifstream &f)
{
    string word, meaning;
    while (!f.eof()) {
        getline(f, word);
        getline(f, meaning);
        WordMeaning wm(word, meaning);
        words.insert(wm);
    }
}

//TODO
string Dictionary::searchFor(string word) const
{
    WordMeaning wm(word, "");
    WordMeaning wmx = words.find(wm);
    WordMeaning nF("","");
    if (wmx == nF) {
        BSTItrIn<WordMeaning> it(words);
        string wbef, mbef, waft, maft;
        while (!it.isAtEnd() && it.retrieve()<wm) {
            wbef = it.retrieve().getWord();
            mbef = it.retrieve().getMeaning();
            it.advance();
        }
        if (!it.isAtEnd()) {
            waft = it.retrieve().getWord();
            maft = it.retrieve().getMeaning();
        }
        throw WordInexistent(wbef, mbef, waft, maft);
    }
    else {
        return wmx.getMeaning();
    }

}

//TODO
bool Dictionary::correct(string word, string newMeaning)
{
    WordMeaning wm(word, "");
    WordMeaning wmx = words.find(wm);
    if (wmx == WordMeaning("", "")) {
        words.insert(WordMeaning(word, newMeaning));
        return false;
    }
    else {
        words.remove(wm);
        wmx.setMeaning(newMeaning);
        words.insert(wmx);
        return true;
    }
}

//TODO
void Dictionary::print() const
{
    BSTItrIn<WordMeaning> it(words);
    while (!it.isAtEnd())
    {
        cout << it.retrieve().getWord() << endl << it.retrieve().getMeaning() << endl;
        it.advance();
    }

    cout << "novo iterador"<< endl;
    iteratorBST<WordMeaning> it2 = words.begin();
    while (it2!=words.end()) {
        cout << (*it2).getWord() << endl << (*it2).getMeaning() << endl;
        it2++;
    }
}

