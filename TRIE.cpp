#include <bits/stdc++.h>
using namespace std;
#define ALPHABETSIZE 256

class TrieNode
{
    public:
    bool isEndWord;
    TrieNode *children[ALPHABETSIZE];
    TrieNode()
    {
        this->isEndWord=false;
        for(int i=0;i<ALPHABETSIZE;i++)
        {
            this->children[i] = NULL;
        }
    }
};

class Trie
{
    TrieNode *root;
    public:
    Trie()
    {
        this->root=new TrieNode();
    }

    //insertion in Trie
    void insert(const string str)
    {
        TrieNode *crawler = this->root;

        for(int i=0;i<str.size();i++)
        {
            //Now we have to check whether character present in the Trie ?
            //So if it is present so it must be Not NULL .
            if(crawler->children[int(str[i])] != NULL)
            {
                crawler = crawler->children[int(str[i])];
            }
            else
            {
                crawler->children[int(str[i])] = new TrieNode();
                crawler = crawler->children[int(str[i])];
            }
        }
        crawler->isEndWord = true;
    }

    //Search for string in Trie
    bool search(const string str)
    {
        TrieNode *crawler = this->root;
        
        for(int i=0;i<str.size();i++)
        {
            if(crawler->children[str[i]] == NULL)
            {
                return false;
            }
            crawler = crawler->children[str[i]];
        }
        return (crawler->isEndWord == true);
    }

    //check is it my leaf or any other word is present in Trie with this node
    bool isLeaf(TrieNode *crawler)
    {
        for(int i=0;i<ALPHABETSIZE;i++)
        {
            if(crawler->children[i])
            {
                return false;
            }        
        }
        return true;
    }

    //Helper function for Remove
    bool removeHelper(TrieNode* crawler, const string &str, int index)
    {
        if(crawler)
        {
            if(index == str.size())
            {
                crawler->isEndWord = false;
                /*this will remove our word from Trie but we have to clean characters placed by
                  string in Trie*/
                return isLeaf(crawler);
            }
            else
            {
                if(removeHelper(crawler->children[str[index]], str, index++))
                {
                    delete crawler->children[str[index]];
                    return ( !crawler->isEndWord && isLeaf(crawler) );
                }
            }
        }
        return false;
    }

    //remove string from Trie
    void remove(const string str)
    {
        TrieNode *crawler = this->root;
        removeHelper(crawler,str,0);
    }
};