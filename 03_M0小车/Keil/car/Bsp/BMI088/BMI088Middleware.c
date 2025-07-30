#include "BMI088Middleware.h"
#include "ti_msp_dl_config.h"

#define BMI088_USING_SPI_UNIT   SPI_BMI_INST

// extern SPI_HandleTypeDef BMI088_USING_SPI_UNIT;

/**
************************************************************************
* @brief:      	BMI088_GPIO_init(void)
* @param:       void
* @retval:     	void
* @details:    	BMI088������GPIO��ʼ������
************************************************************************
**/
void BMI088_GPIO_init(void)
{

}
/**
************************************************************************
* @brief:      	BMI088_com_init(void)
* @param:       void
* @retval:     	void
* @details:    	BMI088������ͨ�ų�ʼ������
************************************************************************
**/
void BMI088_com_init(void)
{


}
/**
************************************************************************
* @brief:      	BMI088_delay_ms(uint16_t ms)
* @param:       ms - Ҫ�ӳٵĺ�����
* @retval:     	void
* @details:    	�ӳ�ָ���������ĺ���������΢���ӳ�ʵ��
************************************************************************
**/
void BMI088_delay_ms(uint16_t ms)
{
    // while(ms--)
    // {
    //     BMI088_delay_us(1000);
    // }
    delay_cycles( (CPUCLK_FREQ/1000) * (ms) );
}
/**
************************************************************************
* @brief:      	BMI088_delay_us(uint16_t us)
* @param:       us - Ҫ�ӳٵ�΢����
* @retval:     	void
* @details:    	΢�뼶�ӳٺ�����ʹ��SysTick��ʱ��ʵ��
************************************************************************
**/
void BMI088_delay_us(uint16_t us)
{
    delay_cycles( (CPUCLK_FREQ/1000000) * (us) );
    // uint32_t ticks = 0;
    // uint32_t told = 0;
    // uint32_t tnow = 0;
    // uint32_t tcnt = 0;
    // uint32_t reload = 0;
    // reload = SysTick->LOAD;
    // ticks = us * 1680;
    // told = SysTick->VAL;
    // while (1)
    // {
    //     tnow = SysTick->VAL;
    //     if (tnow != told)
    //     {
    //         if (tnow < told)
    //         {
    //             tcnt += told - tnow;
    //         }
    //         else
    //         {
    //             tcnt += reload - tnow + told;
    //         }
    //         told = tnow;
    //         if (tcnt >= ticks)
    //         {
    //             break;
    //         }
    //     }
    // }
}
/**
************************************************************************
* @brief:      	BMI088_ACCEL_NS_L(void)
* @param:       void
* @retval:     	void
* @details:    	��BMI088���ٶȼ�Ƭѡ�ź��õͣ�ʹ�䴦��ѡ��״̬
************************************************************************
**/
void BMI088_ACCEL_NS_L(void)
{
    // HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_RESET);
    DL_GPIO_clearPins(GPIO_CS_PIN_CS1_PORT,GPIO_CS_PIN_CS1_PIN);
}
/**
************************************************************************
* @brief:      	BMI088_ACCEL_NS_H(void)
* @param:       void
* @retval:     	void
* @details:    	��BMI088���ٶȼ�Ƭѡ�ź��øߣ�ʹ�䴦�ڷ�ѡ��״̬
************************************************************************
**/
void BMI088_ACCEL_NS_H(void)
{
    // HAL_GPIO_WritePin(ACC_CS_GPIO_Port, ACC_CS_Pin, GPIO_PIN_SET);
    
    DL_GPIO_setPins(GPIO_CS_PIN_CS1_PORT,GPIO_CS_PIN_CS1_PIN);
}
/**
************************************************************************
* @brief:      	BMI088_GYRO_NS_L(void)
* @param:       void
* @retval:     	void
* @details:    	��BMI088������Ƭѡ�ź��õͣ�ʹ�䴦��ѡ��״̬
************************************************************************
**/
void BMI088_GYRO_NS_L(void)
{
    // HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PIN_RESET);
   DL_GPIO_clearPins(GPIO_CS_PIN_CS2_PORT,GPIO_CS_PIN_CS2_PIN);
}
/**
************************************************************************
* @brief:      	BMI088_GYRO_NS_H(void)
* @param:       void
* @retval:     	void
* @details:    	��BMI088������Ƭѡ�ź��øߣ�ʹ�䴦�ڷ�ѡ��״̬
************************************************************************
**/
void BMI088_GYRO_NS_H(void)
{
    // HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PIN_SET);
    
    DL_GPIO_setPins(GPIO_CS_PIN_CS2_PORT,GPIO_CS_PIN_CS2_PIN);
}
/**
************************************************************************
* @brief:      	BMI088_read_write_byte(uint8_t txdata)
* @param:       txdata - Ҫ���͵�����
* @retval:     	uint8_t - ���յ�������
* @details:    	ͨ��BMI088ʹ�õ�SPI���߽��е��ֽڵĶ�д����
************************************************************************
**/
uint8_t BMI088_read_write_byte(uint8_t txdata)
{
    uint8_t rx_data;
    // HAL_SPI_TransmitReceive(&BMI088_USING_SPI_UNIT, &txdata, &rx_data, 1, 1000);
    //发送数据
    DL_SPI_transmitData8(SPI_BMI_INST,txdata);
    //等待SPI总线空闲
    while(DL_SPI_isBusy(SPI_BMI_INST));
    //接收数据
    rx_data = DL_SPI_receiveData8(SPI_BMI_INST);
    //等待SPI总线空闲
    while(DL_SPI_isBusy(SPI_BMI_INST));

    return rx_data;
}

