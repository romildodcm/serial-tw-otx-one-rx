String received = "id1,1000,850*", received_measurements = "", string = "Carlos Touca";

void setup()
{
    Serial.begin(9600);
    delay(5000);
}
void loop()
{
    Serial.print("a string: " + string);
    Serial.print("\n");
    Serial.print("a posicao da letra 'u' na string eh: ");
    Serial.print(string.indexOf("u"));
    Serial.print("\n");
    Serial.print("a posicao da letra 'a' na string eh: ");
    Serial.print(string.indexOf("a"));
    Serial.print("\n");
    Serial.print("a posicao da letra 'a' na string eh: ");
    Serial.print(string.indexOf("a", 6));
    Serial.print("\n");
    Serial.print("a posicao da string 'Tou' na string eh: ");
    Serial.print(string.indexOf("Tou"));
    Serial.println("----------------------------");

    int comma_index = received.indexOf(",");
    int asterisk_index = received.indexOf("*");

    received_measurements = received.substring(comma_index + 1, asterisk_index);

    // DEBUG
    Serial.println("Received: " + received);
    Serial.println("Measurement: " + received_measurements);

    delay(10000);
}

/******************** OUTPUT *************************************
 * 22:45:11.897 -> a string: Carlos Touca
 * 22:45:11.897 -> a posicao da letra 'u' na string eh: 9
 * 22:45:11.944 -> a posicao da letra 'a' na string eh: 1
 * 22:45:11.989 -> a posicao da letra 'a' na string eh: 11
 * 22:45:12.036 -> a posicao da string 'Tou' na string eh: 7
 * ----------------------------
 * 22:45:12.084 -> Received: id1,1000,850*
 * 22:45:12.132 -> Measurement: 1000,850
 * 
 * ***************************************************************/