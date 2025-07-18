前缀基本上都为DL_

先讲一下TI的时钟：

**BUSCLK**：由内部高频振荡器提供的CPU时钟，通常芯片默认设置为了32MHz。

**MFCLK**：只能使用固定的4MHz时钟(参考用户手册132页)。开启的话需要配置时钟树的SYSOSC_4M分支，才能够正常开启。

**LFCLK**：由内部的低频振荡器提供时钟（32KHz）。在运行、睡眠、停止和待机模式下有效，使用该时钟可以实现更低的功耗。

如果不清楚细节可以看看[【立创·天猛星MSPM0G3507开发板】介绍 | 立创开发板技术文档中心](https://wiki.lckfb.com/zh-hans/tmx-mspm0g3507/)，关于TI的他是最详细的了。

需要注意的是配置完成后记得看PinMux的引脚对不对，有时需要手动修改。

[TOC]

# 一、延时

CPUCLK_FREQ为主频频率，一般在ti_msp_dl_config.h里已经定义，默认32M

delay_cycles为系统函数

延时一秒：

```
delay_cycles(主频hz)
```

延时1ms：

```
delay_cycles(CPUCLK_FREQ/1000);
```

延时1us：

```
delay_cycles(CPUCLK_FREQ/1000000);
```

因此，可以封装为(也可以宏定义)：

```
void delay_ms(unsigned int ms)
{
  delay_cycles( (CPUCLK_FREQ/1000) * (ms) );
}

void delay_us(unsigned int us)
{
  delay_cycles( (CPUCLK_FREQ/1000000) * (us) );
}
```

还有一种为系统滴答定时器，需开启SYSTICK

```
void SysTick_Handler(void)
{
    uwTick++;
}
```

方框内需是1ms.若为1us，SysTick_Handler每1us触发一次。

![image-20250715155502706](./assets/image-20250715155502706.png)

## 更改系统主频MCLK

![image-20250715155600612](./assets/image-20250715155600612.png)

然后打开时钟树

![image-20250715155618224](./assets/image-20250715155618224.png)

配置SYSPLL

![image-20250715155648990](./assets/image-20250715155648990.png)

![image-20250715155659929](./assets/image-20250715155659929.png)

# 二、GPIO控制

**![image-20250715151336750](./assets/image-20250715151336750.png)**

## 该函数为控制引脚输出高电平：

```
void DL_GPIO_setPins(GPIO_Regs* gpio, uint32_t pins)
```

说明：

该函数用于将指定的GPIO端口的某些引脚设置为高电平（输出1）。

- gpio：GPIO端口的寄存器指针（如GPIOA、GPIOB等）。

- pins：需要设置为高电平的引脚位掩码（如DL_GPIO_PIN_0 | DL_GPIO_PIN_1）。

## 该函数为控制引脚输出低电平：

```
void DL_GPIO_clearPins(GPIO_Regs* gpio, uint32_t pins)
```

说明：

该函数用于将指定的GPIO端口的某些引脚设置为低电平（输出0）。

- gpio：GPIO端口的寄存器指针。

- pins：需要设置为低电平的引脚位掩码。

## 该函数为控制引脚的电平翻转：

```
void DL_GPIO_togglePins(GPIO_Regs* gpio, uint32_t pins)
```

说明：

该函数用于将指定的GPIO引脚电平进行翻转（高变低，低变高）。

- gpio：GPIO端口的寄存器指针。

- pins：需要翻转的引脚位掩码。

## 读取引脚的状态：

```
uint32_t DL_GPIO_readPins(GPIO_Regs* gpio, uint32_t pins)
```

说明：

该函数用于读取指定GPIO端口所有引脚的当前电平状态。

- gpio：GPIO端口的寄存器指针。

- 返回值：每一位代表一个引脚的电平状态（1为高，0为低）。

## 配置引脚为输入/输出

正常初始化就已经设置，一般用不到

```
void DL_GPIO_init(GPIO_Regs* gpio, uint32_t pins, DL_GPIO_DIR direction)
```

说明：

该函数用于初始化GPIO引脚的方向（输入或输出）。

- gpio：GPIO端口的寄存器指针。

- pins：需要配置的引脚位掩码。

- direction：引脚方向（如DL_GPIO_DIR_INPUT或DL_GPIO_DIR_OUTPUT）。

# 三、I2C读写

## I2C发送数据（写）

```
void DL_I2C_transmitData(I2C_Regs* i2c, uint8_t data)
```

说明：

该函数用于通过I2C总线发送一个字节数据。

- i2c：I2C外设的寄存器指针（如I2C0、I2C1等）。

- data：要发送的8位数据。

## I2C接收数据（读）

```
uint8_t DL_I2C_receiveData(I2C_Regs* i2c)
```

说明：

该函数用于从I2C总线接收一个字节数据。

- i2c：I2C外设的寄存器指针。

- 返回值：接收到的8位数据。

## I2C发送起始信号

```
void DL_I2C_generateStart(I2C_Regs* i2c)
```

说明：

该函数用于产生I2C起始信号，开始一次I2C通信。

- i2c：I2C外设的寄存器指针。

## I2C发送停止信号

```
void DL_I2C_generateStop(I2C_Regs* i2c)
```

说明：

该函数用于产生I2C停止信号，结束一次I2C通信。

- i2c：I2C外设的寄存器指针。

## I2C检查总线忙状态

```
bool DL_I2C_isBusBusy(I2C_Regs* i2c)
```

说明：

该函数用于检测I2C总线是否处于忙状态。

- i2c：I2C外设的寄存器指针。

- 返回值：true表示总线忙，false表示空闲。

## I2C设置从设备地址

```
void DL_I2C_setTargetAddress(I2C_Regs* i2c, uint8_t address)
```

说明：

该函数用于设置I2C通信的目标从设备地址。

- i2c：I2C外设的寄存器指针。

- address：7位从设备地址。

## example

```
void IRI2C_WriteByte(uint8_t addr, uint8_t dat) {
    uint8_t temp[2];
    temp[0] = addr; // 第1步：temp[0]存放要写入的寄存器地址
    temp[1] = dat;  // 第2步：temp[1]存放要写入的数据

    // 第3步：将要发送的数据写入I2C控制器的发送FIFO（一次写入2字节：寄存器地址+数据）
    DL_I2C_fillControllerTXFIFO(I2C_0_INST, temp, 2);

    // 第4步：等待I2C控制器空闲，确保FIFO数据已准备好
    while (!(DL_I2C_getControllerStatus(I2C_0_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));

    // 第5步：启动I2C主机传输，向目标设备(IR_I2C_ADDR)写入2字节数据
    DL_I2C_startControllerTransfer(I2C_0_INST, IR_I2C_ADDR, DL_I2C_CONTROLLER_DIRECTION_TX, 2);

    // 第6步：等待I2C总线传输完成（总线忙时一直等待）
    while (DL_I2C_getControllerStatus(I2C_0_INST) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);

    // 第7步：再次确认I2C控制器空闲
    while (!(DL_I2C_getControllerStatus(I2C_0_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));

    // 第8步：清空I2C发送FIFO，防止残留数据影响下次传输
    DL_I2C_flushControllerTXFIFO(I2C_0_INST);
}

uint8_t IRI2C_ReadByte(uint8_t addr) {
    uint8_t data;

    // 第1步：将要读取的寄存器地址写入I2C控制器的发送FIFO
    DL_I2C_fillControllerTXFIFO(I2C_0_INST, &addr, 1);

    // 第2步：关闭I2C发送FIFO触发中断（防止干扰）
    DL_I2C_disableInterrupt(I2C_0_INST, DL_I2C_INTERRUPT_CONTROLLER_TXFIFO_TRIGGER);

    // 第3步：等待I2C控制器空闲
    while (!(DL_I2C_getControllerStatus(I2C_0_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));

    // 第4步：启动I2C主机传输，先向目标设备写入1字节（寄存器地址）
    DL_I2C_startControllerTransfer(I2C_0_INST, IR_I2C_ADDR, DL_I2C_CONTROLLER_DIRECTION_TX, 1);

    // 第5步：等待I2C总线传输完成
    while (DL_I2C_getControllerStatus(I2C_0_INST) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);

    // 第6步：再次确认I2C控制器空闲
    while (!(DL_I2C_getControllerStatus(I2C_0_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));

    // 第7步：启动I2C主机接收，准备从目标设备读取1字节数据
    DL_I2C_startControllerTransfer(I2C_0_INST, IR_I2C_ADDR, DL_I2C_CONTROLLER_DIRECTION_RX, 1);

    // 第8步：等待I2C总线传输完成
    while (DL_I2C_getControllerStatus(I2C_0_INST) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);

    // 第9步：再次确认I2C控制器空闲
    while (!(DL_I2C_getControllerStatus(I2C_0_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));

    // 第10步：从I2C控制器接收FIFO中读取数据
    data = DL_I2C_receiveControllerData(I2C_0_INST);

    // 第11步：返回读取到的数据
    return data;
}
```



# 四、SPI读写

## SPI发送数据（写）

```
void DL_SPI_transmitData8(SPI_Regs *spi, uint8_t data)
void DL_SPI_transmitData16(SPI_Regs *spi, uint16_t data)
```

说明：

该函数用于通过SPI总线发送一个字节数据。

- spi：SPI外设的寄存器指针（如SPI0、SPI1等）。

- data：要发送的8/16位数据。

## SPI接收数据（读）

```
uint8_t DL_SPI_receiveData8(SPI_Regs *spi)
uint16_t DL_SPI_receiveData16(SPI_Regs *spi)
```

说明：

该函数用于从SPI总线接收一个字节数据。

- spi：SPI外设的寄存器指针。

- 返回值：接收到的8/16位数据。

## SPI发送并接收数据（全双工）

```
uint8_t DL_SPI_transmitReceiveData(SPI_Regs* spi, uint8_t data)
```

说明：

该函数用于通过SPI总线发送一个字节数据的同时接收一个字节数据（全双工）。

- spi：SPI外设的寄存器指针。

- data：要发送的8位数据。

- 返回值：接收到的8位数据。

## SPI检查忙状态

```
bool DL_SPI_isBusy(SPI_Regs* spi)
```

说明：

该函数用于检测SPI总线是否处于忙状态。

- spi：SPI外设的寄存器指针。

- 返回值：true表示SPI忙，false表示空闲。

## SPI配置相关（初始化、设置模式等）

正常初始化就已经配置，一般用不到

```
void DL_SPI_init(SPI_Regs* spi, DL_SPI_Config* config)
```

说明：

该函数用于初始化SPI外设，包括模式、时钟、极性等参数设置。

- spi：SPI外设的寄存器指针。

- config：SPI配置结构体指针。



```
//发送数据，8表示8位
void DL_SPI_transmitData8(SPI_Regs *spi, uint8_t data)
void DL_SPI_transmitData16(SPI_Regs *spi, uint16_t data)
```

```
//等待SPI总线空闲
bool DL_SPI_isBusy(const SPI_Regs *spi)
```

## example

SPI发送8位数据

```
void spi_write_bus(unsigned char dat)
{
    // 第1步：通过SPI接口发送8位数据（dat）
    DL_SPI_transmitData8(SPI_LCD_INST, dat);

    // 第2步：等待SPI总线空闲，确保数据已发送完成
    while(DL_SPI_isBusy(SPI_LCD_INST));
}
```

SPI发送16位数据（分两次8位发送）

```
void LCD_WR_DATA(unsigned int dat)
{
    // 第1步：先发送高8位数据
    LCD_Writ_Bus(dat >> 8);

    // 第2步：再发送低8位数据
    LCD_Writ_Bus(dat);
}
```



# 五、UART收发

![image-20250715155959684](./assets/image-20250715155959684.png)



![](./assets/image-20250715160410862.png)

![image-20250715160437761](./assets/image-20250715160437761.png)

## 发送一个字节数据

```
void DL_UART_Main_transmitData(UART_Regs *uart, uint8_t data)
```

说明：

该函数用于通过UART发送一个8位（1字节）数据。

- uart：UART外设的寄存器指针（如UART_0_INST）。

- data：要发送的数据。

## 接收一个字节数据

```
uint8_t DL_UART_Main_receiveData(UART_Regs *uart)
```

说明：

该函数用于从UART接收一个8位（1字节）数据。

- uart：UART外设的寄存器指针。

- 返回值：接收到的数据。

## 检查UART是否忙

```
bool DL_UART_isBusy(UART_Regs *uart)
```

说明：

该函数用于判断UART当前是否处于忙状态（正在发送或接收数据）。

- uart：UART外设的寄存器指针。

- 返回值：true表示忙，false表示空闲。

## 获取UART中断状态

```
uint32_t DL_UART_getPendingInterrupt(UART_Regs *uart)
```

说明：

该函数用于获取UART当前挂起的中断类型。

- uart：UART外设的寄存器指针。

- 返回值：中断类型（如接收中断、发送中断等）。

初始化：

```
//清除串口中断标志    
NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);    
//使能串口中断    
NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
```

重定向：

```
int fputc(int ch, FILE *stream)
{
        while( DL_UART_isBusy(UART_0_INST) == true );

        DL_UART_Main_transmitData(UART_0_INST, ch);

        return ch;
}
```

## example

### 典型串口发送单个字符函数

```
void uart0_send_char(char ch)
{
    // 当串口0忙的时候等待，不忙的时候再发送传进来的字符
    while(DL_UART_isBusy(UART_0_INST) == true);
    // 发送单个字符
    DL_UART_Main_transmitData(UART_0_INST, ch);
}
```

### 典型串口发送字符串函数

```
void uart0_send_string(char* str)
{
    // 当前字符串地址不在结尾 并且 字符串首地址不为空
    while(*str != 0 && str != 0)
    {
        // 发送字符串首地址中的字符，并且在发送完成之后首地址自增
        uart0_send_char(*str++);
    }
}
```

### 典型串口接收中断服务函数

```
void UART_0_INST_IRQHandler(void)
{
    // 如果产生了串口中断
    switch(DL_UART_getPendingInterrupt(UART_0_INST))
    {
        case DL_UART_IIDX_RX: // 如果是接收中断
            // 读取接收到的数据
            uart_data = DL_UART_Main_receiveData(UART_0_INST);
            // 发送回去（回显）
            uart0_send_char(uart_data);
            // 解析数据
            uart_parse_byte(uart_data);
            break;
        default:
            break;
    }
}
```

### 串口缓冲区应用



# 六、tim/pwm设置

![image-20250715160558900](./assets/image-20250715160558900.png)

![image-20250715155959684](./assets/image-20250715155959684.png)

## 设置定时器的PWM占空比（设置比较值）

```
void DL_TimerA_setCaptureCompareValue(TIMERA_Regs *timer, uint32_t value, uint32_t ccIndex)
```

说明：

该函数用于设置定时器某一路的捕获/比较寄存器值，从而改变PWM的占空比。TimerA根据实际情况更改，比如我是用定时器B,那就是DL_TimerB_setCaptureCompareValue

- timer：定时器外设的寄存器指针（如PWM_LED_INST、PWM_MOTORL_INST等）。

- value：要设置的比较值（决定PWM高电平持续时间）。

- ccIndex：通道索引（如GPIO_PWM_LED_C1_IDX，表示第几路PWM）。

## 启动定时器

正常初始化就已经启动，一般用不到

```
void DL_TimerA_startCounter(TIMERA_Regs *timer, DL_TimerA_START_MODE mode)
```

说明：

该函数用于启动定时器。

- timer：定时器外设的寄存器指针。

- mode：启动模式（如DL_TIMERA_START_MODE_UP，向上计数模式）。

##  停止定时器

```
void DL_TimerA_stopCounter(TIMERA_Regs *timer)
```

说明：

该函数用于停止定时器。

- timer：定时器外设的寄存器指针。

## 设置定时器周期（自动重装载值）

```
void DL_TimerA_setLoadValue(TIMERA_Regs *timer, uint32_t value)
```

说明：

该函数用于设置定时器的周期（即PWM的周期）。

- timer：定时器外设的寄存器指针。

- value：周期值（计数到该值后重新计数）。

## 设置定时器中断

```
void DL_TimerA_enableInterrupt(TIMERA_Regs *timer, uint32_t interrupt)
```

说明：

该函数用于使能定时器的中断功能。

- timer：定时器外设的寄存器指针。

- interrupt：中断类型（如DL_TIMERA_INTERRUPT_CC0）。

## 清除定时器中断标志

```
void DL_TimerA_clearInterruptStatus(TIMERA_Regs *timer, uint32_t interrupt)
```

说明：

该函数用于清除定时器的中断标志位。

- timer：定时器外设的寄存器指针。

- interrupt：中断类型

## example

```
// 以呼吸灯为例，逐步调节PWM占空比
for (int i = 0; i <= 999; i++)
{
    // 设置LED的PWM占空比
    DL_TimerA_setCaptureCompareValue(PWM_LED_INST, i, GPIO_PWM_LED_C1_IDX);
    delay_cycles(32000);  // 延迟以控制亮度变化速度
}
for (int i = 999; i > 0; i--)
{
    DL_TimerA_setCaptureCompareValue(PWM_LED_INST, i, GPIO_PWM_LED_C1_IDX);
    delay_cycles(32000);
}
```



# 七、tim/编码器读取

![image-20250715155804173](./assets/image-20250715155804173.png)

## 编码器中断服务函数（外部中断方式）

```
//外部中断处理函数
void GROUP1_IRQHandler(void)
{
	uint32_t gpio_status;

	//获取中断信号情况
	gpio_status = DL_GPIO_getEnabledInterruptStatus(GPIOB, GPIO_ENCODER_PIN_LA_PIN | GPIO_ENCODER_PIN_LB_PIN);
	//编码器A相上升沿触发
	if((gpio_status & GPIO_ENCODER_PIN_LA_PIN) == GPIO_ENCODER_PIN_LA_PIN)
	{
		//如果在A相上升沿下，B相为低电平
		if(!DL_GPIO_readPins(GPIOB,GPIO_ENCODER_PIN_LB_PIN))
		{
			motor_encoder.temp_count--;
		}
		else
		{
			motor_encoder.temp_count++;
		}
	}//编码器B相上升沿触发
	else if((gpio_status & GPIO_ENCODER_PIN_LB_PIN)==GPIO_ENCODER_PIN_LB_PIN)
	{
		//如果在B相上升沿下，A相为低电平
		if(!DL_GPIO_readPins(GPIOB,GPIO_ENCODER_PIN_LA_PIN))
		{
			motor_encoder.temp_count++;
		}
		else
		{
			motor_encoder.temp_count--;
		}
	}
	//清除状态
	DL_GPIO_clearInterruptStatus(GPIOB,GPIO_ENCODER_PIN_LA_PIN|GPIO_ENCODER_PIN_LB_PIN);
}
```

