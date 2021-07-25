/***************************************************
 * Request data from 1/2 sensor connected via serial
 * parameter: "s1" for sensor 1 or "s2" for sensor 2
 * returns: data received from the sensor
 *          or snr (serial not received).
 * ************************************************/
String serial_data_request(String sensor = "")
{
    int request_attempt = 0, comma_index;
    unsigned long wait_for_request = 0;
    String received;
    String received_measurement;

    // Clear
    if (Serial.available())
    {
        // Serial.println("Had in serial before requesting sensor " + sensor + " data:");
        while (Serial.available())
        {
            received.concat(Serial.read());
        }
        received = "";
    }

    // #DEBUG
    // Serial.print("Begin sensor data request: ");
    // Serial.println(millis());

    while (!Serial.available() && request_attempt < 3)
    {
        request_attempt++;

        // #DEBUG
        // Serial.print("Time on while for requesting sensor " + sensor + "data: ");
        // Serial.println(millis());
        // Serial.print("Serial request attempt: " + String(request_attempt));
        // Serial.println(request_attempt);

        delay(100);
        // Sensor id
        Serial.print(String(sensor) + '\n');
        // Serial.println();

        wait_for_request = millis();
        while ((abs(millis() - wait_for_request) < 2000) && !Serial.available())
        {
            // #DEBUG
            // Serial.print("Serial delay while, serial status: ");
            // Serial.println(Serial.available());

            delay(100);
        }
    }

    if (Serial.available())
    {
        // "s1,1000" -> "sensor id, measurement"
        received = Serial.readStringUntil('\n');

        if (sensor.equals(received.substring(0, 2)))
        {
            comma_index = received.indexOf(",");
            received_measurement = received.substring(comma_index + 1);

            // DEBUG
            Serial.println("Received: " + received);
            Serial.println("Measurement: " + received_measurement);

            return received_measurement;
        }
    }
    else
    {
        // If not received, "snr" = Serial Not Received
        // received.concat(sensor);
        received.concat("snr");

        // #DEBUG
        Serial.println("Serial unavailable snr code, sends: " + received);

        return received;
    }
}

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    delay(5000);

    String out;
    out = serial_data_request("s1");
    Serial.println("Data received for command s1: " + out);
    Serial.println("---------------------------------------");

    delay(1000);
    out = serial_data_request("s2");
    Serial.println("Data received for command s2: " + out);
    Serial.println("---------------------------------------");
}