
#include "TextBuffer.h"

#ifdef _WIN32
#include <crtdbg.h>
#endif

// Color codes
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_PURPLE "\033[35m"
#define COLOR_RESET "\033[0m"

template <typename T>
void assertEqual(const T &actual, const T &expected, int testNum, const string &msg = "")
{
    if (actual == expected)
    {
        cout << "Test " << testNum << ": " << COLOR_GREEN << "Passed" << COLOR_RESET;
        if (!msg.empty())
            cout << " - " << msg;
        cout << endl;
    }
    else
    {
        cout << "Test " << testNum << ": " << COLOR_RED << "Failed" << COLOR_RESET;
        if (!msg.empty())
            cout << " - " << msg;
        cout << "\n  Expected: " << expected << "\n  Actual:   " << actual << endl;
    }
}

void assertEqual(const string &actual, const char *expected, int testNum, const string &msg = "")
{
    assertEqual<string>(actual, string(expected), testNum, msg);
}
void assertEqual(const char *actual, const string &expected, int testNum, const string &msg = "")
{
    assertEqual<string>(string(actual), expected, testNum, msg);
}
void assertEqual(const char *actual, const char *expected, int testNum, const string &msg = "")
{
    assertEqual<string>(string(actual), string(expected), testNum, msg);
}

// ---------------------------------------------------------------------------
// *---------------------------- Test cua thay ------------------------------*
void sample_01(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(3);
    dll.insertAtHead(2);
    dll.insertAtHead(1);
    string result = dll.toString();
    string expected = "[1, 2, 3]";
    assertEqual(result, expected, testNum, "toString");
}

void sample_02(int testNum)
{
    DoublyLinkedList<char> dll;
    dll.insertAtTail('A');
    dll.insertAtTail('B');
    dll.insertAtTail('C');
    int sizeResult = dll.size();
    char getResult = dll.get(1);
    assertEqual(sizeResult, 3, testNum, "size");
    assertEqual(getResult, 'B', testNum, "get(1)");
}

void sample_03(int testNum)
{
    TextBuffer tb;
    tb.insert('a');
    tb.insert('b');
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "ab", testNum, "TextBuffer getContent");
    assertEqual(cursor, 2, testNum, "TextBuffer getCursorPos");
}

void sample_04(int testNum)
{
    TextBuffer tb;
    tb.insert('x');
    tb.insert('y');
    tb.moveCursorLeft();
    tb.insert('z');
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "xzy", testNum, "TextBuffer insert/move");
    assertEqual(cursor, 2, testNum, "TextBuffer getCursorPos after insert/move");
}

void sample_05(int testNum)
{
    TextBuffer::HistoryManager hm;
    hm.addAction("insert", 0, 'a');
    hm.addAction("insert", 1, 'b');
    int size = hm.size();
    assertEqual(size, 2, testNum, "HistoryManager size");
    string *result = hm.getHistoryString();
    assertEqual(*result, "[(insert, 0, a), (insert, 1, b)]", testNum, "HistoryManager getHistoryString");
    delete result;
}

void sample_06(int testNum)
{
    TextBuffer tb;
    tb.insert('a');
    tb.insert('b');
    tb.insert('c');
    bool caught = false;
    try
    {
        tb.moveCursorTo(0);
        tb.moveCursorLeft();
    }
    catch (const cursor_error &e)
    {
        caught = true;
    }
    assertEqual(caught, true, testNum, "TextBuffer cursor_error exception");
}

void sample_07(int testNum)
{
    DoublyLinkedList<char> dll;
    dll.insertAtTail('X');
    dll.insertAtTail('Y');
    dll.insertAtTail('Z');
    bool caught = false;
    try
    {
        dll.get(5);
    }
    catch (const out_of_range &e)
    {
        caught = true;
    }
    assertEqual(caught, true, testNum, "DoublyLinkedList out_of_range exception");
}

// ---------------------------------------------------------------------------
// *----------------------- DoublyLinkedList Tests ---------------------------*

// test insert
void sample_08(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(10);
    dll.insertAtHead(20);
    dll.insertAtHead(5);
    string result = dll.toString();
    string expected = "[5, 20, 10]";
    assertEqual(result, expected, testNum, "Insert at head");
}

void sample_09(int testNum)
{
    DoublyLinkedList<float> dll;
    dll.insertAtHead(1.0);
    dll.insertAtHead(2);
    dll.insertAtHead(3);
    dll.insertAtHead(4.5);
    string result = dll.toString();
    string expected = "[4.5, 3, 2, 1]";
    assertEqual(result, expected, testNum, "Insert at head");
}

void sample_10(int testNum)
{
    DoublyLinkedList<string> dll;
    dll.insertAtTail("Hello");
    dll.insertAtTail("World");
    dll.insertAtTail("!");
    string result = dll.toString();
    string expected = "[Hello, World, !]";
    assertEqual(result, expected, testNum, "Insert at tail");
}

void sample_11(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtTail(100);
    dll.insertAtTail(200);
    dll.insertAtTail(300);
    string result = dll.toString();
    string expected = "[100, 200, 300]";
    assertEqual(result, expected, testNum, "Insert at tail");
}

void sample_12(int testNum)
{
    DoublyLinkedList<double> dll;
    dll.insertAtHead(1.1);
    dll.insertAtTail(2.2);
    dll.insertAtHead(0.5);
    dll.insertAtTail(3.3);
    string result = dll.toString();
    string expected = "[0.5, 1.1, 2.2, 3.3]";
    assertEqual(result, expected, testNum, "Insert at head and tail");
}

void sample_13(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(5);
    dll.insertAtTail(10);
    dll.insertAtHead(1);
    dll.insertAtHead(2);
    dll.insertAtTail(20);
    dll.insertAtTail(30);
    dll.insertAtHead(0);
    string result = dll.toString();
    string expected = "[0, 2, 1, 5, 10, 20, 30]";
    assertEqual(result, expected, testNum, "Insert at head and tail");
}

void sample_14(int testNum)
{
    DoublyLinkedList<char> dll;
    dll.insertAtHead('A');
    dll.insertAtTail('B');
    dll.insertAt(1, 'C');
    string result = dll.toString();
    string expected = "[A, C, B]";
    assertEqual(result, expected, testNum, "Insert at specific index");
}

void sample_15(int testNum)
{
    DoublyLinkedList<string> dll;
    dll.insertAtTail("First");
    dll.insertAtTail("Second");
    dll.insertAt(1, "Middle");
    string result = dll.toString();
    string expected = "[First, Middle, Second]";
    assertEqual(result, expected, testNum, "Insert at specific index");
}

void sample_16(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.insertAt(2, 4);
    dll.insertAt(3, 5);
    dll.insertAt(4, 6);
    dll.insertAt(5, 7);
    dll.insertAt(6, 8);
    dll.insertAt(5, 9);
    string result = dll.toString();
    string expected = "[1, 3, 4, 5, 6, 9, 7, 8, 2]";
    assertEqual(result, expected, testNum, "Insert at specific index");
}

void sample_17(int testNum)
{
    DoublyLinkedList<int> dll;
    bool caught = false;
    try
    {
        dll.insertAt(1, 1); // without head
    }
    catch (const out_of_range &)
    {
        caught = true;
    }
    assertEqual(caught, true, testNum, "Insert at invalid index");
}

void sample_18(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.insertAt(2, 4);
    dll.insertAt(3, 5);
    dll.insertAt(4, 6);
    dll.insertAt(5, 7);
    dll.insertAt(6, 8);
    dll.insertAt(5, 9);
    bool caught = false;
    try
    {
        dll.insertAt(10, 11); // without head
    }
    catch (const out_of_range &)
    {
        caught = true;
    }
    string result = dll.toString();
    assertEqual(caught, true, testNum, "Insert at specific index");
}

void sample_19(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.insertAt(2, 4);
    dll.insertAt(3, 5);
    dll.insertAt(4, 6);
    dll.insertAt(5, 7);
    dll.insertAt(6, 8);
    dll.insertAt(5, 9);
    bool caught = false;
    try
    {
        dll.insertAt(-2, 11); // without head
    }
    catch (const out_of_range &)
    {
        caught = true;
    }
    string result = dll.toString();
    assertEqual(caught, true, testNum, "Insert at specific index");
}

// delete tests
void sample_20(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.deleteAt(1);
    string result = dll.toString();
    string expected = "[1, 2]";
    assertEqual(result, expected, testNum, "Delete at index 1");
}

void sample_21(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.deleteAt(0);
    string result = dll.toString();
    string expected = "[3, 2]";
    assertEqual(result, expected, testNum, "Delete at head");
}

void sample_22(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.deleteAt(2);
    string result = dll.toString();
    string expected = "[1, 3]";
    assertEqual(result, expected, testNum, "Delete at tail");
}

