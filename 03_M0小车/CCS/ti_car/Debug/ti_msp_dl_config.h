/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_MOTOR_L */
#define PWM_MOTOR_L_INST                                                   TIMG8
#define PWM_MOTOR_L_INST_IRQHandler                             TIMG8_IRQHandler
#define PWM_MOTOR_L_INST_INT_IRQN                               (TIMG8_INT_IRQn)
#define PWM_MOTOR_L_INST_CLK_FREQ                                        1000000
/* GPIO defines for channel 1 */
#define GPIO_PWM_MOTOR_L_C1_PORT                                           GPIOA
#define GPIO_PWM_MOTOR_L_C1_PIN                                   DL_GPIO_PIN_22
#define GPIO_PWM_MOTOR_L_C1_IOMUX                                (IOMUX_PINCM47)
#define GPIO_PWM_MOTOR_L_C1_IOMUX_FUNC               IOMUX_PINCM47_PF_TIMG8_CCP1
#define GPIO_PWM_MOTOR_L_C1_IDX                              DL_TIMER_CC_1_INDEX

/* Defines for PWM_MOTOR_R */
#define PWM_MOTOR_R_INST                                                   TIMG0
#define PWM_MOTOR_R_INST_IRQHandler                             TIMG0_IRQHandler
#define PWM_MOTOR_R_INST_INT_IRQN                               (TIMG0_INT_IRQn)
#define PWM_MOTOR_R_INST_CLK_FREQ                                        1000000
/* GPIO defines for channel 1 */
#define GPIO_PWM_MOTOR_R_C1_PORT                                           GPIOA
#define GPIO_PWM_MOTOR_R_C1_PIN                                   DL_GPIO_PIN_13
#define GPIO_PWM_MOTOR_R_C1_IOMUX                                (IOMUX_PINCM35)
#define GPIO_PWM_MOTOR_R_C1_IOMUX_FUNC               IOMUX_PINCM35_PF_TIMG0_CCP1
#define GPIO_PWM_MOTOR_R_C1_IDX                              DL_TIMER_CC_1_INDEX



/* Defines for TIMER_TICK */
#define TIMER_TICK_INST                                                  (TIMA0)
#define TIMER_TICK_INST_IRQHandler                              TIMA0_IRQHandler
#define TIMER_TICK_INST_INT_IRQN                                (TIMA0_INT_IRQn)
#define TIMER_TICK_INST_LOAD_VALUE                                        (999U)




/* Defines for I2C_OLED */
#define I2C_OLED_INST                                                       I2C0
#define I2C_OLED_INST_IRQHandler                                 I2C0_IRQHandler
#define I2C_OLED_INST_INT_IRQN                                     I2C0_INT_IRQn
#define I2C_OLED_BUS_SPEED_HZ                                             400000
#define GPIO_I2C_OLED_SDA_PORT                                             GPIOA
#define GPIO_I2C_OLED_SDA_PIN                                      DL_GPIO_PIN_0
#define GPIO_I2C_OLED_IOMUX_SDA                                   (IOMUX_PINCM1)
#define GPIO_I2C_OLED_IOMUX_SDA_FUNC                    IOMUX_PINCM1_PF_I2C0_SDA
#define GPIO_I2C_OLED_SCL_PORT                                             GPIOA
#define GPIO_I2C_OLED_SCL_PIN                                      DL_GPIO_PIN_1
#define GPIO_I2C_OLED_IOMUX_SCL                                   (IOMUX_PINCM2)
#define GPIO_I2C_OLED_IOMUX_SCL_FUNC                    IOMUX_PINCM2_PF_I2C0_SCL

