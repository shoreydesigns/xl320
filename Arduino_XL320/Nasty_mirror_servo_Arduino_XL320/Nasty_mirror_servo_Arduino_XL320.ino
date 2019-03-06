/*
  Motor : XL320

  DEVICENAME "1" -> Serial1
  DEVICENAME "2" -> Serial2
  DEVICENAME "3" -> Serial3
*/

#include <DynamixelSDK.h>

 //  Control Table of EEPROM Area                                          | min|max  |Intial Value
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
    //SerialUSB.println(Dxl.readWord(1,15)); //RW Max Torque                    0  1023 1023
    //SerialUSB.println(Dxl.readByte(1,17)); //RW Status Return Level           0  2     2 
    // This value decides how to return Status Packet when Dynamixel receives an Instruction Packet.
    // 0 PING Instruction   Status Packet will not be returned for all Instructions
    // 1 PING  & READ Instruction   Status Packet will be returned only for READ Instruction
    // 2 All Instructions   Status Packet will be returned for all Instructions

    //SerialUSB.println(Dxl.readByte(1,18)); //RW Shutdown Error Information    0  7    3
    
    //  RAM Area                                                             | min|max  |Intial Value
    //SerialUSB.println(Dxl.readByte(1,24)); //RW Motor Torque On/Off           0  1    0
    //SerialUSB.println(Dxl.readByte(1,25)); //RW RGB LED                       0  7    0
    //SerialUSB.println(Dxl.readByte(1,27)); //RW D Derivative Gain             0  254  0
    //SerialUSB.println(Dxl.readByte(1,28)); //RW I Integral Gain               0  254  0
    //SerialUSB.println(Dxl.readByte(1,29)); //RW P Proportional Gain           0  254  32
    
    //SerialUSB.println(Dxl.readWord(1,30)); //RW Desired Position              0  1023  -
    //SerialUSB.println(Dxl.readWord(1,32)); //RW Moving Speed(Velocity)        0  2047  -
    //SerialUSB.println(Dxl.readWord(1,35)); //RW Torque Limit(Goal Torque)     0  1023  -
    //SerialUSB.println(Dxl.readWord(1,37)); //R Present Position               -  -     -
    //SerialUSB.println(Dxl.readWord(1,39)); //R Present Speed                  -  -     -
    //SerialUSB.println(Dxl.readWord(1,41)); //R Present Load                   -  -     -
    
    //SerialUSB.println(Dxl.readByte(1,45)); //R Present Voltage                -  -     -
    //SerialUSB.println(Dxl.readByte(1,46)); //R Present Temperature            -  -     -
    //SerialUSB.println(Dxl.readByte(1,47)); //R If Instruction is registered   -  -     0
    //SerialUSB.println(Dxl.readByte(1,49)); //R Moving Movement Status         -  -     0
    //SerialUSB.println(Dxl.readByte(1,50)); //R Hardware Error Status          -  -     0
    //SerialUSB.println(Dxl.readWord(1,45)); //RW Punch Min Current Threshold   0  1023  32

// Control table address (XL320)
//Control Table of EEPROM Area                                       | min|max  |Intial Value
#define ADDR_MODEL_NUMBER 0   //Word R Model Number                     -  -    350
#define ADDR_FIRMWARE 2 //Byte R Firmware Version                       -  --
#define ADDR_SERVO_ID 3 //Byte RW DYNAMIXEL ID                          0  252  1
#define ADDR_COMM_SPEED 4 //Byte RW Communication Speed                 0  3    3
#define ADDR_RESPONSE_DELAY_TIME 5 //ByteRW Response Delay Time         0  254  250
#define ADDR_CW_ANGLE_LIMIT 6  //Word RW Clockwise Angle Limit          0  1023 0
#define ADDR_CCW_ANGLE_LIMIT 8 //Word RW Counter-Clockwise Angle Limit  0  1023 1023
#define ADDR_CONTROL_MODE 11 //Byte RW Control Mode 1Wheel 2Joint       1  2    2
#define ADDR_TEMP_LIMIT 12)); //Byte RW Temperature Limit               0  159  65
#define ADDR_MAX_VOLT 13)); //Byte RW Min Voltage Limit                 50 250  65
#define ADDR_MIN_VOLT 14)); //Byte RW Max Voltage Limit                 50 250  90
#define ADDR_MAX_TORQUE 15)); //Word RW Max Torque                      0  1023 1023
#define ADDR_STATUS_RETURN_LEVEL 17)); //Byte RW Status Return Level    0  2     2 
// This value decides how to return Status Packet when Dynamixel receives an Instruction Packet.
    // 0 PING Instruction   Status Packet will not be returned for all Instructions
    // 1 PING  & READ Instruction   Status Packet will be returned only for READ Instruction
    // 2 All Instructions   Status Packet will be returned for all Instructions
