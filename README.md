📦 Project Motivation

Traditional cleaning in railway compartments often leads to inconsistent sanitation, which increases the risk of disease transmission. With rising public health concerns, especially post-COVID, there's a strong need for smarter and safer sanitation solutions. SANITRON addresses this by introducing automation into the sanitization process—reducing human effort while improving reliability.

⚙️ System Architecture

SANITRON consists of the following major components:

ESP32 – Main controller handling logic and connectivity

ESP32-CAM – Captures real-time footage for monitoring

PIR Sensor – Detects human presence to pause spraying

Ultrasonic Mist Maker – Converts sanitizer into fine mist

Motor Driver (L298N) – Drives 4-wheel motion

Servo Motors (SG90) – Controls movement of spray arms

Blynk App – For remote manual control and monitoring

🔁 Operating Flow

Bot is placed at the start of the train coach

Powers on, connects to Wi-Fi, and links to Blynk

Uses PIR sensor to detect people and stop misting

Moves through the compartment while spraying sanitizer

Sends live video feed using ESP32-CAM

Can be manually controlled via Blynk if needed

🧠 Key Highlights

Uses mist-based sanitization to avoid slippery surfaces

Enables remote monitoring and override

Fully mobile using side shaft motors and BO motors

Low-cost and easy to replicate using off-the-shelf components

🧪 Challenges Faced

Balancing power between motors and misting system

Handling Wi-Fi dropout in large compartments

Fine-tuning the sensitivity of motion detection

Ensuring stability while spraying and moving

🛠 Future Work

Implement autonomous path planning

Add obstacle mapping with IR or LIDAR

Build a custom mobile app instead of Blynk

Improve battery backup and add solar charging option
