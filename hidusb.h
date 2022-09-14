/*****************************************************************
 ** 文件名:  hidusb.h
 ** 2020-2022 珠海禾田电子科技有限公司 Co.Ltd
 
 ** 创建人: 骆军城
 ** 日  期: 2022-01
 ** 描  述: hidapi应用接口
 ** 版  本: V1.0

 ** 修改人:
 ** 日  期:
 ** 修改描述:
 ** 版  本: 
******************************************************************/

#ifndef __HT_HIDUSB_H_
#define	__HT_HIDUSB_H_


#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************
* 包含头文件(如非特殊需要，H文件不建议包含其它H文件)
******************************************************************/
#include <stdint.h>

#include "libusb.h"

/*****************************************************************
* 宏定义
******************************************************************/

/*****************************************************************
* 结构定义
******************************************************************/


/*****************************************************************
* 函数原型声明
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



