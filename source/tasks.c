#include "../cjson/cJSON.h"


struct Task {
    char* title;
    char* description;
} tasks[100];

int length = 0;



void loadTasks () {
    FILE* file = fopen("data.json", "r");


    if (file == NULL) {
        file = fopen("data.json", "wb");
        fputs("[]", file);
    } else {
        char buffer[1024] = {0};
        fread(buffer, 1, sizeof(buffer), file);


        cJSON* root = cJSON_Parse(buffer);
        length = cJSON_GetArraySize(root);


        for (int i = 0; i < length; i++) {
            cJSON* object = cJSON_GetArrayItem(root, i);

            cJSON* title = cJSON_GetObjectItem(object, "title");
            cJSON* description = cJSON_GetObjectItem(object, "description");

            tasks[i].title = malloc(100);
            tasks[i].description = malloc(100);

            strcpy(tasks[i].title, title->valuestring);
            strcpy(tasks[i].description, description->valuestring);
        }
        
        cJSON_Delete(root);
    }
    

    fclose(file);
}


void saveTasks () {
    cJSON* root = cJSON_CreateArray();

    for (int i = 0; i < length; i++) {
        cJSON* task = cJSON_CreateObject();

        cJSON_AddStringToObject(task, "title", tasks[i].title);
        cJSON_AddStringToObject(task, "description", tasks[i].description);

        cJSON_AddItemToArray(root, task);
    }


    char* out = cJSON_Print(root);

    FILE* file = fopen("data.json", "w");
    fprintf(file, "%s", out);
    fclose(file);

    free(out);
    cJSON_Delete(root);
}


void addTask (char* title, char* description) {

    for (int i = 0; i < length; i++) {
        if (strcmp (tasks[i].title, title) == 0) {
            printColor ("The task already exists!", "red");
            return;
        }
    }


    tasks[length].title = malloc(100);
    tasks[length].description = malloc(100);


    strcpy (tasks[length].title, title);
    strcpy (tasks[length].description, description);


    length++;
    printColor ("Task added successfully!", "green");

    saveTasks ();
}




void removeTask (char* title) {
    bool passedObject = false;

    for (int i = 0; i < length; i++) {
        if (strcmp (tasks[i].title, title) == 0) {
            passedObject = true;
            length--;

            if (i == length) 
                break;
        }

        if (passedObject) {
            strcpy (tasks[i].title, tasks[i + 1].title);
            strcpy (tasks[i].description, tasks[i + 1].description);
        }
    }


    if (!passedObject)
        printColor ("Task not found!", "red");
    else {
        printColor ("Task removed successfully!", "green");
        free(tasks[length].title);
        free(tasks[length].description);
    }


    saveTasks ();
}




void readTask (char* title) {

    for (int i = 0; i < length; i++) {
        if (strcmp (tasks[i].title, title) == 0) {
            printf (cyan "\nTask - %s : %s\n\n" white, tasks[i].title, tasks[i].description);
            return;
        }
    }

    printColor("Task not found!", "red");
}




void listTasks () {
    if (length == 0) {
        printColor("No tasks to show", "yellow");
        return;
    }

    printColor("Tasks:", "yellow");

    for (int i = 0; i < length; i++) 
        printf(blue "%s\n" white, tasks[i].title);
        
    printf("\n\n");
}