/* Defines for I2C_GRAY */
#define I2C_GRAY_INST                                                       I2C1
#define I2C_GRAY_INST_IRQHandler                                 I2C1_IRQHandler
#define I2C_GRAY_INST_INT_IRQN                                     I2C1_INT_IRQn
#define I2C_GRAY_BUS_SPEED_HZ                                             100000
#define GPIO_I2C_GRAY_SDA_PORT                                             GPIOA
#define GPIO_I2C_GRAY_SDA_PIN                                     DL_GPIO_PIN_10
#define GPIO_I2C_GRAY_IOMUX_SDA                                  (IOMUX_PINCM21)
#define GPIO_I2C_GRAY_IOMUX_SDA_FUNC                   IOMUX_PINCM21_PF_I2C1_SDA
#define GPIO_I2C_GRAY_SCL_PORT                                             GPIOA
#define GPIO_I2C_GRAY_SCL_PIN                                     DL_GPIO_PIN_11
#define GPIO_I2C_GRAY_IOMUX_SCL                                  (IOMUX_PINCM22)
#define GPIO_I2C_GRAY_IOMUX_SCL_FUNC                   IOMUX_PINCM22_PF_I2C1_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                           40000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_31
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_28
#define GPIO_UART_0_IOMUX_RX                                      (IOMUX_PINCM6)
#define GPIO_UART_0_IOMUX_TX                                      (IOMUX_PINCM3)
#define GPIO_UART_0_IOMUX_RX_FUNC                       IOMUX_PINCM6_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                       IOMUX_PINCM3_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_40_MHZ_115200_BAUD                                      (21)
#define UART_0_FBRD_40_MHZ_115200_BAUD                                      (45)
/* Defines for UART_1 */
#define UART_1_INST                                                        UART1
#define UART_1_INST_FREQUENCY                                           40000000
#define UART_1_INST_IRQHandler                                  UART1_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_1_RX_PORT                                                GPIOB
#define GPIO_UART_1_TX_PORT                                                GPIOB
#define GPIO_UART_1_RX_PIN                                         DL_GPIO_PIN_5
#define GPIO_UART_1_TX_PIN                                         DL_GPIO_PIN_4
#define GPIO_UART_1_IOMUX_RX                                     (IOMUX_PINCM18)
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM17)
#define GPIO_UART_1_IOMUX_RX_FUNC                      IOMUX_PINCM18_PF_UART1_RX
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM17_PF_UART1_TX
#define UART_1_BAUD_RATE                                                (115200)
#define UART_1_IBRD_40_MHZ_115200_BAUD                                      (21)
#define UART_1_FBRD_40_MHZ_115200_BAUD                                      (45)




/* Defines for SPI_BMI */
#define SPI_BMI_INST                                                       SPI1
#define SPI_BMI_INST_IRQHandler                                 SPI1_IRQHandler
#define SPI_BMI_INST_INT_IRQN                                     SPI1_INT_IRQn
#define GPIO_SPI_BMI_PICO_PORT                                            GPIOB
#define GPIO_SPI_BMI_PICO_PIN                                     DL_GPIO_PIN_8
#define GPIO_SPI_BMI_IOMUX_PICO                                 (IOMUX_PINCM25)
#define GPIO_SPI_BMI_IOMUX_PICO_FUNC                 IOMUX_PINCM25_PF_SPI1_PICO
#define GPIO_SPI_BMI_POCI_PORT                                            GPIOB
#define GPIO_SPI_BMI_POCI_PIN                                     DL_GPIO_PIN_7
#define GPIO_SPI_BMI_IOMUX_POCI                                 (IOMUX_PINCM24)
#define GPIO_SPI_BMI_IOMUX_POCI_FUNC                 IOMUX_PINCM24_PF_SPI1_POCI
/* GPIO configuration for SPI_BMI */
#define GPIO_SPI_BMI_SCLK_PORT                                            GPIOB
#define GPIO_SPI_BMI_SCLK_PIN                                     DL_GPIO_PIN_9
#define GPIO_SPI_BMI_IOMUX_SCLK                                 (IOMUX_PINCM26)
#define GPIO_SPI_BMI_IOMUX_SCLK_FUNC                 IOMUX_PINCM26_PF_SPI1_SCLK



