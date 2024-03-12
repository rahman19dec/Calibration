import json
import matplotlib.pyplot as plt

class SensorCalibrator:

    def __init__(self, linearity):
        # self.calibration_name = calibration_name
        self.linearity = linearity
        self.calibration_data = {}

    def calibrate(self, sensor_data, expected_data):
        # Calculate the mean of sensor_data and expected_data
        mean_sensor = sum(sensor_data) / len(sensor_data)
        mean_expected = sum(expected_data) / len(expected_data)

        # Calculate the slope (m)
        numerator = sum((sensor - mean_sensor) * (expected - mean_expected) for sensor, expected in zip(sensor_data, expected_data))
        denominator = sum((sensor - mean_sensor) ** 2 for sensor in sensor_data)
        slope = numerator / denominator

        # Calculate the intercept (c)
        intercept = mean_expected - slope * mean_sensor

        # Plot the sensor data and expected data
        plt.scatter(sensor_data, expected_data, label='Sensor Data')
        plt.plot(sensor_data, [slope * x + intercept for x in sensor_data], color='red', label='Linear Fit')
        plt.xlabel('Sensor Data')
        plt.ylabel('Expected Data')
        plt.legend()
        plt.show()

        # Store calibration data in the instance dictionary
        self.calibration_data['slope'] = slope
        self.calibration_data['intercept'] = intercept


    @classmethod
    def load_calibration(cls, calibration_name):
        filename = f"{calibration_name}_calibration.json"
        with open(filename, 'r') as file:
            calibration_data = json.load(file)
        calibrator = cls(calibration_name)
        calibrator.calibration_data = calibration_data
        return calibrator
    
    def apply_calibration(self, sensor_data):
        if 'slope' in self.calibration_data and 'intercept' in self.calibration_data:
            calibrated_data = [self.calibration_data['slope'] * x + self.calibration_data['intercept'] for x in sensor_data]
            return calibrated_data
        else:
            print("Calibration data not found. Please calibrate first.")
            return None
    
    def save_calibration(self, calibration_name):
        filename = f"{calibration_name}_calibration.json"
        with open(filename, 'w') as file:
            json.dump(self.calibration_data, file)
        print(f"Calibration data saved to '{filename}'.")