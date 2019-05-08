
/** NAME: Robin Heinonen
  * DATE: 10/29/17
  * PID: A53091242
  * DESCRIPTION: dictionary benchmark program
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

/* this overloaded function takes a pointer to a dictionary and benchmarks it*/
void benchmark(DictionaryBST* dict,int min_size,int step_size,int num_iterations,char* dictfile)
{
  cout<<"# Benchmarking BST" << endl;
  for(int i=0;i<num_iterations;i++)
  {
    dict=new DictionaryBST();
    ifstream in;
    in.open(dictfile);

    if(!in.is_open())
    {
        cout<< "Invalid input file. No file was opened. Please try again.\n";
        return;
    }

    Utils::load_dict(*dict,in,min_size+i*step_size);
    vector<string> words;
    Utils::load_vector(words,in,100);

    long long ave_time=0;
    Timer t;

    for(int j=0;j<1000;j++)
    {
      t.begin_timer();
      for(vector<string>::iterator it=words.begin();it!=words.end();++it)
      {
        dict->find(*it);
      }
      ave_time+=t.end_timer();
    }
    ave_time/=1000;

    cout<<min_size+i*step_size<< "\t" << ave_time << endl;

    in.close();
    delete dict;
  }
}

void benchmark(DictionaryHashtable* dict,int min_size,int step_size,int num_iterations,char* dictfile)
{
  cout<<"# Benchmarking hashtable" << endl;
  for(int i=0;i<num_iterations;i++)
  {
    dict=new DictionaryHashtable();
    ifstream in;
    in.open(dictfile);

    if(!in.is_open())
    {
        cout<< "Invalid input file. No file was opened. Please try again.\n";
        return;
    }

    Utils::load_dict(*dict,in,min_size+i*step_size);
    vector<string> words;
    Utils::load_vector(words,in,100);

    long long ave_time=0;
    Timer t;

    for(int j=0;j<1000;j++)
    {
      t.begin_timer();
      for(vector<string>::iterator it=words.begin();it!=words.end();++it)
      {
        dict->find(*it);
      }
      ave_time+=t.end_timer();
    }
    ave_time/=1000;

    cout<<min_size+i*step_size<< "\t" << ave_time << endl;

    in.close();
    delete dict;
  }
}

void benchmark(DictionaryTrie* dict,int min_size,int step_size,int num_iterations,char* dictfile)
{
  cout<<"# Benchmarking MWT" << endl;
  for(int i=0;i<num_iterations;i++)
  {
    dict=new DictionaryTrie();
    ifstream in;
    in.open(dictfile);

    if(!in.is_open())
    {
        cout<< "Invalid input file. No file was opened. Please try again.\n";
        return;
    }

    Utils::load_dict(*dict,in,min_size+i*step_size);
    vector<string> words;
    Utils::load_vector(words,in,100);

    long long ave_time=0;
    Timer t;

    for(int j=0;j<1000;j++)
    {
      t.begin_timer();
      for(vector<string>::iterator it=words.begin();it!=words.end();++it)
      {
        dict->find(*it);
      }
      ave_time+=t.end_timer();
    }
    ave_time/=1000;

    cout<<min_size+i*step_size<< "\t" << ave_time << endl;

    in.close();
    delete dict;
  }
}

int main(int argc,char* argv[])
{
  if(argc!=5)
  {
    cout<< "Wrong number of inputs." << endl;
    return -1;
  }

  int min_size=atoi(argv[1]);
  int step_size=atoi(argv[2]);
  int num_iterations=atoi(argv[3]);
  DictionaryBST* bst=nullptr;
  DictionaryHashtable* hash=nullptr;
  DictionaryTrie* trie=nullptr;

  benchmark(bst,min_size,step_size,num_iterations,argv[4]);
  benchmark(hash,min_size,step_size,num_iterations,argv[4]);
  benchmark(trie,min_size,step_size,num_iterations,argv[4]);

  return 0;
}
