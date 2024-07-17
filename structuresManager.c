#include "structuresManager.h"

/// DEFINITIONS
/* Gets the ID entered by the user.
    Returns a valid ID (in this case, an integer number greater than 0) */
int getWizardID() {
    int id;

    do {
        printf("\n\t> ");
        scanf("%i", &id);
        while(getchar() != '\n');

        if (!id)
            printf("\n\tOOPS :/ Please enter an integer number greater than 0\n");
    } while (!id);

    return id;
}

/* Loads the information of the Wizard structure (stWizard).
    Receives as parameters the wizard ID number (assuming it's unique) and the wand structure.
    Returns the Wizard structure loaded with information */
stWizard loadWizardSt(int ID, stWand wand) {
    stWizard wizard;

    wizard.ID = ID;

    strcpy(wizard.name, wand.carrier);

    printf("\n\tPlease, enter the house you belong: ");
    fflush(stdin);
    scanf("%s", wizard.house);

    wizard.wand = wand;

    wizard.visible = 1;

    return wizard;
}

/* Shows a Wizard and it's wand.
    Recevies as parameter the wizard that's going to be shown */
void showWizard(stWizard wizard) {
    printf("\n\n\t************** WIZARD **************\n");
    printf("\n\t ID: %i\n", wizard.ID);
    printf("\n\t Name: %s\n", wizard.name);
    printf("\n\t House: %s\n", wizard.house);
    printf("\n\t Wand:\n");
    printf("\n\t - wood: %s\n", wizard.wand.wood);
    printf("\n\t - core: %s", wizard.wand.core);
    printf("\n\n\t************************************\n");
}

/* Shows a Wand of a Wizard.
    Recevies as parameter the wand that's going to be shown */
void showWand(stWand wand) {
    printf("\n\n\t************** WAND **************\n");
    printf("\n\t Wood: %s\n", wand.wood);
    printf("\n\t Core: %s\n", wand.core);
    printf("\n\t Carrier: %s", wand.carrier);
    printf("\n\n\t**********************************\n");
}

/* Modify a Wizard structure (assuming it's loaded).
    Receives as parameter the Wizard that is going to modified
    Returns the modified version of the Wizard received as paramater */
stWizard modifyWizardSt(stWizard wizard) {
    char modWay;
    int modWayCode;

    showWizard(wizard);

    printf("\n\tModification Ways\n");
    printf("\n\t < C >. Complete");
    printf("\n\t < F >. One Field");

    do {
        printf("\n\n\tPlease, enter the modification way: ");
        fflush(stdin);
        scanf(" %c", &modWay);

        modWayCode = toupper(modWay);

        if (modWayCode != 67 && modWayCode != 70)
            printf("\n\tOOPS :/ Please enter a valid option\n");

    } while (modWayCode != 67 && modWayCode != 70);

    if (modWayCode == 67)
        wizard = modifyWizardComplete(wizard);
    else
        wizard = modifyWizardByField(wizard);

    
    printf("\n\tThis is the wizard modified\n");
    showWizard(wizard);

    return wizard;
}

/* Modifies both structures (stWizard and stWand) completely.
    Receives as parameter the structure of the Wizard that's going to be modified.
    Returns the modified version of the Wizard received as paramater */
stWizard modifyWizardComplete(stWizard wizard) {
    printf("\n\n\tPlease, enter the NEW name: ");
    while(getchar() != '\n');
    fflush(stdin);
    gets(wizard.name);

    strcpy(wizard.wand.carrier, wizard.name);

    printf("\n\n\tPlease, enter the NEW house: ");
    fflush(stdin);
    scanf("%s", wizard.house);

    return wizard;
}

/* Modifies both structures (stWizard and stWand) by one field at a time.
    Receives as parameter the structure of the Wizard that's going to be modified.
    Returns the modified version of the Wizard received as paramater */
stWizard modifyWizardByField(stWizard wizard) {
    char field;
    int fieldCode, validField;

    printf("\n\tList of Fields\n");
    printf("\n\t< N > Name");
    printf("\n\t< H > House");
    printf("\n\t< W > Wand");

    do {
        printf("\n\n\tPlease, enter the field you want to modify: ");
        fflush(stdin);
        scanf(" %c", &field);

        fieldCode = toupper(field);
        
        if (fieldCode != 78 && fieldCode != 72 && fieldCode != 87)
            printf("\n\tOOPS :/ Please, enter a valid option\n");

    } while (fieldCode != 78 && fieldCode != 72 && fieldCode != 87);

    if (fieldCode == 78) {
        printf("\n\n\tEnter the NEW name: ");
        fflush(stdin);
        scanf("%s", wizard.name);

        strcpy(wizard.wand.carrier, wizard.name);
    } else if (fieldCode == 72) {
        printf("\n\n\tEnter the NEW house: ");
        fflush(stdin);
        scanf("%s", wizard.house);
    } else {
        printf("\n\tModifying a wand\n");
    }

    return wizard;
}

