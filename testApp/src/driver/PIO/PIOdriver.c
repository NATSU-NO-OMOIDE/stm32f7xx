/*********************************************************************
 * include files.
*********************************************************************/
#include "PIOdriver.h"
#include "type.h"
#include "iodefine.h"

/* PIO�h���C�o���������� */
void PIO_init(void)
{
	/* IO�|�[�g D �ɃN���b�N������ */
	REG_RCC_AHB1ENR |= 0x8;

	/* PD12�̃|�[�g���[�h��ėp�o�̓��[�h�ɐݒ� */
	REG_GPIO_D.MODER |= ( 1 << 24 );

	/* PD12�̃|�[�g�o�̓X�s�[�h�������ɐݒ� */
	REG_GPIO_D.OSPEEDR |= ( ( 1 << 24 ) | ( 1 << 25 ) );
}

/* PIO�h���C�o�������݋@�\ */
void PIO_write(uint8_t lv)
{
	/* L�������ꍇ */
	if( lv == PIO_SIGNAL_LV_L )
	{
		REG_GPIO_D.ODR &= ~( 1 << 12 );
	}
	/* H�������ꍇ */
	else
	{
		REG_GPIO_D.ODR |= ( 1 << 12 );
	}
}

/* PIO�h���C�o�ǂݍ��݋@�\ */
uint8_t PIO_read(void)
{
	uint8_t lv;

	/* L�������ꍇ */
	if( ( ( REG_GPIO_D.ODR >> 12 ) & 0x1 ) == PIO_SIGNAL_LV_L )
	{
		lv = PIO_SIGNAL_LV_L;
	}
	/* H�������ꍇ */
	else
	{
		lv = PIO_SIGNAL_LV_H;
	}

	return (lv);
}
