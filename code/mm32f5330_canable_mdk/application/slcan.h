#ifndef _SLCAN_H
#define _SLCAN_H

#include "stdint.h"
#include "hal_flexcan.h"

int8_t slcan_parse_frame(uint8_t *buf, FLEXCAN_Mb_Type *frame_header, uint8_t* frame_data);
int8_t slcan_parse_str(uint8_t *buf, uint8_t len);

// maximum rx buffer len: extended CAN frame with timestamp
#define SLCAN_MTU 30 // (sizeof("T1111222281122334455667788EA5F\r")+1)

#define SLCAN_STD_ID_LEN 3
#define SLCAN_EXT_ID_LEN 8

#define GIT_VERSION "2023"
#define GIT_REMOTE  "0519"

#endif // _SLCAN_H
