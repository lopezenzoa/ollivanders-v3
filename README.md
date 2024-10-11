# ollivanders-v3

## Brief
Make a wand shop to manage an infinite number of wands is a complex task by its nature. This project is an attempt to resolve the mentioned problem.

Meant to be a college project, it resulted in a very interesting to practice with procedural programming using the C programming language. Practicing with records, functions, external libraries and binary files to permanent storage was a great experience.

## Basic commands
The first time you compile and execute the 'main.c' file at the command prompt, the following menu is displayed:

> < A > Add a Wizard\
< D > Delete a Wizard\
< M > Modify a Wizard\
< S > Search a Wizard\
< SW > Search a Wand\
< L > List Wizards

Every action is defined as follows:
* A: Adds a new Wizard, allowing the user to acquire a Wand with a personality test.
* D: Deletes an existing Wizard from the file.
* M: Modifies an existing Wizards, allowing to change the entire information of the it or an specific field.
* S: Searches for a Wizard from the 'wizards' file.
* SW: Searches for a Wand of a searched Wizard.
* L: Lists all Wizards from the 'wizards' file, allowing to list all visible wizards, filter by a specific house or the obituary(the place for deleted Wizards).

Any option (letter) which is not in the menu, is not considered a valid option.

## Libraries
There are four external libraries in order to make simpler the code and more readable.
Every library is described below:

* operations: groups all 6 valid operations.
* filesManager: concerned for every interaction with the file.
* structuresManager: in charge to manipulate both structures in the application: Wizards and Wands.
* pila: requisite to presenting the project at college. It's meant to be a simpler way to work with stacks.

Both filesManager and structuresManager libraries include a header 'shared.h' file for constants and structures declaration.

## Structures
As it was said before, the application has two structures: Wizards and Wands.

The Wand structure is made of 4 fields:
* *wood*: a string for the Wand's wood.
* *core*: a string for the Wand's core.
* *carrier*: a string for the name of the Wizard who owns the Wand.
* *visible*: an integer to know if the wand is visible or not (since there's no boolean values). Then, all possible values for this field is 0 (not visible) or 1 (visible).

On the other hand, the Wizard structure is made of 5 fields:
* *ID*: an random generated and unique integer for searching.
* *name*: a string for the Wizard name.
* *house*: a string for the Wizard house.
* *wand*: the structure of the Wizard's Wand.
* *visible*: an integer to know if the Wizard is visible or not (see the field with the same name for the Wand structure)

It's good to mention that:
1. every ID for each Wizard is random generated and unique.
2. The field 'visible' on every structure is meant to perform a pseudo removal, since it's necessary to hold deleted Wizards for the obituary.
3. The value for the field 'carrier' in the Wand structure is the same for the field 'name' of the Wizard structure.

## Binary Files
Every Wizard, when created, is written in the 'wizards' file. At the previous version 'ollivanders-v2', the Wands were written to another file called 'wands' (another requisite for presenting at college), while this newer version simplifies the storage to one file.
