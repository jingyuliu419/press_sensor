/**
 ****************************************************************************************************
 * @file        atk_mw8266d.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MW8266Dģ����������
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� MiniSTM32 V4������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "atk_mw8266d.h"
#include <string.h>
#include <stdio.h>

/**
 * @brief       ATK-MW8266DӲ����ʼ��
 * @param       ��
 * @retval      ��
 */
static void atk_mw8266d_hw_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    ATK_MW8266D_RST_GPIO_CLK_ENABLE();
    
    gpio_init_struct.Pin = ATK_MW8266D_RST_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_NOPULL;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MW8266D_RST_GPIO_PORT, &gpio_init_struct);
}

/**
 * @brief       ATK-MW8266DӲ����λ
 * @param       ��
 * @retval      ��
 */
void atk_mw8266d_hw_reset(void)
{
    ATK_MW8266D_RST(0);
    HAL_Delay(100);
    ATK_MW8266D_RST(1);
    HAL_Delay(500);
}

/**
 * @brief       ATK-MW8266D����ATָ��
 * @param       cmd    : �����͵�ATָ��
 *              ack    : �ȴ�����Ӧ
 *              timeout: �ȴ���ʱʱ��
 * @retval      ATK_MW8266D_EOK     : ����ִ�гɹ�
 *              ATK_MW8266D_ETIMEOUT: �ȴ�����Ӧ��ʱ������ִ��ʧ��
 */
uint8_t atk_mw8266d_send_at_cmd(char *cmd, char *ack, uint32_t timeout)
{
    uint8_t *ret = NULL;
    
    atk_mw8266d_uart_rx_restart();
    atk_mw8266d_uart_printf("%s\r\n", cmd);
    
    if ((ack == NULL) || (timeout == 0))
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        while (timeout > 0)
        {
            ret = atk_mw8266d_uart_rx_get_frame();
            if (ret != NULL)
            {
                if (strstr((const char *)ret, ack) != NULL)
                {
                    return ATK_MW8266D_EOK;
                }
                else
                {
                    atk_mw8266d_uart_rx_restart();
                }
            }
            timeout--;
            HAL_Delay(1);
        }
        
        return ATK_MW8266D_ETIMEOUT;
    }
}

/**
 * @brief       ATK-MW8266D��ʼ��
 * @param       baudrate: ATK-MW8266D UARTͨѶ������
 * @retval      ATK_MW8266D_EOK  : ATK-MW8266D��ʼ���ɹ�������ִ�гɹ�
 *              ATK_MW8266D_ERROR: ATK-MW8266D��ʼ��ʧ�ܣ�����ִ��ʧ��
 */
uint8_t atk_mw8266d_init(uint32_t baudrate)
{
    // atk_mw8266d_hw_init();                          /* ATK-MW8266DӲ����ʼ�� */
    // atk_mw8266d_hw_reset();                         /* ATK-MW8266DӲ����λ */
    atk_mw8266d_uart_init(baudrate);                /* ATK-MW8266D UART��ʼ�� */
    if (atk_mw8266d_at_test() != ATK_MW8266D_EOK)   /* ATK-MW8266D ATָ����� */
    {
        return ATK_MW8266D_ERROR;
    }
    
    return ATK_MW8266D_EOK;
}

/**
 * @brief       ATK-MW8266D�ָ���������
 * @param       ��
 * @retval      ATK_MW8266D_EOK  : �ָ��������óɹ�
 *              ATK_MW8266D_ERROR: �ָ���������ʧ��
 */
uint8_t atk_mw8266d_restore(void)
{
    uint8_t ret;
    
    ret = atk_mw8266d_send_at_cmd("AT+RESTORE", "ready", 3000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D ATָ�����
 * @param       ��
 * @retval      ATK_MW8266D_EOK  : ATָ����Գɹ�
 *              ATK_MW8266D_ERROR: ATָ�����ʧ��
 */
uint8_t atk_mw8266d_at_test(void)
{
    uint8_t ret;
    uint8_t i;
    
    for (i=0; i<3; i++)
    {
        ret = atk_mw8266d_send_at_cmd("AT", "OK", 500);
        if (ret == ATK_MW8266D_EOK)
        {
            return ATK_MW8266D_EOK;
        }
    }
    
    return ATK_MW8266D_ERROR;
}

/**
 * @brief       ����ATK-MW8266D����ģʽ
 * @param       mode: 1��Stationģʽ
 *                    2��APģʽ
 *                    3��AP+Stationģʽ
 * @retval      ATK_MW8266D_EOK   : ����ģʽ���óɹ�
 *              ATK_MW8266D_ERROR : ����ģʽ����ʧ��
 *              ATK_MW8266D_EINVAL: mode�������󣬹���ģʽ����ʧ��
 */
uint8_t atk_mw8266d_set_mode(uint8_t mode)
{
    uint8_t ret;
    
    switch (mode)
    {
        case 1:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=1", "OK", 500);    /* Stationģʽ */
            break;
        }
        case 2:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=2", "OK", 500);    /* APģʽ */
            break;
        }
        case 3:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=3", "OK", 500);    /* AP+Stationģʽ */
            break;
        }
        default:
        {
            return ATK_MW8266D_EINVAL;
        }
    }
    
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D������λ
 * @param       ��
 * @retval      ATK_MW8266D_EOK  : ������λ�ɹ�
 *              ATK_MW8266D_ERROR: ������λʧ��
 */
