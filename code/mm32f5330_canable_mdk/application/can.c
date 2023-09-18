#include "can.h"
#include "led.h"
#include "error.h"

static FLEXCAN_TimConf_Type flexcan_tim_conf;
static FLEXCAN_Init_Type flexcan_init;
static FLEXCAN_RxFifoConf_Type rxfifo_conf;
static FLEXCAN_RxFifoMaskConf_Type rxfifo_mask;
static can_bus_state_t bus_state = OFF_BUS;
static uint8_t can_autoretransmit = 1u;
static uint32_t can_bitrate;
static can_txbuf_t txqueue = {0};

void app_flexcan_init(void);          /* Setup flexcan. */
void app_flexcan_tx(uint8_t *tx_buf); /* Transport frame. */
void app_flexcan_rx(uint8_t *rx_buf); /* Receive frame. */

// Initialize CAN peripheral settings, but don't actually start the peripheral
void can_init(void)
{
    // default to 125 kbit/s
    /* Set bit timing. */
    flexcan_tim_conf.EnableExtendedTime = true;
    flexcan_tim_conf.PhaSegLen1 = BOARD_FLEXCAN_PHASEGLEN1;
    flexcan_tim_conf.PhaSegLen2 = BOARD_FLEXCAN_PHASEGLEN2;
    flexcan_tim_conf.PropSegLen = BOARD_FLEXCAN_PROSEGLEN;
    flexcan_tim_conf.JumpWidth  = BOARD_FLEXCAN_JUMPWIDTH;

    /* Setup FlexCAN. */
    flexcan_init.MaxXferNum = APP_FLEXCAN_XFER_MaxNum; /* The max mb number to be used. */
    flexcan_init.ClockSource = FLEXCAN_ClockSource_Periph; /* Use peripheral clock. */
    flexcan_init.BitRate = APP_FLEXCAN_XFER_BITRATE; /* Set bitrate. */
    flexcan_init.ClockFreqHz = BOARD_FLEXCAN_CLOCK_FREQ; /* Set clock frequency. */
    flexcan_init.SelfWakeUp = FLEXCAN_SelfWakeUp_BypassFilter; /* Use unfiltered signal to wake up flexcan. */
    flexcan_init.WorkMode = FLEXCAN_WorkMode_Normal; /* Normal workmode, can receive and transport. */
    flexcan_init.Mask = FLEXCAN_Mask_Global; /* Use global mask for filtering. */
    flexcan_init.EnableSelfReception = false; /* Not receiving mb frame sent by self. */
    flexcan_init.EnableTimerSync = true; /* Every tx or rx done, refresh the timer to start from zero. */
    flexcan_init.TimConf = &flexcan_tim_conf; /* Set timing sychronization. */

    /* Set tx mb. */
    FLEXCAN_ResetMb(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_CH);
    FLEXCAN_SetMbCode(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_CH, FLEXCAN_MbCode_TxInactive);

    /* Set rx_fifo mask */
    rxfifo_mask.RxIdA = 0x0;
    rxfifo_mask.FilterFormat = FLEXCAN_FifoIdFilterFormat_A;
    rxfifo_mask.MbFormat = FLEXCAN_MbFormat_Standard;
    rxfifo_mask.MbType = FLEXCAN_MbType_Data;
    

    /* Set rx_fifo. */
    uint32_t FileterTable[] = {0,0,0,0};
    rxfifo_conf.FilterFormat = FLEXCAN_FifoIdFilterFormat_A;
    rxfifo_conf.IdFilterNum = 1;
    rxfifo_conf.priority = FLEXCAN_FifoPriority_FifoFirst;
    rxfifo_conf.IdFilterTable = FileterTable;
    

    bus_state = OFF_BUS;
}

// Start the CAN peripheral
void can_enable(void)
{
    if (bus_state == OFF_BUS)
    {
        flexcan_init.BitRate = can_bitrate; /* Set bitrate. */
        
        FLEXCAN_Init(BOARD_FLEXCAN_PORT, &flexcan_init);
        
        FLEXCAN_SetRxFifoGlobalMaskConf(BOARD_FLEXCAN_PORT, &rxfifo_mask);
        FLEXCAN_EnableRxFifo(BOARD_FLEXCAN_PORT, &rxfifo_conf);
        
        bus_state = ON_BUS;

        led_blue_on();
    }
}

// Disable the CAN peripheral and go off-bus
void can_disable(void)
{
    if (bus_state == ON_BUS)
    {
        FLEXCAN_Enable(BOARD_FLEXCAN_PORT, false);
        bus_state = OFF_BUS;

        led_green_on();
    }
}

