# ollivanders-v3

## Brief
Make a wand shop to manage an infinite number of wands is a complex task by its nature. That is the reason this application exists.

Meant to be a college project, it results a very interesting to experiment with procedural programming using the C programming language. Practicing with records, functions, external libraries and binary files to permanent storage was an great experience.

## Basic commands
The first time you compile and execute the 'main.c' file at the command prompt, the following menu is displayed:

< A > Add a Wizard\
< D > Delete a Wizard\
< M > Modify a Wizard\
< S > Search a Wizard\
< SW > Search a Wand\
< L > List Wizards

A: Adds a new Wizard, allowing the user to acquire a Wand with a personality test.\
D: Deletes an existing Wizard from the file.\
M: Modifies an existing Wizards, allowing to change the entire information of the it or an specific field.\
S: Searches for a Wizard from the 'wizards' file.\
SW: Searches for a Wand of a searched Wizard.\
L: Lists all Wizards from the 'wizards' file, allowing to list all visible wizards, filter by a specific house or the obituary(the place for deleted Wizards).

Any option (letter) which is not in the menu, is not considered a valid option.

## Libraries
There are four external libraries in order to make simpler the code and more readable.

- operations: groups all 6 valid operations.
- filesManager: concerned for every interaction with the file, simulating a buffer.
- structuresManager: in charge to manipulate both structures in the application: Wizards and Wands.
- pila: requisite to presenting the project at college. It's meant to be a simpler way to work with stacks.

Both filesManager and structuresManager libraries include a header 'shared.h' file for constants and structures declaration.

## Structures
As it was said before, the application has two structures: Wizards and Wands. Each one is declared as follows:

typedef struct {\
&emsp;char wood[STANDARD_LENGTH];\
&emsp;char core[STANDARD_LENGTH * 2];\
&emsp;char carrier[STANDARD_LENGTH];\
&emsp;int visible;\
} stWand;

typedef struct {\
&emsp;int ID;\
&emsp;char name[STANDARD_LENGTH];\
&emsp;char house[STANDARD_LENGTH];\
&emsp;stWand wand;\
&emsp;int visible;\
} stWizard;

It's good to mention that:
- every ID for each Wizard is random generated and unique, in order to execute searching.
- The field 'visible' on every structure is meant to perform a logic down, since it's necessary to hold deleted Wizards for the obituary.
- The value for the field 'carrier' in the Wand structure is the same for the field 'name' of the Wizard structure.

## Binary Files
Every Wizard, when created, is written in the 'wizards' file. At the previous version 'ollivanders-v2' the Wands were written to another file called 'wands' (another requisite for presenting at college), while this newer version simplifies the storage to one file.


