/*
 * L610.c
 *
 *      Created on      :2024年3月22日
 *      Author          :潘泊名
 *      Version         :V1.0
 *      Description     :FibocomL610接口库
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
 * @brief:FibocomL610模块初始化
 * @param:null
 * @return:null
 */
void L610_Init()
{
    printf("模块初始化\r\n");
    Delay_Ms(5000);

    printf("AT\r\n");
    Delay_Ms(1000);
}

/*
 * @brief:查询FibocomL610
 * @param:null
 * @return:null
 */
void L610_Lookup()
{
    //查询版本信息
    printf("ATI\r\n");
    Delay_Ms(1000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"Fibocom");
    while(strx==NULL)
    {
       printf("查询信息失败\n");
       Delay_Ms(1000);
       USART_Rbuffer_Num = 0;
       printf("ATI\r\n");
       Delay_Ms(1000);
       strx=strstr((const char*)USART_Rbuffer,(const char*)"Fibocom");
    }
    printf("版本信息正确\n");
    Delay_Ms(1000);

    //查询PS注册情况
    printf("AT+CGREG?\r\n");
    Delay_Ms(1000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"+CGREG: 0,1");
    while(strx==NULL)
    {
       printf("PS注册无效\n");
       Delay_Ms(1000);
       USART_Rbuffer_Num = 0;
       printf("AT+CGREG?\r\n");
       Delay_Ms(1000);
       strx=strstr((const char*)USART_Rbuffer,(const char*)"+CGREG: 0,1");
    }
    printf("PS注册有效\n");
    Delay_Ms(1000);

}

/*
 * @brief:FibocomL610申请IP
 * @param:null
 * @return:null
 */
void L610_RequestIP()
{
    //请求IP
    printf("AT+MIPCALL?\r\n");
    Delay_Ms(1000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"+MIPCALL: 1");
    while(strx==NULL)
    {
       printf("还未获取到IP\n");
       Delay_Ms(1000);
       USART_Rbuffer_Num = 0;
       printf("AT+MIPCALL=1\r\n");
       Delay_Ms(1000);
       strx=strstr((const char*)USART_Rbuffer,(const char*)"+MIPCALL: 1");
    }
    printf("获取IP成功\n");
    Delay_Ms(1000);

}

/*
 * @brief:FibocomL610设置平台信息，设置连接参数,并连接
 * @param:null
 * @return:null
 */
