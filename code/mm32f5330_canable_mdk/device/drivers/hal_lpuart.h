/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_LPUART_H__
#define __HAL_LPUART_H__

#include "hal_common.h"

/*!
 * @addtogroup LPUART
 * @{
 */

/*!
 * @brief LPUART interrupt status offset number.
 */
#define LPUART_STATUS_INTSTATUS_SHIFT  16u  /*!< LPUART interrupt status offset number, distinguish from the status flag. */

/*!
 * @brief LPAURT status valid bit
 */
#define LPUART_STATUS_INTSTATUS_MASK  ((1u << LPUART_STATUS_INTSTATUS_SHIFT) - 1u)  /*!< LPAURT status valid bit. */

/*!
 * @addtogroup LPUART_STATUS
 * @{
 */
#define LPUART_STATUS_RX_OVERFLOW              LPUART_LPUSTA_RXOV_MASK  /*!< Status flag when receive over flow. */
#define LPUART_STATUS_FRAME_ERR                LPUART_LPUSTA_FERR_MASK  /*!< Status flag when frame format error. */
#define LPUART_STATUS_MATCH                    LPUART_LPUSTA_MATCH_MASK /*!< Status flag when the data in the receiving buffer is the same as the data matching register. */
#define LPUART_STATUS_RX_FULL                  LPUART_LPUSTA_RXF_MASK   /*!< Status flag when LPUART receiving buffer is full. */
#define LPUART_STATUS_TX_EMPTY                 LPUART_LPUSTA_TXE_MASK   /*!< Status flag when LPUART transmiter buffer is empty. */
#define LPUART_STATUS_TX_DONE                  LPUART_LPUSTA_TC_MASK    /*!< Status flag when LPUART transmiter shifter is empty after the transfer is done. */
#define LPUART_STATUS_PARITY_ERR               LPUART_LPUSTA_PERR_MASK  /*!< Status flag when parity bit error. */
#define LPUART_STATUS_START                    LPUART_LPUSTA_START_MASK /*!< Status flag when start bit detected. */
#define LPUART_STATUS_INTSTATUS_RX_DONE       (LPUART_LPUIF_RXIF_MASK << LPUART_STATUS_INTSTATUS_SHIFT)    /*!< Interrupt enable when LPUART receive a frame of data done. */
#define LPUART_STATUS_INTSTATUS_TX_EMPTY      (LPUART_LPUIF_TXIF_MASK << LPUART_STATUS_INTSTATUS_SHIFT)    /*!< Interrupt enable when LPUART transmiter buffer is empty. */
#define LPUART_STATUS_INTSTATUS_TRAILINGEDGE  (LPUART_LPUIF_RXNEGIF_MASK << LPUART_STATUS_INTSTATUS_SHIFT) /*!< Interrupt enable when falling edge is detected. */
#define LPUART_STATUS_INTSTATUS_TX_DONE       (LPUART_LPUIF_TCIF_MASK << LPUART_STATUS_INTSTATUS_SHIFT)    /*!< Interrupt enable when LPUART transmiter is done. */
/*!
 * @}
 */

/*!
 * @addtogroup LPUART_DMA
 * @{
 */
#define LPUART_DMA_TX     LPUART_LPUEN_DMAT_MASK   /*!< Enable LPUART DMA tx only. */
#define LPUART_DMA_RX     LPUART_LPUEN_DMAR_MASK   /*!< Enable LPUART DMA rx only. */
#define LPUART_DMA_TXRX  (LPUART_LPUEN_DMAT_MASK | LPUART_LPUEN_DMAR_MASK)  /*!< Enable LPUART DMA tx and rx. */
/*!
 * @}
 */

/*!
 * @brief LPUART clock source select.
 */
typedef enum
{
    LPUART_ClockSource_LSE = 0u,  /*!< Clock soucre is LSE. */
    LPUART_ClockSource_Other = 1u,  /*!< Select clock source is not LSE,need use the function LPUART_SetBaudrate2() to set baudrate. */
} LPUART_ClockSource_Type;

