#ifndef __TEXT_BUFFER_H__
#define __TEXT_BUFFER_H__

#include "main.h"

template <typename T>
class DoublyLinkedList
{
    // TODO: may provide some attributes
public:
    class Node;

protected:
    Node *head;
    Node *tail;
    int count;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertAtHead(T data);
    void insertAtTail(T data);
    void insertAt(int index, T data);
    void deleteAt(int index);
    T &get(int index) const;
    int indexOf(T item) const;
    bool contains(T item) const;
    int size() const;
    void reverse();
    string toString(string (*convert2str)(T &) = 0) const;
    int countOfOccurences(T data) const;
    int *listOccurrenceIndexes(T data, int count) const;

    Node *getHead() const { return head; }
    void setHead(Node *newHead) { head = newHead; }
    Node *getTail() const { return tail; }
    void setTail(Node *newTail) { tail = newTail; }
    void setCount(int newCount) { count = newCount; }

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *prev;
        friend class DoublyLinkedList<T>;

    public:
        Node()
        {
            this->next = nullptr;
            this->prev = nullptr;
        }

        Node(const T &data)
        {
            this->data = data;
            this->next = nullptr;
            this->prev = nullptr;
        }

        Node *getNext() const
        {
            return next;
        }

        void setNext(Node *next)
        {
            this->next = next;
        }

        void setPrev(Node *prev)
        {
            this->prev = prev;
        }

        Node *getPrev() const
        {
            return prev;
        }
        T getData() const
        {
            return data;
        }
    };
};

class TextBuffer
{
public:
    class HistoryManager;

private:
    DoublyLinkedList<char> buffer;
    int cursorPos;
    HistoryManager *listAction;

    // TODO: may provide some attributes

public:
    TextBuffer();
    ~TextBuffer();

    void insert(char c);
    void deleteChar();
    void moveCursorLeft();
    void moveCursorRight();
    void moveCursorTo(int index);
    string getContent() const;
    int getCursorPos() const;
    int findFirstOccurrence(char c) const;
    int *findAllOccurrences(char c, int &count) const;
    void sortAscending();
    void deleteAllOccurrences(char c);
    void undo();
    void redo();

public:
    class HistoryManager
    {

        // TODO: may provide some attributes
    public:
        struct Action
        {
            string actionName;
            int cursorPos;
            char data;
            Action(string name, int pos, char c) : actionName(name), cursorPos(pos), data(c) {}
        };

        class Node
        {
        public:
            Action *action;
            Node *next;
            Node *prev;

        public:
            Node(Action *a)
            {
                this->action = a;
                this->next = nullptr;
                this->prev = nullptr;
            }

            ~Node()
            {
                delete action;
            }
            friend class HistoryManager;
        };
        friend class TextBuffer;

    private:
        Node *actionHead;
        Node *actionTail;
        Node *current;
        int actionCount;

    public:
        HistoryManager();
        ~HistoryManager();
        string *getHistoryString() const;
        void addAction(const string &actionName, int cursorPos, char c);
        void printHistory() const;
        int size() const;

        Node *getCurrentAction() const { return current; }
        void moveCurrentLeft()
        {
            if (current)
            {
                current = current->prev;
            }
        }
        void moveCurrentRight()
        {
            if (current)
            {
                current = current->next;
            }
        }
        void clearRedoHistory();
    };
};

#endif // __TEXT_BUFFER_H__
