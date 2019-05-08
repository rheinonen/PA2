#include "util.h"
#include "DictionaryHashtable.h"

/** NAME: Robin Heinonen
  * DATE: 10/24/17
  * PID: A53091242
  * DESCRIPTION: DictionaryHastable class definition
  * PA2 CSE 100 2017
  */

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
  return hashtable.insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
  return hashtable.count(word);
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
