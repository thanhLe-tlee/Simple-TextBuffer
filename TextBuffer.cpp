#include "TextBuffer.h"
// ----------------- Helper function -----------------
void throwOutOfIndex()
{
    throw out_of_range("Index is invalid!");
}

typename DoublyLinkedList<char>::Node *split(DoublyLinkedList<char>::Node *head)
{
    DoublyLinkedList<char>::Node *fast = head;
    DoublyLinkedList<char>::Node *slow = head;
    while (fast != nullptr && fast->getNext() != nullptr)
    {
        fast = fast->getNext()->getNext();
        if (fast != nullptr)
        {
            slow = slow->getNext();
        }
    }

    DoublyLinkedList<char>::Node *temp = slow->getNext();
    if (slow)
    {
        slow->setNext(nullptr);
    }

    return temp;
}

typename DoublyLinkedList<char>::Node *merge(DoublyLinkedList<char>::Node *first, DoublyLinkedList<char>::Node *second)
{
    if (first == nullptr)
    {
        return second;
    }

    if (second == nullptr)
    {
        return first;
    }

    char data1_lower = tolower(first->getData());
    char data2_lower = tolower(second->getData());

    if (data1_lower < data2_lower)
    {
        first->setNext(merge(first->getNext(), second));
        if (first->getNext())
            first->getNext()->setPrev(first); // Update prev pointer
        return first;
    }
    else if (data1_lower > data2_lower)
    {
        second->setNext(merge(first, second->getNext()));
        if (second->getNext())
            second->getNext()->setPrev(second);
        return second;
    }
    else
    {
        if (first->getData() < second->getData())
        {
            first->setNext(merge(first->getNext(), second));
            if (first->getNext())
                first->getNext()->setPrev(first);
            return first;
        }
        else
        {
            second->setNext(merge(first, second->getNext()));
            if (second->getNext())
                second->getNext()->setPrev(second);
            return second;
        }
    }
}

typename DoublyLinkedList<char>::Node *mergeSort(DoublyLinkedList<char>::Node *head)
{
    if (head == nullptr || head->getNext() == nullptr)
        return head;

    DoublyLinkedList<char>::Node *second = split(head);

    head = mergeSort(head);
    second = mergeSort(second);
    DoublyLinkedList<char>::Node *sortedHead = merge(head, second);
    DoublyLinkedList<char>::Node *current = sortedHead;
    DoublyLinkedList<char>::Node *prevNode = nullptr;
    while (current != nullptr)
    {
        current->setPrev(prevNode);
        prevNode = current;
        current = current->getNext();
    }
    return sortedHead;
}

// ----------------- DoublyLinkedList -----------------

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    // TODO
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    // TODO
    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }

    tail = nullptr;
    count = 0;
}

// TODO: implement other methods of DoublyLinkedList

template <typename T>
void DoublyLinkedList<T>::insertAtHead(T data)
{
    Node *newNode = new Node(data);

    if (head == nullptr)
    {
        head = tail = newNode;
    }
    else
    {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }

    count++;
}

template <typename T>
void DoublyLinkedList<T>::insertAtTail(T data)
{
    Node *newNode = new Node(data);

    if (head == nullptr)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    count++;
}

template <typename T>
void DoublyLinkedList<T>::insertAt(int index, T data)
{
    if (index < 0 || index > count)
    {
        throwOutOfIndex();
    }

    if (index == 0)
    {
        insertAtHead(data);
        return;
    }

    if (index == count)
    {
        insertAtTail(data);
        return;
    }

    Node *newNode = new Node(data);
    Node *temp = head;

    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    // lúc này temp đang ở vị trí mà mình muốn insert, tức temp đang ở vị trí index;
    newNode->next = temp;
    newNode->prev = temp->prev;
    temp->prev->next = newNode;
    temp->prev = newNode;
    count++;
}

