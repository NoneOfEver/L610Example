/*
 * L610.c
 *
 *      Created on      :2024��3��22��
 *      Author          :�˲���
 *      Version         :V1.0
 *      Description     :FibocomL610�ӿڿ�
 *
 *
 *
 */

#include "L610.h"



char *strx;
char *strstr(const char *, const char *);
char USART_Rbuffer[1024];
char USART_Rbuffer_Num;
char *endptr;
int len;
int number;


/*
 * @brief:FibocomL610ģ���ʼ��
 * @param:null
 * @return:null
 */
void L610_Init()
{
    printf("ģ���ʼ��\r\n");
    Delay_Ms(5000);

    printf("AT\r\n");
    Delay_Ms(1000);
}

/*
 * @brief:��ѯFibocomL610
 * @param:null
 * @return:null
 */
void L610_Lookup()
{
    //��ѯ�汾��Ϣ
    printf("ATI\r\n");
    Delay_Ms(1000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"Fibocom");
    while(strx==NULL)
    {
       printf("��ѯ��Ϣʧ��\n");
       Delay_Ms(1000);
       USART_Rbuffer_Num = 0;
       printf("ATI\r\n");
       Delay_Ms(1000);
       strx=strstr((const char*)USART_Rbuffer,(const char*)"Fibocom");
    }
    printf("�汾��Ϣ��ȷ\n");
    Delay_Ms(1000);

    //��ѯPSע�����
    printf("AT+CGREG?\r\n");
    Delay_Ms(1000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"+CGREG: 0,1");
    while(strx==NULL)
    {
       printf("PSע����Ч\n");
       Delay_Ms(1000);
       USART_Rbuffer_Num = 0;
       printf("AT+CGREG?\r\n");
       Delay_Ms(1000);
       strx=strstr((const char*)USART_Rbuffer,(const char*)"+CGREG: 0,1");
    }
    printf("PSע����Ч\n");
    Delay_Ms(1000);

}

/*
 * @brief:FibocomL610����IP
 * @param:null
 * @return:null
 */
void L610_RequestIP()
{
    //����IP
    printf("AT+MIPCALL?\r\n");
    Delay_Ms(1000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"+MIPCALL: 1");
    while(strx==NULL)
    {
       printf("��δ��ȡ��IP\n");
       Delay_Ms(1000);
       USART_Rbuffer_Num = 0;
       printf("AT+MIPCALL=1\r\n");
       Delay_Ms(1000);
       strx=strstr((const char*)USART_Rbuffer,(const char*)"+MIPCALL: 1");
    }
    printf("��ȡIP�ɹ�\n");
    Delay_Ms(1000);

}

/*
 * @brief:FibocomL610����ƽ̨��Ϣ���������Ӳ���,������
 * @param:null
 * @return:null
 */
void L610_SetAndConnect()
{

    //����ƽ̨�豸��Ϣ AT+TCDEVINFOSET=1,"Z2JKC5OLC7","smartCart","hvRtR5SpePhwDqL5nWDR2Q=="
    printf("AT+TCDEVINFOSET=1,\"Z2JKC5OLC7\",\"smartCart\",\"hvRtR5SpePhwDqL5nWDR2Q==\"\r\n");
    Delay_Ms(1000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"+TCDEVINFOSET: OK");
    while(strx==NULL)
    {
       printf("ƽ̨��Ϣ����ʧ��\n");
       Delay_Ms(1000);
       USART_Rbuffer_Num = 0;
       printf("AT+TCDEVINFOSET=1,\"Z2JKC5OLC7\",\"smartCart\",\"hvRtR5SpePhwDqL5nWDR2Q==\"\r\n");
       Delay_Ms(1000);
       strx=strstr((const char*)USART_Rbuffer,(const char*)"+TCDEVINFOSET: OK");
    }
    printf("ƽ̨��Ϣ���óɹ�\n");
    Delay_Ms(1000);

    //�������Ӳ���������
    printf("AT+TCMQTTCONN=1,20000,240,1,1\r\n");
    Delay_Ms(2000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"+TCMQTTCONN: OK");
    while(strx==NULL)
    {
        strx=strstr((const char*)USART_Rbuffer,(const char*)"+CME ERROR: 4");//�������������Ϊ֮ǰ�Ѿ����ӹ��ˣ��Ͽ���������һ�ξͿ�����
        if(strx==NULL)
        {
            printf("����ʧ��\n");
            Delay_Ms(2000);
            USART_Rbuffer_Num = 0;
            printf("AT+TCMQTTCONN=1,20000,240,1,1\r\n");
            Delay_Ms(2000);
            strx=strstr((const char*)USART_Rbuffer,(const char*)"+TCMQTTCONN: OK");

        }
        else
        {
            printf("AT+TCMQTTDISCONN\r\n");
            Delay_Ms(100);
            printf("AT+TCDEVINFOSET=1,\"Z2JKC5OLC7\",\"smartCart\",\"hvRtR5SpePhwDqL5nWDR2Q==\"\r\n");
            Delay_Ms(100);
            printf("AT+TCMQTTCONN=1,20000,240,1,1\r\n");
            Delay_Ms(2000);
            strx=strstr((const char*)USART_Rbuffer,(const char*)"+TCMQTTCONN: OK");

        }
    }
    printf("���ӳɹ�\n");
    Delay_Ms(1000);

}

