#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

typedef struct
{
    float slope;
    float intercept;
} CalibrationData;

typedef struct
{
    char *linearity;
    CalibrationData calibration_data;
} SensorCalibrator;

// Function to save calibration data to a JSON file
void save_calibration(const char *filename, SensorCalibrator *calibrator)
{
    cJSON *root = cJSON_CreateObject();
    cJSON *sensor = cJSON_CreateObject();

    cJSON_AddItemToObject(sensor, "slope", cJSON_CreateNumber(calibrator->calibration_data.slope));
    cJSON_AddItemToObject(sensor, "intercept", cJSON_CreateNumber(calibrator->calibration_data.intercept));

    cJSON_AddItemToObject(root, "Custom_Sensor", sensor);

    char *json_string = cJSON_Print(root);
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Failed to open file for writing.\n");
        cJSON_Delete(root);
        return;
    }
    fprintf(file, "%s\n", json_string);
    fclose(file);
    free(json_string);
    cJSON_Delete(root);
    printf("Calibration data saved to '%s'.\n", filename);
}

// Function to load calibration data from a JSON file
void load_calibration(const char *filename, SensorCalibrator *calibrator)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Failed to open file for reading.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *json_string = (char *)malloc(file_size + 1);
    if (json_string == NULL)
    {
        printf("Error: Failed to allocate memory for JSON string.\n");
        fclose(file);
        return;
    }

    fread(json_string, 1, file_size, file);
    json_string[file_size] = '\0';
    fclose(file);

    cJSON *root = cJSON_Parse(json_string);
    free(json_string);

    if (root == NULL)
    {
        printf("Error: Failed to parse JSON string.\n");
        return;
    }

    cJSON *sensor = cJSON_GetObjectItemCaseSensitive(root, "Custom_Sensor");
    if (sensor == NULL)
    {
        printf("Error: JSON data format is incorrect.\n");
        cJSON_Delete(root);
        return;
    }

    cJSON *slope = cJSON_GetObjectItemCaseSensitive(sensor, "slope");
    cJSON *intercept = cJSON_GetObjectItemCaseSensitive(sensor, "intercept");

    if (!cJSON_IsNumber(slope) || !cJSON_IsNumber(intercept))
    {
        printf("Error: Invalid slope or intercept value.\n");
        cJSON_Delete(root);
        return;
    }

    calibrator->calibration_data.slope = (float)slope->valuedouble;
    calibrator->calibration_data.intercept = (float)intercept->valuedouble;

    cJSON_Delete(root);
    printf("Calibration data loaded from '%s'.\n", filename);
}