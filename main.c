#include "structuresManager.c"
#include "filesManager.c"

void ollivanders();

/* GENERAL AUXILIARIES */
void showWelcome();
void showOperations();
int getOpt();
void executeOpts(int);

/* OPTS PROTOTYPES */
void addWizard();
void deleteWizard();
void modifyWizard();
void searchWizard();
void listWizards();

/* LIST WIZARDS AUXILIARIES PROTOTYPES */
void listVisibleWizards();
void listWizardsByHouse();
void listObituary();

int main() {
    ollivanders(); // believe, because something magic can occurs...
    return 0;
}

/*  GENERAL */
void ollivanders() {
    int choosenOpt;

    // main loop of the program
    do {
        showWelcome();

        showOperations();
        choosenOpt = getOpt();

        if (choosenOpt == 27)
            printf("\n\tThank you to visit OLLIVANDERS!\n\tBelieve, because something magic can occurs...\n\n");
        else if (choosenOpt != -1)
            executeOpts(choosenOpt);
        else
            printf("\n\tOOPS :/ Please enter a valid Operation\n");
    } while (choosenOpt != 27);
}

/// AUXILIARIES DEFINITIONS

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
        "< L > List Wizards"
    };

    printf("\n\tA list of recommended actions\n");

    for (int i = 0; i < OPTS_AMOUNT; i++)
        printf("\n\t%s", OPTS[i]);
}

/* Gets the user's Operation.
    Returns the ASCII code for the character entered (returning -1 for an invalid character) */
int getOpt() {
    char opt;
    int optCode;

    printf("\n\n\tPlease, enter the character for the Operation (ESC to exit): ");
    fflush(stdin);
    scanf(" %c", &opt);

    optCode = toupper(opt);

    // getting empty spaces
    if (optCode == 32)
        optCode = -1;

    return optCode;
}

/* Executes the user's choosen Operation over the choosen structure through a switch statement.
    Receives as parameters both ASCII codes of the Operation and the structure */
void executeOpts(int optCode) {
    char abort;
    int abortCode;
    
    switch(optCode) {
        case 65:
            do {
                showWelcome();
                addWizard();

                printf("\n\tPress any character to add another wizard (ESC for exit): ");
                fflush(stdin);
                scanf(" %c", &abort);

                abortCode = abort;
            } while (abortCode != 27);
            break;
        case 68:
            do {
                showWelcome();
                deleteWizard();

                printf("\n\tPress any character to delete another wizard (ESC for exit): ");
                fflush(stdin);
                scanf(" %c", &abort);

                abortCode = abort;
            } while (abortCode != 27);
            break;
        case 77:
            do {
                showWelcome();
                modifyWizard();

                printf("\n\tPress any character to modify another wizard (ESC for exit): ");
                fflush(stdin);
                scanf(" %c", &abort);

                abortCode = abort;
            } while (abortCode != 27);
            break;
        case 83:
            do {
                showWelcome();
                searchWizard();

                printf("\n\tPress any character to search another wizard (ESC for exit): ");
                fflush(stdin);
                scanf(" %c", &abort);

                abortCode = abort;
            } while (abortCode != 27);
            break;
        case 76:
            do {
                showWelcome();
                listWizards();

                printf("\n\tPress any character to list by other view (ESC for exit): ");
                fflush(stdin);
                scanf(" %c", &abort);

                abortCode = abort;
            } while (abortCode != 27);
            break;
        default:
            showWelcome();
            printf("\n\tOOPS :/ That operation is not defined\n");
            break;
        }
}

/// OPTS DEFINITIONS
void addWizard() {
    stWizard wizard;
    stWand wand;
    int wizardID, nameFound;

    wand = addWand();

    do {
        nameFound = checkName(wand.carrier);

        if (nameFound) {
            do {
                showWelcome();

                printf("\n\tThat name was already belongs to a wizard\n\n\tPlease enter another name: ");
                fflush(stdin);
                gets(wand.carrier);

                nameFound = checkName(wand.carrier);
            } while (nameFound);
        }
    } while (nameFound);

    wizardID = getID();
    wizard = loadWizardSt(wizardID, wand);

    showWelcome();

    showWizard(wizard);
    writeWizard(wizard); // writing the wizard in the file
}

void deleteWizard() {
    char confirm;
    int pos, id;
    stWizard wizard;

    showWelcome();

    id = getWizardID();
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
    int pos, id;
    stWizard wizard;

    showWelcome();

    id = getWizardID();
    searchWizardByID(id, &pos, &wizard);

    if (pos != -1 && wizard.visible) {
        wizard = modifyWizardSt(wizard);
        modifyWizardInFile(wizard, pos);
    } else
        printf("\n\tOOPS :/ The entered ID was not found in the file '%s'\n", WIZARDS_FILENAME);
}

void searchWizard() {
    stWizard wizard;
    int pos, id;

    showWelcome();

    id = getWizardID();
    searchWizardByID(id, &pos, &wizard);

    if (pos != -1 && wizard.visible)
        showWizard(wizard);
    else
        printf("\n\tOOPS :/ The entered ID was not found in the file '%s'\n", WIZARDS_FILENAME);
}

void listWizards() {
    char listingView;
    int listingViewCode;

    showWelcome();

    printf("\n\tListing Views\n");
    printf("\n\t< V >. Visible Wizards");
    printf("\n\t< H >. Wizards of a specific house");
    printf("\n\t< O >. Obituary");

    do {
        printf("\n\n\tPlease, enter the view you want to list the wizards: ");
        fflush(stdin);
        scanf(" %c", &listingView);

        listingViewCode = toupper(listingView);

        if (listingViewCode != 86 && listingViewCode != 72 && listingViewCode != 79)
            printf("\n\tOOPS :/ Please, enter a valid listing view\n");

    } while (listingViewCode != 86 && listingViewCode != 72 && listingViewCode != 79);

    showWelcome();

    if (listingViewCode == 86)
        listVisibleWizards();
    else if (listingViewCode == 72)
        listWizardsByHouse();
    else
        listObituary();
}

/// LIST WIZARDS AUXILIARIES DEFINITIONS
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