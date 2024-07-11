#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "pila.c"

/* CONSTANTS */
#define STANDARD_LENGTH 30
#define OPTS_AMOUNT 5
#define WIZARDS_FILENAME "wizards"

/* Every structure has an identifier for searching it at the files.
    Also, they have an int variable named "visible" for elimination */
typedef struct {
    char wood[STANDARD_LENGTH];
    char core[STANDARD_LENGTH * 2];
    char carrier[STANDARD_LENGTH];
    int visible;
} stWand;

typedef struct {
    int ID;
    char name[STANDARD_LENGTH];
    char house[STANDARD_LENGTH];
    stWand wand;
    int visible;
} stWizard;

#endif