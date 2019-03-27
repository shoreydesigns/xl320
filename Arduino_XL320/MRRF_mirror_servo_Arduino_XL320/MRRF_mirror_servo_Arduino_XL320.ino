/*
  Motor : XL320

  DEVICENAME "1" -> Serial1
  DEVICENAME "2" -> Serial2
  DEVICENAME "3" -> Serial3
*/

#include <DynamixelSDK.h>



// Control table address (XL320)
//Control Table of EEPROM Area                                       | min|max  |Intial Value
//Word R Model Number                     -  -    350
#define ADDR_MODEL_NUMBER 0   
//Byte R Firmware Version                       -  --
#define ADDR_FIRMWARE 2 
//Byte RW DYNAMIXEL ID                          0  252  1
#define ADDR_SERVO_ID 3 
//Byte RW Communication Speed                 0  3    3
#define ADDR_COMM_SPEED 4 
//ByteRW Response Delay Time         0  254  250
#define ADDR_RESPONSE_DELAY_TIME 5 
//Word RW Clockwise Angle Limit          0  1023 0
#define ADDR_CW_ANGLE_LIMIT 6  
//Word RW Counter-Clockwise Angle Limit  0  1023 1023
#define ADDR_CCW_ANGLE_LIMIT 8 
//Byte RW Control Mode 1Wheel 2Joint       1  2    2
#define ADDR_CONTROL_MODE 11 
//Byte RW Temperature Limit               0  159  65
#define ADDR_TEMP_LIMIT 12 
//Byte RW Min Voltage Limit                 50 250  65
#define ADDR_MAX_VOLT 13 
//Byte RW Max Voltage Limit                 50 250  90
#define ADDR_MIN_VOLT 14 
//Word RW Max Torque                      0  1023 1023
#define ADDR_MAX_TORQUE 15 
//Byte RW Status Return Level    0  2     2 
#define ADDR_STATUS_RETURN_LEVEL 17 
// This value decides how to return Status Packet when Dynamixel receives an Instruction Packet.
    // 0 PING Instruction   Status Packet will not be returned for all Instructions
    // 1 PING  & READ Instruction   Status Packet will be returned only for READ Instruction
    // 2 All Instructions   Status Packet will be returned for all Instructions
//Byte //RW Shutdown Error Information    0  7    3
#define ADDR_SHUTDOWN_ERROR 18

//  RAM Area                                                        | min|max  |Intial Value
//Byte RW Motor Torque On/Off           0  1    0
#define ADDR_TORQUE_SWITCH 24  
//Byte RW RGB LED                                  0  7    0
#define ADDR_LED 25 
//Byte RW D Derivative Gain                     0  254  0
#define ADDR_D_GAIN 27 
//Byte RW I Integral Gain                       0  254  0
#define ADDR_I_GAIN 28 
// Byte RW P Proportional Gain                  0  254  32
#define ADDR_P_GAIN 29 

//Word RW Desired Position                0  1023  -
#define ADDR_GOAL_POSITION 30
//Word RW Moving Speed(Velocity)          0  2047  -
#define ADDR_MOVING_SPEED 32 
//Word RW Torque Limit(Goal Torque)        0  1023  -
#define ADDR_GOAL_TORQUE 35 
//Word R Present Position            -  -     -
#define ADDR_PRESENT_POSITION  37 
//Word R Present Speed                   -  -     -
#define ADDR_PRESENT_SPEED 39 
//Word R Present Load                     -  -     -
#define ADDR_PRESENT_LOAD 41 

//BytE R Present Voltage               -  -     -
#define ADDR_PRESENT_VOLTAGE 45 
//Byte R Present Temperature                      -  -     -
#define ADDR_TEMP 46 
//Byte R If Instruction is registered - - 0
#define ADDR_INSTRUCTION_REGISTERED 47
// Byte /R Moving Movement Status       -  -     0
#define ADDR_MOVEMENT_STATUS 49
//Byte R Hardware Error Status           -  -     0
#define ADDR_HARDWARE_ERROR 50
//Word  RW Punch Min Current Threshold           0  1023  32
#define ADDR_PUNCH 51 

    


// Protocol version
// See which protocol version is used in the Dynamixel
#define PROTOCOL_VERSION                2.0                 

// Default setting
// Dynamixel ID: 1
#define MASTER_IDA                          1  
#define MASTER_IDB                          3 
#define MASTER_IDC                          5                  
// Dynamixel ID: 2
#define SLAVE_IDA                          2 
#define SLAVE_IDB                          4 
#define SLAVE_IDC                          6                   
#define BAUDRATE                        1000000
// Check which port is being used on your controller
#define DEVICENAME                      "1"                 
                                                            // ex) Windows: "COM1"   Linux: "/dev/ttyUSB0"