void sample_23(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    bool caught = false;
    try
    {
        dll.deleteAt(5); // out of range
    }
    catch (const out_of_range &)
    {
        caught = true;
    }
    assertEqual(caught, true, testNum, "Delete at invalid index");
}

void sample_24(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    bool caught = false;
    try
    {
        dll.deleteAt(-1); // negative index
    }
    catch (const out_of_range &)
    {
        caught = true;
    }
    assertEqual(caught, true, testNum, "Delete at negative index");
}

// get tests

void sample_25(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    int result = dll.get(1);
    assertEqual(result, 3, testNum, "Get at index 1");
}

void sample_26(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    int result = dll.get(0);
    assertEqual(result, 1, testNum, "Get at head");
}

void sample_27(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    int result = dll.get(2);
    assertEqual(result, 2, testNum, "Get at tail");
}

void sample_28(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    bool caught = false;
    try
    {
        dll.get(5); // out of range
    }
    catch (const out_of_range &)
    {
        caught = true;
    }
    assertEqual(caught, true, testNum, "Get at invalid index");
}

void sample_29(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    bool caught = false;
    try
    {
        dll.get(-1); // negative index
    }
    catch (const out_of_range &)
    {
        caught = true;
    }
    assertEqual(caught, true, testNum, "Get at negative index");
}

// get index tests

void sample_30(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    int index = dll.indexOf(3);
    assertEqual(index, 1, testNum, "Index of 3");
}

void sample_31(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    int index = dll.indexOf(1);
    assertEqual(index, 0, testNum, "Index of 1");
}

void sample_32(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    int index = dll.indexOf(2);
    assertEqual(index, 2, testNum, "Index of 2");
}

void sample_33(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    int index = dll.indexOf(4); // not present
    assertEqual(index, -1, testNum, "Invalid index of 4");
}

void sample_34(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    int index = dll.indexOf(5); // not present
    assertEqual(index, -1, testNum, "Invalid index of 5");
}

// count tests

void sample_35(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    int count = dll.size();
    assertEqual(count, 3, testNum, "Count of elements");
}

void sample_36(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.insertAtTail(4);
    dll.insertAtHead(0);
    dll.insertAt(3, 5);
    dll.insertAt(6, 6);
    int count = dll.size();
    assertEqual(count, 7, testNum, "Count of elements");
}

// contain tests

void sample_37(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    bool contains = dll.contains(2);
    assertEqual(contains, true, testNum, "Contains 2");
}

void sample_38(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    bool contains = dll.contains(4);
    assertEqual(contains, false, testNum, "Contains 4");
}

void sample_39(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    bool contains = dll.contains(1);
    assertEqual(contains, true, testNum, "Contains 1");
}

void sample_40(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    bool contains = dll.contains(3);
    assertEqual(contains, true, testNum, "Contains 3");
}

void sample_41(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    bool contains = dll.contains(5);
    assertEqual(contains, false, testNum, "Contains 5");
}

// reverse tests

void sample_42(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.reverse();
    string result = dll.toString();
    string expected = "[2, 3, 1]";
    assertEqual(result, expected, testNum, "Reverse list");
}

void sample_43(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.insertAtTail(4);
    dll.reverse();
    string result = dll.toString(); // 1 3 2 4 => reversed list: 4 2 3 1
    string expected = "[4, 2, 3, 1]";
    assertEqual(result, expected, testNum, "Reverse list");
}

void sample_44(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.reverse();
    string result = dll.toString();
    string expected = "[1]";
    assertEqual(result, expected, testNum, "Reverse element list");
}

void sample_45(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.reverse(); // empty list
    string result = dll.toString();
    string expected = "[]";
    assertEqual(result, expected, testNum, "Reverse empty list");
}

void sample_46(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.insertAtTail(4);
    dll.insertAtHead(5);
    dll.insertAt(3, 6);
    dll.reverse();
    string result = dll.toString(); // 5 1 3 6 2 4 => reversed list: 4 2 6 3 1 5
    string expected = "[4, 2, 6, 3, 1, 5]";
    assertEqual(result, expected, testNum, "Reverse list");
}

void sample_47(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.reverse(); // empty list
    assertEqual(dll.toString(), "[]", testNum, "Reverse null list");
}

// mixed tests

void sample_48(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.reverse();
    string result = dll.toString();
    string expected = "[2, 3, 1]";
    assertEqual(result, expected, testNum, "Mixed operations");
}

void sample_49(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.deleteAt(0);
    dll.reverse();
    string result = dll.toString();
    string expected = "[2, 3]";
    assertEqual(result, expected, testNum, "Mixed operations");
}

void sample_50(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.insertAtTail(4);
    dll.deleteAt(2);
    dll.reverse();
    string result = dll.toString(); // 1 3 4 => 4 3 1
    string expected = "[4, 3, 1]";
    assertEqual(result, expected, testNum, "Complex mixed operations");
}

void sample_51(int testNum)
{
    DoublyLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtTail(2);
    dll.insertAt(1, 3);
    dll.insertAtTail(4);
    dll.insertAtHead(5);
    dll.insertAt(3, 6);
    dll.insertAt(6, 7);
    dll.reverse();
    // 5 1 3 6 2 4 6 => reversed list: 7 4 8 2 6 3 1 5
    dll.insertAt(2, 8);
    string result = dll.toString();
    string expected = "[7, 4, 8, 2, 6, 3, 1, 5]";
    int size = dll.size();
    int index = dll.indexOf(6);
    assertEqual(result, expected, testNum, "Complex mixed operations");
    assertEqual(size, 8, testNum, "Size");
    assertEqual(index, 4, testNum, "Index");
}

// ---------------------------------------------------------------------------
// *---------------------------- TextBuffer Tests ----------------------------*

// test buffer initialization

void sample_52(int testNum)
{
    TextBuffer tb;
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "", testNum, "TextBuffer empty");
    assertEqual(cursor, 0, testNum, "TextBuffer initial cursor position");
}

// test insert

void sample_53(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "Hello", testNum, "TextBuffer insert");
    assertEqual(cursor, 5, testNum, "TextBuffer cursor position after insert");
}

void sample_54(int testNum)
{
    TextBuffer tb;
    tb.insert('W');
    tb.insert('o');
    tb.insert('r');
    tb.insert('l');
    tb.insert('d');
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "World", testNum, "TextBuffer insert");
    assertEqual(cursor, 5, testNum, "TextBuffer cursor position after insert");
}

void sample_55(int testNum)
{
    TextBuffer tb;
    tb.insert('/');
    tb.insert('#');
    tb.insert('$');
    tb.insert('%');
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "/#$%", testNum, "TextBuffer insert");
    assertEqual(cursor, 4, testNum, "TextBuffer cursor position after insert");
}

// test delete char

void sample_56(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.deleteChar();
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "Hell", testNum, "TextBuffer delete char");
    assertEqual(cursor, 4, testNum, "TextBuffer cursor position after delete");
}

void sample_57(int testNum)
{
    TextBuffer tb;
    tb.insert('W');
    tb.insert('o');
    tb.insert('r');
    tb.insert('l');
    tb.insert('d');
    tb.moveCursorLeft();
    tb.deleteChar();
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "Word", testNum, "TextBuffer delete char");
    assertEqual(cursor, 3, testNum, "TextBuffer cursor position after delete");
}

void sample_58(int testNum)
{
    TextBuffer tb;
    tb.insert('T');
    tb.insert('e');
    tb.insert('s');
    tb.insert('t');
    tb.moveCursorLeft();
    tb.moveCursorLeft();
    tb.deleteChar();
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "Tst", testNum, "TextBuffer delete char");
    assertEqual(cursor, 1, testNum, "TextBuffer cursor position after delete");
}

// test move cursor

void sample_59(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorLeft();
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "Hello", testNum, "TextBuffer move cursor left");
    assertEqual(cursor, 4, testNum, "TextBuffer cursor position after move left");
}

void sample_60(int testNum)
{
    TextBuffer tb;
    tb.insert('W');
    tb.insert('o');
    tb.insert('r');
    tb.insert('l');
    tb.insert('d');
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "World", testNum, "TextBuffer move cursor right");
    // catch cursor error
    bool caught = false;
    try
    {
        tb.moveCursorRight();
    }
    catch (const cursor_error &e)
    {
        caught = true;
    }
    assertEqual(caught, true, testNum, "catch cursor_error on move right");
}

void sample_61(int testNum)
{
    TextBuffer tb;
    tb.insert('T');
    tb.insert('e');
    tb.insert('s');
    tb.insert('t');
    tb.moveCursorLeft();
    tb.moveCursorLeft();
    tb.moveCursorLeft();
    tb.moveCursorLeft();
    bool caught = false;
    try
    {
        tb.moveCursorLeft(); // should throw cursor_error
    }
    catch (const cursor_error &e)
    {
        caught = true;
    }
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "Test", testNum, "TextBuffer move cursor left");
    assertEqual(caught, true, testNum, "catch cursor_error on move left");
}