void L610_SetAndConnect()
{

    //设置平台设备信息 AT+TCDEVINFOSET=1,"Z2JKC5OLC7","smartCart","hvRtR5SpePhwDqL5nWDR2Q=="
    printf("AT+TCDEVINFOSET=1,\"Z2JKC5OLC7\",\"smartCart\",\"hvRtR5SpePhwDqL5nWDR2Q==\"\r\n");
    Delay_Ms(1000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"+TCDEVINFOSET: OK");
    while(strx==NULL)
    {
       printf("平台信息设置失败\n");
       Delay_Ms(1000);
       USART_Rbuffer_Num = 0;
       printf("AT+TCDEVINFOSET=1,\"Z2JKC5OLC7\",\"smartCart\",\"hvRtR5SpePhwDqL5nWDR2Q==\"\r\n");
       Delay_Ms(1000);
       strx=strstr((const char*)USART_Rbuffer,(const char*)"+TCDEVINFOSET: OK");
    }
    printf("平台信息设置成功\n");
    Delay_Ms(1000);

    //设置连接参数并连接
    printf("AT+TCMQTTCONN=1,20000,240,1,1\r\n");
    Delay_Ms(2000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"+TCMQTTCONN: OK");
    while(strx==NULL)
    {
        strx=strstr((const char*)USART_Rbuffer,(const char*)"+CME ERROR: 4");//报这个错误是因为之前已经连接过了，断开重新连接一次就可以了
        if(strx==NULL)
        {
            printf("连接失败\n");
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
    printf("连接成功\n");
    Delay_Ms(1000);

}

/*
 * @brief:FibocomL610订阅上报下行属性
 * @param:null
 * @return:null
 */
void L610_Sub()
{

    //订阅上报下行属性 AT+TCMQTTSUB="$thing/down/property/Z2JKC5OLC7/smartCart",1
    printf("AT+TCMQTTSUB=\"$thing/down/property/Z2JKC5OLC7/smartCart\",1\r\n");
    Delay_Ms(2000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"+TCMQTTSUB: OK");
    while(strx==NULL)
    {
       printf("订阅标签失败\n");
       Delay_Ms(1000);
       USART_Rbuffer_Num = 0;
       printf("AT+TCMQTTSUB=\"$thing/down/property/Z2JKC5OLC7/smartCart\",1\r\n");
       Delay_Ms(1000);
       strx=strstr((const char*)USART_Rbuffer,(const char*)"+TCMQTTSUB: OK");
    }
    printf("订阅标签成功\n");
    Delay_Ms(1000);

}

/*
 * @brief:FibocomL610上报
 * @param:productID:商品条码ID
 * @return:NULL
 */
void L610_Pub(const char* productID)
{
    //上报属性 AT+TCMQTTPUB="$thing/up/property/Z2JKC5OLC7/smartCart",1,"{\"method\":\"report\",\"clientToken\":\"123\",\"params\":{\"productID\":345}}"
    printf("AT+TCMQTTPUB=\"$thing/up/property/Z2JKC5OLC7/smartCart\",1,\"{\\\"method\\\":\\\"report\\\",\\\"clientToken\\\":\\\"123\\\",\\\"params\\\":{\\\"productID\\\":%s}}\"\r\n",productID);
    Delay_Ms(1000);
    strx=strstr((const char*)USART_Rbuffer,(const char*)"thing");//上报回馈返回的太快，抓不住”OK“，所以干脆挑一个靠后一点的信息作为成功的标志
    while(strx==NULL)
    {
       printf("上报失败\n");
       Delay_Ms(1000);
       USART_Rbuffer_Num = 0;
       printf("AT+TCMQTTPUB=\"$thing/up/property/Z2JKC5OLC7/smartCart\",1,\"{\\\"method\\\":\\\"report\\\",\\\"clientToken\\\":\\\"123\\\",\\\"params\\\":{\\\"productID\\\":%s}}\"\r\n",productID);
       Delay_Ms(1000);
       strx=strstr((const char*)USART_Rbuffer,(const char*)"thing");
    }
    printf("上报成功\n");
    //Delay_Ms(1000);

}

/*
 * @brief:FibocomL610接收
 * @param:NULL
 * @return:const ProductInfo* productInfo：收到的产品信息
 */
const ProductInfo* L610_Recive()
{
    static ProductInfo productInfo; // 静态变量保存商品信息
    char* strx;


    Delay_Ms(1000);
    USART_Rbuffer_Num = 0;
    memset(USART_Rbuffer, 0, sizeof(USART_Rbuffer));
    while(1)
    {
        if(USART_Rbuffer[0] != 0)
        {
            Delay_Ms(1000);
            //查找productID
            strx=strstr((const char*)USART_Rbuffer,(const char*)"productID");
            if (strx==NULL)
                printf("商品ID属性获取失败\n");
            else
            {
                int i = 0;
                strx += strlen("productID") + 3; // 移动到 productID 的值的位置
                while (*strx != '\"' && i < MAX_STRING_LENGTH)
                {
                    productInfo.productID[i++] = *strx++; // 逐字符复制 productID
                }
                productInfo.productID[i] = '\0'; // 添加字符串结束符
                printf("商品ID属性获取成功\n");
                Delay_Ms(500);
                printf("收到信息：productID=%s\n" , productInfo.productID);
                Delay_Ms(500);
                USART_Rbuffer_Num = 0;
            }
            //查找productName
            strx=strstr((const char*)USART_Rbuffer,(const char*)"productName");
            if (strx==NULL)
                printf("商品Name属性获取失败\n");
            else
            {
                int i = 0;
                strx += strlen("productName") + 3; // 移动到 productName 的值的位置
                while ( *strx != '\"' && i < MAX_STRING_LENGTH)
                {
                    productInfo.productName[i++] = *strx++; // 逐字符复制 productName
                }
                productInfo.productName[i] = '\0'; // 添加字符串结束符
                printf("商品Name属性获取成功\n");
                Delay_Ms(500);
                printf("收到信息：productName=%s\n" , productInfo.productName);
                Delay_Ms(500);
                USART_Rbuffer_Num = 0;
            }

            //查找productPrice
            strx=strstr((const char*)USART_Rbuffer,(const char*)"productPrice");
            if (strx==NULL)
                printf("商品Price属性获取失败\n");
            else
            {
                int i = 0;
                strx += strlen("productPrice") + 2; // 移动到 productPrice 的值的位置
                while (*strx !=',' && *strx != '\"' && i < MAX_STRING_LENGTH)
                {
                    productInfo.productPriceStr[i++] = *strx++; // 逐字符复制 productPriceStr
                }
                productInfo.productPriceStr[i] = '\0'; // 添加字符串结束符
                printf("商品Price属性获取成功\n");
                productInfo.productPrice=strtof(productInfo.productPriceStr,&endptr);

                Delay_Ms(500);
                printf("收到信息：productPriceStr=%s\n" , productInfo.productPriceStr);
                //printf("%f\n" , productInfo.productPrice);
                Delay_Ms(500);
                USART_Rbuffer_Num = 0;
            }

            //查找productWeight
            strx=strstr((const char*)USART_Rbuffer,(const char*)"productWeight");
            if (strx==NULL)
                printf("商品Weight属性获取失败\n");
            else
            {
                int i = 0;
                strx += strlen("productWeight") + 2; // 移动到 productWeight 的值的位置
                while (*strx !=',' && *strx != '\"' && i < MAX_STRING_LENGTH)
                {
                    productInfo.productWeightStr[i++] = *strx++; // 逐字符复制 productWeightStr
                }
                productInfo.productWeightStr[i] = '\0'; // 添加字符串结束符
                printf("商品Weight属性获取成功\n");
                productInfo.productWeight=strtof(productInfo.productWeightStr,&endptr);
                Delay_Ms(500);
                printf("收到信息：productWeightStr=%s\n" , productInfo.productWeightStr);
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
