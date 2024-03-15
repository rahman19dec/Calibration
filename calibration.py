import json
import matplotlib.pyplot as plt

class SensorCalibrator:

    def __init__(self, linearity):
        # self.calibration_name = calibration_name
        self.linearity = linearity
        self.sensor_name = ''
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

        # Add annotations
        plt.text(sensor_data[-1], expected_data[-1], f'Slope: {slope:.2f}\nIntercept: {intercept:.2f}',
                 fontsize=10, verticalalignment='bottom', horizontalalignment='right')

        plt.show()

        # Store calibration data in the instance dictionary
        self.calibration_data['slope'] = slope
        self.calibration_data['intercept'] = intercept


    def load_calibration(self, sensor_name):
        self.sensor_name = sensor_name
        filename = "Calibrations.json"  # Assuming the JSON file is named Calibrations.json
        with open(filename, 'r') as file:
            all_calibrations = json.load(file)
        if sensor_name in all_calibrations:
            self.calibration_data = all_calibrations[sensor_name]
            print(f"Calibration data loaded for sensor '{sensor_name}': {self.calibration_data}")

        else:
            print(f"No calibration data found for sensor '{sensor_name}'.")


    def save_calibration(self, sensor_name):
        filename = "Calibrations.json"  # Assuming the JSON file is named Calibrations.json
        try:
            with open(filename, 'r') as file:
                all_calibrations = json.load(file)
        except FileNotFoundError:
            all_calibrations = {}

        all_calibrations[sensor_name] = self.calibration_data

        with open(filename, 'w') as file:
            json.dump(all_calibrations, file, indent=4)

        print(f"Calibration data saved for sensor '{sensor_name}'.")


    def apply_calibration(self, sensor_data):
        if 'slope' in self.calibration_data and 'intercept' in self.calibration_data:
            calibrated_data = [self.calibration_data['slope'] * x + self.calibration_data['intercept'] for x in sensor_data]
            return calibrated_data
        else:
            print("Calibration data not found. Please calibrate first.")
            return None