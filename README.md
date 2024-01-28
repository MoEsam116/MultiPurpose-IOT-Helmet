# MultiPurpose-IOT-Helmet

Welcome to the documentation for the IoT Multipurpose Helmet project. This project combines various sensors and IoT capabilities to create a smart helmet with temperature and moisture monitoring (using DHT11), LED light control, and gas detection (using MQ5 sensor). Additionally, an LDR sensor is used to automatically control the LED light based on ambient light conditions.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Components](#components)
- [Setup](#setup)
- [Usage](#usage)
- [IoT Server](#iot-server)
- [Contributors](#contributors)
- [License](#license)

## Introduction

The IoT Multipurpose Helmet is designed to enhance safety and comfort by integrating various sensors and IoT functionalities. This documentation provides information on setting up the hardware, connecting to the IoT server, and utilizing the different features of the helmet.

## Features

1. Temperature and moisture monitoring using DHT11 sensor.
2. Gas detection using MQ5 sensor.
3. LED light control with manual and automatic modes.
4. Ambient light-based LED control using LDR sensor.

## Components

- STM32 Blue Pill microcontroller
- DHT11 sensor
- MQ5 gas sensor
- LDR sensor
- LED light module
- IoT server

## Setup

1. Clone the repository to your local machine.
2. Connect the sensors and LED light module to the STM32 Blue Pill following the provided circuit diagram.
3. Use an STM32-compatible IDE (e.g., STM32CubeIDE) to open and build the project.
4. Flash the compiled binary to the STM32 Blue Pill.
5. Configure the IoT server settings in the code.

## Usage

1. Wear the IoT Multipurpose Helmet.
2. Power on the helmet.
3. Monitor temperature, moisture, and gas levels in real-time.
4. Manually control the LED light using the specified buttons.
5. Enable automatic LED control for ambient light conditions.

## IoT Server

The helmet sends sensor data to the designated IoT server. You can set up your server or use a cloud-based platform to visualize and analyze the data. Refer to the server documentation for more details.

## Contributors

- Mohamed Waleed
- Mohamed Esam
- Mohamed Ayman
- Mohamed Wael
- Mohamed Ibrahim
- Ibrahim Mohamed

## License

This project is open-source and available under the terms of the Unlicense.

> **Note:** This software is provided "as is" without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose, and noninfringement. In no event shall the authors or copyright holders be liable for any claim, damages, or other liability, whether in an action of contract, tort, or otherwise, arising from, out of, or in connection with the software or the use or other dealings in the software.