// Set the bitrate of the CAN peripheral
void can_set_bitrate(enum can_bitrate bitrate)
{
    if (bus_state == ON_BUS)
    {
        // cannot set bitrate while on bus
        return;
    }

    switch (bitrate)
    {
        case CAN_BITRATE_10K:
            can_bitrate = 10000;
            break;
        case CAN_BITRATE_20K:
            can_bitrate = 20000;
            break;
        case CAN_BITRATE_50K:
            can_bitrate = 50000;
            break;
        case CAN_BITRATE_100K:
            can_bitrate = 100000;
            break;
        case CAN_BITRATE_125K:
            can_bitrate = 125000;
            break;
        case CAN_BITRATE_250K:
            can_bitrate = 250000;
            break;
        case CAN_BITRATE_500K:
            can_bitrate = 500000;
            break;
        case CAN_BITRATE_750K:
            can_bitrate = 750000;
            break;
        case CAN_BITRATE_1000K:
            can_bitrate = 1000000;
            
            break;
        case CAN_BITRATE_INVALID:
        default:
            can_bitrate = 1000000;
            break;
    }

    led_green_on();
}

// Set CAN peripheral to silent mode
void can_set_silent(uint8_t silent)
{
    if (bus_state == ON_BUS)
    {
        // cannot set silent mode while on bus
        return;
    }
    if (silent)
    {
        flexcan_init.WorkMode = FLEXCAN_WorkMode_ListenOnly;
    } else {
        flexcan_init.WorkMode = FLEXCAN_WorkMode_Normal;
    }

    led_green_on();
}

// Enable/disable auto-retransmission
void can_set_autoretransmit(uint8_t autoretransmit)
{
    if (bus_state == ON_BUS)
    {
        // Cannot set autoretransmission while on bus
        return;
    }
    if (autoretransmit)
    {
        //can_autoretransmit = ENABLE;
    } else {
        //can_autoretransmit = DISABLE;
    }

    led_green_on();
}

// Send a message on the CAN bus
uint32_t can_tx(FLEXCAN_Mb_Type *tx_msg_header, uint8_t* tx_msg_data)
{
    // Check if space available in the buffer (FIXME: wastes 1 item)
    if( ((txqueue.head + 1) % TXQUEUE_LEN) == txqueue.tail)
    {
        error_assert(ERR_FULLBUF_CANTX);
        return 1u;
    }

    // Copy header struct into array
    txqueue.header[txqueue.head] = *tx_msg_header;

    // Increment the head pointer
    txqueue.head = (txqueue.head + 1) % TXQUEUE_LEN;

    return 0u;
}

// Receive message from the CAN bus RXFIFO
uint32_t can_rx(FLEXCAN_Mb_Type *rx_msg_header, uint8_t* rx_msg_data)
{
    uint32_t status = FLEXCAN_ReadRxFifo(BOARD_FLEXCAN_PORT, rx_msg_header);//HAL_CAN_GetRxMessage(&can_handle, CAN_RX_FIFO0, rx_msg_header, rx_msg_data);
    FLEXCAN_ClearMbStatus(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_RXFIFO_AVAIl_STATUS);

    led_blue_on();

    return status;
}

// Process messages in the TX output queue
void can_process(void)
{
    if((txqueue.tail != txqueue.head) && ((FLEXCAN_GetStatus(BOARD_FLEXCAN_PORT) & FLEXCAN_STATUS_TX) == 0u) )
    {
        // Transmit can frame
        uint32_t status = FLEXCAN_WriteTxMb(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_CH, &txqueue.header[txqueue.tail]);
        FLEXCAN_SetMbCode(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_CH, FLEXCAN_MbCode_TxDataOrRemote); /* Write code to send. */
        txqueue.tail = (txqueue.tail + 1) % TXQUEUE_LEN;

        led_green_on();

        // This drops the packet if it fails (no retry). Failure is unlikely
        // since we check if there is a TX mailbox free.
        if(status != true)
        {
            error_assert(ERR_CAN_TXFAIL);
        }
    }
}

// Check if a CAN message has been received and is waiting in the FIFO
uint8_t is_can_msg_pending(void)
{
    if (bus_state == OFF_BUS)
    {
        return 0;
    }
    return ((FLEXCAN_GetMbStatus(BOARD_FLEXCAN_PORT) & BOARD_FLEXCAN_RXFIFO_AVAIl_STATUS) > 0);
}
