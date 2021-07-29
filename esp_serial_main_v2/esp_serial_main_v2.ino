// on esp8266 de teste

String serial_data_request(String sensor_id = "")
{
    int request_attempt = 0, comma_index, asterisk_index, sensor_id_length;
    unsigned long wait_for_request = 0;
    String received;
    String received_measurements;

    sensor_id_length = sensor_id.length();

    // Clear serial buffer
    if (Serial.available())
    {
        // Serial.println("Had in serial before requesting sensor_id " + sensor_id + " data:");
        while (Serial.available())
        {
            received.concat(Serial.read());
        }
        received = "";
    }

    // #DEBUG
    // Serial.print("Begin sensor_id data request: ");
    // Serial.println(millis());

    while (!Serial.available() && request_attempt < 5)
    {
        request_attempt++;

        // #DEBUG
        // Serial.print("Time on while for requesting sensor_id " + sensor_id + "data: ");
        // Serial.println(millis());
        // Serial.print("Serial request attempt: " + String(request_attempt));
        // Serial.println(request_attempt);

        delay(100);
        // Sensor id
        Serial.print(String(sensor_id) + '\n');
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
        // "id1,1000,850*" -> "sensor_id id, measurement"
        received = Serial.readStringUntil('\n');

        if (sensor_id.equals(received.substring(0, sensor_id_length)))
        {
            comma_index = received.indexOf(",");
            asterisk_index = received.indexOf("*");

            received_measurements = received.substring(comma_index + 1, asterisk_index);

            // DEBUG
            Serial.println("Received: " + received);
            Serial.println("Measurement: " + received_measurements);

            return received_measurements;
        }
    }
    else
    {
        // If not received, "snr" = Serial Not Received
        // received.concat(sensor_id);
        received_measurements.concat("snr,snr");

        // #DEBUG
        Serial.println("Serial unavailable snr code, sends: " + received_measurements);

        return received_measurements;
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
    out = serial_data_request("id1");
    Serial.println("Data received for command id1: " + out);
    Serial.println("-----------------------------------------------------");
}

/*********************** RESULTADO **************************
23:02:49.726 -> id1
23:02:49.866 -> Received: id1,133,49*

23:02:49.866 -> Measurement: 133,49
23:02:49.913 -> Data received for command id1: 133,49
23:02:49.913 -> -----------------------------------------------------
23:02:54.928 -> id1
23:02:55.069 -> Received: id1,133,49*

23:02:55.069 -> Measurement: 133,49
23:02:55.115 -> Data received for command id1: 133,49
23:02:55.163 -> -----------------------------------------------------
23:03:00.167 -> id1
23:03:00.309 -> Received: id1,922,367*

23:03:00.309 -> Measurement: 922,367
23:03:00.309 -> Data received for command id1: 922,367
23:03:00.356 -> -----------------------------------------------------

******************************************************/