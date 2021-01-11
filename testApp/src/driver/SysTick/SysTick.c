/*
 * SysTick.c
 *
 *  Created on: 2021/01/11
 *      Author: NATSU_NO_OMOIDE
 */

#include "iodefine.h"
#include "SysTick.h"

uint8_t tick_1ms_flag;

void SysTick_Handler(void);

/* OSタイマドライバ初期化 */
void SysTick_init(void)
{
	REG_STK.VAL  = 0;		/* カウンタの現在値をクリア */
	REG_STK.LOAD = 16000;	/* カウントダウン開始位置を設定(1ms = 16000(16MHz) ) */
	REG_STK.CTRL = 0x6;		/* 制御レジスタを設定 */
							/*  - 2bit : クロックソースにプロセッサ･クロック（AHB）を設定 */
							/*  - 1bit : SysTick 例外要求を有効 */
							/*  - 0bit : カウンタ停止 */

	tick_1ms_flag = 0;
}

/* OSタイマ開始 */
void SysTick_start(void)
{
	REG_STK.CTRL |= 0x1;	/* カウンタ開始 */
}

/* OSタイマ停止 */
void SysTick_stop(void)
{
	REG_STK.CTRL &= ~(0x1);	/* カウンタ停止 */
}

/* 割り込みハンドラ */
void SysTick_Handler(void)
{
	if ( ( REG_STK.CTRL & 0x00010000UL ) != 0UL )
	{
		tick_1ms_flag = 1;
	}
}
