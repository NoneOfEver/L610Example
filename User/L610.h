/*
 * L610.c
 *
 *      Created on      :2024��3��22��
 *      Author          :�˲���
 *      Version         :V1.0
 *      Description     :FibocomL610�ӿڿ�,���汾Ϊ��һ�棬���Դֲڣ���Ҫȱ���Լ��ɸĽ������£�
 *                          1.�²����ڴ��ڴ�ӡ�ľ����ԣ��޷���ʾ��ӡ�����ĸ������֣������Ǵ�ӡ�̶���������
 *                            �����Ҫ�ں����ⲿ������ת���ĸ������Ƿ���ȷ���������ȷ�����������д�ַ�����ת�����͵ĺ�����
 *                          2.���ڹ�ʱ�϶̣����汾�в�����³���ԣ�����׳�ԣ��ƻ�δ����V2����ǿ��
 *                          3.����Ŀ�ƻ���Դ����˴ӵ�һ�濪ʼӦ�滮�����׶��ԣ���δ���汾�н����д���ע�ͣ��Լ�VSCode
 *                            ��ʶ��ɵ����Ľ����ĵ���������ĿĿ¼�����README.md�ļ�
 *
 *
 *
 *
 */

#ifndef USER_L610_H_
#define USER_L610_H_

#include "debug.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ���������ճ���Ϊ100
#define MAX_STRING_LENGTH 100

extern char *strx;
extern char *strstr(const char *, const char *);
extern char USART_Rbuffer[1024];
extern char USART_Rbuffer_Num;
extern char *endptr;
extern int len;
extern int number;

//���ص���Ʒ��Ϣ�ṹ��
typedef struct{
    char productID[MAX_STRING_LENGTH+1];
    float productPrice;
    char productName[MAX_STRING_LENGTH+1];
    float productWeight;
    char productPriceStr[MAX_STRING_LENGTH];
    char productWeightStr[MAX_STRING_LENGTH];
} ProductInfo;

void L610_Init();
void L610_Lookup();
void L610_RequestIP();
void L610_SetAndConnect();
void L610_Sub();
void L610_Pub(const char* productID);
const ProductInfo* L610_Recive();

#endif /* USER_L610_H_ */
