/*
 * Copyright 2023 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef __HAL_RCC_H__
#define __HAL_RCC_H__

#include "hal_common.h"

/*!
 * @addtogroup RCC
 * @{
 */

/*!
 * @addtogroup RCC_AHB1_PERIPH
 * @{
 */
#define RCC_AHB1_PERIPH_GPIOA  (1u << 0u) /*!< AHB1 peripheral GPIOA clock 0 bit. */
#define RCC_AHB1_PERIPH_GPIOB  (1u << 1u) /*!< AHB1 peripheral GPIOB clock 1 bit. */
#define RCC_AHB1_PERIPH_GPIOC  (1u << 2u) /*!< AHB1 peripheral GPIOC clock 2 bit. */
#define RCC_AHB1_PERIPH_GPIOD  (1u << 3u) /*!< AHB1 peripheral GPIOD clock 3 bit. */
#define RCC_AHB1_PERIPH_GPIOH  (1u << 7u) /*!< AHB1 peripheral GPIOH clock 7 bit. */
#define RCC_AHB1_PERIPH_GPIOI  (1u << 8u) /*!< AHB1 peripheral GPIOI clock 8 bit. */
#define RCC_AHB1_PERIPH_CRC    (1u << 12u) /*!< AHB1 peripheral CRC clock 12 bit. */
#define RCC_AHB1_PERIPH_FLASH  (1u << 13u) /*!< AHB1 peripheral FLASH clock 13 bit. */
#define RCC_AHB1_PERIPH_SRAM   (1u << 14u) /*!< AHB1 peripheral SRAM clock 14 bit. */
#define RCC_AHB1_PERIPH_CORDIC (1u << 15u) /*!< AHB1 peripheral CORDIC clock 15 bit. */
#define RCC_AHB1_PERIPH_DMA1   (1u << 21u) /*!< AHB1 peripheral DMA1 clock 21 bit. */
#define RCC_AHB1_PERIPH_DMA2   (1u << 22u) /*!< AHB1 peripheral DMA2 clock 22 bit. */
#define RCC_AHB1_PERIPH_USBFS  (1u << 24u) /*!< AHB1 peripheral USBFS clock 24 bit. */

/*!
 * @}
 */

/*!
 * @addtogroup RCC_APB1_PERIPH
 * @{
 */
#define RCC_APB1_PERIPH_TIM2   (1u << 0u) /*!< APB1 peripheral TIM2 clock 0 bit. */
#define RCC_APB1_PERIPH_TIM3   (1u << 1u) /*!< APB1 peripheral TIM3 clock 1 bit. */
#define RCC_APB1_PERIPH_TIM4   (1u << 2u) /*!< APB1 peripheral TIM4 clock 2 bit. */
#define RCC_APB1_PERIPH_TIM5   (1u << 3u) /*!< APB1 peripheral TIM5 clock 3 bit. */
#define RCC_APB1_PERIPH_TIM6   (1u << 4u) /*!< APB1 peripheral TIM6 clock 4 bit. */
#define RCC_APB1_PERIPH_TIM7   (1u << 5u) /*!< APB1 peripheral TIM7 clock 5 bit. */
#define RCC_APB1_PERIPH_I3C    (1u << 8u) /*!< APB1 peripheral I3C clock 8 bit. */
#define RCC_APB1_PERIPH_WWDG   (1u << 11u) /*!< APB1 peripheral WWDG clock 11 bit. */
#define RCC_APB1_PERIPH_SPI2   (1u << 14u) /*!< APB1 peripheral SPI2 clock 14 bit. */
#define RCC_APB1_PERIPH_SPI3   (1u << 15u) /*!< APB1 peripheral SPI3 clock 15 bit. */
#define RCC_APB1_PERIPH_UART2  (1u << 17u) /*!< APB1 peripheral UART2 clock 17 bit. */
#define RCC_APB1_PERIPH_UART3  (1u << 18u) /*!< APB1 peripheral UART3 clock 18 bit. */
#define RCC_APB1_PERIPH_UART4  (1u << 19u) /*!< APB1 peripheral UART4 clock 19 bit. */
#define RCC_APB1_PERIPH_I2C1   (1u << 21u) /*!< APB1 peripheral I2C1 clock 21 bit. */
#define RCC_APB1_PERIPH_I2C2   (1u << 22u) /*!< APB1 peripheral I2C2 clock 22 bit. */
#define RCC_APB1_PERIPH_CRS    (1u << 24u) /*!< APB1 peripheral CRS clock 24 bit. */
#define RCC_APB1_PERIPH_FLEXCAN1 (1u << 25u) /*!< APB1 peripheral FLEXCAN1 clock 25 bit. */
#define RCC_APB1_PERIPH_BKP    (1u << 27u) /*!< APB1 peripheral BKP clock 27 bit. */
#define RCC_APB1_PERIPH_PWR_DBG  (1u << 28u) /*!< APB1 peripheral PWR clock 28 bit. */
#define RCC_APB1_PERIPH_DAC    (1u << 29u) /*!< APB1 peripheral DAC clock 29 bit. */