// test move cursor to

void sample_62(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(2);
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "Hello", testNum, "TextBuffer move cursor to index 2");
    assertEqual(cursor, 2, testNum, "TextBuffer cursor position after move to");
}

void sample_63(int testNum)
{
    TextBuffer tb;
    tb.insert('W');
    tb.insert('o');
    tb.insert('r');
    tb.insert('l');
    tb.insert('d');
    tb.moveCursorTo(4);
    string content = tb.getContent();
    int cursor = tb.getCursorPos();
    assertEqual(content, "World", testNum, "TextBuffer move cursor to index 4");
    assertEqual(cursor, 4, testNum, "TextBuffer cursor position after move to");
}

// find first occurrence of a character

void sample_64(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    int index = tb.findFirstOccurrence('l');
    assertEqual(index, 2, testNum, "TextBuffer find first occurrence");
}

void sample_65(int testNum)
{
    TextBuffer tb;
    tb.insert('W');
    tb.insert('o');
    tb.insert('r');
    tb.insert('l');
    tb.insert('d');
    int index = tb.findFirstOccurrence('o');
    assertEqual(index, 1, testNum, "TextBuffer find first occurrence");
}

// test find all occurrences of a character

void sample_66(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.insert('l');
    int count = 0;
    int *indexes = tb.findAllOccurrences('l', count);
    int expectedCount = 3;
    int expectedIndexes[] = {2, 3, 5};
    bool pass = (count == expectedCount);
    for (int i = 0; i < count && pass; ++i)
    {
        if (indexes[i] != expectedIndexes[i])
            pass = false;
    }
    assertEqual(pass, true, testNum, "TextBuffer findAllOccurrences");
    delete[] indexes;
}

void sample_67(int testNum)
{
    TextBuffer tb;
    tb.insert('W');
    tb.insert('o');
    tb.insert('r');
    tb.insert('l');
    tb.insert('d');
    int count = 0;
    int *indexes = tb.findAllOccurrences('o', count);
    int expectedCount = 1;
    int expectedIndexes[] = {1};
    bool pass = (count == expectedCount);
    for (int i = 0; i < count && pass; ++i)
    {
        if (indexes[i] != expectedIndexes[i])
            pass = false;
    }
    assertEqual(pass, true, testNum, "TextBuffer findAllOccurrences");
    delete[] indexes;
}

// test sort accending of TextBuffer

void sample_68(int testNum)
{
    TextBuffer tb;
    tb.insert('c');
    tb.insert('b');
    tb.insert('a');
    tb.sortAscending();
    string result = tb.getContent();
    string expected = "abc";
    assertEqual(result, expected, testNum, "TextBuffer sort ascending");
}

void sample_69(int testNum)
{
    TextBuffer tb;
    tb.insert('a');
    tb.insert('b');
    tb.insert('c');
    tb.insert('d');
    tb.insert('f');
    tb.insert('D');
    tb.insert('A');
    tb.sortAscending();
    string result = tb.getContent();
    string expected = "AabcDdf";
    assertEqual(result, expected, testNum, "TextBuffer sort ascending");
}

void sample_70(int testNum)
{
    TextBuffer tb;
    tb.insert('z');
    tb.sortAscending();
    string result = tb.getContent();
    string expected = "z";
    assertEqual(result, expected, testNum, "TextBuffer sort ascending");
}

// test delete all occurrences of a character

void sample_71(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.deleteAllOccurrences('l');
    string result = tb.getContent();
    string expected = "Heo";
    assertEqual(result, expected, testNum, "TextBuffer delete all occurrences");
}

void sample_72(int testNum)
{
    TextBuffer tb;
    tb.insert('W');
    tb.insert('o');
    tb.insert('r');
    tb.insert('l');
    tb.insert('d');
    tb.deleteAllOccurrences('o');
    string result = tb.getContent();
    string expected = "Wrld";
    assertEqual(result, expected, testNum, "TextBuffer delete all occurrences");
}

void sample_73(int testNum)
{
    TextBuffer tb;
    tb.insert('a');
    tb.insert('b');
    tb.insert('c');
    tb.insert('d');
    tb.insert('e');
    tb.deleteAllOccurrences('f');
    string result = tb.getContent();
    string expected = "abcde";
    assertEqual(result, expected, testNum, "TextBuffer delete all occurrences");
}

// test undo and redo operations

void sample_74(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.undo();
    string result = tb.getContent();
    string expected = "Hell";
    assertEqual(result, expected, testNum, "TextBuffer undo operation");
}

void sample_75(int testNum)
{
    TextBuffer tb;
    tb.insert('W');
    tb.insert('o');
    tb.insert('r');
    tb.insert('l');
    tb.insert('d');
    tb.undo();
    tb.undo();
    string result = tb.getContent();
    string expected = "Wor";
    assertEqual(result, expected, testNum, "TextBuffer undo operation");
}

void sample_76(int testNum)
{
    TextBuffer tb;
    tb.insert('T');
    tb.insert('e');
    tb.insert('s');
    tb.insert('t');
    tb.undo();
    tb.redo();
    string result = tb.getContent();
    string expected = "Test";
    assertEqual(result, expected, testNum, "TextBuffer redo operation");
}

void sample_77(int testNum)
{
    TextBuffer tb;
    tb.insert('A');
    tb.insert('B');
    tb.insert('C');
    tb.undo();
    tb.undo();
    tb.redo();
    string result = tb.getContent();
    string expected = "AB";
    assertEqual(result, expected, testNum, "TextBuffer undo and redo operations");
}

void sample_78(int testNum)
{
    TextBuffer tb;
    tb.insert('X');
    tb.insert('Y');
    tb.insert('Z');
    tb.undo();
    tb.undo();
    tb.undo();
    string result = tb.getContent();
    string expected = "";
    assertEqual(result, expected, testNum, "TextBuffer undo all operations");
}

void sample_79(int testNum)
{
    TextBuffer tb;
    tb.insert('A');
    tb.insert('B');
    tb.insert('C');
    tb.undo();
    tb.redo();
    tb.redo();
    string result = tb.getContent();
    string expected = "ABC";
    assertEqual(result, expected, testNum, "TextBuffer redo without new insert");
}

void sample_80(int testNum)
{
    TextBuffer tb;
    tb.insert('A');
    tb.insert('B');
    tb.insert('C');
    tb.undo();
    tb.redo();
    tb.redo();
    tb.insert('D');
    string result = tb.getContent();
    string expected = "ABCD";
    assertEqual(result, expected, testNum, "TextBuffer redo after new insert");
}

void sample_81(int testNum)
{
    TextBuffer tb;
    tb.insert('A');
    tb.insert('B');
    tb.insert('C');
    tb.undo();
    tb.undo();
    tb.redo();
    tb.redo();
    string result = tb.getContent();
    string expected = "ABC";
    assertEqual(result, expected, testNum, "TextBuffer redo after undo");
}

// test undo redo with cursor movement pos

void sample_82(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(2);
    tb.undo();
    int cursor = tb.getCursorPos();
    assertEqual(cursor, 5, testNum, "TextBuffer cursor position");
}

void sample_83(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(2);
    tb.undo();
    tb.redo();
    int cursor = tb.getCursorPos();
    assertEqual(cursor, 2, testNum, "TextBuffer cursor position ");
}

void sample_84(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(2);
    tb.undo();
    tb.redo();
    tb.moveCursorTo(4);
    int cursor = tb.getCursorPos();
    assertEqual(cursor, 4, testNum, "TextBuffer cursor position");
}

// test printHistory

void sample_85(int testNum)
{
    TextBuffer::HistoryManager hm;
    hm.addAction("insert", 0, 'A');
    hm.addAction("insert", 1, 'B');
    hm.addAction("insert", 2, 'C');
    hm.addAction("move", 3, 'L');
    hm.addAction("insert", 2, 'X');
    hm.addAction("move", 3, 'R');
    hm.addAction("delete", 4, 'C');
    string *history = hm.getHistoryString();
    string expected = "[(insert, 0, A), (insert, 1, B), (insert, 2, C), (move, 3, L), (insert, 2, X), (move, 3, R), (delete, 4, C)]";
    assertEqual(*history, expected, testNum, "TextBuffer history");
    delete history;
}

void sample_86(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.redo();
    string result = tb.getContent();
    string expected = "Hello";
    assertEqual(result, expected, testNum, "TextBuffer redo operation");
}

void sample_87(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorLeft();
    tb.undo();
    int cursor = tb.getCursorPos();
    assertEqual(cursor, 5, testNum, "TextBuffer cursor position after undo");
}

void sample_88(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorLeft();
    tb.redo();
    int cursor = tb.getCursorPos();
    assertEqual(cursor, 4, testNum, "TextBuffer cursor position after redo");
}

