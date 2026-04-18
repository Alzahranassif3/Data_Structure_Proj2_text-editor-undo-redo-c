# Text Editor with Undo/Redo in C

## 📌 Overview

This project is a simple text editor simulation written in C.
It allows users to load text from a file, insert and delete words, and perform Undo/Redo operations using custom data structures.

---

## ⚙️ Features

* Load text from file
* Display text
* Insert words:

  * At beginning
  * At end
  * Between words
* Delete words
* Undo operations
* Redo operations
* Save updated text to file

---

## 🧠 Data Structures Used

* **Linked List** → to store the text
* **Queue** → to handle multi-word insertion
* **Stack** → to implement Undo/Redo operations

---

## 📂 File Structure

```
main.c
initialText.txt
updated_text.txt
README.md
```

---

## ▶️ How to Run

1. Compile the program:

```
gcc main.c -o editor
```

2. Run:

```
./editor
```

---

## 📥 Input File

* The program reads from:

```
initialText.txt
```

Example:

```
this is a sample text
```

---

## 📤 Output

* Updated text is saved to:

```
updated_text.txt
```

---

## 🔄 Undo / Redo Logic

* Each operation (insert/delete) is stored in a stack
* Undo reverses the last operation
* Redo reapplies the undone operation

---


## 👩‍💻 Author

AlZahra Ahmad Nassif
