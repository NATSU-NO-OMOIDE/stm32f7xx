/*********************************************************************
 * include files.
*********************************************************************/
#include "PIOdriver.h"
#include "type.h"
#include "iodefine.h"

/* PIOドライバ初期化処理 */
void PIO_init(void)
{
	/* IOポート D にクロックを供給 */
	REG_RCC_AHB1ENR |= 0x8;

	/* PD12のポートモードを汎用出力モードに設定 */
	REG_GPIO_D.MODER |= ( 1 << 24 );

	/* PD12のポート出力スピードを高速に設定 */
	REG_GPIO_D.OSPEEDR |= ( ( 1 << 24 ) | ( 1 << 25 ) );
}

/* PIOドライバ書き込み機能 */
void PIO_write(uint8_t lv)
{
	/* Lだった場合 */
	if( lv == PIO_SIGNAL_LV_L )
	{
		REG_GPIO_D.ODR &= ~( 1 << 12 );
	}
	/* Hだった場合 */
	else
	{
		REG_GPIO_D.ODR |= ( 1 << 12 );
	}
}

/* PIOドライバ読み込み機能 */
uint8_t PIO_read(void)
{
	uint8_t lv;

	/* Lだった場合 */
	if( ( ( REG_GPIO_D.ODR >> 12 ) & 0x1 ) == PIO_SIGNAL_LV_L )
	{
		lv = PIO_SIGNAL_LV_L;
	}
	/* Hだった場合 */
	else
	{
		lv = PIO_SIGNAL_LV_H;
	}

	return (lv);
}
