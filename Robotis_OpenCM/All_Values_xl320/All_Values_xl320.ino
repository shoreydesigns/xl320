/* R+Task 2.0 Mini Default Sketch - OpenCM IDE port (XL_320)
 
                Compatibility
 CM900                  X
 OpenCM9.04             O
 
                  Dynamixel Compatibility
               AX    MX      RX    XL-320    Pro
 CM900          X      X      X        O      X
 OpenCM9.04     X      X      X        O      X
 **** OpenCM 485 EXP board is needed to use 4 pin Dynamixel and Pro Series ****  
 
 created 22 May 2014
 by ROBOTIS CO,.LTD.
 */

/* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP


//#define PresentLoad 41
Dynamixel Dxl(DXL_BUS_SERIAL1);  // Communicating with DYNAMIXELs attached to OpenCM9.04 headers

void setup() {
  // Dynamixel 2.0 Protocol -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(3);               // Begin communication at 1Mbps
  delay(100);
  Dxl.writeByte (254, 24, 0); // Broadcast to all XL-320's to disable torque using Broadcast ID# 254
  delay(100);                 // so we can access the EEPROM addresses.
  Dxl.writeByte (254, 11, 2); // Let's make sure all XL-320's are in JOINT MODE!
  delay(100);
  Dxl.writeByte (254, 24, 1); // Enable Torque for all DYNAMIXELs listening and get started!
  delay(100);
  Dxl.writeWord ( 254, 30, 512);
  delay(3000);
  Dxl.writeByte (1, 24, 0); // Broadcast to all XL-320's to disable torque using Broadcast ID# 254
   Dxl.writeWord (1, 15, 1023); // Max Torque
  Dxl.writeByte (3, 24, 0); // Broadcast to all XL-320's to disable torque using Broadcast ID# 254
  Dxl.writeByte (5, 24, 0); // Broadcast to all XL-320's to disable torque using Broadcast ID# 254
  delay(100);
  pinMode(BOARD_LED_PIN, OUTPUT);
}


void loop() 
{
   Dxl.writeByte (1, 24, 1); // Broadcast to all XL-320's to disable torque using Broadcast ID# 254
  // Dxl.writeWord (1, 15, 1023); // Max Torque
  /*
  int count = 0;
  for(count = 0; count<=7;count++){
    Dxl.ledOn(2, count);// XL-320 only movement XL-320 it has RGB LED 
    digitalWrite(BOARD_LED_PIN, HIGH); // set to as HIGH LED is turn-off
    delay(100);// Wait for 0.1 second
     
    Dxl.ledOff(2);//All Dynamixel LED off
    digitalWrite(BOARD_LED_PIN, LOW);  // set to as LOW LED is turn-on
    delay(100);// Wait for 0.1 second
  } 
 */
 //if (((Dxl.readWord(2,37) - Dxl.readWord(2,30)) -(Dxl.readWord(1,37) - Dxl.readWord(1,30))) > 20 && ((Dxl.readWord(2,37) - Dxl.readWord(2,30)) -(Dxl.readWord(1,37) - Dxl.readWord(1,30))) < 500)
 if ((Dxl.readWord(2,37) - Dxl.readWord(2,30)) > 20 && ((Dxl.readWord(2,37) - Dxl.readWord(2,30)) < 500))
   {
     Dxl.ledOn(2, 5);// Purple LED
     Dxl.writeByte (1, 24, 1); // Broadcast to all XL-320's torque on
   }
   else if ((Dxl.readWord(2,37) - Dxl.readWord(2,30)) < -20 && (Dxl.readWord(2,37) - Dxl.readWord(2,30)) > -500)
   {
     Dxl.ledOn(2, 2);// Green LED
     Dxl.writeByte (1, 24, 0); // Broadcast to all XL-320's torque on
   }
   else
   {
     Dxl.ledOn(2, 0);// LED off
     Dxl.writeByte (1, 24, 0); // Broadcast to all XL-320's to disable torque using Broadcast ID# 254
   }
   //                                                                        | min|max  |Intial Value
    //SerialUSB.println(Dxl.readWord(1,0)); //R Model Number                    -  -    350
    //SerialUSB.println(Dxl.readByte(1,2)); //R Firmware Version                -  --
    //SerialUSB.println(Dxl.readByte(1,3)); //RW DYNAMIXEL ID                   0  252  1
    //SerialUSB.println(Dxl.readByte(1,4)); //RW Communication Speed            0  3    3
    //SerialUSB.println(Dxl.readByte(1,5)); //RW Response Delay Time            0  254  250
    //SerialUSB.println(Dxl.readWord(1,6)); //RW Clockwise Angle Limit          0  1023 0
    //SerialUSB.println(Dxl.readWord(1,8)); //RW Counter-Clockwise Angle Limit  0  1023 1023
    //SerialUSB.println(Dxl.readByte(1,11)); //RW Control Mode 1Wheel 2Joint    1  2    2
    //SerialUSB.println(Dxl.readByte(1,12)); //RW Temperature Limit             0  159  65
    //SerialUSB.println(Dxl.readByte(1,13)); //RW Min Voltage Limit             50 250  65
    //SerialUSB.println(Dxl.readByte(1,14)); //RW Max Voltage Limit             50 250  90
     //SerialUSB.println(Dxl.readWord(1,15)); //RW Max Torque                   0  1023 1023
   //if (
   SerialUSB.println((Dxl.readWord(2,37) - Dxl.readWord(2,30)) - (Dxl.readWord(1,37) - Dxl.readWord(1,30)));
 //SerialUSB.println(Dxl.readWord(2,37) - Dxl.readWord(2,30)); // delta of Goal Position & Present Position
  //SerialUSB.println(Dxl.readWord(2,37)); //Present Position
  //SerialUSB.println(Dxl.readByte(2,49)); //Moving
 
  //SerialUSB.println(Dxl.readWord(2,30)); //Goal Position
 //SerialUSB.println(Dxl.readWord(2,39)); //Present Speed
 //SerialUSB.println(Dxl.readWord(2,41)); //Present Load
 //SerialUSB.println(Dxl.readByte(2,45)); //Present Voltage
  Dxl.writeWord ( 2, 30, Dxl.readWord(1,37));  // Set ID#2 Goal Position = ID#1 Present Position
 // Dxl.writeWord ( 4, 30, Dxl.readWord(3,37));  // Set ID#4 Goal Position = ID#3 Present Position
 // Dxl.writeWord ( 6, 30, Dxl.readWord(5,37));  // Set ID#6 Goal Position = ID#5 Present Position
 
 
}






