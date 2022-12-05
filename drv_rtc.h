/*!
	@file   drv_rtc.h
	@brief  <brief description here>
	@t.odo	-
	---------------------------------------------------------------------------

	MIT License
	Copyright (c) 2020 Federico Carnevale, Ioannis Deligiannis

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
/******************************************************************************
* Preprocessor Definitions & Macros
******************************************************************************/

#ifndef DRV_RTC_H_
#define DRV_RTC_H_

#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

#if __has_include("rtc.h")
	#include "rtc.h"
	#define DRV_RTC_ENABLED

/******************************************************************************
* Enumerations, structures & Variables
******************************************************************************/

#if !defined(ENUM_I_STATUS)
#define ENUM_I_STATUS
typedef enum
{
	I_OK 			= 0x00,
	I_INVALID 		= 0x01,
	I_EXISTS 		= 0x02,
	I_NOTEXISTS 		= 0x03,
	I_FAILED 		= 0x04,
	I_EXPIRED 		= 0x05,
	I_UNKNOWN 		= 0x06,
	I_INPROGRESS 		= 0x07,
	I_IDLE			= 0x08,
	I_FULL			= 0x09,
	I_EMPTY			= 0x0A,
	I_YES			= 0x0B,
	I_NO			= 0x0C,
	I_SKIP			= 0x0D,
	I_LOCKED 		= 0x0E,
	I_INACTIVE 		= 0x0F,
	I_ACTIVE 		= 0x10,
	I_READY		 	= 0x11,
	I_WAIT 			= 0x12,
	I_OVERFLOW 		= 0x13,
	I_CONTINUE 		= 0x14,
	I_STOPPED 		= 0x15,
	I_WARNING 		= 0x16,
	I_SLEEP 		= 0x17,
	I_DEEPSLEEP 		= 0x18,
	I_STANDBY 		= 0x19,
	I_GRANTED 		= 0x1A,
	I_DENIED 		= 0x1B,
	I_DEBUG_01 		= 0xE0,
	I_DEBUG_02 		= 0xE1,
	I_DEBUG_03 		= 0xE2,
	I_DEBUG_04 		= 0xE3,
	I_DEBUG_05 		= 0xE4,
	I_DEBUG_06 		= 0xE5,
	I_DEBUG_07 		= 0xE6,
	I_DEBUG_08 		= 0xE7,
	I_DEBUG_09 		= 0xE8,
	I_DEBUG_10 		= 0xE9,
	I_DEBUG_11 		= 0xEA,
	I_DEBUG_12 		= 0xEB,
	I_DEBUG_13 		= 0xEC,
	I_DEBUG_14 		= 0xED,
	I_DEBUG_15 		= 0xEE,
	I_DEBUG_16 		= 0xEF,
	I_MEMALIGNED		= 0xFC,
	I_MEMUNALIGNED		= 0xFD,
	I_NOTIMPLEMENTED 	= 0xFE,
	I_ERROR 		= 0xFF
}i_status;
#endif

/*
 * Main structure
 */

typedef struct
{
	uint8_t Hours;
	uint8_t Minutes;
	uint8_t Seconds;
	uint8_t TimeFormat;
	uint8_t WeekDay;
	uint8_t Month;
	uint8_t Day;
	uint8_t Year;
	uint32_t WakeUpCounter;
	RTC_HandleTypeDef* handler;
	void(*mx_init)();
}rtc_t;

/******************************************************************************
* Declaration | Public Functions
******************************************************************************/

/*
 * rtc_initialize : function used for initialize the peripheral, MUST be fill in the main structure
 * RTC_HandleTypeDef and the mx_init
 */
i_status rtc_initialize(rtc_t* instance);

/*
 * rtc_deinitialize : function used for de-initialize the peripheral.
 *
 */
i_status rtc_deinitialize(rtc_t* instance);

/*
 * rtc_get_time_data : function used for store in the main structure time and date
 *
 */
i_status rtc_get_time_data(rtc_t* instance);

/*
 * rtc_set_time : function used for store in the MCU new time.
 *
 */
i_status rtc_set_time(rtc_t* instance,uint8_t Hours,uint8_t Minutes, uint8_t Seconds);

/*
 * rtc_set_date : function used for store in the MCU new date.
 *
 */
i_status rtc_set_date(rtc_t* instance,uint8_t WeekDay,uint8_t Month, uint8_t Date, uint8_t Year);

/*
 * rtc_deactivateWakeupTimer : function used for deactivate wake up timer.
 *
 */
i_status rtc_deactivateWakeupTimer(rtc_t* instance);

/*
 * rtc_setWakeUpTimer : function used for activate wake up timer. MUST be fill the "WakeUpCounter" in a main structure.
 *
 */
i_status rtc_setWakeUpTimer(rtc_t* instance);

/******************************************************************************
* EOF - NO CODE AFTER THIS LINE
******************************************************************************/
#else
	#warning "Warning: Missing 'rtc.h' header file. Please enable RTC first"
#endif
#endif /* DRIVERS_INC_DRV_RTC_H_ */
