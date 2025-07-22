# 📄 Simple Text Buffer — CO2003 Data Structures & Algorithms Assignment 1

## 📌 Overview

This project implements a **simple text editor buffer** using **Object-Oriented Programming (OOP)** principles and a **Doubly Linked List (DLL)**.  
It is designed for the **CO2003 Data Structures and Algorithms** course at Ho Chi Minh City University of Technology (HCMUT).

Students are required to:
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

**Command (as required in the assignment spec):**

```bash
g++ -o main main.cpp TextBuffer.cpp -I . -std=c++17