/*!
 * @}
 */

/*!
 * @addtogroup RCC_APB2_PERIPH
 * @{
 */
#define RCC_APB2_PERIPH_TIM1        (1u << 0u) /*!< APB2 peripheral TIM1 clock 0 bit. */
#define RCC_APB2_PERIPH_TIM8        (1u << 1u) /*!< APB2 peripheral TIM8 clock 1 bit. */
#define RCC_APB2_PERIPH_UART1       (1u << 4u) /*!< APB2 peripheral UART1 clock 4 bit. */
#define RCC_APB2_PERIPH_ADC1        (1u << 8u) /*!< APB2 peripheral ADC1 clock 8 bit. */
#define RCC_APB2_PERIPH_ADC2        (1u << 9u) /*!< APB2 peripheral ADC2 clock 9 bit. */
#define RCC_APB2_PERIPH_SPI1        (1u << 12u) /*!< APB2 peripheral SPI1 clock 12 bit. */
#define RCC_APB2_PERIPH_SYSCFG      (1u << 14u) /*!< APB2 peripheral SYSCFG clock 14 bit. */
#define RCC_APB2_PERIPH_COMP        (1u << 15u) /*!< APB2 peripheral USART clock 20 bit. */
#define RCC_APB2_PERIPH_USART       (1u << 20u) /*!< APB2 peripheral FLEXCAN2 clock 24 bit. */
#define RCC_APB2_PERIPH_MINDSWITCH  (1u << 28u) /*!< APB2 peripheral MINDSWITCH clock 28 bit. */
#define RCC_APB2_PERIPH_LPTIM       (1u << 30u) /*!< APB2 peripheral LPTIM clock 30 bit. */
#define RCC_APB2_PERIPH_LPUART      (1u << 31u) /*!< APB2 peripheral LPUART clock 31 bit. */

/*!
 * @}
 */

/*!
 * @brief Define the clock source for MCO output.
 */
typedef enum
{
    RCC_MCO_NoClock     = 0u, /*!< MCO NoClock 0 bits. */
    RCC_MCO_LSI         = 2u, /*!< MCO LSI 2 bits. */
    RCC_MCO_LSE         = 3u, /*!< MCO LSE 3 bits. */
    RCC_MCO_SYSCLK      = 4u, /*!< MCO SYSCLK 4 bits. */
    RCC_MCO_HSI         = 5u, /*!< MCO HSI 5 bits. */
    RCC_MCO_HSE         = 6u, /*!< MCO HSE 6 bits. */
    RCC_MCO_PLL1CLK     = 7u, /*!< MCO PLL1CLK 7 bits. */
    RCC_MCO_PLL2CLK     = 8u, /*!< MCO PLL2CLK 8 bits. */
} RCC_MCO_Type;

/*!
 * @brief Define the clock source for MCO output.
 */
typedef enum
{
    RCC_ResetStatus_LPWR       = 31u, /*!< Low Power Reset Flag. */
    RCC_ResetStatus_WWDG       = 30u, /*!< Window Watchdog Reset Flag. */
    RCC_ResetStatus_IWDG       = 29u, /*!< Independent Watchdog Reset Flag. */
    RCC_ResetStatus_SW         = 28u, /*!< Software Reset Flag. */
    RCC_ResetStatus_POR        = 27u, /*!< POR/PDR Reset Flag. */
    RCC_ResetStatus_PIN        = 26u, /*!< PIN Reset Flag. */
    RCC_ResetStatus_CPULOCKUP  = 23u, /*!< CPU Lockup Reset Flag. */
    RCC_ResetStatus_PVD        = 22u, /*!< PVD Reset Flag. */
    RCC_ResetStatus_LSIREADY   = 1u, /*!< LSI Ready. */
} RCC_ResetStatus_Type;

