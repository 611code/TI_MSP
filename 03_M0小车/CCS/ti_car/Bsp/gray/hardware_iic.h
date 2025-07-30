#include "gw_grayscale_sensor.h"
#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_i2c.h"
#include <string.h>

unsigned char Ping(void);
unsigned char IIC_Get_Digtal(void);
unsigned char IIC_Get_Anolog(unsigned char * Result,unsigned char len);
unsigned char IIC_Get_Single_Anolog(unsigned char Channel);
unsigned char IIC_Anolog_Normalize(uint8_t Normalize_channel);
unsigned short IIC_Get_Offset(void );

