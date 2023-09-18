/*
 * Copyright 2023 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_dac.h"

void DAC_Init(DAC_Type * DACx, uint32_t channel, DAC_Init_Type * init)
{
    uint32_t cr = 0u;

    cr = DACx->CR & ~(( DAC_CR_BOFF1_MASK
                      | DAC_CR_TEN1_MASK
                      ) << (channel<<4u));    /* Calculate the shift and clear the indicated bit. */

    /* Enable Output Buffer. */
    if (init->EnableOutBuf == false)
    {
        cr |= (DAC_CR_BOFF1_MASK << (channel<<4u));
    }

    /* Trigger Source. */
    if (init->EnableTrigger)
    {
        cr |= ((DAC_CR_TEN1_MASK) << (channel<<4u));
    }

    DAC->CR = cr;
}

void DAC_Enable(DAC_Type * DACx, uint32_t channel, bool enable)
{
    if (enable)
    {
        DACx->CR |= (DAC_CR_EN1_MASK << (channel << 4u));
    }
    else
    {
        DACx->CR &= ~(DAC_CR_EN1_MASK << (channel << 4u));
    }
}

void DAC_EnableChannelOutput(DAC_Type * DACx, uint32_t channel, bool enable)
{
    if (enable)
    {
        DACx->CR |= (DAC_CR_OEEN1_MASK << (channel << 4u));
    }
    else
    {
        DACx->CR &= ~(DAC_CR_OEEN1_MASK << (channel << 4u));
    }
}

uint32_t DAC_GetData(DAC_Type * DACx, uint32_t channel)
{
    uint32_t ret = 0u;

    if(channel == DAC_CHN_1)
    {
        ret = (DACx->DOR1 & DAC_DOR1_DACC1DOR_MASK);
    }

    return ret;
}

uint32_t DAC_PutData(DAC_Type * DACx, uint32_t channel, uint32_t value, DAC_Align_Type align)
{
    uint32_t ret = 0u;

    switch (align)
    {

        case DAC_Align_8b_Right:
        {
            DAC_PutData8bRightAlign(DACx, channel, value);
            ret = DAC_GetData(DACx, channel);
            break;
        }
        case DAC_Align_12b_Left:
        {
            DAC_PutData12bLeftAlign(DACx, channel, value);
            ret = DAC_GetData(DACx, channel);
            break;
        }
        case DAC_Align_12b_Right:
        {
            DAC_PutData12bRightAlign(DACx, channel, value);
            ret = DAC_GetData(DACx, channel);
            break;
        }
        default:
            break;
    }
    return ret;
}

void DAC_EnableAddNoise(DAC_Type * DACx, uint32_t channel, DAC_AddNoise_Init_Type * init)
{
    if (init == NULL)
    {
        DAC->CR &=  ~(DAC_CR_WAVE1_MASK << (channel << 4u));
    }
    else
    {
        DAC->CR |= (( DAC_CR_WAVE1(1u) /* Noise wave need to set WAVEx = 01. */
                   |  DAC_CR_MAMP1(init->AddNoise)
                   ) << (channel << 4u));
    }
}

void DAC_EnableAddTriangle(DAC_Type * DACx, uint32_t channel, DAC_AddTriangle_Init_Type * init)
{
    if (init == NULL)
    {
        DAC->CR &=  ~(DAC_CR_WAVE1_MASK << (channel << 4u));
    }
    else
    {
        DAC->CR |= (( DAC_CR_WAVE1(2u) /* Noise wave need to set WAVEx = 1x. */
                   |  DAC_CR_MAMP1(init->AddTriangle)
                   ) << (channel << 4u));
    }
}

void DAC_EnableDMA(DAC_Type * DACx, uint32_t channel, bool enable)
{
    if (enable)
    {
        DACx->CR |= (DAC_CR_DMAEN1_MASK << (channel<<4u));
    }
    else
    {
        DACx->CR &= ~(DAC_CR_DMAEN1_MASK << (channel<<4u));
    }
}

void DAC_DoSwTrigger(DAC_Type * DACx, uint32_t channel)
{
    DACx->SWTRIGR |=  (DAC_SWTRIGR_SWTRIG1_MASK << channel);
}

uint32_t DAC_GetDataRegAddr(DAC_Type * DACx, uint32_t channel, DAC_Align_Type align)
{
    uint32_t ret = 0u;

    switch (align)
    {
        case DAC_Align_8b_Right:
        {
            ret = DAC_GetData8bRegAddr(DACx, channel);
            break;
        }
        case DAC_Align_12b_Left:
        {
            ret = DAC_GetData12bLeftRegAddr(DACx, channel);
            break;
        }
        case DAC_Align_12b_Right:
        {
            ret = DAC_GetData12bRightRegAddr(DACx, channel);
            break;
        }
        default:
            break;
    }
    return ret;
}

/* input value bit[7:0]. 12b output: xxxxxxxx0000. */
void DAC_PutData8bRightAlign(DAC_Type * DACx, uint32_t channel, uint32_t value)
{
    if (channel == DAC_CHN_1)
    {
        DACx->DHR8R1 = value;
    }
}

/* input value bit[15:4]. 12b output: xxxxxxxxxxxx. */
void DAC_PutData12bLeftAlign(DAC_Type * DACx, uint32_t channel, uint32_t value)
{
    if (channel == DAC_CHN_1)
    {
        DACx->DHR12L1 = value;
    }
}

/* input value bit[11:0], 12b output: xxxxxxxxxxxx. */
void DAC_PutData12bRightAlign(DAC_Type * DACx, uint32_t channel, uint32_t value)
{
    if (channel == DAC_CHN_1)
    {
        DACx->DHR12R1 = value;
    }
}

uint32_t DAC_GetData8bRegAddr(DAC_Type * DACx, uint32_t channel)
{
    uint32_t ret = 0u;

    if (channel == DAC_CHN_1)
    {
        ret = (uint32_t)(&(DACx->DHR8R1));
    }

    return ret;
}

uint32_t DAC_GetData12bLeftRegAddr(DAC_Type * DACx, uint32_t channel)
{
    uint32_t ret = 0u;

    if (channel == DAC_CHN_1)
    {
        ret = (uint32_t)(&(DACx->DHR12L1));
    }

    return ret;
}

uint32_t DAC_GetData12bRightRegAddr(DAC_Type * DACx, uint32_t channel)
{
    uint32_t ret = 0;

    if (channel == DAC_CHN_1)
    {
        ret = (uint32_t)(&(DACx->DHR12R1));
    }
    return ret;
}


/* EOF. */
