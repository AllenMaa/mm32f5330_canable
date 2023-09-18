/*
 * Copyright 2023 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "hal_common.h"
#include "hal_rcc.h"

void RCC_EnableAHB1Periphs(uint32_t ahb1_periphs, bool enable)
{
    (enable) ? (RCC->AHBENR |= ahb1_periphs) : (RCC->AHBENR &= ~ahb1_periphs);
}

void RCC_EnableAPB1Periphs(uint32_t apb1_periphs, bool enable)
{
    (enable) ? (RCC->APB1ENR |= apb1_periphs) : (RCC->APB1ENR &= ~apb1_periphs);
}

void RCC_EnableAPB2Periphs(uint32_t apb2_periphs, bool enable)
{
    (enable) ? (RCC->APB2ENR |= apb2_periphs) : (RCC->APB2ENR &= ~apb2_periphs);
}

void RCC_ResetAHB1Periphs(uint32_t ahb1_periphs)
{
    RCC->AHBRSTR |= ahb1_periphs;
    RCC->AHBRSTR &= ~ahb1_periphs;
}

void RCC_ResetAPB1Periphs(uint32_t apb1_periphs)
{
    RCC->APB1RSTR |= apb1_periphs;
    RCC->APB1RSTR &= ~apb1_periphs;
}

void RCC_ResetAPB2Periphs(uint32_t apb2_periphs)
{
    RCC->APB2RSTR |= apb2_periphs;
    RCC->APB2RSTR &= ~apb2_periphs;
}

void RCC_SetMCOConf(RCC_MCO_Type source)
{
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_MCO_MASK) | RCC_CFGR_MCO(source);
}

void RCC_SetADCClockDiv(ADC_Type * ADCx, uint32_t div)
{
    if (ADCx == ADC1)
    {
        RCC->ADC1CFGR = (RCC->ADC1CFGR & ~RCC_ADC1CFGR_PRE_MASK) | RCC_ADC1CFGR_PRE(div);
    }
    else if (ADCx == ADC2)
    {
        RCC->ADC2CFGR = (RCC->ADC2CFGR & ~RCC_ADC2CFGR_PRE_MASK) | RCC_ADC2CFGR_PRE(div);
    }
}

void RCC_SetADCCalibClockDiv(ADC_Type * ADCx, uint32_t div)
{
    if (ADCx == ADC1)
    {
        RCC->ADC1CFGR = (RCC->ADC1CFGR & ~RCC_ADC1CFGR_PRECAL_MASK) | RCC_ADC1CFGR_PRECAL(div);
    }
    else if (ADCx == ADC2)
    {
        RCC->ADC2CFGR = (RCC->ADC2CFGR & ~RCC_ADC2CFGR_PRECAL_MASK) | RCC_ADC1CFGR_PRECAL(div);
    }
}

void RCC_SetDACClockDiv(uint32_t div)
{
    RCC->DACCFGR = (RCC->DACCFGR & ~RCC_DACCFGR_PRE_MASK) | RCC_DACCFGR_PRE(div);
}

void RCC_SetTPIUClockDiv(uint32_t div)
{
    RCC->TPIUCFGR = (RCC->TPIUCFGR & ~RCC_TPIUCFGR_PRE_MASK) | RCC_TPIUCFGR_PRE(div);
}

void RCC_EnableBKPWriteProtect(bool enable)
{
    (enable) ? (RCC->BDCR &= ~RCC_BDCR_DBP_MASK) : (RCC->BDCR |= RCC_BDCR_DBP_MASK);
}

void RCC_EnableBKPReset(bool enable)
{
    (enable) ? (RCC->BDCR |= RCC_BDCR_BDRST_MASK) : (RCC->BDCR &= ~RCC_BDCR_BDRST_MASK);
}

void RCC_EnableRTCClock(bool enable)
{
    (enable) ? (RCC->BDCR |= RCC_BDCR_RTCEN_MASK) : (RCC->BDCR &= ~RCC_BDCR_RTCEN_MASK);
}

void RCC_SetRTCClockSource(uint32_t source)
{
    RCC->BDCR |= RCC_BDCR_RTCSEL(source);
}

void RCC_EnableLSEBypassMode(bool enable)
{
    (enable) ? (RCC->BDCR |= RCC_BDCR_LSEBYP_MASK) : (RCC->BDCR &= ~RCC_BDCR_LSEBYP_MASK);
}

uint32_t GetLSEReadyStatus(void)
{
    return (RCC->BDCR &= RCC_BDCR_LSERDY_MASK);
}

void RCC_EnableLSEClock(bool enable)
{
    (enable) ? (RCC->BDCR |= RCC_BDCR_LSEON_MASK) : (RCC->BDCR &= ~RCC_BDCR_LSEON_MASK);
}

uint32_t GetResetStatus(RCC_ResetStatus_Type status )
{
    return (RCC->CSR &= status);
}

void ClearResetStatus(void)
{
    RCC->CSR = RCC_CSR_RMVF_MASK;
}

void RCC_EnableCPULock(bool enable)
{
    (enable) ? (RCC->CSR |= RCC_CSR_LOCKUPEN_MASK) : (RCC->BDCR &= ~RCC_CSR_LOCKUPEN_MASK);
}

void RCC_EnablePVDReset(bool enable)
{
    (enable) ? (RCC->CSR |= RCC_CSR_PVDRSTEN_MASK) : (RCC->BDCR &= ~RCC_CSR_PVDRSTEN_MASK);
}

void RCC_EnableLSIClockOutput(bool enable)
{
    (enable) ? (RCC->CSR |= RCC_CSR_LSIOE_MASK) : (RCC->BDCR &= ~RCC_CSR_LSIOE_MASK);
}

void RCC_EnableLSIClock(bool enable)
{
    (enable) ? (RCC->CSR |= RCC_CSR_LSION_MASK) : (RCC->BDCR &= ~RCC_CSR_LSION_MASK);
}

void RCC_SetLPTIMClockSource(RCC_ClockSource_Type source)
{
    RCC->CFGR2 = (RCC->CFGR2 & ~RCC_CFGR2_LPTIMCLKSEL_MASK) | RCC_CFGR2_LPTIMCLKSEL(source);
}

void RCC_SetLPUARTClockSource(RCC_ClockSource_Type source)
{
    RCC->CFGR2 = (RCC->CFGR2 & ~RCC_CFGR2_LPUARTCLKSEL_MASK) | RCC_CFGR2_LPUARTCLKSEL(source);
}

void RCC_SetFLEXCANClockDiv(RCC_FLEXCANClockDiv_Type div)
{
    RCC->CFGR2 = (RCC->CFGR2 & ~RCC_CFGR2_CANPRE_MASK) | RCC_CFGR2_CANPRE(div);
}

void RCC_SetFLEXCANCClockSource(RCC_FLEXCANClockSource_Type source)
{
    RCC->CFGR2 = (RCC->CFGR2 & ~RCC_CFGR2_CANCLKSEL_MASK) | RCC_CFGR2_CANCLKSEL(source);
}

void RCC_SetTIMClockDiv(RCC_TIMClockDiv_Type div)
{
    RCC->CFGR2 = (RCC->CFGR2 & ~RCC_CFGR2_TIMADVPRE_MASK) | RCC_CFGR2_TIMADVPRE(div);
}

void RCC_SetTIMClockSource(RCC_TIMClockSource_Type source)
{
    RCC->CFGR2 = (RCC->CFGR2 & ~RCC_CFGR2_TIMADVCKSEL_MASK) | RCC_CFGR2_TIMADVCKSEL(source);
}

/* EOF. */
