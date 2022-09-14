/*****************************************************************
 ** �ļ���:  ht_main.c
 ** 2020-2022 �麣������ӿƼ����޹�˾ Co.Ltd
 
 ** ������: �����
 ** ��  ��: 2022-01
 ** ��  ��: �������ļ�
 ** ��  ��: V1.0

 ** �޸���:
 ** ��  ��:
 ** �޸�����:
 ** ��  ��: 
******************************************************************/

/*****************************************************************
* ����ͷ�ļ�
******************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "hidusb.h"


/*****************************************************************
* �궨��(���ڵ�ǰC�ļ�ʹ�õĺ궨��д�ڵ�ǰC�ļ��У�������д��H�ļ���)
******************************************************************/

/*****************************************************************
* �ṹ����(���ڵ�ǰC�ļ�ʹ�õĽṹ��д�ڵ�ǰC�ļ��У�������д��H�ļ���)
******************************************************************/

/*****************************************************************
* ȫ�ֱ�������
******************************************************************/

/*****************************************************************
* ��̬��������
******************************************************************/
static libusb_context 			*gUSBCtx = NULL;
/*****************************************************************
* �ⲿ�������������ȫ�ֱ���û����������H�ļ�����������ʱ���ڴ˴�������
*�����������H�ļ���������ֻ�������H�ļ����ɣ�
******************************************************************/

/*****************************************************************
* ����ԭ������
******************************************************************/

/*****************************************************************
* ��������
*ע�⣬��д���������ȶ������еľֲ������ȣ���������
*�������м�����µı����Ķ��塣
******************************************************************/

/*************************************************
** Function��	hidUSB_write
** Description: usb�������ݺ���
** Input:	none
** Output��	none

** Return:	none
** Author�������
** Date��2022-01-25

** Modification History��
** Author��
** Date��
** Description��
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
** Function��	hidUSB_read
** Description: usb�������ݺ���
** Input:	none
** Output��	none

** Return:	none
** Author�������
** Date��2022-01-25

** Modification History��
** Author��
** Date��
** Description��
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
** Function��	hidUSB_open
** Description: libusb��ʼ��
** Input:	none
** Output��	none

** Return:	none
** Author�������
** Date��2022-01-25

** Modification History��
** Author��
** Date��
** Description��
*************************************************/
int hidUSB_open(libusb_device_handle **dev_hdlout, uint16_t vendor_id, uint16_t product_id)
{
	int ret = -1;
	
	libusb_device_handle *tdev_handle = NULL;

    //��ָ��pid��vid���豸
    tdev_handle = libusb_open_device_with_vid_pid(NULL, vendor_id, product_id);
    if(tdev_handle == NULL)
	{
        perror("Cannot open device\n");
		return -1;
    }

	//�ں�������������루��һ����û��ô�㶮Ϊɶ��Ҫ���������ѻ�ӭ���Ը����ң�
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
** Function��	hidUSB_close
** Description: 
** Input:	none
** Output��	none

** Return:	none
** Author�������
** Date��2022-01-25

** Modification History��
** Author��
** Date��
** Description��
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
** Function��	hidUSB_DeInit
** Description: libusbȥ��ʼ��
** Input:	none
** Output��	none

** Return:	none
** Author�������
** Date��2022-01-25

** Modification History��
** Author��
** Date��
** Description��
*************************************************/
void hidUSB_DeInit(void)
{
	libusb_exit(gUSBCtx);
}


/*************************************************
** Function��	hidUSB_Init
** Description: libusb��ʼ��
** Input:	none
** Output��	none

** Return:	none
** Author�������
** Date��2022-01-25

** Modification History��
** Author��
** Date��
** Description��
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