#define ADDR_SHUTDOWN_ERROR 18//Byte //RW Shutdown Error Information    0  7    3

//  RAM Area                                                        | min|max  |Intial Value
#define ADDR_TORQUE_SWITCH 24  //Byte RW Motor Torque On/Off           0  1    0
#define ADDR_LED 25 //Byte RW RGB LED                                  0  7    0
#define ADDR_D_GAIN 27 //Byte RW D Derivative Gain                     0  254  0
#define ADDR_I_GAIN 28 //Byte RW I Integral Gain                       0  254  0
#define ADDR_P_GAIN 29 // Byte RW P Proportional Gain                  0  254  32

#define ADDR_GOAL_POSITION 30//Word RW Desired Position                0  1023  -
#define ADDR_MOVING_SPEED 32 //Word RW Moving Speed(Velocity)          0  2047  -
#define ADDR_GOAL_TORQUE 35 //Word RW Torque Limit(Goal Torque)        0  1023  -
#define ADDR_PRESENT_POSITION  37 //Word R Present Position            -  -     -
#define ADDR_PRESENT_SPEED 39 //Word R Present Speed                   -  -     -
#define ADDR_PRESENT_LOAD 41 //Word R Present Load                     -  -     -

#define ADDR_PRESENT_VOLTAGE 45 //BytE R Present Voltage               -  -     -
#define ADDR_TEMP 46 //Byte R Present Temperature                      -  -     -
#define ADDR_INSTRUCTION_REGISTERED 47//Byte R If Instruction is registered - - 0
#define ADDR_MOVEMENT_STATUS 49// Byte /R Moving Movement Status       -  -     0
#define ADDR_HARDWARE_ERROR 50//Byte R Hardware Error Status           -  -     0
#define ADDR_PUNCH 51 //Word  RW Punch Min Current Threshold           0  1023  32

    


// Protocol version
#define PROTOCOL_VERSION                2.0                 // See which protocol version is used in the Dynamixel

// Default setting
#define MASTER_ID                          1                   // Dynamixel ID: 1
#define SLAVE_ID                          2                   // Dynamixel ID: 2
#define BAUDRATE                        1000000
#define DEVICENAME                      "1"                 // Check which port is being used on your controller
                                                            // ex) Windows: "COM1"   Linux: "/dev/ttyUSB0"

#define TORQUE_ON                   1                   // Value for enabling the torque
#define TORQUE_OFF                  0                   // Value for disabling the torque
#define DXL_MINIMUM_POSITION_VALUE      600                 // Dynamixel will rotate between this value
#define DXL_MAXIMUM_POSITION_VALUE      200                 // and this value (note that the Dynamixel would not move when the position value is out of movable range. Check e-manual about the range of the Dynamixel you use.)
#define DXL_MOVING_STATUS_THRESHOLD     20                  // Dynamixel moving status threshold

#define ESC_ASCII_VALUE                 0x1b



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);


  Serial.println("Start..");


  // Initialize PortHandler instance
  // Set the port path
  // Get methods and members of PortHandlerLinux or PortHandlerWindows
  dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);

  // Initialize PacketHandler instance
  // Set the protocol version
  // Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
  dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

  int index = 0;
  int dxl_comm_result = COMM_TX_FAIL;             // Communication result
  int dxl_goal_position[2] = {DXL_MINIMUM_POSITION_VALUE, DXL_MAXIMUM_POSITION_VALUE};         // Goal position

  uint8_t dxl_error = 0;                          // Dynamixel error
  int16_t Slave_present_position = 512;               // Present position
  int16_t Master_present_position = 512;               // Present position
  int16_t present_position320XL = 512;     // Present position  #define ADDR_PRESENT_POSITION      37
  int16_t ccwAngleLimit = 0; //#define ADDR_CCW_ANGLE_LIMIT 8 //Word RW Counter-Clockwise Angle Limit  0  1023 1023