// Value for enabling the torque
#define TORQUE_ON                   1                   
// Value for disabling the torque
#define TORQUE_OFF                  0                   
// Dynamixel will rotate between this value
#define DXL_MINIMUM_POSITION_VALUE      00                 
// and this value (note that the Dynamixel would not move when the position value is out of movable range. Check e-manual about the range of the Dynamixel you use.)
#define DXL_MAXIMUM_POSITION_VALUE      1023//200                 
// Dynamixel moving status threshold
#define DXL_MOVING_STATUS_THRESHOLD     20                  

#define ESC_ASCII_VALUE                 0x1b



void setup() {
  // put your setup code here, to run once:



  // Initialize PortHandler instance
  // Set the port path
  // Get methods and members of PortHandlerLinux or PortHandlerWindows
  dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);

  // Initialize PacketHandler instance
  // Set the protocol version
  // Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
  dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

  //int index = 0;
  int dxl_comm_result = COMM_TX_FAIL;             // Communication result
  //int dxl_goal_position[2] = {DXL_MINIMUM_POSITION_VALUE, DXL_MAXIMUM_POSITION_VALUE};         // Goal position

  uint8_t dxl_error = 0;                          // Dynamixel error
  int16_t Slave_present_positionA = 512;               // Present position
    int16_t Slave_present_positionB = 512;               // Present position
      int16_t Slave_present_positionC = 512;               // Present position
  int16_t Master_present_positionA = 512;               // Present position
    int16_t Master_present_positionB = 512;               // Present position
      int16_t Master_present_positionC = 512;               // Present position
  //int16_t present_position320XL = 512;     // Present position  #define ADDR_PRESENT_POSITION      37
  //int16_t ccwAngleLimit = 0; //#define ADDR_CCW_ANGLE_LIMIT 8 //Word RW Counter-Clockwise Angle Limit  0  1023 1023




  // Open port
  portHandler->openPort();

  // Set port baudrate
  portHandler->setBaudRate(BAUDRATE);

  // Enable Dynamixel Torque for slave
  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, SLAVE_IDA, ADDR_TORQUE_SWITCH, TORQUE_ON);
   dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, SLAVE_IDB, ADDR_TORQUE_SWITCH, TORQUE_ON);
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, SLAVE_IDC, ADDR_TORQUE_SWITCH, TORQUE_ON);



  // Disable Dynamixel Torque for master
  dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, MASTER_IDA, ADDR_TORQUE_SWITCH, TORQUE_OFF);
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, MASTER_IDB, ADDR_TORQUE_SWITCH, TORQUE_OFF);
      dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, MASTER_IDC, ADDR_TORQUE_SWITCH, TORQUE_OFF);

//packetHandler->write2ByteTxRx(portHandler, SLAVE_ID, ADDR_MAX_TORQUE, 1023);
packetHandler->write2ByteTxRx(portHandler, SLAVE_IDA, ADDR_GOAL_TORQUE, 1023);
packetHandler->write2ByteTxRx(portHandler, SLAVE_IDB, ADDR_GOAL_TORQUE, 1023);
packetHandler->write2ByteTxRx(portHandler, SLAVE_IDC, ADDR_GOAL_TORQUE, 1023);
while(1)
  {
      // Read present position
      dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, MASTER_IDA, ADDR_PRESENT_POSITION, (uint16_t*)&Master_present_positionA);

      // Write Master Value to Slave
      packetHandler->write2ByteTxRx(portHandler, SLAVE_IDA, ADDR_GOAL_POSITION, Master_present_positionA);
//////////////////////////////////////////////
       // Read present position
      dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, MASTER_IDB, ADDR_PRESENT_POSITION, (uint16_t*)&Master_present_positionB);

      // Write Master Value to Slave
      packetHandler->write2ByteTxRx(portHandler, SLAVE_IDB, ADDR_GOAL_POSITION, Master_present_positionB);
////////////////////////////////////////////////////////////////////
       // Read present position
      dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, MASTER_IDC, ADDR_PRESENT_POSITION, (uint16_t*)&Master_present_positionC);

      // Write Master Value to Slave
      packetHandler->write2ByteTxRx(portHandler, SLAVE_IDC, ADDR_GOAL_POSITION, Master_present_positionC);
  }

  // Close port
  portHandler->closePort();

}

void loop() {
  
  // put your main code here, to run repeatedly:

}


