void setup()
{
    Serial.begin(115200);
    Serial.println("setup");
}

void loop()
{
    if (Serial.available()) {
        Serial.println((int)Serial.read());
    }
}

