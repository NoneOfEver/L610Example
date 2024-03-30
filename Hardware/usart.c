
#include "usart.h"

u8 USART_Rbuffer_Num = 0;
u8 USART_Tbuffer_Num = 0;
u8 USART_Rbuffer[buffer_len];//���ջ���������

void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void USARTx_Init(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    USART_InitTypeDef  USART_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);


    /* USART2 TX-->A.2   RX-->A.3 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;              //����PA2Ϊ�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;        //����PA3Ϊ��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;      //��ռ���ȼ�Ϊ1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;           //�����ȼ�Ϊ1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);                              //�ж����ȼ���ʼ��

    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

    USART_Cmd(USART2,ENABLE);
}

void USARTx_SendByte(USART_TypeDef* pUSARTx, uint8_t data)
{
    USART_SendData(pUSARTx, data);
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

void USARTx_SendStr(USART_TypeDef* pUSARTx, char *str)
{
    uint8_t i = 0;
    do
    {
       USARTx_SendByte(pUSARTx, *(str+i));
       i++;
    }while(*(str+i) != '\0');
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //�жϲ���
    {
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);                //����жϱ�־


        USART_Rbuffer[USART_Rbuffer_Num] = USART_ReceiveData(USART2); //��������

        USART_Rbuffer_Num++;

    }
//    printf("recv uart msg\r\n");

//    for(USART_Tbuffer_Num=0;USART_Tbuffer_Num < USART_Rbuffer_Num;USART_Tbuffer_Num++)
//    {
//        USARTx_SendByte(USART2,USART_Rbuffer[USART_Tbuffer_Num]); //��������
//    }

//    USART_Rbuffer_Num = 0; //��ʼ��
//    USART_Tbuffer_Num = 0;
}


