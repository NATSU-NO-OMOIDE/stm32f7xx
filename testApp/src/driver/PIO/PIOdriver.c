/*********************************************************************
 * include files.
*********************************************************************/
#include "PIOdriver.h"
#include "type.h"
#include "iodefine.h"

typedef struct
{
	uint32_t port_reg_addr;
	uint8_t  port_idx;
} PIO_PORTSET;

static PIO_PORTSET s_pio_port_config_table[PIO_PORT_GROUP_NUM] =
{
	{ REG_GPIO_D_BASE_ADDR, 12 },
	{ REG_GPIO_D_BASE_ADDR, 13 },
	{ REG_GPIO_D_BASE_ADDR, 14 },
	{ REG_GPIO_D_BASE_ADDR, 15 }
};

/* PIOドライバ初期化処理 */
void PIO_init(void)
{
	ST_REG_GPIO* port_reg;
	uint8_t      port_idx;

	/* IOポート D にクロックを供給 */
	REG_RCC_AHB1ENR |= 0x8;

	for(int i = 0; i < PIO_PORT_GROUP_NUM; i++)
	{
		/* ポートグループのレジスタアドレスとポート番号を取得 */
		port_reg = (ST_REG_GPIO*)s_pio_port_config_table[i].port_reg_addr;
		port_idx = s_pio_port_config_table[i].port_idx;

		/* ポートモードを汎用出力モードに設定 */
		port_reg->MODER |= ( 1 << ( port_idx * 2 ) );

		/* ポート出力スピードを高速に設定 */
		port_reg->OSPEEDR |= ( ( 1 << ( port_idx * 2 ) )
						  |    ( 1 << ( ( port_idx * 2 ) + 1 ) ) );
	}
}

/* PIOドライバ書き込み機能 */
void PIO_write(PIO_PORT_GROUP_ID port_group_id, uint8_t lv)
{
	ST_REG_GPIO* port_reg;
	uint8_t      port_idx;

	/* ポートグループのレジスタアドレスとポート番号を取得 */
	port_reg = ( ST_REG_GPIO* )s_pio_port_config_table[port_group_id].port_reg_addr;
	port_idx = s_pio_port_config_table[port_group_id].port_idx;

	/* Lだった場合 */
	if( lv == PIO_SIGNAL_LV_L )
	{
		port_reg->ODR &= ~( 1 << port_idx );
	}
	/* Hだった場合 */
	else
	{
		port_reg->ODR |= ( 1 << port_idx );
	}
}

/* PIOドライバ読み込み機能 */
uint8_t PIO_read(PIO_PORT_GROUP_ID port_group_id)
{
	ST_REG_GPIO* port_reg;
	uint8_t      port_idx;
	uint8_t 	 lv;

	/* ポートグループのレジスタアドレスとポート番号を取得 */
	port_reg = (ST_REG_GPIO*)s_pio_port_config_table[port_group_id].port_reg_addr;
	port_idx = s_pio_port_config_table[port_group_id].port_idx;

	/* Lだった場合 */
	if( ( ( port_reg->ODR >> port_idx ) & 0x1 ) == PIO_SIGNAL_LV_L )
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
