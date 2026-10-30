#ifndef _APP_RADIO_H_
#define _APP_RADIO_H_

#include "rail.h"
#include "sl_rail.h"
#include "sl_rail_types.h"
#include "sl_rail_ieee802154.h"
#include <stdint.h>

extern volatile uint32_t app_radio_rx_completion_count;
extern volatile uint32_t app_radio_rx_packet_received_count;
extern volatile uint32_t app_radio_rx_packet_queued_count;
extern volatile uint32_t app_radio_rx_nonpacket_completion_count;
extern volatile uint32_t app_radio_rx_queue_drop_count;
extern volatile uint32_t app_radio_rx_last_completion_events;
extern volatile uint32_t app_radio_rx_packets_processed_count;
extern volatile uint16_t app_radio_last_rx_packet_length;
extern volatile uint8_t app_radio_last_rx_packet[128];


sl_rail_status_t app_radio_init(void);
sl_rail_status_t app_radio_send_demo_packet(uint8_t channel_a);
bool app_radio_get_packet(uint8_t *dest_buffer, uint16_t *p_length, uint16_t max_buf_size);
sl_rail_status_t app_radio_start_rx_channel(uint8_t channel_a);
void app_radio_process_received_packets(void);

#endif //_APP_RADIO_H_
