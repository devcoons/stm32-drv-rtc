/*!
	@file   drv_rtc.c
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

/******************************************************************************
* Includes
******************************************************************************/

#include "drv_rtc.h"

#ifdef DRV_RTC_ENABLED

/******************************************************************************
* Enumerations, structures & Variables
******************************************************************************/

/******************************************************************************
* Declaration | Static Functions
******************************************************************************/

/******************************************************************************
* Definition  | Static Functions
******************************************************************************/

/******************************************************************************
* Definition  | Public Functions
******************************************************************************/

i_status rtc_initialize(rtc_t* instance)
{
	if( instance== NULL)
		return I_ERROR;
	instance->mx_init();
	HAL_RTCEx_SetSmoothCalib(&hrtc, RTC_SMOOTHCALIB_PERIOD_32SEC, RTC_SMOOTHCALIB_PLUSPULSES_RESET, 400);

	return I_OK;
}

i_status rtc_deinitialize(rtc_t* instance)
{
	if( instance== NULL)
		return I_ERROR;

	if (HAL_OK == HAL_RTC_DeInit(instance->handler))
		return I_OK;
	else
		return I_ERROR;
}

i_status rtc_get_time_data(rtc_t* instance)
{
	RTC_TimeTypeDef sTime ;
	RTC_DateTypeDef sDate;

	if( instance == NULL)
		return I_ERROR;

	if(HAL_ERROR ==HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD))
		return I_ERROR;

	instance->Hours = sTime.Hours;
	instance->Minutes = sTime.Minutes;
	instance->Seconds = sTime.Seconds;
	instance->TimeFormat = sTime.TimeFormat;

	if(HAL_ERROR == HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD))
		return I_ERROR;

	instance->WeekDay=sDate.WeekDay;
	instance->Month=sDate.Month;
	instance->Day=sDate.Date;
	instance->Year=sDate.Year;

	return I_OK;

}

i_status rtc_set_time(rtc_t* instance,uint8_t Hours,uint8_t Minutes, uint8_t Seconds)
{
	RTC_TimeTypeDef sTime ;

	if(instance== NULL)
		return I_ERROR;

	sTime.Hours = Hours;
	sTime.Minutes = Minutes;
	sTime.Seconds = Seconds;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;

	if(HAL_OK == HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD))
		return I_OK;
	else
		return I_ERROR;


}

i_status rtc_set_date(rtc_t* instance,uint8_t WeekDay,uint8_t Month, uint8_t Date, uint8_t Year)
{

	RTC_DateTypeDef sDate;
	if(instance== NULL)
		return I_ERROR;

	sDate.WeekDay = WeekDay;
	sDate.Month = Month;
	sDate.Date = Date;
	sDate.Year = Year;

	if(HAL_OK == HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD))
		return I_OK;
	else
		return I_ERROR;
}

/*
i_status rtc_set_datetime(rtc* instance)
{

}
*/
i_status rtc_deactivateWakeupTimer(rtc_t* instance)
{
	if(HAL_OK==HAL_RTCEx_DeactivateWakeUpTimer(instance->handler))
		return I_OK;
	else
		return I_ERROR;
}

i_status rtc_setWakeUpTimer(rtc_t* instance)
{
	#if defined(STM32L5)
		if(HAL_OK==HAL_RTCEx_SetWakeUpTimer_IT(instance->handler, instance->WakeUpCounter, RTC_WAKEUPCLOCK_CK_SPRE_16BITS,0))
		{
	#elif defined(STM32H7)
		if(HAL_OK==HAL_RTCEx_SetWakeUpTimer_IT(instance->handler, instance->WakeUpCounter, RTC_WAKEUPCLOCK_RTCCLK_DIV16))
		{
			HAL_RTCEx_WakeUpTimerIRQHandler(instance->handler);
	#endif
		return I_OK;
		}
	else
		return I_ERROR;
}

/******************************************************************************
* EOF - NO CODE AFTER THIS LINE
******************************************************************************/
#endif