/* Defines for ADC_GRAY */
#define ADC_GRAY_INST                                                       ADC0
#define ADC_GRAY_INST_IRQHandler                                 ADC0_IRQHandler
#define ADC_GRAY_INST_INT_IRQN                                   (ADC0_INT_IRQn)
#define ADC_GRAY_ADCMEM_ADC_Channel0                          DL_ADC12_MEM_IDX_0
#define ADC_GRAY_ADCMEM_ADC_Channel0_REF         DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC_GRAY_ADCMEM_ADC_Channel0_REF_VOLTAGE_V                                     3.3
#define GPIO_ADC_GRAY_C0_PORT                                              GPIOA
#define GPIO_ADC_GRAY_C0_PIN                                      DL_GPIO_PIN_27



/* Defines for DMA_CH0_RX */
#define DMA_CH0_RX_CHAN_ID                                                   (1)
#define UART_0_INST_DMA_TRIGGER_0                            (DMA_UART0_RX_TRIG)
/* Defines for DMA_CH1_TX */
#define DMA_CH1_TX_CHAN_ID                                                   (0)
#define UART_0_INST_DMA_TRIGGER_1                            (DMA_UART0_TX_TRIG)


/* Defines for PIN_K1: GPIOA.7 with pinCMx 14 on package pin 49 */
#define KEY_PIN_K1_PORT                                                  (GPIOA)
#define KEY_PIN_K1_PIN                                           (DL_GPIO_PIN_7)
#define KEY_PIN_K1_IOMUX                                         (IOMUX_PINCM14)
/* Defines for PIN_K2: GPIOB.10 with pinCMx 27 on package pin 62 */
#define KEY_PIN_K2_PORT                                                  (GPIOB)
#define KEY_PIN_K2_PIN                                          (DL_GPIO_PIN_10)
#define KEY_PIN_K2_IOMUX                                         (IOMUX_PINCM27)
/* Defines for PIN_K3: GPIOB.11 with pinCMx 28 on package pin 63 */
#define KEY_PIN_K3_PORT                                                  (GPIOB)
#define KEY_PIN_K3_PIN                                          (DL_GPIO_PIN_11)
#define KEY_PIN_K3_IOMUX                                         (IOMUX_PINCM28)
/* Defines for PIN_K4: GPIOB.14 with pinCMx 31 on package pin 2 */
#define KEY_PIN_K4_PORT                                                  (GPIOB)
#define KEY_PIN_K4_PIN                                          (DL_GPIO_PIN_14)
#define KEY_PIN_K4_IOMUX                                         (IOMUX_PINCM31)
/* Defines for PIN_CS1: GPIOB.6 with pinCMx 23 on package pin 58 */
#define GPIO_CS_PIN_CS1_PORT                                             (GPIOB)
#define GPIO_CS_PIN_CS1_PIN                                      (DL_GPIO_PIN_6)
#define GPIO_CS_PIN_CS1_IOMUX                                    (IOMUX_PINCM23)
/* Defines for PIN_CS2: GPIOA.12 with pinCMx 34 on package pin 5 */
#define GPIO_CS_PIN_CS2_PORT                                             (GPIOA)
#define GPIO_CS_PIN_CS2_PIN                                     (DL_GPIO_PIN_12)
#define GPIO_CS_PIN_CS2_IOMUX                                    (IOMUX_PINCM34)
/* Port definition for Pin Group GPIO_ENCODER */
#define GPIO_ENCODER_PORT                                                (GPIOA)

