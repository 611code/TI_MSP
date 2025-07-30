#include "adc_app.h"

#define GRAY_ADC_INST ADC_GRAY_INST
#define GRAY_ADC_CHANNEL ADC_GRAY_ADCMEM_ADC_Channel0_REF

unsigned int adc_getValue(void)
{
    unsigned int gAdcResult = 0;

    //使能ADC转换
    DL_ADC12_enableConversions(GRAY_ADC_INST);
    //软件触发ADC开始转换
    DL_ADC12_startConversion(GRAY_ADC_INST);

    //如果当前状态 不是 空闲状态
    while (DL_ADC12_getStatus(GRAY_ADC_INST) != DL_ADC12_STATUS_CONVERSION_IDLE );

    //清除触发转换状态
    DL_ADC12_stopConversion(GRAY_ADC_INST);
    //失能ADC转换
    DL_ADC12_disableConversions(GRAY_ADC_INST);

    //获取数据
    gAdcResult = DL_ADC12_getMemResult(GRAY_ADC_INST, GRAY_ADC_CHANNEL);

    return gAdcResult;
}