void sample_89(int testNum)
{
    TextBuffer tb;
    tb.insert('A');
    tb.insert('B');
    tb.insert('C');
    tb.moveCursorLeft();
    tb.insert('X');
    tb.moveCursorRight();
    tb.deleteChar();
    tb.undo();
    tb.undo();
    tb.undo();
    tb.redo();
    tb.redo();
    tb.redo();
    string result = tb.getContent();
    string expected = "ABX";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer complex undo/redo");
    assertEqual(cursor, 3, testNum, "TextBuffer cursor position");
}

void sample_90(int testNum)
{
    TextBuffer tb;
    tb.insert('A');
    tb.insert('B');
    tb.insert('C');
    tb.moveCursorLeft();
    tb.insert('X');
    tb.moveCursorRight();
    tb.deleteChar();
    tb.undo();
    tb.undo();
    tb.undo();
    tb.undo();
    tb.undo();
    tb.undo();
    tb.undo();
    tb.undo();
    string result = tb.getContent();
    string expected = "";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer complex undo/redo");
    assertEqual(cursor, 0, testNum, "TextBuffer cursor position");
}

void sample_91(int testNum)
{
    TextBuffer tb;
    tb.insert('A');
    tb.insert('B');
    tb.insert('C');
    tb.moveCursorLeft();
    tb.insert('X');
    tb.moveCursorRight();
    tb.deleteChar();
    tb.redo();
    tb.redo();
    tb.redo();
    tb.redo();
    tb.redo();
    tb.redo();
    tb.redo();
    tb.redo();
    tb.redo();

    string result = tb.getContent();
    string expected = "ABX";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer complex undo/redo");
    assertEqual(cursor, 3, testNum, "TextBuffer cursor position");
}

// test size of historyManager

void sample_92(int testNum)
{
    TextBuffer::HistoryManager hm;
    hm.addAction("insert", 0, 'A');
    hm.addAction("insert", 1, 'B');
    hm.addAction("insert", 2, 'C');
    hm.addAction("move", 3, 'L');
    hm.addAction("insert", 2, 'X');
    hm.addAction("move", 3, 'R');
    hm.addAction("delete", 4, 'C');
    int size = hm.size();
    assertEqual(size, 7, testNum, "TextBuffer history size");
}

// test deleteAllOccurrences with cursor movement

void sample_93(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    // tb.moveCursorTo(2);
    tb.deleteAllOccurrences('l');
    string result = tb.getContent();
    string expected = "Heo";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer delete all occurrences");
    assertEqual(cursor, 0, testNum, "TextBuffer cursor position");
}

void sample_94(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.deleteAllOccurrences('l');
    tb.undo();
    tb.undo();
    tb.undo();
    string result = tb.getContent();
    string expected = "Hell";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer delete all occurrences");
    assertEqual(cursor, 4, testNum, "TextBuffer cursor position");
}

void sample_95(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.deleteAllOccurrences('l');
    tb.undo();
    tb.undo();
    string result = tb.getContent();
    string expected = "Hello";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer delete all occurrences");
    assertEqual(cursor, 4, testNum, "TextBuffer cursor position");
}

void sample_96(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.deleteAllOccurrences('l');
    tb.undo();
    tb.redo();
    string result = tb.getContent();
    string expected = "Heo";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer delete all occurrences");
    assertEqual(cursor, 2, testNum, "TextBuffer cursor position");
}

void sample_97(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.deleteAllOccurrences('f');
    tb.undo();
    tb.redo();
    string result = tb.getContent();
    string expected = "Hello";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer delete all occurrences");
    assertEqual(cursor, 5, testNum, "TextBuffer cursor position");
}

void sample_98(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.deleteChar();
    tb.insert('o');
    tb.deleteChar();
    tb.undo();
    tb.undo();
    tb.undo();
    tb.redo();
    string result = tb.getContent();
    string expected = "Hell";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer delete char and undo");
    assertEqual(cursor, 4, testNum, "TextBuffer cursor position after undo");
}

void sample_99(int testNum)
{
    TextBuffer tb;
    tb.insert('b');
    tb.insert('a');
    tb.insert('n');
    tb.insert('a');
    tb.insert('n');
    tb.insert('a');
    tb.insert('c');
    tb.deleteAllOccurrences('a');
    tb.undo();
    string result = tb.getContent();
    string expected = "bannc";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer deleteAllOccurrences and undo");
    assertEqual(cursor, 2, testNum, "TextBuffer cursor position after undo");
}

void sample_100(int testNum)
{
    TextBuffer tb;
    tb.insert('b');
    tb.insert('a');
    tb.insert('n');
    tb.insert('a');
    tb.insert('n');
    tb.insert('a');
    tb.insert('c');
    tb.deleteAllOccurrences('a');
    tb.undo();
    tb.undo();
    string result = tb.getContent();
    string expected = "bananc";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer deleteAllOccurrences and undo");
    assertEqual(cursor, 4, testNum, "TextBuffer cursor position after undo");
}

void sample_101(int testNum)
{
    TextBuffer tb;
    tb.insert('b');
    tb.insert('a');
    tb.insert('n');
    tb.insert('a');
    tb.insert('n');
    tb.insert('a');
    tb.insert('c');
    tb.deleteAllOccurrences('a');
    tb.undo();
    tb.undo();
    tb.undo();
    tb.undo();
    string result = tb.getContent();
    string expected = "banana";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer deleteAllOccurrences and undo");
    assertEqual(cursor, 6, testNum, "TextBuffer cursor position after undo");
}

void sample_102(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.deleteAllOccurrences('f');
    string result = tb.getContent();
    string expected = "Hello";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer delete all occurrences");
    assertEqual(cursor, 5, testNum, "TextBuffer cursor position");
}

void sample_103(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    string *result = tb.printStringHistory();
    string expected = "[(insert, 0, H), (insert, 1, e), (insert, 2, l), (insert, 3, l), (insert, 4, o)]";
    assertEqual(*result, expected, testNum, "TextBuffer printHistory");
    delete result;
}

void sample_104(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(1);
    tb.deleteChar();
    string *result = tb.printStringHistory();
    string expected = "[(insert, 0, H), (insert, 1, e), (insert, 2, l), (insert, 3, l), (insert, 4, o), (move, 5, J), (delete, 1, H)]";
    assertEqual(*result, expected, testNum, "TextBuffer printHistory");
    delete result;
}

void sample_105(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(1);
    tb.deleteChar();
    tb.moveCursorTo(2);
    tb.moveCursorRight();
    tb.moveCursorLeft();
    tb.moveCursorLeft();
    tb.sortAscending();
    string *result = tb.printStringHistory();
    int cursor = tb.getCursorPos();
    assertEqual(cursor, 0, testNum, "TextBuffer cursor position after undo");
    assertEqual(tb.getContent(), "ello", testNum, "TextBuffer content after undo");
    string expected = "[(insert, 0, H), (insert, 1, e), (insert, 2, l), (insert, 3, l), (insert, 4, o), (move, 5, J), (delete, 1, H), (move, 0, J), (move, 2, R), (move, 3, L), (move, 2, L), (sort, 1, )]";
    assertEqual(*result, expected, testNum, "TextBuffer printHistory after undo");
    delete result;
}

void sample_106(int testNum)
{
    TextBuffer tb;
    tb.insert('X');
    tb.insert('Y');
    tb.insert('Z');
    tb.insert('z');
    tb.insert('y');
    tb.insert('l');
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(1);
    tb.deleteChar();
    tb.moveCursorTo(2);
    tb.moveCursorRight();
    tb.moveCursorLeft();
    tb.moveCursorLeft();
    tb.sortAscending();
    string *result = tb.printStringHistory();
    int cursor = tb.getCursorPos();
    assertEqual(cursor, 0, testNum, "TextBuffer cursor position after undo");
    assertEqual(tb.getContent(), "eHllloYyZz", testNum, "TextBuffer content after undo");
    string expected = "[(insert, 0, X), (insert, 1, Y), (insert, 2, Z), (insert, 3, z), (insert, 4, y), (insert, 5, l), (insert, 6, H), (insert, 7, e), (insert, 8, l), (insert, 9, l), (insert, 10, o), (move, 11, J), (delete, 1, X), (move, 0, J), (move, 2, R), (move, 3, L), (move, 2, L), (sort, 1, )]";
    assertEqual(*result, expected, testNum, "TextBuffer printHistory after undo");
    delete result;
}

