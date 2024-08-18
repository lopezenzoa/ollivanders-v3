#include "operations.c"

void ollivanders();
void executeOpts(int);

int main() {
    ollivanders(); // believe, because something magic can occurs...
    return 0;
}

void ollivanders() {
    int choosenOpt;

    // main loop of the program
    do {
        showWelcome();

        showOperations();
        choosenOpt = getOpt();

        if (choosenOpt == 27) {
            showWelcome();
            printf("\n\tThank you to visit OLLIVANDERS!\n\tBelieve, because something magic can occurs...\n\n");
        } else if (choosenOpt != -1) {
            showWelcome();
            executeOpts(choosenOpt);
        } else {
            showWelcome();
            printf("\n\tOOPS :/ Please enter a valid Operation\n");
        }
    } while (choosenOpt != 27);
}


/**
 * Executes the user's operation through a switch statement.
 * @param optCode ASCII code of the operation.
*/
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
        case 170:
            do {
                showWelcome();
                searchWand();

                printf("\n\tPress any character to search another wand (ESC for exit): ");
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