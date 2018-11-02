// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <cctype>
#include <algorithm>  // for swap
using namespace std;

const int LIM = 26;
const int HASHSIZE = 50000;


void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

// Linkedlist Node
struct Node
{
	Node(string value, int key, unsigned long sup)
		: m_value(value), key(key), next(nullptr), supKey(sup)
	{}
	string m_value;
	int key;
	unsigned long supKey;
	Node* next;
};

class DictionaryImpl
{
public:
	// Initializes all hash table values as nullptr
	DictionaryImpl();
	// Destroys nodes because they're dynamic variables
	~DictionaryImpl();
	// Inserts a word
	void insert(string& word);
	// call the provided callback function once for every word that is an anagram of letters parameter
	void lookup(string& letters, void callback(string));
private:
	int hashFunc(string& word);
	unsigned long primeMult;
	Node * hashTab[HASHSIZE];  // hash table formed from Node pointers
};

DictionaryImpl::DictionaryImpl()
{
	// Iterates through the hash table values and sets every value to nullptr
	for (int x = 0; x < HASHSIZE; x++)
	{
		hashTab[x] = nullptr;
	}
}

DictionaryImpl::~DictionaryImpl()
{
	// Iterate through all values of the hash table
	for (int x = 0; x < HASHSIZE; x++)
	{
		Node* start = hashTab[x];
		// destroy each node in the buckets until we 
		// reach the end of the hash table, indicated by nullptr
		while (start != nullptr)
		{
			Node* previous = start;
			start = (*start).next;
			delete previous;
		}
	}
}

// helper function for hashFunc that gets rid of unnecessary letters
void cleanup(string& str)
{
	string::iterator it = str.begin();
	for (string::const_iterator asdf = str.begin(); asdf != str.end(); asdf++)
	{
		if (isalpha(*asdf))
		{
			(*it) = tolower(*asdf);
			it++;
		}
	}
	str.erase(it, str.end());  // chop off everything from "to" to end.
}

int DictionaryImpl::hashFunc(string& word)
{
	// value to return (returns -1 if things don't go right)
	int result = -1;
	// gets rid of unnecessary letters
	cleanup(word);
	primeMult = 1;
	// prime number list for hash table
	int prime[LIM] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101 };
	for (size_t x = 0; x < word.length(); x++)
	{
		// Multiply each letters with the next (prime numbers)
		primeMult *= prime[word[x] - 'a'];
	}
	result = primeMult % HASHSIZE;
	return result;
}

void DictionaryImpl::insert(string& word)
{
	int key = hashFunc(word);
	// Assign new entry to bucket
	Node*& entry = hashTab[key];
	// directly add if the bucket is empty, else add to the end of items in the bucket
	if (entry == nullptr)
	{
		entry = new Node(word, key, primeMult);
	}
	else
	{
		Node* t = new Node(word, key, primeMult);
		Node* prev = entry;
		while ((*prev).next)
		{
			prev = (*prev).next;
		}
		(*prev).next = t;
	}
}

void DictionaryImpl::lookup(string& letters, void callback(string))
{
	// if at the simplest case, return and don't execute the code below
	if (callback == nullptr)
	{
		return;
	}
	if (letters.empty())
	{
		return;
	}

	// setup unique ID, hashkey
	int key = hashFunc(letters);
	const unsigned long callSuper = primeMult;
	Node* xx = hashTab[key];

	while (xx != nullptr)
	{
		// same unique ID for anagrams
		if ((*xx).supKey == callSuper)
		{
			callback((*xx).m_value);
			xx = (*xx).next;
		}
		else
		{
			xx = (*xx).next;
		}
	}
}

// Each successive call to this function generates the next permutation of the
// characters in the parameter.  For example,
//    string s = "eel";
//    generateNextPermutation(s);  // now s == "ele"
//    generateNextPermutation(s);  // now s == "lee"
//    generateNextPermutation(s);  // now s == "eel"
// You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
	string::iterator last = permutation.end() - 1;
	string::iterator p;

	for (p = last; p != permutation.begin() && *p <= *(p - 1); p--)
		;
	if (p != permutation.begin())
	{
		string::iterator q;
		for (q = p + 1; q <= last && *q > *(p - 1); q++)
			;
		swap(*(p - 1), *(q - 1));
	}
	for (; p < last; p++, last--)
		swap(*p, *last);
}

//******************** Dictionary functions **********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code.

Dictionary::Dictionary()
{
	m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
	delete m_impl;
}

void Dictionary::insert(string word)
{
	m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
	m_impl->lookup(letters, callback);
}