/* Shows an array of Wizards, in a recursive way.
    Recevies as parameters the array of Wizards, it's size and the current position at the array */
void showWizardsArray(int wizardsAmount, int pos, stWizard wizards[]) {
    if (wizardsAmount > 0) {
        showWizard(wizards[pos]);
        showWizardsArray(wizardsAmount - 1, pos + 1, wizards);
    }
}

/* Sorts a given array of Wizards by their name.
    Receives as paramaters an array of wizards and it's size.
    Invokes findMinPos() and swap() to sort the array using selection method */
void sortWizardsArray(int wizardsAmount, stWizard wizards[]) {
    int minPos;

    for (int i = 0; i < wizardsAmount - 1; i++) {
        minPos = findMinPos(i, wizardsAmount, wizards);
        swap(i, minPos, wizards);
    }
}

/* Finds the position of the minor Wizard comparing with the name of each one.
    Receives as paramaters an array of wizards, it's size and the current position at the array */
int findMinPos(int pos, int wizardsAmount, stWizard wizards[]) {
    stWizard minWizard = wizards[pos];
    int minPos = pos;

    for (int i = pos + 1; i < wizardsAmount; i++)
        if (strcmp(wizards[i].name, minWizard.name) < 0) {
            minWizard = wizards[i];
            minPos = i;
        }

    return minPos;
}

/* Swaps two Wizards inside of an array, using an auxiliar structure (in this case, the current wizard with the minor) */
void swap(int pos, int minPos, stWizard wizards[]) {
    stWizard aux;

    aux = wizards[minPos];
    wizards[minPos] = wizards[pos];
    wizards[pos] = aux;
}

/* Shows a personality test in order to asign a wand for the user */
void showPersonalityTest() {
    int answer;

    printf("\n\tNext, you have to answer some questions in order to define your wand\n");

    do {
        printf("\n\tHow much do you value bravery and courage (0: Not at all - 10: Extremely important)? ");
        scanf("%i", &answer);
        while (getchar() != '\n');

        if (!answer || answer < 0 || answer > 10)
            printf("\n\tPlease enter an integer number between 0 and 10\n");

    } while (!answer || answer < 0 || answer > 10);

    do {
        printf("\n\tHow curious are you about magical knowledge and mysteries (0: Not curious at all - 10: Incredibly curious)? ");
        scanf("%i", &answer);
        while (getchar() != '\n');

        if (!answer || answer < 0 || answer > 10)
            printf("\n\tPlease enter an integer number between 0 and 10\n");

    } while (!answer);

    do {
        printf("\n\tHow loyal are you to your friends and loved ones (0: Not loyal at all - 10: Unwaveringly loyal)? ");
        scanf("%i", &answer);
        while (getchar() != '\n');

        if (!answer || answer < 0 || answer > 10)
            printf("\n\tPlease enter an integer number between 0 and 10\n");

    } while (!answer);
}

/* Adds a wand to a file.
    Returns the wand structure loaded with info */
stWand addWand() {
    stWand wand;
    int woodIndex, coreIndex;
    char choosenWood[STANDARD_LENGTH], choosenCore[STANDARD_LENGTH * 2];
    char WOODS[16][STANDARD_LENGTH] = {
        "Acacia",
        "Alder",
        "Apple",
        "Ash",
        "Cedar",
        "Cherry",
        "Chestnut",
        "Cypress",
        "Elder",
        "Elm",
        "Ebony",
        "English oak",
        "Silver lime",
        "Spruce",
        "Snakewood",
        "Sugar Maple"
    };
    char CORES[16][STANDARD_LENGTH * 2] = {
        "Unicorn hair",
        "Dragon heartstring",
        "Phoenix feather",
        "Veela hair",
        "Thestral tail hair",
        "Troll whisker",
        "Kelpie hair",
        "Thunderbird tail feather",
        "Dittany stalk",
        "Wampus cat hair",
        "White River Monster spine",
        "Rougarou hair",
        "Kneazle whiskers",
        "Horned Serpent horn",
        "Snallygaster heartstring",
        "Jackalope antler"
    };

    showPersonalityTest();

    // this loop resolves the problem of the empty core
    do {
        // the indices are randomly generated
        woodIndex = rand() % 15;
        coreIndex = rand() % 15;

        strcpy(choosenWood, WOODS[woodIndex]);
        strcpy(choosenCore, CORES[coreIndex]);

    } while (strlen(choosenWood) == 0 || strlen(choosenCore) == 0);

    wand = loadWandSt(choosenWood, choosenCore);

    return wand;
}

/* Loads the information of the wand structure (stWand).
    Receives as parameter the wood and the core, both strings.
    Returns the wand structure loaded with information */
stWand loadWandSt(char wood[], char core[]) {
    stWand wand;

    strcpy(wand.wood, wood);
    strcpy(wand.core, core);

    printf("\n\n\tPlease, enter your name: ");
    fflush(stdin);
    gets(wand.carrier);

    wand.visible = 1;

    return wand;
}