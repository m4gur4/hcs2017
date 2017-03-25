#include <iostream>
#include <cstdio>

using namespace std;

#include "dictionary.h"

#define DICTIONARY "dictionaries/large"

int main(int argc, char* argv[])
{
    // check for correct number of arguments
    if (argc != 2 && argc != 3)
        {
            cout<<"Usage: speller [dictionary] text"<<endl;
            return 1;
        }

    Ddic testDictionary;
    Timekeeper timer;

    char* dictionary = DICTIONARY;
    if (argc == 3)
        dictionary = argv[1];

    // load dictionary
        timer.start();
    testDictionary.load(dictionary);
        timer.stop("load");

    // determine dictionary's size
        timer.start();
    testDictionary.getSize();
        timer.stop("size"); // :-)

    Worker work;

    char* text = (argc == 3) ? argv[2] : argv[1];

        timer.start();
    work.processText(text,testDictionary);
        timer.stop("check");

    // report benchmarks
    timer.showTelemetry();

    return 0;
}
