/** NAME: Robin Heinonen
  * DATE: 10/24/17
  * PID: A53091242
  * DESCRIPTION: DictionaryBST class definition
  * PA2 CSE 100 2017
  */

#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
  return dictionarySet.insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
  return dictionarySet.count(word);
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
