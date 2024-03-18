from calibration import SensorCalibrator

# Initialize a calibrator
calibrator = SensorCalibrator(True)

# Calibrate the sensor
sensor_data_training = [45, 78, 90, 110, 150]
expected_data = [34, 36, 40, 43, 50]
calibrator.calibrate(sensor_data_training, expected_data)

print('Slope:', calibrator.calibration_data['slope'])
print('Intercept:', calibrator.calibration_data['intercept'])

# Save the calibration data
calibrator.save_calibration("Custom_Sensor2")

# Load the calibration data

# loaded_calibrator = SensorCalibrator.load_calibration("Custom_Sensor2")
loaded_calibrator1 = SensorCalibrator(True)
loaded_calibrator1.load_calibration("Custom_Sensor2")
print('Data:', loaded_calibrator1.calibration_data)

# Apply the calibration

sensor_data = [12, 23, 38, 48]
calibrated_data = loaded_calibrator1.apply_calibration(sensor_data)
print('Calibrated Data:', calibrated_data)


# Load the calibration data

# loaded_calibrator = SensorCalibrator.load_calibration("Custom_Sensor2")
loaded_calibrator2 = SensorCalibrator(True)
loaded_calibrator2.load_calibration("Custom_Sensor3")
print('Data:', loaded_calibrator2.calibration_data)

# Apply the calibration

sensor_data = [15, 24, 36, 46]
calibrated_data = loaded_calibrator2.apply_calibration(sensor_data)
print('Calibrated Data:', calibrated_data)