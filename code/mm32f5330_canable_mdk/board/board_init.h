/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef __BOARD_INIT_H__
#define __BOARD_INIT_H__

#include <stdio.h>
#include <stdint.h>

#include "hal_common.h"
#include "hal_rcc.h"
#include "hal_uart.h"
#include "hal_usb.h"
#include "hal_usb_bdt.h"

#include "clock_init.h"
#include "pin_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT           UART1
#define BOARD_DEBUG_UART_BAUDRATE       115200u
#define BOARD_DEBUG_UART_FREQ           CLOCK_APB2_FREQ

/* USB. */
#define BOARD_USB_PORT                  USB
#define BOARD_USB_IRQn                  USB_FS_IRQn
#define BOARD_USB_IRQHandler            USB_FS_IRQHandler

/* FLEXCAN. */
#define BOARD_FLEXCAN_PORT              FLEXCAN1
#define BOARD_FLEXCAN_CLOCK_FREQ        CLOCK_PLL1_FREQ
#define BOARD_FLEXCAN_RX_MB_CH          0u
#define BOARD_FLEXCAN_TX_MB_CH          15u
#define BOARD_FLEXCAN_RX_MB_INT         FLEXCAN_INT_MB_0
#define BOARD_FLEXCAN_TX_MB_INT         FLEXCAN_INT_MB_15
#define BOARD_FLEXCAN_RX_MB_STATUS      FLEXCAN_STATUS_MB_0
#define BOARD_FLEXCAN_TX_MB_STATUS      FLEXCAN_STATUS_MB_15
#define BOARD_FLEXCAN_RXFIFO_AVAIl_STATUS FLEXCAN_STATUS_MB_5

/* FLEXCAN Bit-timing under PLL1 clok. */
#define BOARD_FLEXCAN_PHASEGLEN1        5u
#define BOARD_FLEXCAN_PHASEGLEN2        1u
#define BOARD_FLEXCAN_PROSEGLEN         2u
#define BOARD_FLEXCAN_JUMPWIDTH         1u

#define APP_FLEXCAN_XFER_BITRATE        125000u  /* The flexcan bitrate = 125 kbps. */
#define APP_FLEXCAN_XFER_ID             0x666u   /* The flexcan xfer Id number. */
#define APP_FLEXCAN_XFER_BUF_LEN        8u       /* The flexcan xfer buffer length. */
#define APP_FLEXCAN_XFER_MaxNum         16u      /* Amount of mb to be used. */
#define APP_FLEXCAN_XFER_PRIORITY       0u       /* Priority of the mb frame. */

#define LED_BLUE_Port                   GPIOA
#define LED_BLUE_Pin                    GPIO_PIN_0
#define LED_BLUE                        LED_BLUE_Port , LED_BLUE_Pin

#define LED_GREEN_Port                  GPIOA
#define LED_GREEN_Pin                   GPIO_PIN_1
#define LED_GREEN                       LED_GREEN_Port , LED_GREEN_Pin

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