template <typename T>
void DoublyLinkedList<T>::deleteAt(int index)
{
    if (index < 0 || index >= count)
    {
        throwOutOfIndex();
    }

    Node *deleteNode = nullptr;
    if (index == 0)
    {
        deleteNode = head;
        head = head->next;
        if (head)
        {
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr;
        }
    }
    else if (index == count - 1)
    {
        deleteNode = tail;
        tail = tail->prev;
        if (tail)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
        }
    }
    else
    {
        Node *curr = head;
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        deleteNode = curr;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    delete deleteNode;
    count--;
}

template <typename T>
T &DoublyLinkedList<T>::get(int index) const
{
    if (index < 0 || index >= count)
    {
        throwOutOfIndex();
    }

    Node *curr = head;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }

    return curr->data;
}

template <typename T>
int DoublyLinkedList<T>::indexOf(T item) const
{
    Node *curr = head;
    int idx = 0;
    while (curr != nullptr)
    {
        if (curr->data == item)
        {
            return idx;
        }
        idx++;
        curr = curr->next;
    }

    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::contains(T item) const
{
    return indexOf(item) != -1;
}

template <typename T>
int DoublyLinkedList<T>::size() const
{
    return count;
}

template <typename T>
void DoublyLinkedList<T>::reverse()
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    Node *curr = head;
    Node *temp = nullptr;

    while (curr != nullptr)
    {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }

    temp = head;
    head = tail;
    tail = temp;
}

template <typename T>
string DoublyLinkedList<T>::toString(string (*convert2str)(T &)) const
{
    string strList = "[";
    Node *curr = head;
    for (int i = 0; i < count && curr != nullptr; i++)
    {
        if (convert2str)
        {
            strList += convert2str(curr->data);
        }
        else
        {
            // Provide default conversion for int, char, string, double, float
            if constexpr (std::is_same<T, int>::value || std::is_same<T, double>::value || std::is_same<T, float>::value)
            {
                strList += std::to_string(curr->data);
            }
            else if constexpr (std::is_same<T, char>::value)
            {
                strList += curr->data;
            }
            else if constexpr (std::is_same<T, std::string>::value)
            {
                strList += curr->data;
            }
            else
            {
                strList += "?";
            }
        }
        if (i != count - 1)
        {
            strList += ", ";
        }
        curr = curr->next;
    }
    strList += "]";
    return strList;
}

template <typename T>
int DoublyLinkedList<T>::countOfOccurences(T data) const
{
    int cnt = 0;
    Node *curr = head;
    while (curr != nullptr)
    {
        if (curr->data == data)
        {
            cnt++;
        }
        curr = curr->next;
    }
    return cnt;
}

template <typename T>
int *DoublyLinkedList<T>::listOccurrenceIndexes(T data, int count) const
{
    int *listOfIndexes = new int[count];
    Node *curr = head;
    int idx = 0;

    for (int i = 0; i < this->count && curr != nullptr; i++)
    {
        if (curr->data == data)
        {
            listOfIndexes[idx] = i;
            idx++;
        }

        curr = curr->next;
    }
    return listOfIndexes;
}

// ----------------- TextBuffer -----------------

TextBuffer::TextBuffer()
{
    // TODO
    this->cursorPos = 0;
    this->listAction = new HistoryManager();
}

TextBuffer::~TextBuffer()
{
    // TODO
    delete listAction;
}

void TextBuffer::insert(char c)
{
    if (cursorPos == 0)
    {
        buffer.insertAtHead(c);
    }
    else if (cursorPos == buffer.size())
    {
        buffer.insertAtTail(c);
    }
    else
    {
        buffer.insertAt(cursorPos, c);
    }
    listAction->addAction("insert", cursorPos, c);
    cursorPos++;
}

void TextBuffer::deleteChar()
{
    if (cursorPos == 0)
    {
        throw cursor_error();
    }

    char deletedChar = buffer.get(cursorPos - 1);
    buffer.deleteAt(cursorPos - 1);
    cursorPos--;
    listAction->addAction("delete", cursorPos, deletedChar);
}

