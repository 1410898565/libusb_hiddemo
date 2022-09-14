/*****************************************************************
 ** 文件名:  ht_main.c
 ** 2020-2022 珠海禾田电子科技有限公司 Co.Ltd
 
 ** 创建人: 骆军城
 ** 日  期: 2022-01
 ** 描  述: 主函数文件
 ** 版  本: V1.0

 ** 修改人:
 ** 日  期:
 ** 修改描述:
 ** 版  本: 
******************************************************************/

/*****************************************************************
* 包含头文件
******************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "hidusb.h"


/*****************************************************************
* 宏定义(仅在当前C文件使用的宏定义写在当前C文件中，否则需写在H文件中)
******************************************************************/

/*****************************************************************
* 结构定义(仅在当前C文件使用的结构体写在当前C文件中，否则需写在H文件中)
******************************************************************/

/*****************************************************************
* 全局变量定义
******************************************************************/

/*****************************************************************
* 静态变量定义
******************************************************************/
static libusb_context 			*gUSBCtx = NULL;
/*****************************************************************
* 外部变量声明（如果全局变量没有在其它的H文件声明，引用时需在此处声明，
*如果已在其它H文件声明，则只需包含此H文件即可）
******************************************************************/

/*****************************************************************
* 函数原型声明
******************************************************************/

/*****************************************************************
* 函数定义
*注意，编写函数需首先定义所有的局部变量等，不允许在
*函数的中间出现新的变量的定义。
******************************************************************/

/*************************************************
** Function：	hidUSB_write
** Description: usb发送数据函数
** Input:	none
** Output：	none

** Return:	none
** Author：骆军城
** Date：2022-01-25

** Modification History：
** Author：
** Date：
** Description：
*************************************************/
int hidUSB_write(libusb_device_handle *dev_handle, unsigned char endpoint, unsigned char *pDataIn, int nDataLen, int ntimeout)
{
    int ret = -1;
    int transferred = 0;

	
    ret = libusb_interrupt_transfer(dev_handle, endpoint, pDataIn, nDataLen, &transferred, ntimeout);
	if(ret<0){
        perror("failed to write\n");
		return 0;
	}

	return transferred;
}

/*************************************************
** Function：	hidUSB_read
** Description: usb接收数据函数
** Input:	none
** Output：	none

** Return:	none
** Author：骆军城
** Date：2022-01-25

** Modification History：
** Author：
** Date：
** Description：
*************************************************/
int hidUSB_read(libusb_device_handle *dev_handle,unsigned char endpoint, unsigned char *pDataRcv, int nDataLen, int ntimeout)
{
    int ret = -1;
    int transferred = 0;
	
    ret = libusb_interrupt_transfer(dev_handle,endpoint, pDataRcv, 64, &transferred, ntimeout);
	if(ret!=0){
        perror("failed to read\n");
		return 0;
	}

	return transferred;
}


/*************************************************
** Function：	hidUSB_open
** Description: libusb初始化
** Input:	none
** Output：	none

** Return:	none
** Author：骆军城
** Date：2022-01-25

** Modification History：
** Author：
** Date：
** Description：
*************************************************/
int hidUSB_open(libusb_device_handle **dev_hdlout, uint16_t vendor_id, uint16_t product_id)
{
	int ret = -1;
	
	libusb_device_handle *tdev_handle = NULL;

    //打开指定pid和vid的设备
    tdev_handle = libusb_open_device_with_vid_pid(NULL, vendor_id, product_id);
    if(tdev_handle == NULL)
	{
        perror("Cannot open device\n");
		return -1;
    }

	//内核驱动激活与分离（这一句我没怎么搞懂为啥需要，懂的朋友欢迎留言告诉我）
	if(libusb_kernel_driver_active(tdev_handle, 0) == 1)
	{ 
		 printf("Kernel Driver Active\n");
		 if(libusb_detach_kernel_driver(tdev_handle, 0) == 0){
			 printf("Kernel Driver Detached!\n");
		 }
	 }

    ret = libusb_claim_interface(tdev_handle, 0);
    if(ret < 0) {
        perror("Cannot Claim Interface\n");
        goto iExit;
    }


	*dev_hdlout = tdev_handle;

	return 0;

iExit:	
	if(tdev_handle)
		libusb_close(tdev_handle);

	return -1;
}

/*************************************************
** Function：	hidUSB_close
** Description: 
** Input:	none
** Output：	none

** Return:	none
** Author：骆军城
** Date：2022-01-25

** Modification History：
** Author：
** Date：
** Description：
*************************************************/
int hidUSB_close(libusb_device_handle *dev_handle)
{
	int ret = -1;

	if(dev_handle)
	{
		ret = libusb_release_interface(dev_handle, 0);
		if(ret!=0)
		{	
			perror("Cannot libusb_release_interface\n");
			return -1;
		}
		
		libusb_close(dev_handle);
	}

	return 0;
}


/*************************************************
** Function：	hidUSB_DeInit
** Description: libusb去初始化
** Input:	none
** Output：	none

** Return:	none
** Author：骆军城
** Date：2022-01-25

** Modification History：
** Author：
** Date：
** Description：
*************************************************/
void hidUSB_DeInit(void)
{
	libusb_exit(gUSBCtx);
}


/*************************************************
** Function：	hidUSB_Init
** Description: libusb初始化
** Input:	none
** Output：	none

** Return:	none
** Author：骆军城
** Date：2022-01-25

** Modification History：
** Author：
** Date：
** Description：
*************************************************/
int hidUSB_Init(void)
{
    int ret = -1;

	ret = libusb_init(&gUSBCtx); 
	if(ret < 0) 
	{
		perror("libusb_init failed\n");
		return -1;	
	} 

	return 0;
}

