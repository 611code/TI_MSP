#include "adc_app.h"
#include "system.h"

#define GRAY_ADC_INST ADC_GRAY_INST
#define GRAY_ADC_CHANNEL ADC_GRAY_ADCMEM_ADC_Channel0_REF

volatile uint16_t ADC_VALUE[16];//ADC采集的数据保存地址

// 等待控制器进入 IDLE 状态，超时返回 0，成功返回 1
static uint8_t wait_idle_with_timeout(uint32_t timeout_ms) {
    uint32_t start = uwTick;
    while (!(DL_ADC12_getStatus(GRAY_ADC_INST) != DL_ADC12_STATUS_CONVERSION_IDLE )) {
        if ((uwTick - start) > timeout_ms) {
            return 0;
        }
    }
    return 1;
}

// void adc_init(void)
// {
//     //设置DMA搬运的起始地址
//     DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) &ADC0->ULLMEM.MEMRES[0]);
//     //设置DMA搬运的目的地址
//     DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) &ADC_VALUE[0]);
//     //开启DMA
//     DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
//     //开启ADC转换
//     DL_ADC12_startConversion(GRAY_ADC_INST);
// }

// //读取ADC的数据
// unsigned int adc_getValue(void)
// {
//     unsigned int gAdcResult = 0;
//     unsigned char i = 0;

//     // //采集多次累加
//     // for( i = 0; i < 8; i++ )
//     // {
//     //         gAdcResult += ADC_VALUE[i];
//     // }
//     // //均值滤波
//     // gAdcResult /= 8;
//     gAdcResult = ADC_VALUE[1];
//     return gAdcResult;
// }

unsigned int adc_getValue(void)
{
    unsigned int gAdcResult = 0;

    //使能ADC转换
    DL_ADC12_enableConversions(GRAY_ADC_INST);
    //软件触发ADC开始转换
    DL_ADC12_startConversion(GRAY_ADC_INST);

    //如果当前状态 不是 空闲状态
    if (!wait_idle_with_timeout(10)) return 0;

    //清除触发转换状态
    DL_ADC12_stopConversion(GRAY_ADC_INST);
    //失能ADC转换
    DL_ADC12_disableConversions(GRAY_ADC_INST);

    //获取数据
    gAdcResult = DL_ADC12_getMemResult(GRAY_ADC_INST, GRAY_ADC_CHANNEL);

    return gAdcResult;
}

