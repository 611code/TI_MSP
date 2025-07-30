#include "IIC.h"
#include "system.h"

#define I2C I2C1



// unsigned char hardware_IIC_WirteByte(unsigned char Salve_Adress,unsigned char Reg_Address, unsigned char dat)
// {	
//     uint8_t temp[2];
//     temp[0] = Reg_Address;
//     temp[1] = dat;
//     DL_I2C_fillControllerTXFIFO(I2C, temp, 2);
//     while (!(DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_IDLE));
//     DL_I2C_startControllerTransfer(I2C, Salve_Adress, DL_I2C_CONTROLLER_DIRECTION_TX, 2);
//     while (DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
//     while (!(DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_IDLE));
//     DL_I2C_flushControllerTXFIFO(I2C);
// 		return 1;
// }
// unsigned char hardware_IIC_WirteBytes(unsigned char Salve_Adress,unsigned char Reg_Address, unsigned char * dat, unsigned char len)
// {
// 		unsigned char temp[len+1];
// 	  temp[0] = Reg_Address;
// 		memcpy(temp+1,dat,len);
//     DL_I2C_fillControllerTXFIFO(I2C, temp, len+1);
//     while (!(DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_IDLE));
//     DL_I2C_startControllerTransfer(I2C, Sensor_Adrees, DL_I2C_CONTROLLER_DIRECTION_TX, len+1);
//     while (DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
//     while (!(DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_IDLE));
//     DL_I2C_flushControllerTXFIFO(I2C);
// 		return 1;
// }
// unsigned char hardware_IIC_ReadByte(unsigned char Salve_Adress,unsigned char Reg_Address) 
// {
//     unsigned char data;
//     DL_I2C_fillControllerTXFIFO(I2C, &Reg_Address, 1);
//     while (!(DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_IDLE));
//     DL_I2C_startControllerTransfer(I2C, Salve_Adress, DL_I2C_CONTROLLER_DIRECTION_TX, 1);
//     while (DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
//     while (!(DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_IDLE));
//     DL_I2C_flushControllerTXFIFO(I2C);
 
//     DL_I2C_startControllerTransfer(I2C, Salve_Adress, DL_I2C_CONTROLLER_DIRECTION_RX, 1);
//     while (DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
//     while (!(DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_IDLE));
//     data = DL_I2C_receiveControllerData(I2C);
 
//     return data;
// }
// unsigned char hardware_IIC_ReadBytes(unsigned char Salve_Adress,unsigned char Reg_Address,unsigned char *data,unsigned char len)
// { 
//     DL_I2C_fillControllerTXFIFO(I2C, &Reg_Address, 1);
//     while (!(DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_IDLE));
//     DL_I2C_startControllerTransfer(I2C, Salve_Adress, DL_I2C_CONTROLLER_DIRECTION_TX, 1);
//     while (DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
//     while (!(DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_IDLE));
//     DL_I2C_flushControllerTXFIFO(I2C);
 
//     DL_I2C_startControllerTransfer(I2C, Salve_Adress, DL_I2C_CONTROLLER_DIRECTION_RX, len);
//     while (DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
//     while (!(DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_IDLE));
	
// 		for (uint8_t i = 0; i < len; i++) {
//     data[i] = DL_I2C_receiveControllerData(I2C);
// 		}
// 		return 1;
// }

#define I2C_TIMEOUT_MS 10  // 超时时间 100 ms

// 等待控制器进入 IDLE 状态，超时返回 0，成功返回 1
static uint8_t wait_idle_with_timeout(uint32_t timeout_ms) {
    uint32_t start = uwTick;
    while (!(DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_IDLE)) {
        if ((uwTick - start) > timeout_ms) {
            return 0;
        }
    }
    return 1;
}

// 等待 BUSY_BUS 标志清除，超时返回 0，成功返回 1
static uint8_t wait_not_busy_with_timeout(uint32_t timeout_ms) {
    uint32_t start = uwTick;
    while (DL_I2C_getControllerStatus(I2C) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS) {
        if ((uwTick - start) > timeout_ms) {
            return 0;
        }
    }
    return 1;
}

