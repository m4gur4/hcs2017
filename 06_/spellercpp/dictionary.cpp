/**
 * Implements a dictionary's functionality.
 */
#include <iostream>
#include <cstdio>
#include <iomanip>  // for formated COUT
#include <malloc.h>
//#include <stdexcept> // for  "throw"

#include "dictionary.h"

/* offset's for output telemetry */
#define OFFSET1 20
#define OFFSET2 12

using namespace std;

/**
 * Source : stackoverflow.com/questions/14409466/simple-hash-functions
 */
unsigned int hashWord(const char* word)
{
    unsigned int counter;
    unsigned int hashValue = 0;
    for(counter = 0; word[counter] != '\0'; counter++)
        hashValue = word[counter] + (hashValue << 6) + (hashValue << 16) - hashValue;
    return (hashValue % HASH_SIZE);
}


/************************************
 *             NodeObject           *
 ************************************/

/* Constructor */
NodeObject::NodeObject(void)
{
    _nodeNext = NULL;
}
/* Constructor with data */
NodeObject::NodeObject(NODE_TYPE data)
{
    _word = data;
    _nodeNext = NULL;
}
NodeObject::~NodeObject()
{
    free(_word); //memory free
}
/* Get value of current node */
NODE_TYPE NodeObject::getValue(void)
{
    return _word;
}
/* Set value to current node */
void NodeObject::setValue(NODE_TYPE data)
{
    _word = data;
}
/* Get pointer to the next node */
NodeObject* NodeObject::getNext(void)
{
    return _nodeNext;
}

/************************************
 *             Timekeeper           *
 ************************************/

/*  Constructor */
Timekeeper::Timekeeper()
{
    startTime = clock();
    index = 0;
}
/*  Destructor */
Timekeeper::~Timekeeper()
{
//
}
/* Initialize next timer */
void Timekeeper::start(void)
{
    startTime = clock();
    if (index>=MAX_NUMBER_OF_TIMERS) index = 0;
    index++;
}

/* Calculate and store timer data */
void Timekeeper::stop(const char* description)
{
    timers[index] = clock() - startTime;
    char* word = (char*) malloc((strlen(description) + 1) * sizeof(char));
    strcpy(word, description);
    descriptions[index]=word;
}

/* Show Timer's data */
void Timekeeper::showTelemetry(void)
{
    float totalTime = 0;
    if (index>0)
        {
            for (int i = 1; i<=index; i++)
                {
                    cout<<"TIME IN "<< left <<setw(OFFSET2)<<descriptions[i]<<": "<< timers[i]<<endl;
                    totalTime=totalTime + timers[i];
                }
        }
    cout<< left <<setw(OFFSET1)<<"TIME IN TOTAL"<<": "<<totalTime<<endl;
}

/************************************
 *                Ddic              *
 ************************************/

/* Constructor */
Ddic::Ddic(void)
{
    wordsInDictionary =0;
    wordsInText =0;
    misspelledWords =0;
    for (int i=0; i< HASH_SIZE; i++)
        {
            wordArray[i] = NULL;
        }
}

/* Loads dictionary */
void Ddic::load(char* dictionary)
{
    FILE* dict = fopen(dictionary, "r");

    if (dict == NULL)
        {
            cout<<"Can't open dictionary file :"<<dictionary<<endl;
            exit(1);
            //throw std::invalid_argument("Can't open dictionary file!");
        }

    /* temporary word */
    char* string = (char*) malloc((MAX_WORD_LENGTH + 1) * sizeof(char));

    int index = 0; // counter for number of char in current "word|string"

    char c; // current char

    while((c = fgetc(dict)) != EOF)
        {
            // end of word
            if (c == '\n')
                {
                    string[index] = '\0';

                    char* word = (char*) malloc((strlen(string) + 1) * sizeof(char));
                    if (word == NULL)
                        cout<<"Allocating memory failed. Aborting"<<endl;
                    strcpy(word, string);

                    NodeObject* newWordNode = new NodeObject (word);

                    int hashIndex = hashWord(string);
                    // if now word(string) in HashArray ..
                    if (wordArray[hashIndex] == NULL)
                        {
                            // then adding first
                            wordArray[hashIndex] = newWordNode;
                        }

                    else
                        {
                            // adding word to linkedlist with number "hashIndex"
                            NodeObject* ptr = wordArray[hashIndex];
                            while(ptr->_nodeNext != NULL)
                                {
                                    ptr = ptr->_nodeNext;
                                }
                            ptr->_nodeNext = newWordNode;
                        }

                    index = 0; // reset index for next word
                    wordsInDictionary++;
                }
            else
                {
                    string[index] = c;
                    index++;
                }
        }

    free(string);
    fclose(dict);

}

