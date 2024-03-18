#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

// gcc -c cJSON.c -o cJSON.o
// gcc -shared -o libcjson.so cJSON.o

// gcc -o test test.c -L. -lcjson

// export LD_LIBRARY_PATH=/media/rahman/Directory/Open\ Source/Calibration:$LD_LIBRARY_PATH

// ./test

// Function to save cJSON object to a JSON file
void save_json(const char *filename, cJSON *json)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Failed to open file for writing.\n");
        return;
    }

    char *json_string = cJSON_Print(json);
    if (json_string == NULL)
    {
        printf("Error: Failed to convert cJSON object to JSON string.\n");
        fclose(file);
        return;
    }

    fputs(json_string, file);
    fclose(file);
    free(json_string);
    printf("JSON data saved to '%s'.\n", filename);
}

// Function to load cJSON object from a JSON file
cJSON *load_json(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Failed to open file for reading.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *json_string = (char *)malloc(file_size + 1);
    if (json_string == NULL)
    {
        printf("Error: Failed to allocate memory for JSON string.\n");
        fclose(file);
        return NULL;
    }

    fread(json_string, 1, file_size, file);
    json_string[file_size] = '\0';

    fclose(file);

    cJSON *json = cJSON_Parse(json_string);
    free(json_string);

    if (json == NULL)
    {
        printf("Error: Failed to parse JSON string.\n");
    }

    return json;
}

int main()
{
    // Create a cJSON object representing JSON data
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", "John");
    cJSON_AddNumberToObject(json, "age", 30);
    cJSON_AddStringToObject(json, "city", "New York");

    // Save cJSON object to a JSON file
    save_json("data.json", json);

    // Load cJSON object from the JSON file
    cJSON *loaded_json = load_json("data.json");
    if (loaded_json != NULL)
    {
        // Extract values from the loaded cJSON object
        cJSON *name = cJSON_GetObjectItemCaseSensitive(loaded_json, "name");
        cJSON *age = cJSON_GetObjectItemCaseSensitive(loaded_json, "age");
        cJSON *city = cJSON_GetObjectItemCaseSensitive(loaded_json, "city");

        // Print extracted values
        printf("Name: %s\n", name->valuestring);
        printf("Age: %d\n", age->valueint);
        printf("City: %s\n", city->valuestring);

        // Clean up cJSON object
        cJSON_Delete(loaded_json);
    }

    // Clean up cJSON object
    cJSON_Delete(json);

    return 0;
}
