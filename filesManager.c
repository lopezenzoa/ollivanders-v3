#include "filesManager.h"

/* Generates a unique ID, compare a random generated ID with all the IDs (wizards and their wands) in the 'wizards' file.
    Returns a unique ID */
int getID() {
    int id, recordsAmount = 0, range, found;
 
    recordsAmount = countRecords(WIZARDS_FILENAME, sizeof(stWizard));

    // Defining a range depending the amount of records helps to minimize the possibility to generate an existing ID
    if (recordsAmount < 20)
        range = 20;
    else
        range = recordsAmount;

    // Generate an new random ID every time it's found in the file
    do {
        id = rand() % range + 1;
        found = checkID(id);
    } while (found);

    return id;
}

/* Loops trough the file 'WIZARDS' searching for an ID.
    Receives as parameter the ID that's going to be compared.
    Returns a flag determining if it was found or not */
int checkID(int id) {
    FILE* buf = fopen(WIZARDS_FILENAME, "rb");
    stWizard wizard;
    int found = 0;

    if (buf) {
        while (found == 0 && fread(&wizard, sizeof(stWizard), 1, buf) > 0)
            if (wizard.ID == id)
                found = 1;

        fclose(buf);
    }
    
    return found;
}

/* Loops trough the file 'WIZARDS' searching for a name.
    Receives as parameter the name that's going to be compared.
    Returns a flag determining if it was found or not */
int checkName(char name[]) {
    FILE* buf = fopen(WIZARDS_FILENAME, "rb");
    stWizard wizard;
    int found = 0;

    if (buf) {
        while (found == 0 && fread(&wizard, sizeof(stWizard), 1, buf) > 0)
            if (strcmp(wizard.name, name) == 0)
                found = 1;

        fclose(buf);
    }
    
    return found;
}

/* Counts the total amount of records in an file.
    Receives as parameters the filename as a string and a records length (in bytes)
    Returns the amount of records in the file (0 by default) */
int countRecords(char filename[], size_t recordLength) {
    FILE* buf = fopen(filename, "rb");
    int recordsAmount = 0;

    if (buf) {
        fseek(buf, 0, SEEK_END);
        recordsAmount = ftell(buf) / recordLength;

        fclose(buf);
    }

    return recordsAmount;
}

/* Writes a loaded stWizard at the end of the file 'wizards'.
    Receives as paramater the structure which is going to be written. */
void writeWizard(stWizard wizard) {
    FILE* buf = fopen(WIZARDS_FILENAME, "ab");
    int added;

    if (buf) {
        added = fwrite(&wizard, sizeof(stWizard), 1, buf);

        if (added)
            printf("\n\tGREAT :) The wizard was added successfully in the file '%s'\n", WIZARDS_FILENAME);
        else
            printf("\n\tOOPS :/ There was a problem during adding the wizard to the file '%s'\n", WIZARDS_FILENAME);

        fclose(buf);
    } else
        printf("\n\tOOPS :/ There was a problem during opening the file '%s'\n", WIZARDS_FILENAME);

}

/* Reads the file 'wizards'
    Receives as parameters an array representing all wizards read and it's size (assuming it's long enough).
    Returns the amount of wizards added to the array */
int readWizardsFile(int size, stWizard wizards[]) {
    FILE* buf = fopen(WIZARDS_FILENAME, "rb");
    stWizard wizard;
    int pos = 0;

    if (buf) {
        while (fread(&wizard, sizeof(stWizard), 1, buf) > 0 && pos < size)
            if (wizard.visible) {
                wizards[pos] = wizard;
                pos++;
            }

        fclose(buf);
    } else
        printf("\n\tOOPS :/ There was a problem during opening the file '%s'\n", WIZARDS_FILENAME);

    return pos;
}

/* Searchs the wizard in the file 'wizards' which matches with the given ID.
    Receives the ID of the wanted wizard and the memory address of it's position at the file.
    Returns the wizard that matches with the given ID (if it's not found, th value of the position is going to be -1) */
void searchWizardByID(int id, int* pos, stWizard* wizard) {
    FILE* buf = fopen(WIZARDS_FILENAME, "rb");
    stWizard aux;
    int found = 0;

    if (!id)
        

    if(buf) {
        *pos = 0;

        while (found == 0 && (fread(&aux, sizeof(stWizard), 1, buf)) > 0)
            if (aux.ID == id) {
                found = 1;
                *wizard = aux;
            }
                
            else
                *pos += 1;

        if (!found)
            *pos = -1;

        fclose(buf);
    } else
        *pos = -1;
}

