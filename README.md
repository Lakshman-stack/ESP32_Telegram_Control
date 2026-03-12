# ESP32_Telegram_Control_Lock
# ESP32 Telegram Control System

## Overview
This project demonstrates how to control an ESP32 device remotely using a Telegram bot.

The ESP32 connects to WiFi and communicates with a Python Flask server.  
The server receives commands from Telegram and sends them to the ESP32.

Using Telegram commands, the LED connected to ESP32 can be turned ON or OFF.

---

## System Architecture

Telegram Bot → Python Flask Server → ESP32 → LED Control

---

## Technologies Used

- ESP32
- Arduino IDE
- Python
- Flask
- Telegram Bot API
- WiFi Communication
- JSON

---

## Project Structure
ESP32_Telegram_Control
│
├── ESP32_API_Client.ino
├── server.py
├── README.md

---

## Hardware Requirements

- ESP32 development board
- USB cable
- Computer

---

## Software Requirements

Install Python libraries:
pip install flask
pip install requests

---

## Step 1: Create Telegram Bot

1. Open Telegram
2. Search **BotFather**
3. Start the bot
4. Run command
/newbot

5. Give a name for the bot
6. Create a username ending with **bot**
7. Copy the **Bot Token**

Example:

---

## Step 2: Get Chat ID

Send a message to your bot.

Open browser and run:



This number is your **Chat ID**.

---

You will see JSON response.

Find:

## Step 3: Configure Server

Open **server.py**

Replace:

---

## Step 5: Upload ESP32 Code

1. Open Arduino IDE
2. Open file **ESP32_API_Client.ino**
3. Update WiFi credentials

4. Upload code to ESP32
5. Open **Serial Monitor**

You should see:

---

## Step 6: Send Telegram Command

Open your Telegram bot and send:
or

ESP32 will receive the command and control the LED.

---

## Example Serial Monitor Output


---

## Applications

- Smart home automation
- IoT remote device control
- Embedded system projects
- Remote monitoring systems

---

## Author

Lakshman Gowda

---

## License

This project is for educational and demonstration purposes.