void sample_107(int testNum)
{
    TextBuffer tb;
    tb.insert('X');
    tb.insert('Y');
    tb.insert('Z');
    tb.insert('z');
    tb.insert('y');
    tb.insert('l');
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(1);
    tb.deleteChar();
    tb.moveCursorTo(2);
    tb.moveCursorRight();
    tb.moveCursorLeft();
    tb.moveCursorLeft();
    tb.sortAscending();
    tb.deleteAllOccurrences('l');
    tb.moveCursorRight();
    string *result = tb.printStringHistory();
    int cursor = tb.getCursorPos();
    assertEqual(cursor, 1, testNum, "TextBuffer cursor position after undo");
    assertEqual(tb.getContent(), "eHoYyZz", testNum, "TextBuffer content after undo");
    string expected = "[(insert, 0, X), (insert, 1, Y), (insert, 2, Z), (insert, 3, z), (insert, 4, y), (insert, 5, l), (insert, 6, H), (insert, 7, e), (insert, 8, l), (insert, 9, l), (insert, 10, o), (move, 11, J), (delete, 1, X), (move, 0, J), (move, 2, R), (move, 3, L), (move, 2, L), (sort, 1, ), (delete, 4, l), (delete, 3, l), (delete, 2, l), (move, 0, R)]";
    assertEqual(*result, expected, testNum, "TextBuffer printHistory after undo");
    delete result;
}

void sample_108(int testNum)
{
    TextBuffer tb;
    tb.insert('X');
    tb.insert('Y');
    tb.insert('Z');
    tb.insert('z');
    tb.insert('y');
    tb.insert('l');
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(1);
    tb.deleteChar();
    tb.moveCursorTo(2);
    tb.moveCursorRight();
    tb.moveCursorLeft();
    tb.moveCursorLeft();
    tb.sortAscending();
    tb.deleteAllOccurrences('l');
    tb.moveCursorRight();
    int index = tb.findFirstOccurrence('l');
    string *result = tb.printStringHistory();
    int cursor = tb.getCursorPos();
    assertEqual(index, -1, testNum, "TextBuffer find first occurrence after undo");
    assertEqual(cursor, 1, testNum, "TextBuffer cursor position after undo");
    assertEqual(tb.getContent(), "eHoYyZz", testNum, "TextBuffer content after undo");
    string expected = "[(insert, 0, X), (insert, 1, Y), (insert, 2, Z), (insert, 3, z), (insert, 4, y), (insert, 5, l), (insert, 6, H), (insert, 7, e), (insert, 8, l), (insert, 9, l), (insert, 10, o), (move, 11, J), (delete, 1, X), (move, 0, J), (move, 2, R), (move, 3, L), (move, 2, L), (sort, 1, ), (delete, 4, l), (delete, 3, l), (delete, 2, l), (move, 0, R)]";
    assertEqual(*result, expected, testNum, "TextBuffer printHistory after undo");
    delete result;
}

void sample_109(int testNum)
{
    TextBuffer tb;
    tb.insert('X');
    tb.insert('Y');
    tb.insert('Z');
    tb.insert('z');
    tb.insert('y');
    tb.insert('l');
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    int index = tb.findFirstOccurrence('l');
    tb.sortAscending();
    int index3 = tb.findFirstOccurrence('l');
    string content = tb.getContent();
    tb.deleteAllOccurrences('l');
    int index2 = tb.findFirstOccurrence('l');
    string result = to_string(index) + ", " + to_string(index2) + ", " + to_string(index3);
    string expected = "5, -1, 2";
    assertEqual(content, "eHllloXYyZz", testNum, "TextBuffer content");
    assertEqual(result, expected, testNum, "TextBuffer find first occurrence after deleteAllOccurrences");
}

void sample_110(int testNum)
{
    TextBuffer tb;
    tb.insert('X');
    tb.insert('Y');
    tb.insert('Z');
    tb.undo();
    tb.undo();
    tb.undo();
    tb.undo();
    string result = tb.getContent();
    string expected = "";
    assertEqual(result, expected, testNum, "TextBuffer undo all operations");
}

void sample_111(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(0);
    bool caught = false;
    try
    {
        tb.deleteChar();
    }
    catch (const cursor_error &e)
    {
        caught = true;
    }
    assertEqual(caught, true, testNum, "TextBuffer move cursor left on empty buffer");
}

void sample_112(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(2);
    tb.deleteAllOccurrences('f');
    string result = tb.getContent();
    string expected = "Hello";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer delete all occurrences");
    assertEqual(cursor, 2, testNum, "TextBuffer cursor position");
}

void sample_113(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.undo();
    tb.redo();
    tb.undo();
    string *result = tb.printStringHistory();
    string expected = "[(insert, 0, H), (insert, 1, e), (insert, 2, l), (insert, 3, l), (insert, 4, o)]";

    assertEqual(*result, expected, testNum, "TextBuffer printHistory after undo/redo");
    delete result;
}

void sample_114(int testNum)
{
    TextBuffer tb;
    tb.insert('c');
    tb.insert('b');
    tb.insert('a');
    tb.sortAscending();
    string result_after_sort = tb.getContent();
    tb.undo();
    string result = tb.getContent();
    string expected = "cba";
    assertEqual(result_after_sort, "abc", testNum, "TextBuffer sort ascending");
    assertEqual(result, expected, testNum, "TextBuffer sort ascending");
    string *history = tb.printStringHistory();
    cout << *history << endl;
    delete history;
}

void sample_115(int testNum)
{
    TextBuffer tb;
    tb.insert('c');
    tb.insert('b');
    tb.insert('a');
    tb.insert('d');
    tb.insert('F');
    tb.insert('E');
    tb.insert('D');
    tb.insert('C');
    tb.insert('B');
    tb.insert('A');
    tb.insert('1');
    tb.insert('2');
    tb.insert('5');
    tb.insert('4');
    tb.insert('!');
    tb.insert('@');
    tb.insert('#');
    tb.insert('*');
    tb.insert('^');
    tb.sortAscending();
    string result = tb.getContent();
    string expected = "!#*1245@^AaBbCcDdEF";
    assertEqual(result, expected, testNum, "TextBuffer sort ascending with special characters");
}

void sample_116(int testNum)
{
    TextBuffer tb;
    tb.insert('c');
    tb.insert('b');
    tb.insert('a');
    tb.insert('d');
    tb.insert('F');
    tb.insert('E');
    tb.insert('D');
    tb.sortAscending();
    tb.insert('C');
    int cursor = tb.getCursorPos();
    string result = tb.getContent();
    string expected = "CabcDdEF";
    assertEqual(result, expected, testNum, "TextBuffer sort ascending with insert after sort");
    assertEqual(cursor, 1, testNum, "TextBuffer cursor position after insert");
}

void sample_117(int testNum)
{
    TextBuffer tb;
    tb.insert('c');
    tb.insert('b');
    tb.insert('a');
    tb.insert('d');
    tb.insert('F');
    tb.insert('E');
    tb.insert('D');
    tb.sortAscending();
    tb.moveCursorTo(4);
    tb.sortAscending();
    int cursor = tb.getCursorPos();
    string result = tb.getContent();
    string expected = "abcDdEF";
    assertEqual(result, expected, testNum, "TextBuffer sort ascending with insert after sort");
    assertEqual(cursor, 0, testNum, "TextBuffer cursor position after insert");
}

void sample_118(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(2);
    tb.undo();
    tb.insert('X');
    tb.redo();
    string result = tb.getContent();
    string expected = "HelloX";
    int cursor = tb.getCursorPos();
    assertEqual(result, expected, testNum, "TextBuffer undo and insert after undo");
    assertEqual(cursor, 6, testNum, "TextBuffer cursor position after insert");
}

void sample_119(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(2);
    tb.undo();
    tb.moveCursorLeft();
    tb.undo();
    tb.redo();
    tb.redo();
    int cursor = tb.getCursorPos();
    assertEqual(cursor, 4, testNum, "TextBuffer cursor position after move");
}

void sample_120(int testNum)
{
    TextBuffer buf;
    buf.insert('a');
    buf.insert('b');
    EXPECT_EQ(buf.getContent(), "ab");
    EXPECT_EQ(buf.getCursorPos(), 2);

    buf.undo();
    EXPECT_EQ(buf.getContent(), "a");
    EXPECT_EQ(buf.getCursorPos(), 1);

    buf.undo();
    EXPECT_EQ(buf.getContent(), "");
    EXPECT_EQ(buf.getCursorPos(), 0);
}

void sample_121(int testNum)
{
    TextBuffer buf;
    buf.insert('x');
    buf.insert('y');
    buf.insert('z');     // xyz
    buf.moveCursorTo(2); // cursor giữa x và y
    EXPECT_EQ(buf.getCursorPos(), 2);

    buf.deleteChar(); // xz
    EXPECT_EQ(buf.getContent(), "xz");
    EXPECT_EQ(buf.getCursorPos(), 1);

    buf.undo(); // undo delete → khôi phục y
    EXPECT_EQ(buf.getContent(), "xyz");
    EXPECT_EQ(buf.getCursorPos(), 2); // cursor sau 'y'
}

