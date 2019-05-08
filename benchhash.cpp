/** NAME: Robin Heinonen
  * DATE: 10/29/17
  * PID: A53091242
  * DESCRIPTION: hashtable benchmark program
  * PA2 CSE 100 2017
  */

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<set>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
using namespace std;

  /* ELF hash, code from http://www.partow.net/programming/hashfunctions/ */
  unsigned int ELFHash(const string& str)
  {
     unsigned int hash = 0;
     unsigned int x    = 0;

     for(std::size_t i = 0; i < str.length(); i++)
     {
        hash = (hash << 4) + str[i];
        if((x = hash & 0xF0000000L) != 0)
        {
           hash ^= (x >> 24);
        }
        hash &= ~x;
     }

     return hash;
  }

  /* DJB hash, code from http://www.partow.net/programming/hashfunctions/ */
  unsigned int DJBHash(const string& str)
  {
     unsigned int hash = 5381;

     for(std::size_t i = 0; i < str.length(); i++)
     {
        hash = ((hash << 5) + hash) + str[i];
     }

     return hash;
  }

  int main(int argc,char* argv[])
  {
    if(argc!=3)
    {
      cout << "wrong number of inputs" << endl;
      return -1;
    }
    char* dictfile=argv[1];
    unsigned int num_words=atoi(argv[2]);
    vector<int> elf(2*num_words,0);
    vector<int> djb(2*num_words,0);
    ifstream in;
    in.open(dictfile);
    int a='a';
    int b='b';

    cout << "sanity testing ascii values" << endl;
    cout << "a =" << a << endl;
    cout << "b =" << b << endl;
    cout << endl;
    cout << "checking hash values" << endl;
    cout << "ELF(a)=" << ELFHash("a") << endl;
    cout << "ELF(it)=" << ELFHash("it") << endl;
    cout << "ELF(dog)=" << ELFHash("dog") << endl;
    cout << "DJB(a)=" << DJBHash("a") << endl;
    cout << "DJB(it)=" << DJBHash("it") << endl;
    cout << "DJB(dog)=" << DJBHash("dog") << endl;

    if(!in.is_open())
    {
        cout<< "Invalid input file. No file was opened. Please try again.\n";
        return -1;
    }
    vector<string> words;
    Utils::load_vector(words,in,num_words);
    for(vector<string>::iterator it=words.begin();it!=words.end();++it)
    {
      elf[ELFHash(*it)%(2*num_words)]++;
      djb[DJBHash(*it)%(2*num_words)]++;
    }
    cout << "Printing the statistics for ELF hash with hash table size " << 2*num_words << endl;
    cout << "#hits \t#slots receiving the #hits" << endl;

    int totslots=0;
    float ave=0;
    int largest=0;

    for(int i=num_words;i>=0;i--)
    {
      int slots=0;
      for(vector<int>::iterator it=elf.begin();it!=elf.end();++it)
      {
        if(*it==i)
        {
          slots++;
        }
      }
      if(slots!=0)
      {
        if(largest==0)
        {
          largest=i;
        }
        totslots+=slots;
        ave+=i*totslots;
        cout << i << "\t" << slots << endl;
      }
    }

    ave=ave/((float)(num_words));
    cout<< "The average number of steps for a successful search for ELF hash"
    << " would be " << ave << endl;

    cout << "The worst case steps that would be needed to find a word is " << largest<< endl;

    totslots=0;
    ave=0;
    largest=0;
    cout << endl;
    cout << "Printing the statistics for DJB hash with hash table size " << 2*num_words << endl;
    cout << "#hits \t#slots receiving the #hits" << endl;
    for(int i=num_words;i>=0;i--)
    {
      int slots=0;
      for(vector<int>::iterator it=djb.begin();it!=djb.end();++it)
      {
        if(*it==i)
        {
          slots++;
        }
      }
      if(slots!=0)
      {
        if(largest==0)
        {
          largest=i;
        }
        totslots+=slots;
        ave+=i*totslots;
        cout << i << "\t" << slots << endl;
      }

    }
    ave=ave/((float)(num_words));
    cout<< "The average number of steps for a successful search for DJB hash"
    << " would be " << ave << endl;

    cout << "The worst case steps that would be needed to find a word is " << largest<< endl;

    return 0;

  }
