*******************************************************
*  Name      :      Bryant Wong    
*  Student ID:      107571009           
*  Class     :  CSC 2421           
*  HW#       :  Final Project 
*  Due Date  :  April 26, 2017
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

This program reads a large data set of names, contact info, and affiliates for an "address book"
type functionality.  The user can choose to search by any of the 15 fields, add an entry, delete an entry,
edit an entry, choose entries to write to file (see final document for more complete description).

*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
   Main program.  Instantiates the addressbook class and calls the menu.

Name:  Menu.cpp
	This calls all the functions to carry out the steps and allows for user input in the description.

Name:  BST.cpp
   Contains all the member functions for a binary search tree class containing nodes with entry class data.
   
Name:  AddressBook.cpp
	Contains functions to carry out all of the functions listed in the description.
	
Name:  AddressBook.h
	Contains all the declarations for AddressBook.cpp and has inline functions for comparing

Affiliates.h
	Contains the Class Affiliates to hold the parameters for each entry's affiliates.

ContactInfo.h
	Contains a class to hold the parameters for each entry's contact info.
	
Entry.h
	Contains a class to hold each entry's identifiers, an instance of contact info class, and affiliates class.

Menu.h
	Contains prototypes for Menu.cpp's functions.

Name:  BST.h
   Contains the declarations for all of the member functions needed for using a binary search tree.

Name:  Node.h
   Contains the functionality of the nodes used in the binary search tree, namely the pointers to the left
and right of the tree, the pointers to the parent, the variable to hold the data and the setters and getters
for all of the above.

   
*******************************************************
*  Circumstances of programs
*******************************************************
The program is complete and compiles and runs on visual studio community perfectly.

The program compiles on csegrid and runs on csegrid.
Updated (4/24/2017):  All menus and submenus are functional.

While running on csegrid, the program encounters segmentation fault when manually adding
an entry or when manually editing an entry's phone numbers when attempting to access 
ContactInfo class (I think...) to set an entry's phone number (4/23/17).




Developed on Visual Studio Community 2015 14.0.25431.01 Update 3.

*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       % unzip [WongFinalProject]

   Now you should see a directory named homework with the files:
	main.cpp
	Menu.cpp
	AddressBook.cpp
	BST.cpp
	Node.h
	BST.h
	AddressBook.h
	Affiliates.h
	ContactInfo.h
	Entry.h
	Menu.h
	databasesmall.txt
	databaselarge.txt
	makefile
	readme
	FinalReport.docx


2. Build the program.

    Change to the directory that contains the file by:
    % cd [WongFinalProject] 

    Compile the program by:
    % make

3. Run the program by:
   % ./finalproject

4. Delete the obj files, executables, and core dump by
   %./make clean
