CIS3110
=======

Assignment 2
------------

Student: Rodrigo Lopes de Carvalho
Student ID: 0905095


Building instructions:
----------------------

Use Makefile provided.

    make
    ./simcpu < input_file

Files
-----


* `include/`
    * `event.hpp`  
        header for Event struct.
    * `process.hpp`  
        header file for Process and Thread structs.
    * `scheduler.hpp`  
        header file for Scheduler Struct.  
* `src/`
    * `event.cpp`  
        implementation file for Event struct  
        contains comparator method for priority queue
    * `process.cpp`  
        implementation file for Process and Thread structs.  
        mostly initialization code.
    * `scheduler.cpp`  
        implementation file for Scheduler Struct.
        contains most code for assignment.
    * `main.cpp`  
        main function.  
        handles arguments and reads input file.
