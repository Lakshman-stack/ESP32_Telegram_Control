from flask import Flask, request, jsonify
import requests
import threading
import time

app = Flask(__name__)

BOT_TOKEN = "8611486448:AAHy0CwXCg3A7-ySJdMBePG_3EiCZL1-iwQ"

last_update_id = 0
user_command = "LED_OFF"


def telegram_listener():
    global last_update_id
    global user_command

    while True:
        url = f"https://api.telegram.org/bot{BOT_TOKEN}/getUpdates"

        response = requests.get(url).json()

        if response["result"]:
            for update in response["result"]:

                if update["update_id"] > last_update_id:
                    last_update_id = update["update_id"]

                    message = update["message"]["text"]

                    print("Telegram Command:", message)

                    if message == "LED_ON":
                        user_command = "LED_ON"

                    elif message == "LED_OFF":
                        user_command = "LED_OFF"

        time.sleep(2)


@app.route('/device/data', methods=['POST'])
def receive_data():

    global user_command

    data = request.json
    print("ESP32 Data:", data)

    return jsonify({"command": user_command})


if __name__ == "__main__":

    threading.Thread(target=telegram_listener).start()

    app.run(host="0.0.0.0", port=5000)