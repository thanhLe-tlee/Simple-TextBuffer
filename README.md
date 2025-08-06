# Assignment 1 - Simple Text Buffer using LinkedList and OOP

## Course: CO2003 - Data Structures and Algorithms  
**Ho Chi Minh City University of Technology – Faculty of Computer Science and Engineering**

--- 

## 📌 Overview

This project implements a **simple text editor buffer** using **Object-Oriented Programming (OOP)** principles and a **Doubly Linked List (DLL)**.  
It is designed for the **CO2003 Data Structures and Algorithms** course at Ho Chi Minh City University of Technology (HCMUT).

This project targets are required to:
- Master basic list data structures.
- Apply sorting and searching algorithms.
- Practice managing undo/redo operations for editing actions.

---

## ⚙️ Features

✅ **Doubly Linked List**  
- Insert at head, tail, or arbitrary index.  
- Delete at arbitrary index.  
- Search by value or index.  
- Reverse the list.  
- Convert to string with a custom converter.

✅ **TextBuffer**  
- Insert and delete characters at the cursor position.
- Move the cursor left, right, or to any position.
- Find first occurrence or all occurrences of a character.
- Sort all characters in ascending order (case-sensitive).
- Undo or redo edits and cursor movements.

✅ **HistoryManager**  
- Store all actions that change the buffer or cursor.
- Print the full action history for verification.
- Clear redo history when new edits happen after an undo.

---

## 🏷️ Compilation

**📋 Instructions:**

1️⃣ **Navigate to the project directory:**
```bash
cd path/to/Simple-TextBuffer-main
```

2️⃣ **Compile the project:**
```bash
g++ -o main main.cpp TextBuffer.cpp -I . -std=c++17
```

3️⃣ **Run the application:**
```bash
./main
```

🎉 **Enjoy testing your Text Buffer implementation!**
