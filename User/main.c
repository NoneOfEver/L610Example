/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

/*
 *@Note

*/

#include "debug.h"
#include "usart.h"
#include <string.h>
#include "L610.h"


/* Global typedef */

/* Global define */

/* Global Variable */


/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    const ProductInfo* productInfoPtr;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();

    USARTx_Init();
    Delay_Ms(100);

    L610_Init();
    L610_Lookup();
    L610_RequestIP();
    L610_SetAndConnect();
    L610_Sub();
    L610_Pub("123");
    L610_Recive();

    productInfoPtr = L610_Recive();
    if (productInfoPtr != NULL) {
    // ����ɹ����յ���Ʒ��Ϣ�����ӡ��Ϣ
        printf("��ƷID: %s\n", productInfoPtr->productID);
        printf("��Ʒ�۸�: %.2f\n", productInfoPtr->productPrice);
        printf("��Ʒ����: %s\n", productInfoPtr->productName);
        printf("��Ʒ����: %.2f\n", productInfoPtr->productWeight);
    }
}

