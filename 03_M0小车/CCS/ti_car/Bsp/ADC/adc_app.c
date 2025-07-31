#include "adc_app.h"
#include "system.h"

#define GRAY_ADC_INST ADC_GRAY_INST
#define GRAY_ADC_CHANNEL ADC_GRAY_ADCMEM_ADC_Channel0_REF

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

