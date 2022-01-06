#ifndef _TONYUSB_H_
#define _TONYUSB_H_

#include <stdlib.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tinyusb.h"
#include "sdkconfig.h"
#include "tusb.h"
//#include "usbd.h"
#include "device/usbd_pvt.h"
#define USE_TONY_USB 1
typedef enum
{
  STATE_CLOSED,  // Endpoints have not yet been opened since USB reset
  STATE_NAK,     // Bulk-out endpoint is in NAK state.
  STATE_IDLE,    // Bulk-out endpoint is waiting for CMD.
  STATE_RCV,     // Bulk-out is receiving DEV_DEP message
  STATE_TX_REQUESTED,
  STATE_TX_INITIATED,
  STATE_TX_SHORTED,
  STATE_CLEARING,
  STATE_ABORTING_BULK_IN,
  STATE_ABORTING_BULK_IN_SHORTED, // aborting, and short packet has been queued for transmission
  STATE_ABORTING_BULK_IN_ABORTED, // aborting, and short packet has been transmitted
  STATE_ABORTING_BULK_OUT,
  STATE_NUM_STATES
} tony_state_enum;


typedef struct
{
  volatile tony_state_enum state;

  uint8_t itf_id;
  uint8_t rhport;
  uint8_t ep_bulk_in;
  uint8_t ep_bulk_out;
  uint8_t ep_int_in;
  // IN buffer is only used for first packet, not the remainder
  // in order to deal with prepending header
  uint8_t ep_bulk_in_buf[64];
  // OUT buffer receives one packet at a time
  uint8_t ep_bulk_out_buf[64];
  uint32_t transfer_size_remaining; // also used for requested length for bulk IN.
  uint32_t transfer_size_sent;      // To keep track of data bytes that have been queued in FIFO (not header bytes)

  uint8_t lastBulkOutTag; // used for aborts (mostly)
  uint8_t lastBulkInTag; // used for aborts (mostly)

  uint8_t const * devInBuffer; // pointer to application-layer used for transmissions

//  tony_capabilities_specific_t const * capabilities;
} tony_interface_state_t;


typedef enum {
  TONY_bREQUEST_INITIATE_ABORT_BULK_OUT      = 1u,
  TONY_bREQUEST_CHECK_ABORT_BULK_OUT_STATUS  = 2u,
  TONY_bREQUEST_INITIATE_ABORT_BULK_IN       = 3u,
  TONY_bREQUEST_CHECK_ABORT_BULK_IN_STATUS   = 4u,
  TONY_bREQUEST_INITIATE_CLEAR               = 5u,
  TONY_bREQUEST_CHECK_CLEAR_STATUS           = 6u,
  TONY_bREQUEST_GET_CAPABILITIES             = 7u,

  TONY_bREQUEST_INDICATOR_PULSE               = 64u, // Optional
} tony_request_type_enum;

typedef enum {
  TONY_STATUS_SUCCESS = 0x01,
  TONY_STATUS_PENDING = 0x02,
  TONY_STATUS_FAILED = 0x80,
  TONY_STATUS_TRANSFER_NOT_IN_PROGRESS = 0x81,
  TONY_STATUS_SPLIT_NOT_IN_PROGRESS = 0x82,
  TONY_STATUS_SPLIT_IN_PROGRESS  = 0x83
} tony_status_enum;

typedef struct TU_ATTR_PACKED
{
  uint8_t TONY_status;
  struct TU_ATTR_PACKED
  {
    unsigned int BulkInFifoBytes : 1; ///< Has queued data or a short packet that is queued
  } bmAbortBulkIn;
  uint8_t _reserved[2];               ///< Must be zero
  uint32_t NBYTES_RXD_TXD;
} tony_check_abort_bulk_rsp_t;

// Used for both abort bulk IN and bulk OUT
typedef struct TU_ATTR_PACKED
{
  uint8_t TONY_status;
  uint8_t bTag;
} tony_initiate_abort_rsp_t;

typedef struct TU_ATTR_PACKED
{
  uint8_t TONY_status;
  struct TU_ATTR_PACKED
  {
    unsigned int BulkInFifoBytes :1;
  } bmClear;
} tony_get_clear_status_rsp_t;
#define TONY_MAX_PACKET_SIZE 64
void tony_init_cb(void);
void tony_reset_cb(uint8_t rhport);
uint16_t tony_open_cb(uint8_t rhport, tusb_desc_interface_t const * itf_desc, uint16_t max_len);
bool tud_tony_start_bus_read(void);
bool tud_tony_initiate_abort_bulk_out_cb(uint8_t *tmcResult);
void tud_tony_open_cb(uint8_t interface_id);
bool tony_control_xfer_cb(uint8_t rhport, uint8_t stage, tusb_control_request_t const * request);

bool tony_xfer_cb(uint8_t rhport, uint8_t ep_addr, xfer_result_t result, uint32_t xferred_bytes);
uint64_t tony_dataInIsr_user(uint32_t num,uint64_t cmd);
//#include "tusb_cdc_acm.h"
//void myusb_init(void);

#endif