unsigned char hardware_IIC_WirteByte(unsigned char Slave_Address,
                                    unsigned char Reg_Address,
                                    unsigned char dat)
{
    uint8_t temp[2] = { Reg_Address, dat };

    DL_I2C_fillControllerTXFIFO(I2C, temp, 2);
    if (!wait_idle_with_timeout(I2C_TIMEOUT_MS)) return 0;

    DL_I2C_startControllerTransfer(I2C, Slave_Address,
                                   DL_I2C_CONTROLLER_DIRECTION_TX, 2);
    if (!wait_not_busy_with_timeout(I2C_TIMEOUT_MS)) return 0;
    if (!wait_idle_with_timeout(I2C_TIMEOUT_MS))     return 0;

    DL_I2C_flushControllerTXFIFO(I2C);
    return 1;
}

unsigned char hardware_IIC_WirteBytes(unsigned char Slave_Address,
                                     unsigned char Reg_Address,
                                     unsigned char *dat,
                                     unsigned char len)
{
    // 注意：Sensor_Adrees 改为 Slave_Address
    uint8_t temp[len + 1];
    temp[0] = Reg_Address;
    memcpy(temp + 1, dat, len);

    DL_I2C_fillControllerTXFIFO(I2C, temp, len + 1);
    if (!wait_idle_with_timeout(I2C_TIMEOUT_MS)) return 0;

    DL_I2C_startControllerTransfer(I2C, Slave_Address,
                                   DL_I2C_CONTROLLER_DIRECTION_TX, len + 1);
    if (!wait_not_busy_with_timeout(I2C_TIMEOUT_MS)) return 0;
    if (!wait_idle_with_timeout(I2C_TIMEOUT_MS))     return 0;

    DL_I2C_flushControllerTXFIFO(I2C);
    return 1;
}

unsigned char hardware_IIC_ReadByte(unsigned char Slave_Address,
                                   unsigned char Reg_Address)
{
    unsigned char data;

    // 先发送寄存器地址
    DL_I2C_fillControllerTXFIFO(I2C, &Reg_Address, 1);
    if (!wait_idle_with_timeout(I2C_TIMEOUT_MS)) return 0;

    DL_I2C_startControllerTransfer(I2C, Slave_Address,
                                   DL_I2C_CONTROLLER_DIRECTION_TX, 1);
    if (!wait_not_busy_with_timeout(I2C_TIMEOUT_MS)) return 0;
    if (!wait_idle_with_timeout(I2C_TIMEOUT_MS))     return 0;

    DL_I2C_flushControllerTXFIFO(I2C);

    // 再读取一个字节
    DL_I2C_startControllerTransfer(I2C, Slave_Address,
                                   DL_I2C_CONTROLLER_DIRECTION_RX, 1);
    if (!wait_not_busy_with_timeout(I2C_TIMEOUT_MS)) return 0;
    if (!wait_idle_with_timeout(I2C_TIMEOUT_MS))     return 0;

    data = DL_I2C_receiveControllerData(I2C);
    return data;
}

unsigned char hardware_IIC_ReadBytes(unsigned char Slave_Address,
                                    unsigned char Reg_Address,
                                    unsigned char *data,
                                    unsigned char len)
{
    // 先发送寄存器地址
    DL_I2C_fillControllerTXFIFO(I2C, &Reg_Address, 1);
    if (!wait_idle_with_timeout(I2C_TIMEOUT_MS)) return 0;

    DL_I2C_startControllerTransfer(I2C, Slave_Address,
                                   DL_I2C_CONTROLLER_DIRECTION_TX, 1);
    if (!wait_not_busy_with_timeout(I2C_TIMEOUT_MS)) return 0;
    if (!wait_idle_with_timeout(I2C_TIMEOUT_MS))     return 0;

    DL_I2C_flushControllerTXFIFO(I2C);

    // 读取 len 字节
    DL_I2C_startControllerTransfer(I2C, Slave_Address,
                                   DL_I2C_CONTROLLER_DIRECTION_RX, len);
    if (!wait_not_busy_with_timeout(I2C_TIMEOUT_MS)) return 0;
    if (!wait_idle_with_timeout(I2C_TIMEOUT_MS))     return 0;

    for (uint8_t i = 0; i < len; i++) {
        data[i] = DL_I2C_receiveControllerData(I2C);
    }
    return 1;
}

