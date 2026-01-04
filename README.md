##  MP3 Tag Reader & Editor (C)

A command-line MP3 Tag Reader & Editor developed in C, designed to view and modify ID3 metadata in MP3 files.
This project demonstrates binary file handling, modular programming, and command-line argument processing using ANSI C.

🚀 Features

* View MP3 metadata (ID3 tags)

  * Title
  * Artist
  * Album
  * Year
  * Genre
  * Comments

* Edit MP3 tag information using CLI options

* Validates MP3 file format

* User-friendly, ANSI-coloured terminal output

* Modular design with separate view and edit modules

## Technologies Used

* C (ANSI C)
* File Handling (Binary Files)
* Structures, Pointers & Enums
* Command Line Arguments
* Modular Programming

##  Project Structure

```
.
├── main.c
├── view.c
├── view.h
├── edit.c
├── edit.h
├── types.h
└── README.md
```

---

## ▶️ Usage

### View MP3 Tags

```bash
./a.out -v sample.mp3
```

### Edit MP3 Tags

```bash
./a.out -e -t "New Title" sample.mp3
./a.out -e -a "New Artist" sample.mp3
```

### Help Menu

```bash
./a.out -h
```

## 📌 Future Enhancements

* Support for ID3v2 tags
* Batch editing of MP3 files
* Improved error handling
* Cross-platform build support


