/**
 ******************************************************************************
 * @Author: ThanNT
 * @Date:   13/08/2016
 ******************************************************************************
**/

#ifndef APP_H
#define APP_H

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/*  task DtCt_LIFE define
 */
/*****************************************************************************/
/* define timer */
#define DtCt_LIFE_TASK_TIMER_LED_LIFE_INTERVAL		(1000)

/* define signal */
#define DtCt_LIFE_SYSTEM_CHECK						(0)

/*****************************************************************************/
/*  task DtCt_SHELL define
 */
/*****************************************************************************/
/* define timer */

/* define signal */
#define DtCt_SHELL_LOGIN_CMD							(0)
#define DtCt_SHELL_REMOTE_CMD							(1)

/*****************************************************************************/
/*  task DtCt_RF24 define
 */
/*****************************************************************************/
/* define timer */
#define DtCt_RF24_IF_TIMER_PACKET_DELAY_INTERVAL		(100)	/* 100 ms */
#define DtCt_RF24_IF_POLLING_INTERVAL					(100)	/* 100ms */

/* define signal */
/* interrupt signal */
#define DtCt_RF24_IF_IRQ_TX_FAIL						(1)
#define DtCt_RF24_IF_IRQ_TX_SUCCESS					(2)
#define DtCt_RF24_IF_IRQ_RX_READY						(3)

#define DtCt_RF24_IF_INIT_NETWORK						(4)
#define DtCt_RF24_IF_PURE_MSG_OUT						(5)
#define DtCt_RF24_IF_COMMON_MSG_OUT					(6)
#define DtCt_RF24_IF_TIMER_PACKET_DELAY				(7)

/*****************************************************************************/
/* task DtCt_IF define
 */
/*****************************************************************************/
/* define timer */
/* define signal */
#define DtCt_IF_PURE_MSG_IN								(1)
#define DtCt_IF_PURE_MSG_OUT							(2)
#define DtCt_IF_COMMON_MSG_IN							(3)
#define DtCt_IF_COMMON_MSG_OUT							(4)

//110500ACFF004E8B
/*****************************************************************************/
/* task DtCt_LCD define
 */
/*****************************************************************************/
/* define timer */
/* define signal */
//#define DtCt_LCD_INIT									(1)
/*****************************************************************************/
/* task DtSt_RS485 define
*/
/*****************************************************************************/
/* define timer */
#define DtCt_RS485_SLAVE_UPDATE_INTERVAL				(50)
#define DtCt_RS485_SLAVE_INIT_INTERVAL					(500)
/* define signal */
#define DtCt_RS485_SLAVE_UPDATE							(2)
#define DtCt_RS485_INIT									(1)

/*****************************************************************************/
/*  app function declare
 */
/*****************************************************************************/
#define SL_AC_NUMBER_SAMPLE_CT_SENSOR				2000
#define SL_TOTAL_CT_SENSOR							(8)
#define SL_SENSOR_CHECKING_REQ						(0)
/*****************************************************************************/
/*  global define variable
 */
/*****************************************************************************/
#define APP_OK										(0x00)
#define APP_NG										(0x01)

#define APP_FLAG_OFF								(0x00)
#define APP_FLAG_ON									(0x01)

extern int  main_app();

#ifdef __cplusplus
}
#endif

#endif //APP_H