uint8_t atk_mw8266d_sw_reset(void)
{
    uint8_t ret;
    
    ret = atk_mw8266d_send_at_cmd("AT+RST", "OK", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        HAL_Delay(1000);
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D���û���ģʽ
 * @param       cfg: 0���رջ���
 *                   1���򿪻���
 * @retval      ATK_MW8266D_EOK  : ���û���ģʽ�ɹ�
 *              ATK_MW8266D_ERROR: ���û���ģʽʧ��
 */
uint8_t atk_mw8266d_ate_config(uint8_t cfg)
{
    uint8_t ret;
    
    switch (cfg)
    {
        case 0:
        {
            ret = atk_mw8266d_send_at_cmd("ATE0", "OK", 500);   /* �رջ��� */
            break;
        }
        case 1:
        {
            ret = atk_mw8266d_send_at_cmd("ATE1", "OK", 500);   /* �򿪻��� */
            break;
        }
        default:
        {
            return ATK_MW8266D_EINVAL;
        }
    }
    
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D����WIFI
 * @param       ssid: WIFI����
 *              pwd : WIFI����
 * @retval      ATK_MW8266D_EOK  : WIFI���ӳɹ�
 *              ATK_MW8266D_ERROR: WIFI����ʧ��
 */
uint8_t atk_mw8266d_join_ap(char *ssid, char *pwd)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"", ssid, pwd);
    ret = atk_mw8266d_send_at_cmd(cmd, "WIFI GOT IP", 10000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D��ȡIP��ַ
 * @param       buf: IP��ַ����Ҫ16�ֽ��ڴ�ռ�
 * @retval      ATK_MW8266D_EOK  : ��ȡIP��ַ�ɹ�
 *              ATK_MW8266D_ERROR: ��ȡIP��ַʧ��
 */
uint8_t atk_mw8266d_get_ip(char *buf)
{
    uint8_t ret;
    char *p_start;
    char *p_end;
    
    ret = atk_mw8266d_send_at_cmd("AT+CIFSR", "OK", 500);
    if (ret != ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_ERROR;
    }
    
    p_start = strstr((const char *)atk_mw8266d_uart_rx_get_frame(), "\"");
    p_end = strstr(p_start + 1, "\"");
    *p_end = '\0';
    sprintf(buf, "%s", p_start + 1);
    
    return ATK_MW8266D_EOK;
}

/**
 * @brief       ATK-MW8266D����TCP������
 * @param       server_ip  : TCP������IP��ַ
 *              server_port: TCP�������˿ں�
 * @retval      ATK_MW8266D_EOK  : ����TCP�������ɹ�
 *              ATK_MW8266D_ERROR: ����TCP������ʧ��
 */
uint8_t atk_mw8266d_connect_tcp_server(char *server_ip, char *server_port)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%s", server_ip, server_port);
    ret = atk_mw8266d_send_at_cmd(cmd, "CONNECT", 5000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D����͸��
 * @param       ��
 * @retval      ATK_MW8266D_EOK  : ����͸���ɹ�
 *              ATK_MW8266D_ERROR: ����͸��ʧ��
 */
uint8_t atk_mw8266d_enter_unvarnished(void)
{
    uint8_t ret;
    
    ret  = atk_mw8266d_send_at_cmd("AT+CIPMODE=1", "OK", 500);
    ret += atk_mw8266d_send_at_cmd("AT+CIPSEND", ">", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D�˳�͸��
 * @param       ��
 * @retval      ��
 */
void atk_mw8266d_exit_unvarnished(void)
{
    atk_mw8266d_uart_printf("+++");
}

/**
 * @brief       ATK-MW8266D����ԭ���Ʒ�����
 * @param       id : ԭ�����豸���
 *              pwd: ԭ�����豸����
 * @retval      ATK_MW8266D_EOK  : ����ԭ���Ʒ������ɹ�
 *              ATK_MW8266D_ERROR: ����ԭ���Ʒ�����ʧ��
 */
uint8_t atk_mw8266d_connect_atkcld(char *id, char *pwd)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+ATKCLDSTA=\"%s\",\"%s\"", id, pwd);
    ret = atk_mw8266d_send_at_cmd(cmd, "CLOUD CONNECTED", 10000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D�Ͽ�ԭ���Ʒ���������
 * @param       ��
 * @retval      ATK_MW8266D_EOK  : �Ͽ�ԭ���Ʒ��������ӳɹ�
 *              ATK_MW8266D_ERROR: �Ͽ�ԭ���Ʒ���������ʧ��
 */
uint8_t atk_mw8266d_disconnect_atkcld(void)
{
    uint8_t ret;
    
    ret = atk_mw8266d_send_at_cmd("AT+ATKCLDCLS", "CLOUD DISCONNECT", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}
