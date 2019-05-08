/** NAME: Robin Heinonen
  * DATE: 10/24/17
  * PID: A53091242
  * DESCRIPTION: DictionaryTrie class definition
  * PA2 CSE 100 2017
  */

#include "util.h"
#include "DictionaryTrie.h"

/* MWT node constructor */
Node::Node()
{
    freq=0;
    for(int i = 0; i < 27; ++i) {
        children[i] = nullptr;
    }
}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie()
{
  root=new Node();
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  //don't insert if frequency is zero
  if(freq==0)
    return false;

  Node* currNode=root;
    for(int i=0;i<word.size(); i++)
    {
        int letter=ltr2num(word.at(i));
        if(letter<0 || letter>26)
          return false;
        if(currNode->children[letter]==nullptr)
        {
          currNode->children[letter]=new Node();
        }
        currNode=currNode->children[letter];
    }
    bool inserted=(currNode->freq==0);
    currNode->freq=std::max(freq,currNode->freq);
    return inserted;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  Node* currNode=root;
    for(int i=0;i<word.size(); i++)
    {
        int letter=ltr2num(word.at(i));
        if(letter<0 || letter>26)
          return false;
        if(currNode->children[letter]==nullptr)
            return false;
        currNode=currNode->children[letter];
    }

    if(currNode->freq==0)
        return false;
    return true;

}

/** given an array of pairs node pointers and corresponding suffices,
  * this will insert the input pair at the
  * appropriate position if its frequency is greater than/equal to that any of
  * the current elements of the array and/or there is room
  */
void DictionaryTrie::addtolist(std::pair<Node*,std::string> list[],std::pair<Node*,std::string> toadd, int size){
  for(int i=0;i<size;i++)
  {
    if(list[i].first==nullptr)
    {
      list[i]=toadd;
      return;
    }
    if(list[i].first->freq <= toadd.first->freq)
    {
      std::pair<Node*,std::string> temp=list[i];
      list[i]=toadd;
      for(int j=i;j<size-1;j++)
      {
        std::pair<Node*,std::string> temp2=list[j+1];
        list[j+1]=temp;
        temp=temp2;
      }
      return;
    }
  }
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  Node* currNode=root;
  if(num_completions==0)
    return words;

  if(prefix.size()==0)
  {
    std::cout << "Invalid input. Please retry with correct input" << std::endl;
    return words;
  }

  // go to node specified by prefix
  for(int i=0; i<prefix.size(); i++ )
  {
    int ltr=ltr2num(prefix.at(i));
    if(ltr<0 || ltr>26)
    {
      std::cout << "Invalid input. Please retry with correct input" << std::endl;
      return words;
    }
    if(currNode->children[ltr]==nullptr)
      return words;
    currNode=currNode->children[ltr];
  }

// get a sorted array of the num_completions most frequent words (in the form
// of node pointer/string pair)
  std::pair<Node*,std::string> wordlist[num_completions];
  for(int i=0;i<num_completions;i++)
  {
    wordlist[i]=std::make_pair(nullptr,"");
  }

  std::queue<std::pair<Node*,std::string>> BFSqueue;
  std::pair<Node*,std::string> nextpair=std::make_pair(currNode,"");
  BFSqueue.push(nextpair);
  while(!BFSqueue.empty())
  {
    std::pair<Node*,std::string> curr=BFSqueue.front();
    BFSqueue.pop();
    if(curr.first->freq>0)
      addtolist(wordlist,curr,num_completions);
    for(int i=0;i<27; i++)
    {
      if(curr.first->children[i]!=nullptr)
      {
        nextpair=std::make_pair(curr.first->children[i],curr.second+num2ltr(i));
        BFSqueue.push(nextpair);
      }
    }
  }

  //append suffices to prefix
  for(int i=0; i<num_completions; i++)
  {
    if(wordlist[i].first!=nullptr)
      words.push_back(prefix+wordlist[i].second);
  }
  return words;
}

/* helper function for destructor (postorder delete) */
void DictionaryTrie::deleteAll(Node* n)
{
  if(n==nullptr)
    return;
  for(int i=0; i<27; i++)
  {
    deleteAll(n->children[i]);
  }
  delete n;
}

/* maps a character to corresponding integer between 0 and 26*/
int DictionaryTrie::ltr2num(char ltr)
{
  if(ltr==' ')
    return 26;
  return ltr-'a';
}
/* maps a number between 0 and 26 to corresponding character */
char DictionaryTrie::num2ltr(int num)
{
  return "abcdefghijklmnopqrstuvwxyz "[num];
}
/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  deleteAll(root);
}
