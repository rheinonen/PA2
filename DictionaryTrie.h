/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

 /** NAME: Robin Heinonen
   * DATE: 10/24/17
   * PID: A53091242
   * DESCRIPTION: DictionaryTrie class header
   * PA2 CSE 100 2017
   */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>
#include <queue>

/** MWT Node class */

class Node
{
public:
  Node* children[27]; //0-25 are a-z, 26 is space char
  unsigned int freq; //freq=0 means no word
  Node();
};

/**
 *  The class for a dictionary ADT, implemented as a MWT
 */

class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:
  Node* root;

  /* helper function for destructor (postorder delete) */
  void deleteAll(Node* n);

  /* maps a character to corresponding integer between 0 and 26*/
  static int ltr2num(char ltr);

  /* maps a number between 0 and 26 to corresponding character */
  static char num2ltr(int num);

  /** given an array of pairs node pointers and corresponding suffices,
    * this will insert the input pair at the
    * appropriate position if its frequency is greater than/equal to that any of
    * the current elements of the array and/or there is room
    */
  static void addtolist(std::pair<Node*,std::string> list[],std::pair<Node*,std::string> toadd,int size);
};

#endif // DICTIONARY_TRIE_H
