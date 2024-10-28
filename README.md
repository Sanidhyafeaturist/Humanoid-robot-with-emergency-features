# Autonomous Humanoid Robot

## Overview

This project involves an autonomous humanoid robot capable of walking, flying, and independently detecting emergencies. The robot integrates various sensors and GSM communication to respond to critical situations, such as fires or accidents, while continuously monitoring its surroundings.

## Features

- **Independent Operation**: The robot can autonomously switch between walking and flying modes based on environmental conditions.
- **Emergency Detection**: Equipped with fire and sound sensors, the robot can detect emergencies and notify services with its GPS location.
- **Real-time Monitoring**: Continuously measures distance to obstacles and environmental hazards.
- **User-friendly GSM Communication**: Sends SMS alerts to designated emergency numbers.

## Hardware Requirements

To build the robot, you'll need the following components:

- **Microcontroller**: Arduino (e.g., Arduino Uno, Mega)
- **Sensors**:
  - Ultrasonic distance sensor (e.g., HC-SR04)
  - IR sensor (for fire detection)
  - Sound sensor (for accident detection)
  - GPS module (e.g., Neo-6M)
- **Motors**:
  - Brushless motors (for flying)
  - Servo motors (for walking)
- **GSM Module**: (e.g., SIM800L)
- **Power Supply**: Suitable batteries for motors and microcontroller

## Software Requirements

- **Arduino IDE**: Ensure you have the Arduino IDE installed to upload the code.
- **Libraries**:
  - Servo
  - NewPing
  - TinyGsmClient
  - TinyGPS++

## Setup Instructions

1. **Hardware Assembly**:
   - Connect the sensors and motors to the appropriate pins on the Arduino according to the provided code.
   - Ensure all connections are secure and components are powered correctly.

2. **Library Installation**:
   - Open Arduino IDE and install the necessary libraries via the Library Manager.

3. **Code Upload**:
   - Open the provided code in the Arduino IDE.
   - Adjust the GSM and GPS configurations as needed.
   - Upload the code to the Arduino board.

## Usage

Once assembled and programmed, the robot will automatically:
- Walk or fly based on its environmental conditions.
- Continuously monitor for emergencies.
- Send SMS alerts to emergency contacts with location details when a threat is detected.

## Future Enhancements

- Integrate visual processing for better hazard detection and navigation.
- Implement obstacle avoidance algorithms for improved mobility.
- Develop a user interface for manual overrides or settings adjustments.

## License

This project is open-source. Feel free to modify and distribute it under the terms of the [MIT License](LICENSE).