void TextBuffer::moveCursorLeft()
{
    if (cursorPos == 0)
    {
        throw cursor_error();
    }
    listAction->addAction("move", cursorPos, 'L');
    cursorPos--;
}

void TextBuffer::moveCursorRight()
{
    if (cursorPos == buffer.size())
    {
        throw cursor_error();
    }
    listAction->addAction("move", cursorPos, 'R');
    cursorPos++;
}

void TextBuffer::moveCursorTo(int index)
{
    if (index < 0 || index > buffer.size())
    {
        throwOutOfIndex();
    }

    if (cursorPos == index)
    {
        return;
    }

    listAction->addAction("move", index, static_cast<char>(cursorPos));
    cursorPos = index;
}

string TextBuffer::getContent() const
{
    // return buffer.toString();
    string content = "";
    typename DoublyLinkedList<char>::Node *curr = buffer.getHead();
    while (curr != nullptr)
    {
        content += curr->getData();
        curr = curr->getNext();
    }
    return content;
}

int TextBuffer::getCursorPos() const
{
    return cursorPos;
}

int TextBuffer::findFirstOccurrence(char c) const
{
    return buffer.indexOf(c);
}

int *TextBuffer::findAllOccurrences(char c, int &count) const
{
    count = buffer.countOfOccurences(c);
    int *listOccurrenceIndexes = buffer.listOccurrenceIndexes(c, count);
    return listOccurrenceIndexes;
}

void TextBuffer::sortAscending()
{
    DoublyLinkedList<char> tempList;
    while (buffer.size() > 0)
    {
        tempList.insertAtTail(buffer.get(0));
        buffer.deleteAt(0);
    }

    tempList.setHead(mergeSort(tempList.getHead()));
    int count = 0;
    typename DoublyLinkedList<char>::Node *current = tempList.getHead();
    typename DoublyLinkedList<char>::Node *prevNode = nullptr;
    while (current != nullptr)
    {
        count++;
        prevNode = current;
        current = current->getNext();
    }
    tempList.setCount(count);
    tempList.setTail(prevNode);
    buffer.setHead(tempList.getHead());
    buffer.setTail(tempList.getTail());
    buffer.setCount(count);

    tempList.setHead(nullptr);
    tempList.setTail(nullptr);
    tempList.setCount(0);
    listAction->addAction("sort", 0, '\0');
    cursorPos = 0;
}

void TextBuffer::deleteAllOccurrences(char c)
{
    int count, *indexes = findAllOccurrences(c, count);
    for (int i = count - 1; i >= 0; --i)
    {
        buffer.deleteAt(indexes[i]);
        if (cursorPos > indexes[i])
            cursorPos--;
    }
    if (cursorPos > buffer.size())
        cursorPos = buffer.size();
    delete[] indexes;
}

void TextBuffer::undo()
{
    if (listAction->current == nullptr)
    {
        return;
    }

    HistoryManager::Action *actionToUndo = listAction->current->action;

    if (actionToUndo->actionName == "insert")
    {
        buffer.deleteAt(actionToUndo->cursorPos);
        cursorPos = actionToUndo->cursorPos;
    }
    else if (actionToUndo->actionName == "delete")
    {
        buffer.insertAt(actionToUndo->cursorPos, actionToUndo->data);
        cursorPos = actionToUndo->cursorPos + 1;
    }
    else if (actionToUndo->actionName == "move")
    {
        // Undo move: restore previous cursor position (stored in data)
        cursorPos = static_cast<unsigned char>(actionToUndo->data);
    }
    else if (actionToUndo->actionName == "sort")
    {
        cursorPos = actionToUndo->cursorPos;
    }

    listAction->moveCurrentLeft();
}

