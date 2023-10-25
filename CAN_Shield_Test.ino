#include <Arduino.h>
#include <SPI.h>  //arduino SPI library
#include "mcp2515_can.h"  //library for MCP2515 CAN controller with SPI interface

//CS pin for MCP2515
#define SPI_CS_PIN 9

//init for MCP2512 with CS pin
mcp2515_can can(SPI_CS_PIN);

//setup function
void setup() {
    Serial.begin(115200); //set serial baud rate to 115200
    Serial.println("Monitor Begins"); // welcome message
    SPI.begin();  //initialize SPI interface
    
    // lopps with error message until CAN initializes successfully
    while (CAN_OK != can.begin(CAN_500KBPS)) {  // 500 KBPS is the speed of the QFSAE Mock ECU, set this to the speed of your device accordingly
        //error messages
        Serial.println("CAN INIT FAIL");
        Serial.println("TRY AGAIN");
        delay(1000);  //delay to avoid flooding serial monitor
    }
  
  // exits loops when CAN init is successful
  Serial.println("Initialization Success");
  Serial.println("Checking CAN Data...");
}

void loop() {
    // length and buffer array for CAN data
    unsigned char len = 0;
    unsigned char buf[8];

    // checks if new CAN msg is available
    if (CAN_MSGAVAIL == can.checkReceive()) {
        can.readMsgBuf(&len, buf);    //read CAN data given size of data and array to read to

        unsigned long canId = can.getCanId(); //stores value of CAN ID
        
        //prints CAN IDs and CAN message data
        Serial.print("CAN ID: ");
        Serial.println(canId, HEX);
        Serial.print("Byte 0 Data: ");
        Serial.println(buf[0]);
    }
}