/*!
 * @brief LPUART use LSE as clock source's baudrate type.
 */
typedef enum
{
    LPUART_Baudrate_9600 = 0u,  /*!< Baudrate is 9600 when clock source is LSE. */
    LPUART_Baudrate_4800 = 1u,  /*!< Baudrate is 4800 when clock source is LSE. */
    LPUART_Baudrate_2400 = 2u,  /*!< Baudrate is 2400 when clock source is LSE. */
    LPUART_Baudrate_1200 = 3u,  /*!< Baudrate is 1200 when clock source is LSE. */
    LPUART_Baudrate_600  = 4u,  /*!< Baudrate is 600 when clock source is LSE. */
    LPUART_Baudrate_300  = 5u,  /*!< Baudrate is 300 when clock source is LSE. */
} LPUART_Baudrate_Type;

/*!
 * @brief LPUART word length type.
 */
typedef enum
{
    LPUART_WordLength_8 = 0u,  /*!< Word length 8 bits. */
    LPUART_WordLength_7 = 1u,  /*!< Word length 7 bits. */
} LPUART_WordLength_Type;

/*!
 * @brief LPUART stop bits type.
 */
typedef enum
{
    LPUART_StopBits_1 = 0u,  /*!< stop bit is 1 bit. */
    LPUART_StopBits_2 = 1u,  /*!< stop bit is 2 bit. */
} LPUART_StopBits_Type;

/*!
 * @brief LPUART parity type.
 */
typedef enum
{
    LPUART_Parity_None = 0u, /*!< No parity. */
    LPUART_Parity_Even = 1u, /*!< Even parity. */
    LPUART_Parity_Odd  = 2u, /*!< Odd parity. */
} LPUART_Parity_Type;

/*!
 * @brief Provides event to receive an interrupt.
 */
typedef enum
{
    LPUART_RxInterruptAF_Alt0 = 0u,   /*!< When the start event is detected, a reception interrupt is generated. */
    LPUART_RxInterruptAF_Alt1 = 1u,   /*!< When 1 bit data received done, a reception interrupt is generated. */
    LPUART_RxInterruptAF_Alt2 = 2u,   /*!< When receiving data match, a reception interrupt is generated. */
    LPUART_RxInterruptAF_Alt3 = 3u,   /*!< When a falling edge wake-up is detected, a reception interrupt is generated. */
} LPUART_RxInterruptAF_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref LPUART_Init() to initialize the LPUART module.
 */
typedef struct
{
    LPUART_ClockSource_Type   ClockSource;  /*!< LPUART clock source. */
    LPUART_Baudrate_Type      BaudRate;     /*!< Specify the LPUART LSE specific baud rate. */
    LPUART_WordLength_Type    WordLength;   /*!< Specify the number of data bits transmitted or received in a frame. */
    LPUART_StopBits_Type      StopBits;     /*!< Specify the number of stop bits transmitted. */
    LPUART_Parity_Type        Parity;       /*!< Specify the parity mode. */
} LPUART_Init_Type;

/*!
 * @brief Initialize the LPUART module.
 *
 * @param LPUARTx LPUART instance.
 * @param init  Pointer to the initialization structure. See to @ref LPUART_Init_Type.
 * @return None.
 */
void LPUART_Init(LPUART_Type * LPUARTx, LPUART_Init_Type * init);

/*!
 * @brief Enable the LPUART tx module.
 *
 * The LPUART Tx module should be enabled before sending data.
 *
 * @param LPUARTx LPUART instance.
 * @param enable 'true' to enable the module, 'false' to disable the module.
 * @return None.
 */
void LPUART_EnableTx(LPUART_Type * LPUARTx, bool enable);

/*!
 * @brief Enable the LPUART rx module.
 *
 * The LPUART module should be enabled before receiving data.
 *
 * @param LPUARTx LPUART instance.
 * @param enable 'true' to enable the module, 'false' to disable the module.
 * @return None.
 */