// my code
/*
// Dynamixel 2.0 Protocol -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(3);               // Begin communication at 1Mbps
  delay(100);
  // DISABLE Dynamixel Torque
  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, 254, ADDR_TORQUE_SWITCH, TORQUE_OFF , &dxl_error);
  if (dxl_comm_result != COMM_SUCCESS)
  {
    packetHandler->getTxRxResult(dxl_comm_result);
  }
  else if (dxl_error != 0)
  {
    packetHandler->getRxPacketError(dxl_error);
  }
  else
  {
    Serial.print("Dynamixel has been successfully connected \n");
  }
  delay(100); 
//
  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, 254, ADDR_TORQUE_SWITCH, TORQUE_OFF , &dxl_error);
  if (dxl_comm_result != COMM_SUCCESS)
  {
    packetHandler->getTxRxResult(dxl_comm_result);
  }
  else if (dxl_error != 0)
  {
    packetHandler->getRxPacketError(dxl_error);
  }
  else
  {
    Serial.print("Dynamixel has been successfully connected \n");
  }
  delay(100); 
  //TORQUE_OFF 
 // Dxl.writeByte (254, 24, 0); // Broadcast to all XL-320's to disable torque using Broadcast ID# 254
 // delay(100);                 // so we can access the EEPROM addresses.
  Dxl.writeByte (254, 11, 2); // Let's make sure all XL-320's are in JOINT MODE!
  delay(100);
  Dxl.writeByte (254, 24, 1); // Enable Torque for all DYNAMIXELs listening and get started!
  delay(100);
  Dxl.writeWord ( 254, 30, 512);
  delay(3000);
  Dxl.writeByte (1, 24, 0); // Broadcast to all XL-320's to disable torque using Broadcast ID# 254
  Dxl.writeByte (3, 24, 0); // Broadcast to all XL-320's to disable torque using Broadcast ID# 254
  Dxl.writeByte (5, 24, 0); // Broadcast to all XL-320's to disable torque using Broadcast ID# 254
  delay(100);
  pinMode(BOARD_LED_PIN, OUTPUT);

*/


  // Open port
  if (portHandler->openPort())
  {
    Serial.print("Succeeded to open the port!\n");
  }
  else
  {
    Serial.print("Failed to open the port!\n");
    Serial.print("Press any key to terminate...\n");
    return;
  }

  // Set port baudrate
  if (portHandler->setBaudRate(BAUDRATE))
  {
    Serial.print("Succeeded to change the baudrate!\n");
  }
  else
  {
    Serial.print("Failed to change the baudrate!\n");
    Serial.print("Press any key to terminate...\n");
    return;
  }

  // Enable Dynamixel Torque
  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, SLAVE_ID, ADDR_TORQUE_SWITCH, TORQUE_ON, &dxl_error);
  if (dxl_comm_result != COMM_SUCCESS)
  {
    packetHandler->getTxRxResult(dxl_comm_result);
  }
  else if (dxl_error != 0)
  {
    packetHandler->getRxPacketError(dxl_error);
  }
  else
  {
    Serial.print("Dynamixel has been successfully connected \n");
  }

  // not Enable Dynamixel Torque
  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, MASTER_ID, ADDR_TORQUE_SWITCH, TORQUE_OFF, &dxl_error);
  if (dxl_comm_result != COMM_SUCCESS)
  {
    packetHandler->getTxRxResult(dxl_comm_result);
  }
  else if (dxl_error != 0)
  {
    packetHandler->getRxPacketError(dxl_error);
  }
  else
  {
    Serial.print("Dynamixel has been successfully connected2 \n");
  }
 //Dxl.writeByte (254, 11, 2); // Let's make sure all XL-320's are in JOINT MODE!

  while(1)
  {
  

    while(Serial.available()==0);

    int ch;

    ch = Serial.read();
    if (ch == 'q')
      break;
//writeToServo(SLAVE_ID, ADDR_GOAL_POSITION,dxl_goal_position[index]  ); // ( int id, int command, int val)
//Dxl.writeWord ( 2, 30, Dxl.readWord(1,37));  // Set ID#2 Goal Position = ID#1 Present Position

    // Write goal position
    packetHandler->write2ByteTxRx(portHandler, SLAVE_ID, ADDR_GOAL_POSITION, dxl_goal_position[index]);
   // dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, SLAVE_ID, ADDR_GOAL_POSITION, dxl_goal_position[index], &dxl_error);
    //dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, SLAVE_ID, ADDR_GOAL_POSITION, Master_present_position, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
      packetHandler->getTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
      packetHandler->getRxPacketError(dxl_error);
    }

    do
    {
      // Read present position
      dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, SLAVE_ID, ADDR_PRESENT_POSITION, (uint16_t*)&Slave_present_position, &dxl_error);
      if (dxl_comm_result != COMM_SUCCESS)
      {
        packetHandler->getTxRxResult(dxl_comm_result);
      }
      else if (dxl_error != 0)
      {
        packetHandler->getRxPacketError(dxl_error);
      }


       // Read present position
      dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, 1, ADDR_PRESENT_POSITION, (uint16_t*)&Master_present_position, &dxl_error);
      if (dxl_comm_result != COMM_SUCCESS)
      {
        packetHandler->getTxRxResult(dxl_comm_result);
      }
      else if (dxl_error != 0)
      {
        packetHandler->getRxPacketError(dxl_error);
      }

      dxl_goal_position[1]= Master_present_position;
      dxl_goal_position[0]= Master_present_position;
      packetHandler->write2ByteTxRx(portHandler, SLAVE_ID, ADDR_GOAL_POSITION, dxl_goal_position[index]);
      Serial.print("[Slave ID:");      Serial.print(SLAVE_ID);
      Serial.print(" GoalPos:"); Serial.print(dxl_goal_position[index]);
      Serial.print(" PresPos:");  Serial.print(Slave_present_position);
      Serial.println(" ");
      Serial.print("[Master ID:");      Serial.print(1);
      Serial.print(" GoalPos:"); Serial.print(dxl_goal_position[index]);
      Serial.print(" PresPos:");  Serial.print(Master_present_position);
      Serial.println(" ");


    }while(1==1);//((abs(dxl_goal_position[index] - Slave_present_position) > DXL_MOVING_STATUS_THRESHOLD));

    // Change goal position
    if (index == 0)
    {
      index = 1;
    }
    else
    {
      index = 0;
    }
  }

 
  // Close port
  portHandler->closePort();

}

