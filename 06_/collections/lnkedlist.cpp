#include <iostream>
#include <stdexcept>

#define DEBUG

using namespace std;

//typedef char NODE_TYPE;
typedef int NODE_TYPE;

class Node
{
    friend class LinkedList;
private:
    NODE_TYPE _value; /* data */
    Node *_Next; /* pointer to the next */

public:
    /* Default Constructor */
    Node(void)
        : _Next(NULL)
    { }

    /* Constructor with value */
    Node(NODE_TYPE val)
        : _value(val), _Next(NULL)
    { }

    /* Constructors with and a link of the next node */
    Node(NODE_TYPE val, Node* next)
        : _value(val), _Next(next)
    {}

    /* Getters */
    int getValue(void)
    {
        return _value;
    }

    Node* getNext(void)
    {
        return _Next;
    }
};

class LinkedList
{
private:
    /* Pointer to head  */
    Node *_Head;
    /* Pointer to tail  */
    Node *_Tail;

    int sizeOfList;
    /* Get node* to element at position "index" */
    Node* getNodeByIndex(int index);
    /* Find item index by value="data" */
    int getIndexByValue(NODE_TYPE data);
    /* Remove item by node* */
    void removeItem(Node* item);

public:
    /* Default constructor */
    LinkedList(void);
    /* Constructor with value */
    LinkedList(NODE_TYPE data);
    /* Destructor */
    ~LinkedList(void);
    /* Get size of List */
    int getSize();
    /* Add new item to the end of list */
    void addItem(NODE_TYPE data);
    /* Get value by index */
    NODE_TYPE getItem(int index);
    /* Find index by Value */
    int findItem(NODE_TYPE data);
    /* Insert item at index */
    void insertItem(int index, NODE_TYPE data);
    /* Remove item from LinkedList by index */
    void removeItemByIndex(int index);
    /* Remove(first finded) item from LinkedList by value*/
    void removeItemByValue(NODE_TYPE data);
    /* Show LinkedList*/
    void show();
};

/*****************************************************************/
/***********************     PRIVATE     *************************/
/*****************************************************************/

/* Get node* to element at position "index" */
Node* LinkedList::getNodeByIndex(int index)
{
    int counter=0;
    Node *p = _Head;
    if ( (_Head == NULL) || (sizeOfList<index)  || (index<0))
        {
            cout << "Error: At index ["<<index<<"] !!!" << endl;
            throw std::invalid_argument("The list is empty or wrong index");
            return NULL;
        }
    while ((p != NULL) && (counter<index)  )
        {
            counter++;
            p = p->_Next;
        }
    return p;
}

/* Find item index by value="data" */
int LinkedList::getIndexByValue(NODE_TYPE data)
{
    int counter=0;
    Node *p = _Head;
    if ( (_Head == NULL) )
        {
            cout << "The list is empty" << endl;
            return 0;
        }
    while ((p != NULL) && (p->_value != data)  )
        {
            counter++;
            p = p->_Next;
        }
    if (counter<sizeOfList) return counter;
    else return -1;
}

 /* Remove item by node* */
void LinkedList::removeItem(Node* item)
{
    Node* p = item->_Next;
    item->_Next = p->_Next;
    delete p;
    sizeOfList--;
}

/*****************************************************************/
/*************************    PUBLIC     *************************/
/*****************************************************************/
 /* Default constructor */
LinkedList::LinkedList()
{
    /* Initialize the head and tail node */
    _Head = _Tail = NULL;
    sizeOfList = 0;
}

/* Constructor with value */
LinkedList::LinkedList(NODE_TYPE data)
{
    /* Create a new node, acting as both the head and tail node */
    _Head = new Node(data);
    _Tail = _Head;
    sizeOfList = 1;
}

/* Destructor */
LinkedList::~LinkedList()
{
     Node *p = _Head->_Next;
    while ((p != NULL) )
        {
            sizeOfList--;
            _Head->_Next=p->_Next;
            delete p;
            p = p->_Next;
        }
    delete _Head;
}


/* Get size of List */
int LinkedList::getSize()
{
    return sizeOfList;
}

/* Add new item to the end of list */
void LinkedList::addItem(NODE_TYPE data)
{
    /* Create a new node */
    Node* p = new Node(data);
    _Tail->_Next = p;
    _Tail = p;
    sizeOfList++;
}

/* Get value by index */
NODE_TYPE LinkedList::getItem(int index)
{
    Node* p = getNodeByIndex(index);
    return p->_value;
}

/* Find index by Value */
int LinkedList::findItem(NODE_TYPE data)
{
   return getIndexByValue(data);
}

/* Insert item at index */
void LinkedList::insertItem(int index, NODE_TYPE data)
{
#ifdef DEBUG
    cout<<"Insert '"<<data<<"' into ["<<index<<"]"<<endl;
#endif
    if (index>sizeOfList)
        addItem(data);
    else
        {
            Node* p = new Node(data);

            if (index==0)
                {
                    /* insert into head (0-position) */
                    p->_Next= _Head;
                    _Head = p;
                }
            else
                {
                    // in the middle of list
                    Node* prev;
                    prev = getNodeByIndex(index-1);
                    p->_Next = prev->_Next;
                    prev->_Next = p;
                }
        }
    sizeOfList++;
}

/* Remove item from LinkedList by index */
void LinkedList::removeItemByIndex(int index)
{
#ifdef DEBUG
    cout <<"Removed by index ["<<index<<"]"<< endl;
#endif
    removeItem(getNodeByIndex(index-1));
}

/* Remove(first finded) item from LinkedList by value*/
void LinkedList::removeItemByValue(NODE_TYPE data)
{
#ifdef DEBUG
    cout <<"Removed by Value = "<<data<< endl;
#endif
    removeItem(getNodeByIndex(getIndexByValue(data)-1));
}

/* Show LinkedList*/
void LinkedList::show()
{
    Node *p = _Head;
    /* The list is empty? */
    if (_Head == NULL)
        {
            cout << "The list is empty" << endl;
            return;
        }

    cout << " | ";
    while (p != NULL)
        {
            cout << p->_value<<" ";
            p = p->_Next;
        }
    cout <<" | ";
        cout <<"size = "<<getSize()<< endl;
}

/**
 *  Main function
 */


int main(int argc, const char * argv[])
{
    cout<<"Create a list with only one node"<<endl;
    LinkedList worklist(9);
    worklist.show();
    cout<<"Append 10 items "<<endl;
    for (int i = 1; i< 11; i++)
        {
            worklist.addItem(i);
        }
    worklist.show();
    cout<<"Append one item"<<endl;
    worklist.addItem(8);
    worklist.show();

    cout << " Show [4] = '" << worklist.getItem(4) <<"'"<< endl;
//    cout << " Show [50] = '" << worklist.getItem(50) <<"'"<< endl;

    cout << " Find '6' = [" << worklist.findItem(6) <<"]" <<endl;

    cout << " Find '11' = [ " << worklist.findItem(11) <<"]"<< endl;

    worklist.insertItem(0,66);
    worklist.show();
    worklist.insertItem(4,22);
    worklist.show();
    worklist.insertItem(worklist.getSize(),0);
    worklist.show();

    worklist.removeItemByIndex(2);
    worklist.show();

    worklist.removeItemByValue(4);
    worklist.show();

    return 0;
}
