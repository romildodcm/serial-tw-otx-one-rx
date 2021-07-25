#include <SoftwareSerial.h>

const int led = 4;
const int analog_read_interval = 10000;
bool ledBlink = false;
int sample;
unsigned long last_analog_read = 0;

SoftwareSerial serialCom(2, 0); // RX,TX

bool serial_send(int measurement, String sensor_name = "")
{
    String command;
    String sensor_output;
    bool status_bool = false;

    if (serialCom.available())
    {
        command = serialCom.readStringUntil('\n');

        if (command.equals(sensor_name))
        {
            sensor_output.concat(sensor_name);
            sensor_output.concat(",");
            sensor_output.concat(String(measurement));

            // Sends data
            serialCom.println(sensor_output);
            status_bool = true;
        }
    }

    return status_bool;
}

void setup()
{
    serialCom.begin(9600);
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
}

void loop()
{
    if (abs(millis() - last_analog_read) > analog_read_interval)
    {
        last_analog_read = millis();
        // random int number
        sample = random(1023);
    }

    ledBlink = serial_send(sample, "s1");
    // ledBlink = serial_send(sample, "s2");

    if (ledBlink)
    {
        digitalWrite(led, HIGH);
        delay(1000);
        digitalWrite(led, LOW);
        ledBlink = false;
    }
}