#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class WordMeaning {
        string word;
        string meaning;
        public:
        WordMeaning(string w, string m): word(w), meaning(m) {}
        string getWord() const { return word; }
        string getMeaning() const { return meaning; }
        void setWord(string w) {word=w; }
        void setMeaning(string m) { meaning=m; }
        bool operator < (const WordMeaning &wm1) const;
        bool operator ==(const WordMeaning &wm1) const;
};


class Dictionary
{
    BST<WordMeaning> words;
public:
    Dictionary(): words(WordMeaning("","")){};
    BST<WordMeaning> getWords() const;
    void readDictionary(ifstream &f);
    string searchFor(string word) const;
    bool correct(string word, string newMeaning);
    void print() const;
};


//TODO
class WordInexistent
{
    string wbef, mbef, waft, maft;
public:
    WordInexistent(string wobef, string mebef, string woaft, string meaft): wbef(wobef), mbef(mebef), waft(woaft), maft(meaft) {}
    string getWordBefore() const { return wbef; }
    string getMeaningBefore() const { return mbef; }
    string getWordAfter() const { return waft; }
    string getMeaningAfter() const { return maft; }
};

#endif