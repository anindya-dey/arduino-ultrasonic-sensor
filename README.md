# Distance measurement using HC-SR04 Ultrasonic Sensor

In this project, we measure distance using HC-SR04 Ultrasonic sensor.

# Components
1. Arduino Uno
2. HC-SR04 Ultrasonic Sensor
3. DHT11 Temperature and Humidity Sensor
4. One LED and a resistor for limiting current
5. Breadboard
6. Some jumper wires

# Project Breakdown
1. First, we used the Ultrasonic Sensor as is, to calculate the distance of an object in front of it. It returns a `float` which denotes distance in centimetres.
2. Second, just for fun, we added an LED to indicate when we get closer to the sensor. For example, when our distance is less than 10 cm.
3. Last but not the least, as an improvement, we used the DHT22 (temperature and humidity) sensor to improve the speed of sound calculation, because the speed of sound depends on temperature and humidity.
