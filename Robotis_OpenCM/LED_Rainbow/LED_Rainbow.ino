/* Dynamixel ledOn
 Hello World for LED on the Motor (motor Turning is different)
 This example shows how to use dynamixel as ledOn
 
 
               Compatibility
 CM900                  O
 OpenCM9.04             O
 
                   Dynamixel Compatibility
               AX    MX      RX   XL-320    Pro
 CM900          X      X      X        O      X
 OpenCM9.04     X      X      X        O      X
**** OpenCM 485 EXP board is needed to use 4 pin Dynamixel and Pro Series ****
 
 created 22 May 2014
 by ROBOTIS CO,.LTD.
 */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP

#define ID_NUM 1

Dynamixel Dxl(DXL_BUS_SERIAL1);

void setup() {
  // Initialize the dynamixel bus  
  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps  
  Dxl.begin(3);  
}

void loop() {
   //Dxl.ledOn(ID_NUM, count);// XL-320 only movement XL-320 it has RGB LED 
   // the color by Number
   /*
    Dxl.ledOn(ID_NUM, 1); // Red LED
    Dxl.ledOn(ID_NUM, 2);// Green LED
    Dxl.ledOn(ID_NUM, 3);// Yellow LED 
    Dxl.ledOn(ID_NUM, 4);// Blue LED
    Dxl.ledOn(ID_NUM, 5);// Purple LED
    Dxl.ledOn(ID_NUM, 6);// Blue-Green LED 
    Dxl.ledOn(ID_NUM, 7);// Whiteish LED
   */ 
  
    
    // LED Rainbow 
    Dxl.ledOn(ID_NUM, 1); // Red LED
    delay(200);
    Dxl.ledOn(ID_NUM, 3);// Yellow LED 
    delay(200);
    Dxl.ledOn(ID_NUM, 2);// Green LED
    delay(200);
    Dxl.ledOn(ID_NUM, 6);// Blue-Green LED
    delay(200); 
    Dxl.ledOn(ID_NUM, 4);// Blue LED
    delay(200);
    Dxl.ledOn(ID_NUM, 5);// Purple LED
    delay(200);
    //Dxl.ledOff(ID_NUM);//All Dynamixel LED off
    //delay(500);
  
}