void sample_122(int testNum)
{
    TextBuffer buf;
    buf.insert('a');
    buf.insert('b');
    buf.insert('c');     // abc
    buf.moveCursorTo(3); // sau 'c'
    EXPECT_EQ(buf.getCursorPos(), 3);

    buf.moveCursorLeft(); // cursor: 2
    EXPECT_EQ(buf.getCursorPos(), 2);

    buf.undo(); // quay lại 3
    EXPECT_EQ(buf.getCursorPos(), 3);
}

void sample_123(int testNum)
{
    TextBuffer buf;
    buf.insert('1');
    buf.insert('2');
    buf.insert('3');     // 123
    buf.moveCursorTo(1); // giữa 1 và 2
    EXPECT_EQ(buf.getCursorPos(), 1);

    buf.moveCursorRight(); // cursor: 2
    EXPECT_EQ(buf.getCursorPos(), 2);

    buf.undo(); // quay lại 1
    EXPECT_EQ(buf.getCursorPos(), 1);
}

void sample_124(int testNum)
{
    TextBuffer buf;
    buf.insert('x');
    buf.insert('y');
    buf.insert('z'); // xyz

    buf.moveCursorTo(0);
    EXPECT_EQ(buf.getCursorPos(), 0);

    buf.moveCursorTo(2);
    EXPECT_EQ(buf.getCursorPos(), 2);

    buf.undo();
    EXPECT_EQ(buf.getCursorPos(), 0);
}

void sample_125(int testNum)
{
    TextBuffer buf;
    buf.insert('c');
    buf.insert('a');
    buf.insert('b');
    buf.sortAscending();
    EXPECT_EQ(buf.getContent(), "abc");
    EXPECT_EQ(buf.getCursorPos(), 0);
}

void sample_126(int testNum)
{
    TextBuffer buf;
    buf.insert('b');
    buf.insert('A');
    buf.insert('a');
    buf.insert('B');
    buf.sortAscending();
    EXPECT_EQ(buf.getContent(), "AaBb");
}

void sample_127(int testNum)
{
    TextBuffer buf;
    buf.insert('z');
    buf.insert('a');
    buf.insert('z');
    buf.insert('a');
    buf.insert('m');
    buf.sortAscending();
    EXPECT_EQ(buf.getContent(), "aamzz");
}

void sample_128(int testNum)
{
    TextBuffer buf;
    std::string input = "zAbYyBaaCcZxXxMmNnOoPp";
    for (char ch : input)
    {
        buf.insert(ch);
    }

    buf.sortAscending();

    EXPECT_EQ(buf.getContent(), "AaaBbCcMmNnOoPpXxxYyZz");
}

void sample_129(int testNum)
{
    TextBuffer buf;
    buf.insert('a');
    buf.insert('b');
    buf.undo();
    buf.undo();

    EXPECT_EQ(buf.getContent(), "");
    EXPECT_EQ(buf.getCursorPos(), 0);

    buf.redo();
    EXPECT_EQ(buf.getContent(), "a");
    EXPECT_EQ(buf.getCursorPos(), 1);

    buf.redo();
    EXPECT_EQ(buf.getContent(), "ab");
    EXPECT_EQ(buf.getCursorPos(), 2);
}

void sample_130(int testNum)
{
    TextBuffer buf;
    buf.insert('x');
    buf.insert('y');
    buf.insert('z');     // xyz
    buf.moveCursorTo(2); // cursor giữa x và y
    buf.deleteChar();    // xz

    EXPECT_EQ(buf.getContent(), "xz");
    EXPECT_EQ(buf.getCursorPos(), 1);
    buf.undo(); // xyz

    EXPECT_EQ(buf.getContent(), "xyz");
    EXPECT_EQ(buf.getCursorPos(), 2);

    buf.redo(); // xz
    EXPECT_EQ(buf.getContent(), "xz");
    EXPECT_EQ(buf.getCursorPos(), 1);
}

void sample_131(int testNum)
{
    TextBuffer buf;
    buf.insert('a');
    buf.insert('b');
    buf.insert('c');      // abc
    buf.moveCursorTo(3);  // sau 'c'
    buf.moveCursorLeft(); // cursor: 2
    buf.undo();           // cursor: 3

    EXPECT_EQ(buf.getCursorPos(), 3);

    buf.redo(); // quay lại 2
    EXPECT_EQ(buf.getCursorPos(), 2);
}

void sample_132(int testNum)
{
    TextBuffer buf;
    buf.insert('1');
    buf.insert('2');
    buf.insert('3');       // 123
    buf.moveCursorTo(1);   // giữa 1 và 2
    buf.moveCursorRight(); // cursor: 2
    buf.undo();            // cursor: 1

    EXPECT_EQ(buf.getCursorPos(), 1);

    buf.redo(); // quay lại 2
    EXPECT_EQ(buf.getCursorPos(), 2);
}

void sample_133(int testNum)
{
    TextBuffer buf;
    buf.insert('x');
    buf.insert('y');
    buf.insert('z'); // xyz

    buf.moveCursorTo(0); // cursor: 3
    buf.moveCursorTo(2); // cursor: 0
    buf.undo();

    EXPECT_EQ(buf.getCursorPos(), 0); // cursor: 0

    buf.redo(); // cursor: 2
    EXPECT_EQ(buf.getCursorPos(), 2);
}

void sample_134(int testNum)
{
    TextBuffer buf;

    // Step 1: insert('A')
    buf.insert('A');
    EXPECT_EQ(buf.getContent(), "A");
    EXPECT_EQ(buf.getCursorPos(), 1);

    // Step 2: insert('B')
    buf.insert('B');
    EXPECT_EQ(buf.getContent(), "AB");
    EXPECT_EQ(buf.getCursorPos(), 2);

    // Step 3: insert('C')
    buf.insert('C');
    EXPECT_EQ(buf.getContent(), "ABC");
    EXPECT_EQ(buf.getCursorPos(), 3);

    // Step 4: moveCursorLeft()
    buf.moveCursorLeft();
    EXPECT_EQ(buf.getContent(), "ABC");
    EXPECT_EQ(buf.getCursorPos(), 2); // AB|C

    // Step 5: insert('X')
    buf.insert('X');
    EXPECT_EQ(buf.getContent(), "ABXC");
    EXPECT_EQ(buf.getCursorPos(), 3); // ABX|C

    // Step 6: moveCursorRight()
    buf.moveCursorRight();
    EXPECT_EQ(buf.getContent(), "ABXC");
    EXPECT_EQ(buf.getCursorPos(), 4); // ABXC|

    // Step 7: deleteChar() (delete 'C')
    buf.deleteChar();
    EXPECT_EQ(buf.getContent(), "ABX");
    EXPECT_EQ(buf.getCursorPos(), 3); // ABX|

    // Step 8: undo() - restore C
    buf.undo();
    EXPECT_EQ(buf.getContent(), "ABXC");
    EXPECT_EQ(buf.getCursorPos(), 4); // ABXC|

    // Step 9: undo() - moveCursorLeft()
    buf.undo();
    EXPECT_EQ(buf.getContent(), "ABXC");
    EXPECT_EQ(buf.getCursorPos(), 3); // ABX|C

    // Step 10: undo() - remove 'X'
    buf.undo();
    EXPECT_EQ(buf.getContent(), "ABC");
    EXPECT_EQ(buf.getCursorPos(), 2); // AB|C

    // Step 11: redo() - insert 'X'
    buf.redo();
    EXPECT_EQ(buf.getContent(), "ABXC");
    EXPECT_EQ(buf.getCursorPos(), 3); // ABX|C

    // Step 12: redo() - moveCursorRight()
    buf.redo();
    EXPECT_EQ(buf.getContent(), "ABXC");
    EXPECT_EQ(buf.getCursorPos(), 4); // ABXC|

    // Step 13: redo() - deleteChar() 'C'
    buf.redo();
    EXPECT_EQ(buf.getContent(), "ABX");
    EXPECT_EQ(buf.getCursorPos(), 3); // ABX|
}

void sample_135(int testNum)
{
    TextBuffer buf;

    buf.insert('A'); // A|
    buf.insert('B'); // AB|
    buf.insert('C'); // ABC|

    buf.undo(); // AB| (undo C)
    buf.undo(); // A|  (undo B)

    buf.insert('X'); // AX| (redo stack phải bị xóa)

    buf.redo(); // redo stack rỗng -> không làm gì

    EXPECT_EQ(buf.getContent(), "AX");
    EXPECT_EQ(buf.getCursorPos(), 2);
}

void sample_136(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.undo();
    tb.undo();
    tb.redo();
    int cursor = tb.getCursorPos();
    string result = tb.getContent();
    assertEqual(result, "H", testNum, "TextBuffer content");
    assertEqual(cursor, 1, testNum, "TextBuffer cursor position");
}

void sample_137(int testNum)
{
    TextBuffer buf;

    buf.insert('a');
    buf.insert('b');
    EXPECT_EQ(buf.getContent(), "ab");

    buf.moveCursorTo(1);
    buf.insert('x');
    EXPECT_EQ(buf.getContent(), "axb");
}

