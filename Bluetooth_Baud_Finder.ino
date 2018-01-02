/*********************************************************
    BLUETOOTH BAUD FINDER
    This is an Arduino Code for Modifying Bluetooth Setting such as HC05, HM10

    There are many version of Bluetooth Modules
    Everytime I tried to set up bluetooth, I had to select various baudrate settings.

    This code finds baudrate of Bluetooth and set
    the Software Serial Communication based on the baudrate which was found

    You can start to set up with AT command without boring works

    Written by Eunchan Park (박은찬)
    BSD license, all text above must be included in any redistribution
**********************************************************/
#include <SoftwareSerial.h>
#define PIN_NUMBER_SW_SERIAL_TX     2
#define PIN_NUMBER_SW_SERIAL_RX     3

SoftwareSerial BTSerial(PIN_NUMBER_SW_SERIAL_RX, PIN_NUMBER_SW_SERIAL_TX);
void setup() {
    Serial.begin(9600);
    long tempBaud = checkBaudRate();
//    long tempBaud = 38400;
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

long checkBaudRate() {

    long baud[18] = {300, 1200, 2400, 4800, 9600, 19200, 38400,
                     57600, 74880, 115200, 230400, 250000, 500000,
                     1000000, 23400, 460800, 921600, 1382400
                    };
    Serial.println("http://HappyThingsMaker.com");
    int repeatCount = 10;
    while (repeatCount --) {
        for (int i = 0; i < 18 ; i ++) {
            Serial.print("TESTING BAUD : ");
            Serial.println(baud[i]);
            BTSerial.begin(baud[i]);

            BTSerial.write("AT\r\n");
            BTSerial.listen();
            int innerCount = 0;
            while (1) {
                while (BTSerial.available()) {
                    Serial.println("Received something");
                    Serial.print("FOUND BAUD : ");
                    Serial.println(baud[i]);
                    Serial.print("YOU NEED TO CHANGE TERMINAL BAUD RATE AS : ");
                    Serial.println(baud[i]);
                    Serial.println("WITH <CR> & <NL>");
                    delay(100);
                    return baud[i];
                }
                delay(1);
                if (innerCount ++ > 100) {
                    break;
                }
            }

            //some bluetooth don't react when they receive  <CR> & <NL>
            //in this case, we need to send only AT
            BTSerial.write("AT");

            BTSerial.listen();
            innerCount = 0;
            while (1) {
                while (BTSerial.available()) {
                    Serial.println("Received something");
                    Serial.print("FOUND BAUD : ");
                    Serial.println(baud[i]);
                    Serial.print("YOU NEED TO CHANGE TERMINAL BAUD RATE AS : ");
                    Serial.println(baud[i]);
                    Serial.println("WITHOUT <CR> & <NL>");
                    delay(100);
                    return baud[i];
                }
                delay(1);
                if (innerCount ++ > 100) {
                    break;
                }
            }
        }
    }
}
