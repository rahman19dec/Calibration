#include <stdio.h>
#include <stdlib.h>

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

void calibrate(SensorCalibrator *calibrator, float *sensor_data, float *expected_data, int data_length)
{
    float mean_sensor = 0.0;
    float mean_expected = 0.0;
    float numerator = 0.0;
    float denominator = 0.0;

    // Calculate the mean of sensor_data and expected_data
    for (int i = 0; i < data_length; ++i)
    {
        mean_sensor += sensor_data[i];
        mean_expected += expected_data[i];
    }
    mean_sensor /= data_length;
    mean_expected /= data_length;

    // Calculate the slope (m) and the intercept (c)
    for (int i = 0; i < data_length; ++i)
    {
        numerator += (sensor_data[i] - mean_sensor) * (expected_data[i] - mean_expected);
        denominator += (sensor_data[i] - mean_sensor) * (sensor_data[i] - mean_sensor);
    }
    calibrator->calibration_data.slope = numerator / denominator;
    calibrator->calibration_data.intercept = mean_expected - calibrator->calibration_data.slope * mean_sensor;

    // Plot the sensor data and expected data (Not implemented in C)
    printf("Calibration Completed.\n");
    printf("Slope: %f\n", calibrator->calibration_data.slope);
    printf("Intercept: %f\n", calibrator->calibration_data.intercept);
}

void apply_calibration(SensorCalibrator *calibrator, float *sensor_data, float *calibrated_data, int data_length)
{
    for (int i = 0; i < data_length; ++i)
    {
        calibrated_data[i] = calibrator->calibration_data.slope * sensor_data[i] + calibrator->calibration_data.intercept;
    }
}