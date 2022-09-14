/*****************************************************************
 ** �ļ���:  hidusb.h
 ** 2020-2022 �麣������ӿƼ����޹�˾ Co.Ltd
 
 ** ������: �����
 ** ��  ��: 2022-01
 ** ��  ��: hidapiӦ�ýӿ�
 ** ��  ��: V1.0

 ** �޸���:
 ** ��  ��:
 ** �޸�����:
 ** ��  ��: 
******************************************************************/

#ifndef __HT_HIDUSB_H_
#define	__HT_HIDUSB_H_


#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************
* ����ͷ�ļ�(���������Ҫ��H�ļ��������������H�ļ�)
******************************************************************/
#include <stdint.h>

#include "libusb.h"

/*****************************************************************
* �궨��
******************************************************************/

/*****************************************************************
* �ṹ����
******************************************************************/


/*****************************************************************
* ����ԭ������
******************************************************************/
int hidUSB_write(libusb_device_handle *dev_handle, unsigned char endpoint, unsigned char *pDataIn, int nDataLen, int ntimeout);
int hidUSB_read(libusb_device_handle *dev_handle,unsigned char endpoint, unsigned char *pDataRcv, int nDataLen, int ntimeout);
int hidUSB_open(libusb_device_handle **dev_hdlout, uint16_t vendor_id, uint16_t product_id);
int hidUSB_close(libusb_device_handle *dev_handle);

void hidUSB_DeInit(void);
int hidUSB_Init(void);

#ifdef __cplusplus
}
#endif

#endif 