/* Defines for PIN_LA: GPIOA.14 with pinCMx 36 on package pin 7 */
// pins affected by this interrupt request:["PIN_LA","PIN_RA"]
#define GPIO_ENCODER_INT_IRQN                                   (GPIOA_INT_IRQn)
#define GPIO_ENCODER_INT_IIDX                   (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define GPIO_ENCODER_PIN_LA_IIDX                            (DL_GPIO_IIDX_DIO14)
#define GPIO_ENCODER_PIN_LA_PIN                                 (DL_GPIO_PIN_14)
#define GPIO_ENCODER_PIN_LA_IOMUX                                (IOMUX_PINCM36)
/* Defines for PIN_LB: GPIOA.15 with pinCMx 37 on package pin 8 */
#define GPIO_ENCODER_PIN_LB_PIN                                 (DL_GPIO_PIN_15)
#define GPIO_ENCODER_PIN_LB_IOMUX                                (IOMUX_PINCM37)
/* Defines for PIN_RA: GPIOA.16 with pinCMx 38 on package pin 9 */
#define GPIO_ENCODER_PIN_RA_IIDX                            (DL_GPIO_IIDX_DIO16)
#define GPIO_ENCODER_PIN_RA_PIN                                 (DL_GPIO_PIN_16)
#define GPIO_ENCODER_PIN_RA_IOMUX                                (IOMUX_PINCM38)
/* Defines for PIN_RB: GPIOA.17 with pinCMx 39 on package pin 10 */
#define GPIO_ENCODER_PIN_RB_PIN                                 (DL_GPIO_PIN_17)
#define GPIO_ENCODER_PIN_RB_IOMUX                                (IOMUX_PINCM39)
/* Port definition for Pin Group GPIO_AIN */
#define GPIO_AIN_PORT                                                    (GPIOB)

/* Defines for PIN_AIN1: GPIOB.24 with pinCMx 52 on package pin 23 */
#define GPIO_AIN_PIN_AIN1_PIN                                   (DL_GPIO_PIN_24)
#define GPIO_AIN_PIN_AIN1_IOMUX                                  (IOMUX_PINCM52)
/* Defines for PIN_AIN2: GPIOB.25 with pinCMx 56 on package pin 27 */
#define GPIO_AIN_PIN_AIN2_PIN                                   (DL_GPIO_PIN_25)
#define GPIO_AIN_PIN_AIN2_IOMUX                                  (IOMUX_PINCM56)
/* Port definition for Pin Group GPIO_BIN */
#define GPIO_BIN_PORT                                                    (GPIOA)

/* Defines for PIN_BIN1: GPIOA.26 with pinCMx 59 on package pin 30 */
#define GPIO_BIN_PIN_BIN1_PIN                                   (DL_GPIO_PIN_26)
#define GPIO_BIN_PIN_BIN1_IOMUX                                  (IOMUX_PINCM59)
/* Defines for PIN_BIN2: GPIOA.24 with pinCMx 54 on package pin 25 */
#define GPIO_BIN_PIN_BIN2_PIN                                   (DL_GPIO_PIN_24)
#define GPIO_BIN_PIN_BIN2_IOMUX                                  (IOMUX_PINCM54)
/* Port definition for Pin Group Gray_Address */
#define Gray_Address_PORT                                                (GPIOB)

/* Defines for PIN_0: GPIOB.23 with pinCMx 51 on package pin 22 */
#define Gray_Address_PIN_0_PIN                                  (DL_GPIO_PIN_23)
#define Gray_Address_PIN_0_IOMUX                                 (IOMUX_PINCM51)
/* Defines for PIN_1: GPIOB.26 with pinCMx 57 on package pin 28 */
#define Gray_Address_PIN_1_PIN                                  (DL_GPIO_PIN_26)
#define Gray_Address_PIN_1_IOMUX                                 (IOMUX_PINCM57)
/* Defines for PIN_2: GPIOB.27 with pinCMx 58 on package pin 29 */
#define Gray_Address_PIN_2_PIN                                  (DL_GPIO_PIN_27)
#define Gray_Address_PIN_2_IOMUX                                 (IOMUX_PINCM58)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_SYSCTL_CLK_init(void);
void SYSCFG_DL_PWM_MOTOR_L_init(void);
void SYSCFG_DL_PWM_MOTOR_R_init(void);
void SYSCFG_DL_TIMER_TICK_init(void);
void SYSCFG_DL_I2C_OLED_init(void);
void SYSCFG_DL_I2C_GRAY_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_1_init(void);
void SYSCFG_DL_SPI_BMI_init(void);
void SYSCFG_DL_ADC_GRAY_init(void);
void SYSCFG_DL_DMA_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