/*
 * @brief:FibocomL610�����ϱ���������
 * @param:null
 * @return:null
 */
void L610_Sub()
{

    //�����ϱ��������� AT+TCMQTTSUB="$thing/down/property/Z2JKC5OLC7/smartCart",1
    printf("AT+TCMQTTSUB=\"$thing/down/property/Z2JKC5OLC7/smartCart\",1\r\n");
    Delay_Ms(2000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"+TCMQTTSUB: OK");
    while(strx==NULL)
    {
       printf("���ı�ǩʧ��\n");
       Delay_Ms(1000);
       USART_Rbuffer_Num = 0;
       printf("AT+TCMQTTSUB=\"$thing/down/property/Z2JKC5OLC7/smartCart\",1\r\n");
       Delay_Ms(1000);
       strx=strstr((const char*)USART_Rbuffer,(const char*)"+TCMQTTSUB: OK");
    }
    printf("���ı�ǩ�ɹ�\n");
    Delay_Ms(1000);

}

/*
 * @brief:FibocomL610�ϱ�
 * @param:productID:��Ʒ����ID
 * @return:NULL
 */
void L610_Pub(const char* productID)
{
    //�ϱ����� AT+TCMQTTPUB="$thing/up/property/Z2JKC5OLC7/smartCart",1,"{\"method\":\"report\",\"clientToken\":\"123\",\"params\":{\"productID\":345}}"
    printf("AT+TCMQTTPUB=\"$thing/up/property/Z2JKC5OLC7/smartCart\",1,\"{\\\"method\\\":\\\"report\\\",\\\"clientToken\\\":\\\"123\\\",\\\"params\\\":{\\\"productID\\\":%s}}\"\r\n",productID);
    Delay_Ms(1000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"thing");//�ϱ��������ص�̫�죬ץ��ס��OK�������Ըɴ���һ������һ�����Ϣ��Ϊ�ɹ��ı�־
    while(strx==NULL)
    {
       printf("�ϱ�ʧ��\n");
       Delay_Ms(1000);
       USART_Rbuffer_Num = 0;
       printf("AT+TCMQTTPUB=\"$thing/up/property/Z2JKC5OLC7/smartCart\",1,\"{\\\"method\\\":\\\"report\\\",\\\"clientToken\\\":\\\"123\\\",\\\"params\\\":{\\\"productID\\\":%s}}\"\r\n",productID);
       Delay_Ms(1000);
       strx=strstr((const char*)USART_Rbuffer,(const char*)"thing");
    }
    printf("�ϱ��ɹ�\n");
    //Delay_Ms(1000);

}

/*
 * @brief:FibocomL610����
 * @param:NULL
 * @return:const ProductInfo* productInfo���յ��Ĳ�Ʒ��Ϣ
 */
