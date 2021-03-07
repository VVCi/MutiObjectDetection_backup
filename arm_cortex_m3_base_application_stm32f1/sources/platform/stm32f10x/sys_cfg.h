/**
 ******************************************************************************
 * @Author: ThanNT
 * @Date:   05/09/2016
 ******************************************************************************
**/
#ifndef __SYS_CFG_H__
#define __SYS_CFG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "stm32f10x_conf.h"

/* USART Communication boards Interface */
#define USARTx                           USART1
#define USARTx_CLK                       RCC_APB2Periph_USART1
#define USARTx_IRQn                      USART1_IRQn

#define USARTx_TX_PIN                    GPIO_Pin_9
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_GPIO_CLK               RCC_APB2Periph_GPIOA
#define USARTx_TX_SOURCE                 GPIO_PinSource9

#define USARTx_RX_PIN                    GPIO_Pin_10
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RX_GPIO_CLK               RCC_APB2Periph_GPIOA
#define USARTx_RX_SOURCE                 GPIO_PinSource10

extern void sys_cfg_clock();
extern void sys_cfg_tick();
extern void sys_cfg_console();
extern void sys_cfg_update_info();

extern int32_t timeout_rs485;


#ifdef __cplusplus
}
#endif

#endif //__SYS_CFG_H__