void sample_138(int testNum)
{
    TextBuffer buf;
    buf.insert('a');
    buf.insert('b');
    buf.insert('c');
    buf.moveCursorTo(2); // cursor giữa b và c
    buf.deleteChar();
    EXPECT_EQ(buf.getContent(), "ac");

    buf.moveCursorTo(1);
    buf.deleteChar();
    EXPECT_EQ(buf.getContent(), "c");
}

void sample_139(int testNum)
{
    TextBuffer buf;
    buf.insert('x');
    buf.insert('y');
    buf.insert('z');
    buf.moveCursorTo(3); // cursor sau z

    buf.moveCursorLeft(); // -> 2
    EXPECT_EQ(buf.getCursorPos(), 2);
    buf.moveCursorRight(); // -> 3
    EXPECT_EQ(buf.getCursorPos(), 3);
}

void sample_140(int testNum)
{
    TextBuffer buf;
    buf.insert('a');
    buf.insert('b');
    buf.insert('c');
    buf.moveCursorTo(1);
    EXPECT_EQ(buf.getCursorPos(), 1);

    buf.moveCursorTo(3);
    EXPECT_EQ(buf.getCursorPos(), 3);
}

void sample_141(int testNum)
{
    TextBuffer buf;
    EXPECT_EQ(buf.getContent(), "");

    buf.insert('x');
    buf.insert('y');
    buf.insert('z');
    EXPECT_EQ(buf.getContent(), "xyz");
}

void sample_142(int testNum)
{
    TextBuffer buf;
    EXPECT_EQ(buf.getCursorPos(), 0);

    buf.insert('a');
    EXPECT_EQ(buf.getCursorPos(), 1);
}

void sample_143(int testNum)
{
    TextBuffer buf;
    buf.insert('a');
    buf.insert('b');
    buf.insert('a');
    buf.insert('c');

    EXPECT_EQ(buf.findFirstOccurrence('a'), 0);
    EXPECT_EQ(buf.findFirstOccurrence('z'), -1);
}

void sample_144(int testNum)
{
    TextBuffer buf;
    buf.insert('x');
    buf.insert('a');
    buf.insert('b');
    buf.insert('a');
    buf.insert('x');

    int count = 0;
    int *result = buf.findAllOccurrences('a', count);
    EXPECT_EQ(count, 2);
    EXPECT_EQ(result[0], 1)
    EXPECT_EQ(result[1], 3);
    delete[] result;

    int count2 = 0;
    int *result2 = buf.findAllOccurrences('z', count2);
    EXPECT_EQ(count2, 0);
    delete[] result2;
}

void sample_145(int testNum)
{
    TextBuffer buf;
    buf.insert('a');
    buf.insert('b');
    buf.insert('c');
    buf.moveCursorTo(0);

    try
    {
        buf.deleteChar();
        throw std::runtime_error("Expected cursor_error not thrown");
    }
    catch (const cursor_error &e)
    {
        EXPECT_EQ(std::string(e.what()), "Cursor error!");
    }
}

void sample_146(int testNum)
{
    TextBuffer buf;
    buf.insert('a');
    buf.insert('b');
    buf.insert('c');

    try
    {
        buf.moveCursorRight();
        throw std::runtime_error("Expected cursor_error not thrown");
    }
    catch (const cursor_error &e)
    {
        EXPECT_EQ(std::string(e.what()), "Cursor error!");
    }
}

void sample_147(int testNum)
{
    TextBuffer buf;
    buf.insert('a');
    buf.insert('b');
    buf.insert('a');
    buf.insert('c');
    buf.insert('a');

    buf.deleteAllOccurrences('a');

    EXPECT_EQ(buf.getContent(), "bc");
}

void sample_148(int testNum)
{
    TextBuffer buf;
    buf.insert('x');
    buf.insert('y');
    buf.insert('z');

    buf.deleteAllOccurrences('a');

    EXPECT_EQ(buf.getContent(), "xyz");
}

void sample_149(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtHead(10);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), 10);
}

void sample_150(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(20);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), 20);
}

void sample_151(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(3);
    list.insertAt(1, 2); // insert in the middle
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 2);
    EXPECT_EQ(list.get(2), 3);
}

void sample_152(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.insertAt(0, 1); // insert at beginning
    EXPECT_EQ(list.get(0), 1);
}

void sample_153(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAt(2, 3); // insert at end
    EXPECT_EQ(list.get(2), 3);
}

void sample_154(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtHead(2);
    list.insertAtTail(4);
    list.insertAt(1, 3); // between 2 and 4
    EXPECT_EQ(list.get(0), 2);
    EXPECT_EQ(list.get(1), 3);
    EXPECT_EQ(list.get(2), 4);
}

void sample_155(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtHead(3);
    list.insertAtHead(2);
    list.insertAtHead(1);
    list.insertAt(1, 9); // 1, 9, 2, 3
    EXPECT_EQ(list.get(1), 9);
}

void sample_156(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertAt(0, 5); // at head
    EXPECT_EQ(list.get(0), 5);
}

void sample_157(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(100);
    list.insertAtHead(50); // becomes head
    list.insertAt(1, 75);  // between 50 and 100
    EXPECT_EQ(list.get(0), 50);
    EXPECT_EQ(list.get(1), 75);
    EXPECT_EQ(list.get(2), 100);
}

void sample_158(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtHead(3);
    list.insertAtTail(6);
    list.insertAt(1, 4);
    list.insertAt(2, 5);
    list.insertAt(0, 2);
    list.insertAt(0, 1);
    // Final: 1 2 3 4 5 6
    for (int i = 0; i < 6; ++i)
        EXPECT_EQ(list.get(i), i + 1);
}

void sample_159(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    try
    {
        list.insertAt(-1, 100);
        throw std::runtime_error("Expected std::out_of_range not thrown");
    }
    catch (const std::out_of_range &e)
    {
        EXPECT_EQ(std::string(e.what()), "Index is invalid!");
    }
}

void sample_160(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    try
    {
        list.insertAt(2, 100); // size = 1, index = 2 → invalid
        throw std::runtime_error("Expected std::out_of_range not thrown");
    }
    catch (const std::out_of_range &e)
    {
        EXPECT_EQ(std::string(e.what()), "Index is invalid!");
    }
}

void sample_161(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAt(0, 1); // hợp lệ vì list đang rỗng (size = 0)
    list.insertAt(1, 3); // chèn tại cuối (index = size hiện tại = 1)
    list.insertAt(1, 2); // chèn vào giữa: 1, 2, 3
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 2);
    EXPECT_EQ(list.get(2), 3);
}

void sample_162(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.deleteAt(0);
    EXPECT_EQ(list.get(0), 2);
    EXPECT_EQ(list.size(), 2);
}

void sample_163(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.deleteAt(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(1), 20);
}

void sample_164(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(5);
    list.insertAtTail(6);
    list.insertAtTail(7);
    list.deleteAt(1);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(1), 7);
}

void sample_165(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(42);
    list.deleteAt(0);
    EXPECT_EQ(list.size(), 0);
}

void sample_166(int testNum)
{
    DoublyLinkedList<int> list;
    for (int i = 0; i < 5; ++i)
        list.insertAtTail(i + 1); // 1 2 3 4 5
    list.deleteAt(0);             // 2 3 4 5
    list.deleteAt(1);             // 2 4 5
    list.deleteAt(2);             // 2 4
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(0), 2);
    EXPECT_EQ(list.get(1), 4);
}

void sample_167(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    try
    {
        list.deleteAt(-1);
        throw std::runtime_error("Expected std::out_of_range not thrown");
    }
    catch (const std::out_of_range &e)
    {
        EXPECT_EQ(std::string(e.what()), "Index is invalid!");
    }
}

void sample_168(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    try
    {
        list.deleteAt(5);
        throw std::runtime_error("Expected std::out_of_range not thrown");
    }
    catch (const std::out_of_range &e)
    {
        EXPECT_EQ(std::string(e.what()), "Index is invalid!");
    }
}
void sample_169(int testNum)
{
    DoublyLinkedList<int> list;
    list.insertAtHead(2); // 2
    list.insertAtTail(4); // 2 4
    list.insertAt(1, 3);  // 2 3 4
    list.deleteAt(1);     // 2 4
    EXPECT_EQ(list.get(1), 4);
    EXPECT_EQ(list.size(), 2);
}

void sample_170(int testNum)
{
    DoublyLinkedList<int> list;
    for (int i = 0; i < 5; ++i)
        list.insertAtTail(i); // 0 1 2 3 4
    for (int i = 0; i < 5; ++i)
        list.deleteAt(0); // empty
    EXPECT_EQ(list.size(), 0);
}