/* Returns number of words in dictionary */
unsigned int Ddic::getSize(void)
{
    if (wordsInDictionary >= 1)
        return wordsInDictionary;
    return 0;
}

/* Destructor */
Ddic::~Ddic(void)
{
    //  unload(); //not needed
}

/* Unloads dictionary from memory */
void Ddic::unload(void)
{
    for (int i = 0; i < HASH_SIZE; i++)
        {
            while (wordArray[i] != NULL)
                {
                    NodeObject* next = wordArray[i]->_nodeNext;
                    delete wordArray[i];
                    wordArray[i] = next;
                }
        }
}

/* Main spell check  */
bool Ddic::check(const char *word)
{
    wordsInText++;
    // convert word to lowercase
    char wordLowercase[strlen(word)];
    for (int i = 0, length = strlen(word); i < length; i++)
        {
            wordLowercase[i] = tolower(word[i]);
        }
    // adding the null character to the end of word
    wordLowercase[strlen(word)] = '\0';

    // look up the word in the array
    NodeObject* nodeTemp = wordArray[hashWord(wordLowercase)];

    while (nodeTemp != NULL)
        {
            // compare word's
            if (strcmp(nodeTemp->_word, wordLowercase) == 0)
                {
                    return true;
                }
            // go to the next node
            nodeTemp = nodeTemp->_nodeNext;
        }
    misspelledWords++;
    return false;
}

/* Show data */
void Ddic::showTelemetry(void)
{
    cout<<endl;
    cout<< left <<setw(OFFSET1)<<"WORDS MISSPELLED"<<": "<<misspelledWords<<endl;
    cout<< left <<setw(OFFSET1)<<"WORDS IN DICTIONARY"<<": "<<getSize()<<endl;
    cout<< left <<setw(OFFSET1)<<"WORDS IN TEXT"<<": "<<wordsInText<<endl;
}


/************************************
 *              Worker              *
 ************************************/
Worker::Worker(void)
{
    index = 0;
}

Worker::~Worker(void)
{
    //
}

void Worker::processText(const char* fileName, Ddic dictionary)
{
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL)
        {
            cout<<"Could not open text : "<<fileName<<endl;
            exit(2);
            //throw std::invalid_argument("Could not open text");
        }


    cout<<endl<<"MISSPELLED WORDS"<<endl<<endl;

    char word[MAX_WORD_LENGTH+1];

    // spell-check each word in text
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
        {
            // allow only alphabetical characters and apostrophes
            if (isalpha(c) || (c == '\'' && index > 0))
                {
                    // append character to word
                    word[index] = c;
                    index++;
                    // ignore very long words
                    if (index > MAX_WORD_LENGTH)
                        {
                            // consume remainder of alphabetical string
                            while ((c = fgetc(fp)) != EOF && isalpha(c));
                            // prepare for new word
                            index = 0;
                        }
                }

            // ignore words with numbers (like MS Word can)
            else if (isdigit(c))
                {
                    // consume remainder of alphanumeric string
                    while ((c = fgetc(fp)) != EOF && isalnum(c));
                    // prepare for new word
                    index = 0;
                }
            // we must have found a whole word
            else if (index > 0)
                {
                    // terminate current word
                    word[index] = '\0';
                    // check word's spelling
                    bool misspelled = !dictionary.check(word);
                    // print word if misspelled
                    if (misspelled)
                        {
                            cout<<word<<endl;
                        }
                    // prepare for next word
                    index = 0;
                }
        }

    if (ferror(fp))
        {
            fclose(fp);
            cout<<"Error reading text from :"<<fileName<<endl;
            exit(3);
            //throw std::invalid_argument("Error reading text");
        }
    // close text
    fclose(fp);
    // report benchmarks
    dictionary.showTelemetry();
}
