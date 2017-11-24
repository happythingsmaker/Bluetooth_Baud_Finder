/*********************************************************
    Bluetooth Serial Eco
    Written by Eunchan Park (박은찬)
**********************************************************/
#include <SoftwareSerial.h>
#define PIN_NUMBER_SW_SERIAL_TX     2
#define PIN_NUMBER_SW_SERIAL_RX     3

SoftwareSerial BTSerial(PIN_NUMBER_SW_SERIAL_RX, PIN_NUMBER_SW_SERIAL_TX);
void setup() {

    //!!!!!!!!!!!!!! write your baudrate !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    long tempBaud = 38400;

    BTSerial.begin(tempBaud );
    Serial.begin(tempBaud );
}

void loop() {

    if (Serial.available()) {
        BTSerial.write(Serial.read());
    }

    BTSerial.listen();
    if (BTSerial.available()) {
        Serial.write(BTSerial.read());
    }
}
