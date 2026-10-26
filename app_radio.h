#ifndef _APP_RADIO_H_
#define _APP_RADIO_H_

#include "rail.h"
#include "sl_rail.h"
#include "sl_rail_types.h"
#include "sl_rail_ieee802154.h"


void app_radio_init(void);
sl_rail_status_t app_radio_send_demo_packet(uint8_t channel_a);
bool app_radio_get_packet(uint8_t *dest_buffer, uint16_t *p_length, uint16_t max_buf_size);
sl_rail_status_t app_radio_start_rx_channel(uint8_t channel_a);

#endif //_APP_RADIO_H_