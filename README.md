# Social Media ADT (Abstract Data Type) Console Application

This project implements a basic social media platform's core data structures (Posts, Comments, Replies) and operational logic using the C programming language. It is designed around the concept of an Abstract Data Type (ADT), ensuring clear separation between data structure definitions and application-level functions.

A key feature is the Most Recently Viewed Post Log, which tracks the order in which posts are accessed. All program output is buffered in memory and printed only after the user signals the end of input.

##  Project Structure and File Descriptions

The application is modularized into dedicated files for each entity, promoting clean encapsulation:
`platform.c / .h` Core application logic, global state Platform, post list management, and the **Post View Log** . This is the central processing unit of the application. 
`post.c / .h` Handles individual Post creation, display, and memory cleanup.
`comment.c / .h`  Handles individual Comment creation and memory cleanup 
`reply.c / .h` Handles individual reply creation
`main.c` Handles **command-line input parsing using strtok
`Makefile` Simplifies compilation and execution using GCC. 



##  Build and Execution Instructions

This project uses a `Makefile` and is intended to be built using **GCC** and the **`make`** utility in a Unix-like environment (**MinGW64/Git Bash** on Windows, Linux, or macOS).

### 1. Build the Executable

Use the `all` target to compile and link all object files into the executable named **`social.exe`**.

To compile and run the project

```bash
make all
make run

#optional To remove object files
make clean
