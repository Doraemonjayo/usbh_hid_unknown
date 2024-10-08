/*
 * usbh_hid_unknown.c
 *
 *  Created on: Jul 18, 2024
 *      Author: Doradora
 */

#include "usbh_hid_unknown.h"
#include "usbh_hid_parser.h"

static USBH_StatusTypeDef USBH_HID_UnknownDecode(USBH_HandleTypeDef *phost);

uint8_t                  unknown_report_data[USBH_HID_UNKNOWN_REPORT_SIZE];
uint8_t                  unknown_rx_report_buf[USBH_HID_UNKNOWN_REPORT_SIZE];

USBH_StatusTypeDef USBH_HID_UnknownInit(USBH_HandleTypeDef *phost)
{
  uint32_t i;
  HID_HandleTypeDef *HID_Handle = (HID_HandleTypeDef *) phost->pActiveClass->pData;

  for (i = 0U; i < sizeof(unknown_report_data); i++)
  {
	unknown_report_data[i] = 0U;
	unknown_rx_report_buf[i] = 0U;
  }

  if (HID_Handle->length > sizeof(unknown_rx_report_buf))
  {
    HID_Handle->length = (uint16_t)sizeof(unknown_report_data);
  }
  HID_Handle->pData = unknown_rx_report_buf;

  if ((HID_QUEUE_SIZE * sizeof(unknown_report_data)) > sizeof(phost->device.Data))
  {
    return USBH_FAIL;
  }
  else
  {
    USBH_HID_FifoInit(&HID_Handle->fifo, phost->device.Data, (uint16_t)(HID_QUEUE_SIZE * sizeof(unknown_report_data)));
  }

  return USBH_OK;
}

uint8_t *USBH_HID_GetUnknownInfo(USBH_HandleTypeDef *phost)
{
  if (USBH_HID_UnknownDecode(phost) == USBH_OK)
  {
    return unknown_report_data;
  }
  else
  {
    return NULL;
  }
}

static USBH_StatusTypeDef USBH_HID_UnknownDecode(USBH_HandleTypeDef *phost)
{
  HID_HandleTypeDef *HID_Handle = (HID_HandleTypeDef *) phost->pActiveClass->pData;

  if ((HID_Handle->length == 0U) || (HID_Handle->fifo.buf == NULL))
  {
    return USBH_FAIL;
  }
  if (USBH_HID_FifoRead(&HID_Handle->fifo, &unknown_report_data, HID_Handle->length) == HID_Handle->length)
  {
    return USBH_OK;
  }
  return   USBH_FAIL;
}
