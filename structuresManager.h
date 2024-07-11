#ifndef STRUCTURES_MANAGER_H
#define STRUCTURES_MANAGER_H

#include "shared.h"

/// PROTOTYPES
int getWizardID();
stWizard loadWizardSt(int, stWand);
void showWizard(stWizard wizard);
stWizard modifyWizardSt(stWizard);
stWizard modifyWizardComplete(stWizard);
stWizard modifyWizardByField(stWizard);
void showWizardsArray(int, int, stWizard []);
void sortWizardsArray(int, stWizard []);
int findMinPos(int, int, stWizard []);
void swap(int, int, stWizard []);

void showPersonalityTest();
stWand addWand();
stWand loadWandSt(char [], char []);

#endif