/* Searchs the wizard in the file 'wizards' which matches with the given name.
    Receives the name of the wanted wizard and the memory address of it's position at the file.
    Returns the wizard that matches with the given name (if it's not found, th value of the position is going to be -1) */
stWizard searchWizardByName(char name[], int* pos) {
    FILE* buf = fopen(WIZARDS_FILENAME, "rb");
    stWizard aux;
    int found = 0;

    if(buf) {
        *pos = 0;

        while (found == 0 && (fread(&aux, sizeof(stWizard), 1, buf)) > 0)
            if (strcmp(name, aux.name) == 0)
                found = 1;
            else
                *pos += 1;

        if (!found)
            *pos = -1;

        fclose(buf);
    } else
        *pos = -1;

    return aux;
}

/* Modifies an existing wizard in the file 'wizards'.
    Receives as parameters the modified wizard and it's position in the file */
void modifyWizardInFile(stWizard wizard, int pos) {
    FILE* buf = fopen(WIZARDS_FILENAME, "r+b");
    int modified = 0;

    if (buf) {
        fseek(buf, sizeof(stWizard) * pos, SEEK_SET);
        modified = fwrite(&wizard, sizeof(stWizard), 1, buf);

        if (modified)
            printf("\n\tGREAT :) The wizard was modified successfully at the file '%s'\n", WIZARDS_FILENAME);
        else
            printf("\n\tOOPS :/ There was a problem during modifying the wizard at the file '%s'\n", WIZARDS_FILENAME);

        fclose(buf);
    } else
        printf("\n\tOOPS :/ There was a problem during opening the file '%s'\n", WIZARDS_FILENAME);
}

/* Delete an existing wizard from the file 'wizards'.
    Recieves as parameters the wizard which is going to be deleted and it's position at the file */
void deleteWizardInFile(stWizard wizard, int pos) {
    FILE* buf = fopen(WIZARDS_FILENAME, "r+b");
    int deleted = 0;

    if (buf) {
        fseek(buf, sizeof(stWizard) * pos, SEEK_SET);
        fread(&wizard, sizeof(stWizard), 1, buf);

        // Deleting the wizard and it's wand
        wizard.visible = 0;
        wizard.wand.visible = 0;

        fseek(buf, sizeof(stWizard) * (-1), SEEK_CUR);
        deleted = fwrite(&wizard, sizeof(stWizard), 1, buf);

        if (deleted)
            printf("\n\tGREAT :) The wizard was deleted successfully at the file '%s'\n", WIZARDS_FILENAME);
        else
            printf("\n\tOOPS :/ There was a problem during deleting the wizard at the file '%s'\n", WIZARDS_FILENAME);

        fclose(buf);
    } else
        printf("\n\tOOPS :/ There was a problem during opening the file '%s'\n", WIZARDS_FILENAME);
}

/* Counts the amount of wizards that belong to a specific house.
    Receives as parameter the house which is going to be compared.
    Returns the amount of records that match with the house (0 by default) */
int countWizardsByHouse(char house[]) {
    FILE* buf = fopen(WIZARDS_FILENAME, "rb");
    int amount = 0;
    stWizard aux;

    if (buf) {
        while (fread(&aux, sizeof(stWizard), 1, buf) > 0)
            if (strcmp(aux.house, house) == 0 && aux.visible)
                amount++;

        fclose(buf);
    }

    return amount;
}

/* Fills an array of wizards that belong to a specific house.
    Receives as parameters the array which is going to be fill and the house which is going to be compared */
void fillWizByHouseArray(stWizard wizards[], char house[]) {
    FILE* buf = fopen(WIZARDS_FILENAME, "rb");
    stWizard aux;
    int pos = 0;

    if (buf) {
        while (fread(&aux, sizeof(stWizard), 1, buf) > 0)
            if (strcmp(aux.house, house) == 0 && aux.visible) {
                wizards[pos] = aux;
                pos++;
            }

        fclose(buf);
    }
}

/* Stacks all wizards which are no visible (0) in the file 'wizards'.
    Receives as parameter the memory address of the stack */
void stackDeadWizards(Pila* dead) {
    FILE* buf = fopen(WIZARDS_FILENAME, "rb");
    stWizard wizard;

    if (buf) {
        while (fread(&wizard, sizeof(stWizard), 1, buf) > 0) {
            if (!wizard.visible)
                apilar(dead, wizard.ID);
        }

        fclose(buf);
    }
}