/*!
 * @brief Define the clock predivision for FLEXCAN.
 * This bit must be valid before FLEXCAN clock in the RCC_APB2ENR register can be enabled.
 */
typedef enum
{
    RCC_FLEXCANClockDiv_1 = 0u,  /*!< FLEXCAN clock predivision is frequency-neutral. */
    RCC_FLEXCANClockDiv_2 = 1u,  /*!< FLEXCAN clock predivision 2 Frequency division. */
    RCC_FLEXCANClockDiv_3 = 2u,  /*!< FLEXCAN clock predivision 3 Frequency division. */
    RCC_FLEXCANClockDiv_4 = 3u,  /*!< FLEXCAN clock predivision 4 Frequency division */
} RCC_FLEXCANClockDiv_Type;

/*!
 * @brief Define the clock source for FLEXCAN.
 */
typedef enum
{
    RCC_FLEXCANClockSource_Type_PLL1 = 0u,  /*!< FLEXCAN clock source is PLL1. */
    RCC_FLEXCANClockSource_Type_PLL2 = 1u,  /*!< FLEXCAN clock source is PLL2. */
    RCC_FLEXCANClockSource_Type_HSE = 2u,   /*!< FLEXCAN clock source is HSE. */
} RCC_FLEXCANClockSource_Type;

/*!
 * @brief Define the clock predivision for TIM.
 */
typedef enum
{
    RCC_TIMClockDiv_1 = 0u,   /*!< TIM clock predivision is frequency-neutral. */
    RCC_TIMClockDiv_2 = 4u,   /*!< TIM clock predivision 2  Frequency division. */
    RCC_TIMClockDiv_4 = 5u,   /*!< TIM clock predivision 4  Frequency division. */
    RCC_TIMClockDiv_8 = 6u,   /*!< TIM clock predivision 8  Frequency division */
    RCC_TIMClockDiv_16 = 7u,  /*!< TIM clock predivision 16 Frequency division */
} RCC_TIMClockDiv_Type;

/*!
 * @brief Define the clock source for TIM.
 */
typedef enum
{
    RCC_TIMClockSource_Type_PLL2 = 0u,    /*!< TIM clock source is PLL2. */
    RCC_TIMClockSource_Type_SYSCLK = 1u,  /*!< TIM clock source is SYSCFG. */
} RCC_TIMClockSource_Type;

/*!
 * @brief Define the clock source for LPUART & LPTIMER.
 * PCLK is the default clock source for LPTIM.
 * LSE is the default clock source for LPUART.
 */
typedef enum
{
    RCC_ClockSource_LSE = 0u,  /*!< LSE as the clock souerce. */
    RCC_ClockSource_LSI = 1u,  /*!< LSI as the clock souerce. */
    RCC_ClockSource_PCLK = 2u, /*!< PCLK as the clock souerce. */
    RCC_ClockSource_HSI = 3u,  /*!< HSI as the clock souerce. */
} RCC_ClockSource_Type;
/*!
 * @brief Enable the RCC AHB1 periphs clock module.
 *
 * @param ahb1_periphs AHB1 Peripheral instance.
 * @param enable 'true' to enable the AHB1Periphs, 'false' to disable the AHB1Periphs.
 * @return None.
 */
void RCC_EnableAHB1Periphs(uint32_t ahb1_periphs, bool enable);

/*!
 * @brief Reset the RCC AHB1 periphs clock module.
 *
 * @param ahb1_periphs AHB1 Peripheral instance.
 * @return None.
 */
void RCC_ResetAHB1Periphs(uint32_t ahb1_periphs);

/*!
 * @brief Enable the RCC APB1 periphs clock module.
 *
 * @param apb1_periphs APB1 Peripheral instance.
 * @param enable 'true' to enable the APB1Periphs, 'false' to disable the APB1Periphs.
 * @return None.
 */
void RCC_EnableAPB1Periphs(uint32_t apb1_periphs, bool enable);

/*!
 * @brief Reset the RCC APB1 periphs clock module.
 *
 * @param apb1_periphs APB1 Peripheral instance.
 * @return None.
 */
void RCC_ResetAPB1Periphs(uint32_t apb1_periphs);

/*!
 * @brief Enable the RCC APB2 periphs clock module.
 *
 * @param apb2_periphs APB1 Peripheral instance.
 * @param enable 'true' to enable the APB2Periphs, 'false' to disable the APB2Periphs.
 * @return None.
 */
void RCC_EnableAPB2Periphs(uint32_t apb2_periphs, bool enable);

