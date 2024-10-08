/*
 * usbh_hid_unknown.h
 *
 *  Created on: Jul 18, 2024
 *      Author: Doradora
 */

#ifndef __USBH_HID_UNKNOWN_H
#define __USBH_HID_UNKNOWN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usbh_hid.h"

USBH_StatusTypeDef USBH_HID_UnknownInit(USBH_HandleTypeDef *phost);
uint8_t *USBH_HID_GetUnknownInfo(USBH_HandleTypeDef *phost);

#ifndef USBH_HID_UNKNOWN_REPORT_SIZE
#define USBH_HID_UNKNOWN_REPORT_SIZE                       51U
#endif /* USBH_HID_UNKNOWN_REPORT_SIZE */

#ifdef __cplusplus
}
#endif

#endif /* __USBH_HID_UNKNOWN_H */
