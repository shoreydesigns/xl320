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
 
 modified 4 Mar 2019
 Rues derived symmetric force feedback alg. for Sparrow1
 
 */

/* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP

// absolute value
#define ABS(a)                ((a) < 0 ? ((a)*(-1.0)) : (a))

// bounding
#define Limit(v,l,h)        (((v) > (h)) ? (h) : ((v) < (l)) ? (l) : (v))


//#define PresentLoad 41
Dynamixel Dxl(DXL_BUS_SERIAL1);  // Communicating with DYNAMIXELs attached to OpenCM9.04 headers

void setup() {
  // Dynamixel 2.0 Protocol -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(3);               // Begin communication at 1Mbps
  delay(100);
  
  Dxl.writeByte (254, 24, 0); // Broadcast to all XL-320's to disable torque using Broadcast ID# 254
  delay(100);    
               
  Dxl.writeByte (254, 11, 2); // Let's make sure all XL-320's are in JOINT MODE!
  delay(100);
  
  Dxl.writeByte (254, 24, 1); // Enable Torque for all DYNAMIXELs listening and get started!
  delay(100);
  
  Dxl.writeWord (254, 30, 512); // all servos desired position 512
  delay(3000);
  
  Dxl.writeWord (254, 15, 500);    // all servos Min torque
   
   // !?! 3 and 5 !?!?!
  Dxl.writeByte (3, 24, 0);    // servo 3  disable torque 
  Dxl.writeByte (5, 24, 0);    // servo 5  disable torque 
  delay(100); 
  
  Dxl.writeByte(1,5,10); //RW Response Delay Time            0  254  250
  Dxl.writeByte(2,5,10); //RW Response Delay Time            0  254  250
  
  pinMode(BOARD_LED_PIN, OUTPUT);
}


void setTorque(unsigned char servo,  int V) {
   V = Limit(ABS(V), 0, 400); // limit torque to 400 (?) we want enough to move, but not bite off a finger.
   Dxl.writeWord (servo, 35, V);
}

unsigned int getPos(unsigned char servo) {  
   Dxl.readWord(servo, 37);
}


void setDirection(unsigned char servo, int V) {
   if (0) {
   } else if (V > 0) {
     Dxl.writeWord (servo, 30, 1023); 
   } else if (V < 0) {
     Dxl.writeWord (servo, 30, 0); 
   }  
}


void loop() {

  int error;

  // this is non-intuitive. totally.
  error = (getPos(1) - getPos(2))/2; // work out the position error between the two servos
  
  // apply the same torque in opposite directions to each servo, some combination of movement 
  // will happen to eliminate the error.
  setTorque   (1,  error);
  setDirection(1, error); // sign might be backwards, try error, has to be opposite of paired servo
  
  setTorque   (2,  error);
  setDirection(2, -error);// sign might be backwards, try -error, has to be opposite of paired servo
  
  
 if (0) {
 } else if (error < 500)    {    Dxl.ledOn(2, 5);// Purple LED     
 } else if (error > -500)   {    Dxl.ledOn(2, 2);// Green LED     
 }  else                    {    Dxl.ledOn(2, 0);// LED off     
 }
  
 // give the servos time, looping too fast will cause problems
 delay(10); 
 
}