void TextBuffer::redo()
{
    if (listAction->current == nullptr || listAction->current->next == nullptr)
    {
        return;
    }

    listAction->moveCurrentRight();
    HistoryManager::Action *actionToRedo = listAction->current->action;

    if (actionToRedo->actionName == "insert")
    {
        buffer.insertAt(actionToRedo->cursorPos, actionToRedo->data);
        cursorPos = actionToRedo->cursorPos + 1;
    }
    else if (actionToRedo->actionName == "delete")
    {
        buffer.deleteAt(actionToRedo->cursorPos);
        cursorPos = actionToRedo->cursorPos;
    }
    else if (actionToRedo->actionName == "move")
    {
        // Redo move: restore new cursor position (stored in cursorPos)
        cursorPos = actionToRedo->cursorPos;
    }
    else if (actionToRedo->actionName == "sort")
    {
        sortAscending();
    }
}

// TODO: implement other methods of TextBuffer

// ----------------- HistoryManager -----------------
TextBuffer::HistoryManager::HistoryManager()
{
    // TODO
    this->actionHead = nullptr;
    this->actionTail = nullptr;
    this->current = nullptr;
    this->actionCount = 0;
}

TextBuffer::HistoryManager::~HistoryManager()
{
    // TODO

    Node *curr = actionHead;
    while (curr != nullptr)
    {
        Node *temp = curr;
        curr = curr->next;
        delete temp;
    }
    actionHead = nullptr;
    actionTail = nullptr;
    current = nullptr;
    actionCount = 0;
}

// TODO: implement other methods of HistoryManager

void TextBuffer::HistoryManager::addAction(const string &actionName, int cursorPos, char c)
{
    clearRedoHistory();
    Action *newAction = new Action(actionName, cursorPos, c);
    Node *newNode = new Node(newAction);
    if (actionHead == nullptr)
    {
        actionHead = actionTail = newNode;
    }
    else
    {
        actionTail->next = newNode;
        newNode->prev = actionTail;
        actionTail = newNode;
    }
    current = newNode;
    actionCount++;
}

void TextBuffer::HistoryManager::printHistory() const
{
    string historyStr = "[";
    Node *curr = actionHead;
    while (curr != nullptr)
    {
        historyStr += "(" + curr->action->actionName + ", " + to_string(curr->action->cursorPos) + ", ";
        if (curr->action->data == '\0')
        {
            historyStr += "\\0";
        }
        else
        {
            historyStr += string(1, curr->action->data);
        }
        historyStr += ")";
        if (curr->next != nullptr)
        {
            historyStr += ", ";
        }
        curr = curr->next;
    }
    historyStr += "]";
    cout << historyStr << endl;
}

string *TextBuffer::HistoryManager::getHistoryString() const
{
    string *historyStr = new string("[");
    Node *curr = actionHead;
    while (curr != nullptr)
    {
        *historyStr += "(" + curr->action->actionName + ", " + to_string(curr->action->cursorPos) + ", ";
        if (curr->action->data == '\0')
        {
            *historyStr += "\\0";
        }
        else
        {
            *historyStr += string(1, curr->action->data);
        }
        *historyStr += ")";
        if (curr->next != nullptr)
        {
            *historyStr += ", ";
        }
        curr = curr->next;
    }
    *historyStr += "]";
    return historyStr;
}

int TextBuffer::HistoryManager::size() const
{
    return actionCount;
}

void TextBuffer::HistoryManager::clearRedoHistory()
{
    if (current == nullptr)
    {
        return;
    }
    Node *nodeToDelete = current->next;
    while (nodeToDelete != nullptr)
    {
        Node *temp = nodeToDelete;
        nodeToDelete = nodeToDelete->next;
        delete temp;
        actionCount--;
    }
    current->next = nullptr;
    actionTail = current;
}

// Explicit template instantiation for char, string, int, double, float, and Point
template class DoublyLinkedList<char>;
template class DoublyLinkedList<string>;
template class DoublyLinkedList<int>;
template class DoublyLinkedList<double>;
template class DoublyLinkedList<float>;
template class DoublyLinkedList<Point>;