const ProductInfo* L610_Recive()
{
    static ProductInfo productInfo; // ��̬����������Ʒ��Ϣ
    char* strx;


    Delay_Ms(1000);
    USART_Rbuffer_Num = 0;
    memset(USART_Rbuffer, 0, sizeof(USART_Rbuffer));
    while(1)
    {
        if(USART_Rbuffer[0] != 0)
        {
            Delay_Ms(1000);
            //����productID
            strx=strstr((const char*)USART_Rbuffer,(const char*)"productID");
            if (strx==NULL)
                printf("��ƷID���Ի�ȡʧ��\n");
            else
            {
                int i = 0;
                strx += strlen("productID") + 3; // �ƶ��� productID ��ֵ��λ��
                while (*strx != '\"' && i < MAX_STRING_LENGTH)
                {
                    productInfo.productID[i++] = *strx++; // ���ַ����� productID
                }
                productInfo.productID[i] = '\0'; // ����ַ���������
                printf("��ƷID���Ի�ȡ�ɹ�\n");
                Delay_Ms(500);
                printf("�յ���Ϣ��productID=%s\n" , productInfo.productID);
                Delay_Ms(500);
                USART_Rbuffer_Num = 0;
            }
            //����productName
            strx=strstr((const char*)USART_Rbuffer,(const char*)"productName");
            if (strx==NULL)
                printf("��ƷName���Ի�ȡʧ��\n");
            else
            {
                int i = 0;
                strx += strlen("productName") + 3; // �ƶ��� productName ��ֵ��λ��
                while ( *strx != '\"' && i < MAX_STRING_LENGTH)
                {
                    productInfo.productName[i++] = *strx++; // ���ַ����� productName
                }
                productInfo.productName[i] = '\0'; // ����ַ���������
                printf("��ƷName���Ի�ȡ�ɹ�\n");
                Delay_Ms(500);
                printf("�յ���Ϣ��productName=%s\n" , productInfo.productName);
                Delay_Ms(500);
                USART_Rbuffer_Num = 0;
            }

            //����productPrice
            strx=strstr((const char*)USART_Rbuffer,(const char*)"productPrice");
            if (strx==NULL)
                printf("��ƷPrice���Ի�ȡʧ��\n");
            else
            {
                int i = 0;
                strx += strlen("productPrice") + 2; // �ƶ��� productPrice ��ֵ��λ��
                while (*strx !=',' && *strx != '\"' && i < MAX_STRING_LENGTH)
                {
                    productInfo.productPriceStr[i++] = *strx++; // ���ַ����� productPriceStr
                }
                productInfo.productPriceStr[i] = '\0'; // ����ַ���������
                printf("��ƷPrice���Ի�ȡ�ɹ�\n");
                productInfo.productPrice=strtof(productInfo.productPriceStr,&endptr);

                Delay_Ms(500);
                printf("�յ���Ϣ��productPriceStr=%s\n" , productInfo.productPriceStr);
                //printf("%f\n" , productInfo.productPrice);
                Delay_Ms(500);
                USART_Rbuffer_Num = 0;
            }

            //����productWeight
            strx=strstr((const char*)USART_Rbuffer,(const char*)"productWeight");
            if (strx==NULL)
                printf("��ƷWeight���Ի�ȡʧ��\n");
            else
            {
                int i = 0;
                strx += strlen("productWeight") + 2; // �ƶ��� productWeight ��ֵ��λ��
                while (*strx !=',' && *strx != '\"' && i < MAX_STRING_LENGTH)
                {
                    productInfo.productWeightStr[i++] = *strx++; // ���ַ����� productWeightStr
                }
                productInfo.productWeightStr[i] = '\0'; // ����ַ���������
                printf("��ƷWeight���Ի�ȡ�ɹ�\n");
                productInfo.productWeight=strtof(productInfo.productWeightStr,&endptr);
                Delay_Ms(500);
                printf("�յ���Ϣ��productWeightStr=%s\n" , productInfo.productWeightStr);
                //productInfo.productWeight=1.0;
                //printf("%f\n" , productInfo.productWeight);
                Delay_Ms(500);
                USART_Rbuffer_Num = 0;
            }

            USART_Rbuffer_Num = 0;
            memset(USART_Rbuffer, 0, sizeof(USART_Rbuffer));
        }
        Delay_Ms(500);
    }
}
