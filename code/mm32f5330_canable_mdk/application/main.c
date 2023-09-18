/*
 * Copyright 2023 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "board_init.h"
#include "can.h"
#include "slcan.h"
#include "led.h"
#include "error.h"
#include "tusb.h"

void cdc_process(void);

/*------------- MAIN -------------*/
int main(void)
{
    BOARD_Init();

    can_init();
    led_init();
    tusb_init();

    // Storage for status and received message buffer
    FLEXCAN_Mb_Type rx_msg_header;
    uint8_t rx_msg_data[8] = {0};
    uint8_t msg_buf[SLCAN_MTU];

    while (1)
    {
        cdc_process();
        led_process();
        can_process();

        // If CAN message receive is pending, process the message
        if (is_can_msg_pending() != 0u)
        {
            // If message received from bus, parse the frame
            if (can_rx(&rx_msg_header, rx_msg_data) == true)
            {
                // Parse an incoming CAN frame into an outgoing slcan message
                uint16_t msg_len = slcan_parse_frame((uint8_t *)&msg_buf, &rx_msg_header, rx_msg_data);

                // Transmit message via USB-CDC
                if(msg_len)
                {
                    tud_cdc_write(msg_buf, msg_len);
                    tud_cdc_write_flush();
                }
            }
        }
    }
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
  //blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  //blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  //blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  //blink_interval_ms = BLINK_MOUNTED;
}


//--------------------------------------------------------------------+
// USB CDC
//--------------------------------------------------------------------+

// Invoked when received new data
void tud_cdc_rx_cb(uint8_t itf)
{
    (void) itf;
}

// Invoked when received `wanted_char`
void tud_cdc_rx_wanted_cb(uint8_t itf, char wanted_char)
{
    (void) itf;
    (void) wanted_char;
}

// Invoked when space becomes available in TX buffer
void tud_cdc_tx_complete_cb(uint8_t itf)
{
    (void) itf;
}

// Invoked when line state DTR & RTS are changed via SET_CONTROL_LINE_STATE
void tud_cdc_line_state_cb(uint8_t itf, bool dtr, bool rts)
{
    (void) itf;
    (void) dtr;
    (void) rts;
}

// Invoked when line coding is change via SET_LINE_CODING
void tud_cdc_line_coding_cb(uint8_t itf, cdc_line_coding_t const* p_line_coding)
{
    (void) itf;
    (void) p_line_coding;
}

// Invoked when received send break
void tud_cdc_send_break_cb(uint8_t itf, uint16_t duration_ms)
{
    (void) itf;
    (void) duration_ms;
}

uint8_t slcan_str[30];
uint32_t slcan_str_index = 0;

// Process incoming USB-CDC messages from RX FIFO
void cdc_process(void)
{
    __disable_irq();

    if ( tud_cdc_available() )
    {
        // read datas
        char buf[64];
        uint32_t buf_cnt = tud_cdc_read(buf, sizeof(buf));

        for (uint32_t i = 0; i < buf_cnt; i++)
        {
            if (buf[i] == '\r')
            {
                slcan_parse_str(slcan_str, slcan_str_index);
                slcan_str_index = 0;
                memset(slcan_str, 0, sizeof(slcan_str));
            }
            else
            {
                if (slcan_str_index >= sizeof(slcan_str))
                {
                    slcan_str_index = 0;
                }
                slcan_str[slcan_str_index] = buf[i];
                slcan_str_index++;
            }
        }
    }

    __enable_irq();
}

/* EOF. */
