#ifndef FILES_MANAGER_H
#define FILES_MANAGER_H

#include "shared.h"

// Prototypes
int getID();
int checkID(int);
int checkName(char []);
int countRecords(char [], size_t);

void writeWizard(stWizard);
int readWizardsFile(int, stWizard []);
void searchWizardByID(int, int*, stWizard*);
stWizard searchWizardByName(char [], int*);
void modifyWizardInFile(stWizard, int);
void deleteWizardInFile(stWizard, int);
int countWizardsByHouse(char []);
void fillWizByHouseArray(stWizard [], char []);
void stackDeadWizards(Pila*);

#endif