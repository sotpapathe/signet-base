/**
  ******************************************************************************
  * @file    usbd_msc_scsi.h
  * @author  MCD Application Team
  * @brief   Header for the usbd_msc_scsi.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      http://www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_MSC_SCSI_H
#define __USBD_MSC_SCSI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usbd_def.h"
#include "memory_layout.h"
#include "signetdev_common.h"

#define SENSE_LIST_DEEPTH                           4U

/* SCSI Commands */
#define SCSI_FORMAT_UNIT                            0x04U
#define SCSI_INQUIRY                                0x12U
#define SCSI_MODE_SELECT6                           0x15U
#define SCSI_MODE_SELECT10                          0x55U
#define SCSI_MODE_SENSE6                            0x1AU
#define SCSI_MODE_SENSE10                           0x5AU
#define SCSI_ALLOW_MEDIUM_REMOVAL                   0x1EU
#define SCSI_READ6                                  0x08U
#define SCSI_READ10                                 0x28U
#define SCSI_READ12                                 0xA8U
#define SCSI_READ16                                 0x88U

#define SCSI_READ_CAPACITY10                        0x25U
#define SCSI_READ_CAPACITY16                        0x9EU

#define SCSI_REQUEST_SENSE                          0x03U
#define SCSI_START_STOP_UNIT                        0x1BU
#define SCSI_TEST_UNIT_READY                        0x00U
#define SCSI_WRITE6                                 0x0AU
#define SCSI_WRITE10                                0x2AU
#define SCSI_WRITE12                                0xAAU
#define SCSI_WRITE16                                0x8AU

#define SCSI_VERIFY10                               0x2FU
#define SCSI_VERIFY12                               0xAFU
#define SCSI_VERIFY16                               0x8FU

#define SCSI_SEND_DIAGNOSTIC                        0x1DU
#define SCSI_READ_FORMAT_CAPACITIES                 0x23U

#define NO_SENSE                                    0U
#define RECOVERED_ERROR                             1U
#define NOT_READY                                   2U
#define MEDIUM_ERROR                                3U
#define HARDWARE_ERROR                              4U
#define ILLEGAL_REQUEST                             5U
#define UNIT_ATTENTION                              6U
#define DATA_PROTECT                                7U
#define BLANK_CHECK                                 8U
#define VENDOR_SPECIFIC                             9U
#define COPY_ABORTED                                10U
#define ABORTED_COMMAND                             11U
#define VOLUME_OVERFLOW                             13U
#define MISCOMPARE                                  14U


#define INVALID_CDB                                 0x20U
#define INVALID_FIELED_IN_COMMAND                   0x24U
#define PARAMETER_LIST_LENGTH_ERROR                 0x1AU
#define INVALID_FIELD_IN_PARAMETER_LIST             0x26U
#define ADDRESS_OUT_OF_RANGE                        0x21U
#define MEDIUM_NOT_PRESENT                          0x3AU
#define MEDIUM_HAVE_CHANGED                         0x28U
#define WRITE_PROTECTED                             0x27U
#define UNRECOVERED_READ_ERROR                      0x11U
#define WRITE_FAULT                                 0x03U

#define READ_FORMAT_CAPACITY_DATA_LEN               0x0CU
#define READ_CAPACITY10_DATA_LEN                    0x08U
#define MODE_SENSE10_DATA_LEN                       0x08U
#define MODE_SENSE6_DATA_LEN                        0x04U
#define REQUEST_SENSE_DATA_LEN                      0x12U
#define STANDARD_INQUIRY_DATA_LEN                   0x24U
#define BLKVFY                                      0x04U

extern  uint8_t Page00_Inquiry_Data[];
extern  uint8_t Standard_Inquiry_Data[];
extern  uint8_t Standard_Inquiry_Data2[];
extern  uint8_t Mode_Sense6_data[];
extern  uint8_t Mode_Sense10_data[];
extern  uint8_t Scsi_Sense_Data[];
extern  uint8_t ReadCapacity10_Data[];
extern  uint8_t ReadFormatCapacity_Data [];

struct scsi_volume {
	int nr;
	u32 flags;
	u32 region_start;
	u32 n_regions;
	u8 volume_name[MAX_VOLUME_NAME_LEN];
	int started;
	int visible;
	int writable;
};

extern int g_num_scsi_volumes;
extern int g_scsi_num_regions;
extern int g_scsi_region_size_blocks;
extern struct scsi_volume g_scsi_volume[MAX_SCSI_VOLUMES];

void usbd_scsi_init();
void usbd_scsi_idle();
int usbd_scsi_idle_ready();
void usbd_scsi_device_state_change(enum device_state state);

typedef struct _SENSE_ITEM {
	char Skey;
	union {
		struct _ASCs {
			char ASC;
			char ASCQ;
		} b;
		uint8_t	ASC;
		char *pData;
	} w;
} USBD_SCSI_SenseTypeDef;

int8_t SCSI_ProcessCmd(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t *cmd);

void SCSI_SenseCode(USBD_HandleTypeDef *pdev, uint8_t lun, uint8_t sKey,
                    uint8_t ASC, uint8_t ASCQ);

void emmc_user_read_storage_rx_complete();
void emmc_user_write_storage_tx_complete(MMC_HandleTypeDef *hmmc1);

#ifdef __cplusplus
}
#endif

#endif
