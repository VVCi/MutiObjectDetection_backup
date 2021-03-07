/* driver include */
#include "../driver/led/led.h"
#include "../driver/flash/flash.h"
#include "../driver/Arduino-LiquidCrystal-I2C-library/LiquidCrystal_I2C.h"
#include "../driver/modbus_rtu/modbus_rtu.h"
#include "../driver/EmonLib/EmonLib.h"

/* app include */
#include "app.h"
#include "app_dbg.h"

/* task include */

/* sys include */
#include "../sys/sys_irq.h"
#include "../sys/sys_io.h"
#include "../sys/sys_ctrl.h"
#include "../sys/sys_dbg.h"
#include "../sys/sys_arduino.h"

/* common include */
#include "../common/utils.h"

led_t led_life;

/*****************************************************************************/
/* app main function.
 */
/*****************************************************************************/
int main_app() {
	APP_PRINT("main_app() entry OK\n");

	/******************************************************************************
	* init applications
	*******************************************************************************/
	/*********************
	* hardware configure *
	**********************/
	/* init watch dog timer */
	sys_ctrl_independent_watchdog_init();	/* 32s */
	sys_ctrl_soft_watchdog_init(200);		/* 20s */

	/*********************
	* software configure *
	**********************/
	/* life led init */
    led_init(&led_life, led_life_init, led_life_on, led_life_off);
	led_off(&led_life);
       uint8_t tt ;
       uint8_t aaa1 =0;

	while(1) {
        tt = read_button_mode();
       if (tt==0) aaa1 ++;

        while ( aaa1 ==3 )  led_off(&led_life);
        while ( aaa1 ==2)   led_on(&led_life);
        while ( aaa1 ==1){
                                            led_on(&led_life);
                                            delay(1000);
                                            led_off(&led_life);
                                            delay(1000);
        }
        while( aaa1 ==0){
                                            led_on(&led_life);
                                            delay(100);
                                            led_off(&led_life);
                                            delay(100);
        }
	}
}

/* hardware timer interrupt 10ms
 * used for sensor polling
 */
void sys_irq_timer_10ms() {
}
