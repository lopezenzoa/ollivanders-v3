#include "structuresManager.c"
#include "filesManager.c"

/* OPTS PROTOTYPES */
void addWizard();
void deleteWizard();
void modifyWizard();
void searchWizard();
void listWizards();
void searchWand();

/* LIST WIZARDS AUXILIARIES PROTOTYPES */
int getListingOpt();
void listVisibleWizards();
void listWizardsByHouse();
void listObituary();

/* OPTS AUXILIARES */
void showWelcome();
void showOperations();
int getOpt();

/* Shows the header while cleaning the screen.
    It's invoked multiple times along the code in order to mantain the screen clean to show information */
void showWelcome() {
    system("clear");

    printf("\n\tWelcome to OLLIVANDERS!");
    printf("\n\tMakers of Fine Wands since 382 B.C.");
    printf("\n\n");
}

/* Shows the list of possible user's Operations */
void showOperations() {
    char OPTS[OPTS_AMOUNT][STANDARD_LENGTH] = {
        "< A > Add a Wizard",
        "< D > Delete a Wizard",
        "< M > Modify a Wizard",
        "< S > Search a Wizard",
        "< SW > Search a Wand",
        "< L > List Wizards"
    };

    printf("\n\tA list of recommended actions\n");

    for (int i = 0; i < OPTS_AMOUNT; i++)
        printf("\n\t%s", OPTS[i]);
}

/* Gets the user's Operation.
    Returns the ASCII code for the character entered (returning -1 for an invalid character) */
int getOpt() {
    char opt[2] = {' ', '\n'};
    int optCode, exit;
    
    printf("\n\n\tPlease, enter the character for the Operation (ESC to exit): ");
    fflush(stdin);
    gets(opt);

    optCode = toupper(opt[0]) + toupper(opt[1]);
    exit = toupper(opt[0]);

    // catching empty spaces and escape sequence
    if (optCode == 32)
        optCode = -1;
    else if (exit == 27)
        optCode = 27;

    return optCode;
}

/// OPTS DEFINITIONS
void addWizard() {
    stWizard wizard;
    stWand wand;
    int wizardID, nameFound, pos;

    wand = addWand();

    nameFound = checkName(wand.carrier);

    if (nameFound) {
        showWelcome();
        
        showWizard(searchWizardByName(wand.carrier, &pos));
        printf("\n\tThat name already belongs to a wizard\n");
    }

    wizardID = getID();
    wizard = loadWizardSt(wizardID, wand);

    showWelcome();

    showWizard(wizard);
    writeWizard(wizard); // writing the wizard in the file
}

void deleteWizard() {
    char confirm;
    int pos, id = 0;
    stWizard wizard;

    showWelcome();

    printf("\n\tEnter the ID of the Wizard you want to delete");
    searchWizardByID(id, &pos, &wizard);

    if (pos != -1 && wizard.visible) {
        showWizard(wizard);

        printf("\n\tAre you sure you want to delete (y/n)? ");
        fflush(stdin);
        scanf(" %c", &confirm);

        confirm = toupper(confirm);

        if (confirm == 'Y')
            deleteWizardInFile(wizard, pos);
    } else
        printf("\n\tOOPS :/ The entered ID was not found in the file '%s'\n", WIZARDS_FILENAME);
}

void modifyWizard() {
    int pos, id = 0;
    stWizard wizard;

    showWelcome();

    printf("\n\tEnter the ID of the Wizard you want to modify");
    searchWizardByID(id, &pos, &wizard);

    if (pos != -1 && wizard.visible) {
        wizard = modifyWizardSt(wizard);
        modifyWizardInFile(wizard, pos);
    } else
        printf("\n\tOOPS :/ The entered ID was not found in the file '%s'\n", WIZARDS_FILENAME);
}

void searchWizard() {
    stWizard wizard;
    int pos, id = 0;

    showWelcome();

    printf("\n\tEnter the ID of the Wizard you want to search");
    searchWizardByID(id, &pos, &wizard);

    if (pos != -1 && wizard.visible)
        showWizard(wizard);
    else
        printf("\n\tOOPS :/ The entered ID was not found in the file '%s'\n", WIZARDS_FILENAME);
}

void searchWand() {
    stWizard wizard;
    int pos, id = 0;

    showWelcome();

    printf("\n\tEnter the ID of the Wizard you want to search its Wand");
    searchWizardByID(id, &pos, &wizard);

    if (pos != -1 && wizard.visible)
        showWand(wizard.wand);
    else
        printf("\n\tOOPS :/ The entered ID was not found in the file '%s'\n", WIZARDS_FILENAME);
}

void listWizards() {
    int listingViewCode;

    showWelcome();

    printf("\n\tListing Views\n");
    printf("\n\t< V >. Visible Wizards");
    printf("\n\t< H >. Wizards of a specific house");
    printf("\n\t< O >. Obituary");

    listingViewCode = getListingOpt();

    showWelcome();

    if (listingViewCode == 86)
        listVisibleWizards();
    else if (listingViewCode == 72)
        listWizardsByHouse();
    else
        listObituary();
}

/// LIST WIZARDS AUXILIARIES DEFINITIONS
int getListingOpt() {
    char listingView;
    int listingViewCode;

    do {
        printf("\n\n\tPlease, enter the view you want to list the wizards: ");
        fflush(stdin);
        scanf(" %c", &listingView);

        listingViewCode = toupper(listingView);

        if (listingViewCode != 86 && listingViewCode != 72 && listingViewCode != 79)
            printf("\n\tOOPS :/ Please, enter a valid listing view\n");

    } while (listingViewCode != 86 && listingViewCode != 72 && listingViewCode != 79);

    return listingViewCode;
}

void listVisibleWizards() {
    int wizardsAmount = 0;
    stWizard visibleWizards[STANDARD_LENGTH];

    wizardsAmount = readWizardsFile(STANDARD_LENGTH, visibleWizards);

    sortWizardsArray(wizardsAmount, visibleWizards);
    showWizardsArray(wizardsAmount, 0, visibleWizards);
}

void listWizardsByHouse() {
    int wizardsAmount = 0;
    char house[STANDARD_LENGTH];
    stWizard* wizardsByHouse;

    printf("\n\tPlease, enter the name of the house you want to list the wizards: ");
    fflush(stdin);
    scanf("%s", house);

    wizardsAmount = countWizardsByHouse(house);

    if (wizardsAmount) {
        // At least one wizard is from the choosen house
        wizardsByHouse = (stWizard*) malloc(wizardsAmount * sizeof(stWizard));

        fillWizByHouseArray(wizardsByHouse, house);
        showWizardsArray(wizardsAmount, 0, wizardsByHouse);
    } else
        printf("\n\tOOPS :/ There's no wizards from the house you entered\n");
}

void listObituary() {
    Pila dead; inicpila(&dead);
    int pos;
    stWizard deadWizard;

    stackDeadWizards(&dead);

    if (!pilavacia(&dead)) {
        while (!pilavacia(&dead)) {
            searchWizardByID(tope(&dead), &pos, &deadWizard);

            if (pos != -1)
                showWizard(deadWizard);

            desapilar(&dead);
        }
    } else
        printf("\n\tOOPS :/ There's no recent wizards at the obituary\n");
}