/*!
 * @brief Reset the RCC APB2 periphs clock module.
 *
 * @param apb2_periphs APB2 Peripheral instance.
 * @return None.
 */
void RCC_ResetAPB2Periphs(uint32_t apb2_periphs);

/*!
 * @brief MCO  Configuration clock source.
 *
 * @param source The clock source for MCO Configuration.
 * @return None.
 */
void RCC_SetMCOConf(RCC_MCO_Type source);

/*!
 * @brief Set ADC clock div.
 *
 * @param ADCx ADC instance.
 * @param div The ADC clock div.
 * @return None.
 */
void RCC_SetADCClockDiv(ADC_Type * ADCx, uint32_t div);

/*!
 * @brief Set ADC calibration clock div.
 *
 * @param ADCx ADC instance.
 * @param div The ADC calibration clock div.
 * @return None.
 */
void RCC_SetADCCalibClockDiv(ADC_Type * ADCx, uint32_t div);

/*!
 * @brief Set DAC clock div.
 *
 * @param div The DAC clock div.
 * @return None.
 */
void RCC_SetDACClockDiv(uint32_t div);

/*!
 * @brief Enable FSMC synchronization.
 *
 * @param enable 'true' to enable the FSMC synchronization,'false' to disable the FSMC synchronization, .
 * @return None.
 */
void RCC_EnableFSMCSyncMode(bool enable);

/*!
 * @brief Set FSMC clock div.
 *
 * @param div The FSMC clock div.
 * @return None.
 */
void RCC_SetFSMCClockdiv(uint32_t div);

/*!
 * @brief Set TPIU clock div.
 *
 * @param div The TPIU clock div.
 * @return None.
 */
void RCC_SetTPIUClockDiv(uint32_t div);

/*!
 * @brief Enable BKP write Protect.
 *
 * @param enable 'true' to can not allow writting BKP & RTC ,'false' to allow writting BKP & RTC .
 * @return None.
 */
void RCC_EnableBKPWriteProtect(bool enable);

/*!
 * @brief Enable BKP reset.
 *
 * @param enable 'true' to reset BKP ,'false' to not reset.
 * @return None.
 */
void RCC_EnableBKPReset(bool enable);

/*!
 * @brief Enable RTC clock.
 *
 * @param enable 'true' to enable RTC cloxk ,'false' to disable.
 * @return None.
 */
void RCC_EnableRTCClock(bool enable);

/*!
 * @brief Set RTC clock source.
 *
 * @param source the RTC clock source.
 * @return None.
 */
void RCC_SetRTCClockSource(uint32_t source);

/*!
 * @brief Enable LSE Bypass Mode.
 *
 * @param enable 'true' to enable LSE Bypass Mode ,'false' to disable.
 * @return None.
 */
void RCC_EnableLSEBypassMode(bool enable);

/*!
 * @brief Get LSE Oscillator Ready.
 *
 * @param None.
 * @return Ready Status.
 */
uint32_t GetLSEReadyStatus(void);

/*!
 * @brief Enable LSE oscillator clock.
 *
 * @param enable 'true' to enable LSE oscillator clock ,'false' to disable.
 * @return None.
 */
void RCC_EnableLSEClock(bool enable);

/*!
 * @brief Get Reset Status.
 *
 * @param status the reset status ,see to @ref ResetStatus_Type.
 * @return the reset status.
 */
uint32_t GetResetStatus(RCC_ResetStatus_Type status );

/*!
 * @brief Clear all Reset Status.
 *
 * @param None.
 * @return None.
 */
void ClearResetStatus(void);
/*!
 * @brief Enable CPU Lock.
 *
 * @param enable 'true' to enable lock CPU ,'false' to disable.
 * @return None.
 */
void RCC_EnableCPULock(bool enable);
/*!
 * @brief Enable PVD Reset.
 *
 * @param enable 'true' to reset PVD ,'false' to disable.
 * @return None.
 */
void RCC_EnablePVDReset(bool enable);
/*!
 * @brief Enable LSI clock output.
 *
 * @param enable 'true' to  enable LSI clock output,'false' to disable.
 * @return None.
 */
void RCC_EnableLSIClockOutput(bool enable);
/*!
 * @brief Enable LSI Oscillator .
 *
 * @param enable 'true' to  enable LSI Oscillator ,'false' to disable.
 * @return None.
 */
void RCC_EnableLSIClock(bool enable);
/*!
 *@}
 */

#endif /* __HAL_RCC_H__ */
