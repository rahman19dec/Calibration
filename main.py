from calibration import SensorCalibrator

# Initialize a calibrator
calibrator = SensorCalibrator(True)

# Calibrate the sensor
sensor_data_training = [10, 19, 31, 40, 50]
expected_data = [10, 22, 34, 46, 58]
calibrator.calibrate(sensor_data_training, expected_data)

print('Slope:', calibrator.calibration_data['slope'])
print('Intercept:', calibrator.calibration_data['intercept'])

# Save the calibration data
calibrator.save_calibration("temperature")

# Load the calibration data
loaded_calibrator = SensorCalibrator.load_calibration("temperature")
print('Slope:', loaded_calibrator.calibration_data['slope'])
print('Intercept:', loaded_calibrator.calibration_data['intercept'])

# Apply the calibration

sensor_data = [15, 24, 36, 46]
calibrated_data = loaded_calibrator.apply_calibration(sensor_data)
print('Calibrated Data:', calibrated_data)