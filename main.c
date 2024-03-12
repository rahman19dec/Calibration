// #include <stdio.h>
// #include <stdlib.h>
#include "calibration.h"

int main()
{
    SensorCalibrator calibrator;
    calibrator.linearity = "linear";

    float sensor_data_training[] = {10, 20, 30, 40, 50};
    float expected_data[] = {10, 22, 34, 46, 58};
    int data_length = sizeof(sensor_data_training) / sizeof(sensor_data_training[0]);

    // Calibrate the sensor
    calibrate(&calibrator, sensor_data_training, expected_data, data_length);

    float sensor_data[] = {60, 70, 80, 90, 100};
    float calibrated_data[data_length];

    // Apply calibration to new sensor data
    apply_calibration(&calibrator, sensor_data, calibrated_data, data_length);

    // Print calibrated data
    printf("Calibrated Data:\n");
    for (int i = 0; i < data_length; ++i)
    {
        printf("%f ", calibrated_data[i]);
    }
    printf("\n");

    return 0;
}