void writeToServo ( int id, int command, int val){
  int dxl_comm_result = COMM_TX_FAIL;  
  dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, id, command, val, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
      packetHandler->getTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
      packetHandler->getRxPacketError(dxl_error);
    }
}

/*
 // Write goal position
    dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, DXL_ID, ADDR_GOAL_POSITION, dxl_goal_position[index], &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
      packetHandler->getTxRxResult(dxl_comm_result);
    }
    else if (dxl_error != 0)
    {
      packetHandler->getRxPacketError(dxl_error);
    }
 */
