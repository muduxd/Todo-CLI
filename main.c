#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>


#include "cjson/cJSON.h"
#include "source/colors.c"
#include "source/tasks.c"
#include "source/utils.c"
#include "source/ascii.c"



enum commands {
    ADD = 1,
    REMOVE,
    READ,
    LIST,
    HELP,
    EXIT
};




void runCommand();

int main(int argc, char *argv[]) {
    startAscii ();
    loadTasks ();
    runCommand ();

    return 0;
}



void runCommand() {
    printf("Command: ");

    char input[100];
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = '\0';


    char* trimmedInput = Trim(input);
    char* auxInput = malloc(strlen(input) + 1);
    strcpy(auxInput, input);


    char* args = strtok(trimmedInput, " ");
    char* command = malloc(strlen(args) + 1);
    strcpy(command, args);


    int argNum = -1;
    while (args != NULL) {
        argNum++;
        args = strtok(NULL, " ");
    }



    switch (convertCommand(command)) {
        case ADD: {
            if (argNum != 2) {
                printColor("Please enter the required arguments!", "red");
                break;
            }

            char* arg = strtok(auxInput, " ");

            arg = strtok(NULL, " ");
            char* title = parseTitle(arg);

            arg = strtok(NULL, " ");
            char* description = parseDescription(arg);

            addTask(title, description);

            free(title);
            free(description);
            break;
        }



        case REMOVE: {
            if (argNum != 1) {
                printColor ("Please enter the required arguments!", "red");
                break;
            }

            char* arg = strtok(auxInput, " ");

            arg = strtok(NULL, " ");
            char* title = parseTitle(arg);

            removeTask(title);

            free(title);
            break;
        }

        

        case READ: {
            if (argNum != 1) {
                printColor("Please enter the required arguments!", "red");
                break;
            }

            char* arg = strtok(auxInput, " ");

            arg = strtok(NULL, " ");
            char* title = parseTitle(arg);

            readTask(title);

            free(title);
            break;
        }

        

        case LIST: {
            if (argNum != 0) {
                printColor("This commmand doesn't require any arguments!", "red");
                break;
            }

            listTasks();
            break;
        }



        case HELP: {
            if (argNum != 0) {
                printColor("This commmand doesn't require any arguments!", "red");
                break;
            }

            printColor(
                "Commands:                         \n"
                "- add -t='' -b='' : adds a task   \n"
                "- remove -t='' : removes a task   \n"
                "- read -t='' : reads a task       \n"
                "- list : lists all tasks          \n"
                "- help : shows available commands \n"
                "- exit : exits the app            \n",
                "cyan"
            );
            break;
        }



        case EXIT: {
            if (argNum != 0) {
                printColor("This commmand doesn't require any arguments!", "red");
                break;
            }

            free(command);
            free(auxInput);

            printColor("Exiting...", "yellow");
            return;
        }



        default: {
            printColor("Command not found!", "red");
            break;
        }
    }

    free(command);
    free(auxInput);

    runCommand();
}