
//
// slcan: Parse incoming and generate outgoing slcan messages
//

#include <string.h>
#include "can.h"
#include "error.h"
#include "slcan.h"


// Parse an incoming CAN frame into an outgoing slcan message
int8_t slcan_parse_frame(uint8_t *buf, FLEXCAN_Mb_Type *frame_header, uint8_t* frame_data)
{
    uint8_t msg_position = 0;

    for (uint8_t j=0; j < SLCAN_MTU; j++)
    {
        buf[j] = '\0';
    }

    // Add character for frame type
    if (frame_header->TYPE == FLEXCAN_MbType_Data)
    {
        buf[msg_position] = 't';
    } else if (frame_header->TYPE == FLEXCAN_MbType_Remote) {
        buf[msg_position] = 'r';
    }

    // Assume standard identifier
    uint8_t id_len = SLCAN_STD_ID_LEN;
    uint32_t can_id = frame_header->ID;

    // Check if extended
    if (frame_header->FORMAT == FLEXCAN_MbFormat_Extended)
    {
        // Convert first char to upper case for extended frame
        buf[msg_position] -= 32;
        id_len = SLCAN_EXT_ID_LEN;
        can_id = frame_header->ID;
    }
    msg_position++;

    // Add identifier to buffer
    for(uint8_t j = id_len; j > 0; j--)
    {
        // Add nybble to buffer
        buf[j] = (can_id & 0xF);
        can_id = can_id >> 4;
        msg_position++;
    }

    // Add DLC to buffer
    buf[msg_position++] = frame_header->LENGTH;

     buf[msg_position++] = (frame_header->BYTE0 >> 4);
     buf[msg_position++] = (frame_header->BYTE0 & 0x0F);
     buf[msg_position++] = (frame_header->BYTE1 >> 4);
     buf[msg_position++] = (frame_header->BYTE1 & 0x0F);
     buf[msg_position++] = (frame_header->BYTE2 >> 4);
     buf[msg_position++] = (frame_header->BYTE2 & 0x0F);
     buf[msg_position++] = (frame_header->BYTE3 >> 4);
     buf[msg_position++] = (frame_header->BYTE3 & 0x0F);
     buf[msg_position++] = (frame_header->BYTE4 >> 4);
     buf[msg_position++] = (frame_header->BYTE4 & 0x0F);
     buf[msg_position++] = (frame_header->BYTE5 >> 4);
     buf[msg_position++] = (frame_header->BYTE5 & 0x0F);
     buf[msg_position++] = (frame_header->BYTE6 >> 4);
     buf[msg_position++] = (frame_header->BYTE6 & 0x0F);
     buf[msg_position++] = (frame_header->BYTE7 >> 4);
     buf[msg_position++] = (frame_header->BYTE7 & 0x0F);

    // Convert to ASCII (2nd character to end)
    for (uint8_t j = 1; j < msg_position; j++)
    {
        if (buf[j] < 0xA) {
            buf[j] += 0x30;
        } else {
            buf[j] += 0x37;
        }
    }

    // Add CR (slcan EOL)
    buf[msg_position++] = '\r';

    // Return number of bytes in string
    return msg_position;
}


// Parse an incoming slcan command from the USB CDC port
int8_t slcan_parse_str(uint8_t *buf, uint8_t len)
{
    FLEXCAN_Mb_Type frame_header;

    // Default to standard ID unless otherwise specified
    frame_header.FORMAT = FLEXCAN_MbFormat_Standard;
    frame_header.ID = 0;

    // Convert from ASCII (2nd character to end)
    for (uint8_t i = 1; i < len; i++)
    {
        // Lowercase letters
        if(buf[i] >= 'a')
            buf[i] = buf[i] - 'a' + 10;
        // Uppercase letters
        else if(buf[i] >= 'A')
            buf[i] = buf[i] - 'A' + 10;
        // Numbers
        else
            buf[i] = buf[i] - '0';
    }


    // Process command
    switch(buf[0])
    {
        case 'O':
            // Open channel command
            can_enable();
            return 0;

        case 'C':
            // Close channel command
            can_disable();
            return 0;

        case 'S':
            // Set bitrate command

            // Check for valid bitrate
            if(buf[1] >= CAN_BITRATE_INVALID)
            {
                return -1;
            }

            can_set_bitrate(buf[1]);
            return 0;

        case 'm':
        case 'M':
            // Set mode command
            if (buf[1] == 1)
            {
                // Mode 1: silent
                can_set_silent(1);
            } else {
                // Default to normal mode
                can_set_silent(0);
            }
            return 0;

        case 'a':
        case 'A':
            // Set autoretry command
            if (buf[1] == 1)
            {
                // Mode 1: autoretry enabled (default)
                can_set_autoretransmit(1);
            } else {
                // Mode 0: autoretry disabled
                can_set_autoretransmit(0);
            }
            return 0;

        case 'V':
        {
            // Report firmware version and remote
            //char* fw_id = GIT_VERSION " " GIT_REMOTE "\r";
            return 0;
        }

        case 'T':
            frame_header.FORMAT = FLEXCAN_MbFormat_Extended;
        case 't':
            // Transmit data frame command
            frame_header.TYPE = FLEXCAN_MbType_Data;
            break;

        case 'R':
            frame_header.FORMAT = FLEXCAN_MbFormat_Extended;
        case 'r':
            // Transmit remote frame command
            frame_header.TYPE = FLEXCAN_MbType_Remote;
            break;

        default:
            // Error, unknown command
            return -1;
    }


    // Save CAN ID depending on ID type
    uint8_t msg_position = 1;
    if (frame_header.FORMAT == FLEXCAN_MbFormat_Extended) {
        while (msg_position <= SLCAN_EXT_ID_LEN) {
            frame_header.ID *= 16;
            frame_header.ID += buf[msg_position++];
        }
    }
    else {
        while (msg_position <= SLCAN_STD_ID_LEN) {
            frame_header.ID *= 16;
            frame_header.ID += buf[msg_position++];
        }
    }


    // Attempt to parse DLC and check sanity
    frame_header.LENGTH = buf[msg_position++];
    if (frame_header.LENGTH > 8) {
        return -1;
    }

    // Copy frame data to buffer
    uint8_t frame_data[8] = {0};
    frame_header.BYTE0 = (buf[msg_position] << 4) + buf[msg_position+1];
    msg_position += 2;
    frame_header.BYTE1= (buf[msg_position] << 4) + buf[msg_position+1];
    msg_position += 2;
    frame_header.BYTE2 = (buf[msg_position] << 4) + buf[msg_position+1];
    msg_position += 2;
    frame_header.BYTE3 = (buf[msg_position] << 4) + buf[msg_position+1];
    msg_position += 2;
    frame_header.BYTE4 = (buf[msg_position] << 4) + buf[msg_position+1];
    msg_position += 2;
    frame_header.BYTE5 = (buf[msg_position] << 4) + buf[msg_position+1];
    msg_position += 2;
    frame_header.BYTE6 = (buf[msg_position] << 4) + buf[msg_position+1];
    msg_position += 2;
    frame_header.BYTE7 = (buf[msg_position] << 4) + buf[msg_position+1];
    msg_position += 2;

    // Transmit the message
    can_tx(&frame_header, frame_data);

    return 0;
}
