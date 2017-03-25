/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#include "time.h"

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define MAX_WORD_LENGTH 45
//
#define MAX_NUMBER_OF_TIMERS 10
// Hash array default SIZE
#define HASH_SIZE 160000

typedef char* NODE_TYPE;

class NodeObject
{
    friend class Ddic;
private:
    NODE_TYPE _word;
    NodeObject* _nodeNext;
public:
    NodeObject(void);   /* Constructor */
    NodeObject(NODE_TYPE data); /* Constructor with data */
    ~NodeObject();  /* Destructor */
    NODE_TYPE getValue(void);   /* Get value of current node */
    void setValue(NODE_TYPE data);  /* Set value to current node */
    NodeObject* getNext(void);  /* Get pointer to the next node */
};

class Timekeeper
{
private:
    float startTime;
    float timers[MAX_NUMBER_OF_TIMERS];
    char* descriptions[MAX_NUMBER_OF_TIMERS];
    int index;
public:
    Timekeeper();       /* Constructor */
    ~Timekeeper();      /* Destructor */
    void start(void);   /* Initialize next timer */
    void stop(const char* description); /* Calculate and store timer data */
    void showTelemetry(void);   /* Show Timer's data */
};

class Ddic
{
     friend class Worker;
private:
    char* fileName;
    unsigned int wordsInDictionary;
    unsigned int wordsInText;
    unsigned int misspelledWords;
    char* lastError;
    // HashTable array with linked lists in for each key
    NodeObject* wordArray[HASH_SIZE];

public:
    Ddic(void);     /* Constructor */
    ~Ddic(void);    /* Destructor */
    void load(char *dictionary);    /* Loads dictionary */
    unsigned int getSize(void);     /* Returns number of words in dictionary */
    bool check(const char *word);   /* Main spell check  */
    void unload(void);              /* Unloads dictionary from memory */
    void showTelemetry(void);       /* Show data */;
};

class Worker
{
private:
    int index;
public:
    Worker();
    ~Worker(void);
    void processText(const char* fileName, Ddic dictionary);
};

/**
 * Source : stackoverflow.com/questions/14409466/simple-hash-functions
 */
unsigned int hashWord(const char* word);

#endif // DICTIONARY_H
