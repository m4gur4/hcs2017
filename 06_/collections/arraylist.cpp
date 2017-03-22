#include <iostream>
#include <cstdlib> // для system

#define DEBUG

using namespace std;

typedef char ARRAY_TYPE;   // for sample


class ArrayList
{
private:
    ARRAY_TYPE* array;
    int allocated;
    int sizeOfList;

    const static int DEFAULT_SIZE = 10;
    const static int DEFAULT_MULTIPLIER = 2;

    /* Copy "sizeOfOldArray" items in array's  */
    void writeNewArray(ARRAY_TYPE* oldArray, ARRAY_TYPE* newArray, int sizeOfOldArray);
    /* Copy array's */
    void rewriteArray(int newSize);
    /* Move left all items after item at position "indexDel" */
    void moveLeft(ARRAY_TYPE* oldArray, ARRAY_TYPE* newArray, int sizeOfOldArray,int indexDel);
    /* Deleting element at position "index" from ArrayList */
    void deleteElement(int index);

public:

    ArrayList(); /* Default constructor */
    ArrayList(int size); /* Constructor with init size */
    ~ArrayList(); /*  Destructor */

    int getSize();  /* Getting current size of ArrayList */
    void addItem(ARRAY_TYPE data);   /* Adding item to the end of ArrayList */
    void setItem(ARRAY_TYPE data,int index);   /* Set value of item at the "index" position in ArrayList*/
    void removeItem(int index);  /* Remove item at the "index" position in ArrayList */
    ARRAY_TYPE getItem(int index);  /* Getting value of item at the "index" position in ArrayList */
    void trimToSize(int index);  /* Trimming ArrayList from "allocated" to "index" size */
    void trim();  /* Trimming ArrayList from "allocated" to "sizeOfList" size */
    void show(); /* Printing content of ArrayList */
    void showFull(); /* Printing full content of ArrayList */
};
/*****************************************************************/
/***********************     PRIVATE     *************************/
/*****************************************************************/

/* Copy "sizeOfOldArray" items in array's  */
void ArrayList::writeNewArray(ARRAY_TYPE* oldArray, ARRAY_TYPE* newArray, int sizeOfOldArray)
{
    for (int i = 0; i < sizeOfOldArray; i++)
        newArray[i] = oldArray[i];
}

/* Move left all items after item at position "indexDel" */
void ArrayList::moveLeft(ARRAY_TYPE* oldArray, ARRAY_TYPE* newArray, int sizeOfOldArray,int indexDel)
{
    for (int i = 0; i < sizeOfOldArray-1; i++)
        {
            int pos = i;
            if (i>=indexDel) pos++;
            newArray[i] = oldArray[pos];
        }
}

/* Copy array's */
void ArrayList::rewriteArray(int newSize)
{
    ARRAY_TYPE* newArray = new ARRAY_TYPE[allocated];
    writeNewArray(array, newArray, sizeOfList);
    delete[] array;
    array = newArray;
}

/* Deleting element at position "index" from ArrayList */
void ArrayList::deleteElement(int index)
{
    ARRAY_TYPE* newArray = new ARRAY_TYPE[allocated];
    moveLeft(array, newArray, sizeOfList,index);
    delete[] array;
    array = newArray;
}

/*****************************************************************/
/*************************    PUBLIC     *************************/
/*****************************************************************/


/* Default constructor */
ArrayList::ArrayList()
{
    sizeOfList = 0;
    array = new ARRAY_TYPE[DEFAULT_SIZE];
    allocated = DEFAULT_SIZE;
}

/* Constructor with init size */
ArrayList::ArrayList(int size)
{
    sizeOfList = size;
    array = new ARRAY_TYPE[size];
    allocated = size;
}

/*  Destructor */
ArrayList::~ArrayList()
{
    delete array;
}

/* Getting current size of ArrayList */
int ArrayList::getSize()
{
    return sizeOfList;
}

/* Adding item to the end of ArrayList */
void ArrayList::addItem(ARRAY_TYPE data)
{
    if (sizeOfList == allocated)
        rewriteArray(allocated *= DEFAULT_MULTIPLIER);
    array[sizeOfList] = data;
    sizeOfList++;
}

/* Set value of item at the "index" position in ArrayList*/
void ArrayList::setItem(ARRAY_TYPE data,int index)
{
    if (index<sizeOfList)
        array[index] = data;
#ifdef DEBUG
    cout<<"Set item ["<<index<<"] = "<<data<<endl;
#endif
}

/* Remove item at the "index" position in ArrayList */
void ArrayList::removeItem(int index)
{
    deleteElement(index);
    sizeOfList--;
#ifdef DEBUG
    cout<<"Delete item ["<<index<<"]"<<endl;
#endif
}

/* Getting value of item at the "index" position in ArrayList */
ARRAY_TYPE ArrayList::getItem(int index)
{
    ARRAY_TYPE rez = 0;
    if (index<sizeOfList) rez = array[index];
#ifdef DEBUG
    cout<<"Get item ["<<index<<"]=";
#endif
    return rez;
}

/* Trimming ArrayList from "allocated" to "index" size */
void ArrayList::trimToSize(int index)
{
    if (index != allocated)
        {
            rewriteArray(index);
            allocated = index;
            sizeOfList = index;
#ifdef DEBUG
            cout<<"Trim to "<<index<<endl;
#endif
        }
}

/* Trimming ArrayList from "allocated" to "sizeOfList" size */
void ArrayList::trim()
{
    trimToSize(sizeOfList);
}

/* Printing content of ArrayList */
void ArrayList::show()
{
    for (int i = 0; i < sizeOfList; i++)
        {
            cout << array[i] << " ";
        }
}

/* Printing full content of ArrayList */
void ArrayList::showFull()
{
    /* show position item numbers */
    cout<<"|";
    for (int i = 0; i < allocated; i++)
        {
            cout << i%10<<" ";
        }
    cout<<"|"<<endl<<"|";
    /* out element's */
    for (int i = 0; i < allocated; i++)
        {
            cout << array[i]<<" ";
        }
    /* out statistics */
    cout<<"| [ allocated:"<<allocated<<" sizeOfList:"<<sizeOfList<<" ]"<<endl;
}

/**
 *  Main function
 */

int main(void)
{
    ArrayList list;
    for (int i = 65; i < 80; i++)
        list.addItem(i);

    list.showFull();
   // int pos = 5;
    cout<<list.getItem(6)<<endl;

    list.showFull();
    list.trim();
    list.showFull();
    list.removeItem(2);
    list.setItem('$',6);
    list.showFull();
    list.trimToSize(10);
    list.showFull();
    return 0;
}