void sample_171(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.deleteChar();
    tb.sortAscending();
    string *result = tb.printStringHistory();
    string expected = "[(insert, 0, H), (insert, 1, e), (insert, 2, l), (delete, 3, l), (sort, 2, )]";
    assertEqual(*result, expected, testNum, "TextBuffer printHistory after sort");
    delete result;
}

void sample_172(int testNum)
{
    TextBuffer tb;
    tb.insert('A');
    tb.insert('B');
    tb.insert('C');
    tb.undo();
    tb.moveCursorLeft();
    tb.redo();
    string result = tb.getContent();
    int cursor = tb.getCursorPos();
    string expected = "AB";
    assertEqual(result, expected, testNum, "TextBuffer deleteChar at cursor position");
    assertEqual(cursor, 1, testNum, "TextBuffer cursor position after redo");
}

void sample_173(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.sortAscending();
    tb.undo();
    int cursor = tb.getCursorPos();
    string result = tb.getContent();
    string expected = "Hello";
    assertEqual(result, expected, testNum, "TextBuffer content after undo sort");
    assertEqual(cursor, 5, testNum, "TextBuffer cursor position after undo sort");
}

void sample_174(int testNum)
{
    TextBuffer tb;
    tb.insert('X');
    tb.insert('Y');
    tb.insert('Z');
    tb.insert('z');
    tb.insert('y');
    tb.insert('l');
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.moveCursorTo(1);
    tb.deleteChar();
    tb.moveCursorTo(2);
    tb.moveCursorRight();
    tb.moveCursorLeft();
    tb.moveCursorLeft();
    tb.sortAscending();
    tb.undo();
    int cursor_after = tb.getCursorPos();
    string result_after = tb.getContent();
    tb.redo();
    tb.deleteAllOccurrences('l');
    tb.moveCursorTo(3);
    int index = tb.findFirstOccurrence('l');
    string *result = tb.printStringHistory();
    tb.sortAscending();
    int cursor = tb.getCursorPos();
    assertEqual(cursor_after, 1, testNum, "TextBuffer cursor position after undo sort");
    assertEqual(result_after, "YZzylHello", testNum, "TextBuffer content after undo sort");
    assertEqual(index, -1, testNum, "TextBuffer find first occurrence");
    assertEqual(cursor, 0, testNum, "TextBuffer cursor position after undo");
    assertEqual(tb.getContent(), "eHoYyZz", testNum, "TextBuffer content after undo");
    string expected = "[(insert, 0, X), (insert, 1, Y), (insert, 2, Z), (insert, 3, z), (insert, 4, y), (insert, 5, l), (insert, 6, H), (insert, 7, e), (insert, 8, l), (insert, 9, l), (insert, 10, o), (move, 11, J), (delete, 1, X), (move, 0, J), (move, 2, R), (move, 3, L), (move, 2, L), (sort, 1, ), (delete, 4, l), (delete, 3, l), (delete, 2, l), (move, 0, J)]";
    assertEqual(*result, expected, testNum, "TextBuffer printHistory after undo");
    string expected_2 = "[(insert, 0, X), (insert, 1, Y), (insert, 2, Z), (insert, 3, z), (insert, 4, y), (insert, 5, l), (insert, 6, H), (insert, 7, e), (insert, 8, l), (insert, 9, l), (insert, 10, o), (move, 11, J), (delete, 1, X), (move, 0, J), (move, 2, R), (move, 3, L), (move, 2, L), (sort, 1, ), (delete, 4, l), (delete, 3, l), (delete, 2, l), (move, 0, J), (sort, 3, )]";
    assertEqual(*tb.printStringHistory(), expected_2, testNum, "TextBuffer printHistory after sort");
    delete result;
}

void sample_175(int testNum)
{
    TextBuffer tb;
    tb.insert('H');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.deleteChar();
    tb.moveCursorTo(2);
    tb.deleteChar();
    string* result = tb.printStringHistory();
    string expected = "[(insert, 0, H), (insert, 1, e), (insert, 2, l), (insert, 3, l), (insert, 4, o), (delete, 5, o), (move, 4, J), (delete, 2, e)]";
    int cursor = tb.getCursorPos();
    string expected_2 = "Hll";
    assertEqual(cursor, 1, testNum, "TextBuffer cursor position after delete char");
    assertEqual(tb.getContent(), expected_2, testNum, "TextBuffer content after delete char");
    assertEqual(*result, expected, testNum, "TextBuffer printHistory after delete char");
    delete result;
}

// ---------------------------------------------------- //

void run_tests()
{
    sample_01(1);
    sample_02(2);
    sample_03(3);
    sample_04(4);
    sample_05(5);
    sample_06(6);
    sample_07(7);
    sample_08(8);
    sample_09(9);
    sample_10(10);
    sample_11(11);
    sample_12(12);
    sample_13(13);
    sample_14(14);
    sample_15(15);
    sample_16(16);
    sample_17(17);
    sample_18(18);
    sample_19(19);
    sample_20(20);
    sample_21(21);
    sample_22(22);
    sample_23(23);
    sample_24(24);
    sample_25(25);
    sample_26(26);
    sample_27(27);
    sample_28(28);
    sample_29(29);
    sample_30(30);
    sample_31(31);
    sample_32(32);
    sample_33(33);
    sample_34(34);
    sample_35(35);
    sample_36(36);
    sample_37(37);
    sample_38(38);
    sample_39(39);
    sample_40(40);
    sample_41(41);
    sample_42(42);
    sample_43(43);
    sample_44(44);
    sample_45(45);
    sample_46(46);
    sample_47(47);
    sample_48(48);
    sample_49(49);
    sample_50(50);
    sample_51(51);
    sample_52(52);
    sample_53(53);
    sample_54(54);
    sample_55(55);
    sample_56(56);
    sample_57(57);
    sample_58(58);
    sample_59(59);
    sample_60(60);
    sample_61(61);
    sample_62(62);
    sample_63(63);
    sample_64(64);
    sample_65(65);
    sample_66(66);
    sample_67(67);
    sample_68(68);
    sample_69(69);
    sample_70(70);
    sample_71(71);
    sample_72(72);
    sample_73(73);
    sample_74(74);
    sample_75(75);
    sample_76(76);
    sample_77(77);
    sample_78(78);
    sample_79(79);
    sample_80(80);
    sample_81(81);
    sample_82(82);
    sample_83(83);
    sample_84(84);
    sample_85(85);
    sample_86(86);
    sample_87(87);
    sample_88(88);
    sample_89(89);
    sample_90(90);
    sample_91(91);
    sample_92(92);
    sample_93(93);
    sample_94(94);
    sample_95(95);
    sample_96(96);
    sample_97(97);
    sample_98(98);
    sample_99(99);
    sample_100(100);
    sample_101(101);
    sample_102(102);
    sample_103(103);
    sample_104(104);
    sample_105(105);
    sample_106(106);
    sample_107(107);
    sample_108(108);
    sample_109(109);
    sample_110(110);
    sample_111(111);
    sample_112(112);
    sample_113(113);
    sample_114(114);
    sample_115(115);
    sample_116(116);
    sample_117(117);
    sample_118(118);
    sample_119(119);
    cout << COLOR_PURPLE << "Running additional tests from VT..." << COLOR_RESET << endl;
    sample_120(120);
    sample_121(121);
    sample_122(122);
    sample_123(123);
    sample_124(124);
    sample_125(125);
    sample_126(126);
    sample_127(127);
    sample_128(128);
    sample_129(129);
    sample_130(130);
    sample_131(131);
    sample_132(132);
    sample_133(133);
    sample_134(134);
    sample_135(135);
    sample_136(136);
    sample_137(137);
    sample_138(138);
    sample_139(139);
    sample_140(140);
    sample_141(141);
    sample_142(142);
    sample_143(143);
    sample_144(144);
    sample_145(145);
    sample_146(146);
    sample_147(147);
    sample_148(148);
    sample_149(149);
    sample_150(150);
    sample_151(151);
    sample_152(152);
    sample_153(153);
    sample_154(154);
    sample_155(155);
    sample_156(156);
    sample_157(157);
    sample_158(158);
    sample_159(159);
    sample_160(160);
    sample_161(161);
    sample_162(162);
    sample_163(163);
    sample_164(164);
    sample_165(165);
    sample_166(166);
    sample_167(167);
    sample_168(168);
    sample_169(169);
    sample_170(170);
    sample_171(171);
    sample_172(172);
    sample_173(173);
    sample_174(174);
    sample_175(175);

    cout << COLOR_PURPLE << "All tests completed!" << COLOR_RESET << endl;
}

int main(int argc, char **argv)
{
#ifdef _WIN32
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
#endif
    run_tests();
#ifdef _WIN32
    if (!_CrtDumpMemoryLeaks())
    {
        cout << COLOR_GREEN << "No memory leaks detected!" << COLOR_RESET << endl;
    }
    else
    {
        cout << COLOR_RED << "Memory leaks detected!" << COLOR_RESET << endl;
    }
#endif
}
