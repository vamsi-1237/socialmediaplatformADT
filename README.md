
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

To compile and run the project

```bash
make all

#To run the social_media_platform
./bin/code_app.exe

#To run TASK2B
./bin/task2b_app.exe

#optional To remove object files
make clean
