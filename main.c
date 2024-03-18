#include <stdio.h>
#include <stdlib.h>
#include "calibration.h"

int main()
{
    SensorCalibrator calibrator;
    calibrator.linearity = "linear";

    // Load calibration data from a JSON file
    load_calibration("calibration.json", &calibrator);

    // If calibration data doesn't exist or fails to load, perform calibration
    if (calibrator.calibration_data.slope == 0 && calibrator.calibration_data.intercept == 0)
    {
        float sensor_data_training[] = {10, 20, 30, 40, 50};
        float expected_data[] = {10, 22, 34, 46, 58};
        int data_length = sizeof(sensor_data_training) / sizeof(sensor_data_training[0]);

        // Calibrate the sensor
        calibrate(&calibrator, sensor_data_training, expected_data, data_length);

        // Save calibration data to a JSON file
        save_calibration("calibration.json", &calibrator);
    }

    float sensor_data[] = {60, 70, 80, 90, 100};
    float calibrated_data[sizeof(sensor_data) / sizeof(sensor_data[0])];

    // Apply calibration to new sensor data
    apply_calibration(&calibrator, sensor_data, calibrated_data, sizeof(sensor_data) / sizeof(sensor_data[0]));

    // Print calibrated data
    printf("Calibrated Data:\n");
    for (int i = 0; i < sizeof(calibrated_data) / sizeof(calibrated_data[0]); ++i)
    {
        printf("%f ", calibrated_data[i]);
    }
    printf("\n");

    return 0;
}
