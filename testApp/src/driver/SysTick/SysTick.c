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

/* OS�^�C�}�h���C�o������ */
void SysTick_init(void)
{
	REG_STK.VAL  = 0;		/* �J�E���^�̌��ݒl���N���A */
	REG_STK.LOAD = 16000;	/* �J�E���g�_�E���J�n�ʒu��ݒ�(1ms = 16000(16MHz) ) */
	REG_STK.CTRL = 0x6;		/* ���䃌�W�X�^��ݒ� */
							/*  - 2bit : �N���b�N�\�[�X�Ƀv���Z�b�T��N���b�N�iAHB�j��ݒ� */
							/*  - 1bit : SysTick ��O�v����L�� */
							/*  - 0bit : �J�E���^��~ */

	tick_1ms_flag = 0;
}

/* OS�^�C�}�J�n */
void SysTick_start(void)
{
	REG_STK.CTRL |= 0x1;	/* �J�E���^�J�n */
}

/* OS�^�C�}��~ */
void SysTick_stop(void)
{
	REG_STK.CTRL &= ~(0x1);	/* �J�E���^��~ */
}

/* ���荞�݃n���h�� */
void SysTick_Handler(void)
{
	if ( ( REG_STK.CTRL & 0x00010000UL ) != 0UL )
	{
		tick_1ms_flag = 1;
	}
}