void loop() {
  
  // put your main code here, to run repeatedly:

}

/*
 * 
 *  // Disable Dynamixel Torque
 // dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, SLAVE_ID, ADDR_TORQUE_SWITCH, TORQUE_OFF, &dxl_error);
 /*
  if (dxl_comm_result != COMM_SUCCESS)
  {
    packetHandler->getTxRxResult(dxl_comm_result);
  }
  else if (dxl_error != 0)
  {
    packetHandler->getRxPacketError(dxl_error);
  }



 * 
 // Serial.print(Dxl.readWord(1,37));
     // Read present position
     // dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, SLAVE_ID, ADDR_PRESENT_POSITION, (uint16_t*)&present_position320XL); //, &dxl_error);
     
    //Serial.print(packetHandler->read2ByteTxRx(portHandler, SLAVE_ID, ADDR_PRESENT_POSITION, (uint16_t*)&present_position320XL, &dxl_error));
   // Serial.print(" PresPosition:");  Serial.print(present_position320XL);
   //ADDR_CCW_ANGLE_LIMIT
   packetHandler->read2ByteTxRx(portHandler, SLAVE_ID, ADDR_CCW_ANGLE_LIMIT, (uint16_t*)&ccwAngleLimit);
   Serial.print(" PresPosition:");  Serial.print(ccwAngleLimit);
    Serial.print(" \n");
    packetHandler->read2ByteTxRx(portHandler, SLAVE_ID, ADDR_PRESENT_POSITION, (uint16_t*)&present_position320XL);
    Serial.print(" PresPosition:");  Serial.print(present_position320XL);
    Serial.print(" \n");
    Serial.print("Press any key to continue! (or press q to quit!)\n");

 * /
 */