void LPUART_EnableRx(LPUART_Type * LPUARTx, bool enable);

/*!
 * @brief Get the current status flags of the LPUART module.
 *
 * @param LPUARTx LPUART instance.
 * @return Status flags. See to @ref LPUART_STATUS.
 */
uint32_t LPUART_GetStatus(LPUART_Type * LPUARTx);

/*!
 * @brief Clear the status flags of the LPUART module.
 *
 * @param LPUARTx LPUART instance.
 * @param status The mask codes of the indicated flags to be cleared.
 * @return None.
*/
void LPUART_ClearStatus(LPUART_Type * LPUARTx, uint32_t status);

/*!
 * @brief Put the data into transmiter buffer of the LPUART module.
 *
 * @param LPUARTx LPUART instance.
 * @param value Data value to be send through the transmiter.
 * @return None.
 */
void LPUART_PutData(LPUART_Type * LPUARTx, uint8_t value);

/*!
 * @brief Get the data from receiver buffer of the LPUART module.
 *
 * @param LPUARTx LPUART instance.
 * @return The data value received from the receiver.
 */
uint8_t LPUART_GetData(LPUART_Type * LPUARTx);

/*!
 * @brief Enable interrupts of the LPUART module.
 *
 * @param LPUARTx LPUART instance.
 * @param interrupts Interrupt code masks. See to @ref LPUART_STATUS.
 * @param enable 'true' to enable the indicated interrupts, 'false' to disable the indicated interrupts.
 * @return None.
 */
void LPUART_EnableInterrupts(LPUART_Type * LPUARTx, uint32_t interrupts, bool enable);

/*!
 * @brief Read the current enabled interrupts the LPUART module.
 *
 * @param LPUARTx LPUART instance.
 * @return The mask codes enabled interrupts. See to @ref LPUART_STATUS.
 */
uint32_t LPUART_GetEnabledInterrupts(LPUART_Type * LPUARTx);

/*!
 * @brief Enable the DMA trigger from the LPUART module.
 *
 * The DMA trigger events are the same as the interrupts.
 *
 * @param LPUARTx LPUART instance.
 * @param dma DMA xfer direction.
 * @param enable 'true' to enable the DMA trigger, 'false' to disable the DMA trigger.
 * @return None.
 */
void LPUART_EnableDMA(LPUART_Type * LPUARTx, uint32_t dma, bool enable);

/*!
 * @brief Get the hardware Tx data buffer's address the LPUART module.
 *
 * The return value of the address is most used with DMA module.
 *
 * @param LPUARTx LPUART instance.
 * @return The value of the address for LPUART module's hardware Tx data buffer.
 */
uint32_t   LPUART_GetTxDataRegAddr(LPUART_Type * LPUARTx);

/*!
 * @brief Get the hardware Rx data buffer's address the LPUART module.
 *
 * The return value of the address is most used with DMA module.
 *
 * @param LPUARTx LPUART instance.
 * @return The value of the address for LPUART module's hardware Rx data buffer.
 */
uint32_t   LPUART_GetRxDataRegAddr(LPUART_Type * LPUARTx);

/*!
 * @brief Configure the event that generates the receive interrupt.
 *
 * @param LPUARTx LPUART instance.
 * @param interrupt The event that generates the receive interrupt.
 * @return None.
 */
void LPUART_SetRxInterruptAF(LPUART_Type * LPUARTx, LPUART_RxInterruptAF_Type interrupt);

/*!
 * @brief Set baudrate when the clock source is not 32768KHz.
 *
 * @param LPUARTx LPUART instance.
 * @param freq Clock frequency.
 * @param baudrate Baudrate.
 * @return None.
 */
void LPUART_SetBaudrate2(LPUART_Type * LPUARTx, uint32_t freq, uint32_t baudrate);

/*!
 *@}
 */

#endif /* __HAL_UART_H__ */
