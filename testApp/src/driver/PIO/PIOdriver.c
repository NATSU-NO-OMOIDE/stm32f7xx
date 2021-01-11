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

/* PIO�h���C�o���������� */
void PIO_init(void)
{
	ST_REG_GPIO* port_reg;
	uint8_t      port_idx;

	/* IO�|�[�g D �ɃN���b�N������ */
	REG_RCC_AHB1ENR |= 0x8;

	for(int i = 0; i < PIO_PORT_GROUP_NUM; i++)
	{
		/* �|�[�g�O���[�v�̃��W�X�^�A�h���X�ƃ|�[�g�ԍ����擾 */
		port_reg = (ST_REG_GPIO*)s_pio_port_config_table[i].port_reg_addr;
		port_idx = s_pio_port_config_table[i].port_idx;

		/* �|�[�g���[�h��ėp�o�̓��[�h�ɐݒ� */
		port_reg->MODER |= ( 1 << ( port_idx * 2 ) );

		/* �|�[�g�o�̓X�s�[�h�������ɐݒ� */
		port_reg->OSPEEDR |= ( ( 1 << ( port_idx * 2 ) )
						  |    ( 1 << ( ( port_idx * 2 ) + 1 ) ) );
	}
}

/* PIO�h���C�o�������݋@�\ */
void PIO_write(PIO_PORT_GROUP_ID port_group_id, uint8_t lv)
{
	ST_REG_GPIO* port_reg;
	uint8_t      port_idx;

	/* �|�[�g�O���[�v�̃��W�X�^�A�h���X�ƃ|�[�g�ԍ����擾 */
	port_reg = ( ST_REG_GPIO* )s_pio_port_config_table[port_group_id].port_reg_addr;
	port_idx = s_pio_port_config_table[port_group_id].port_idx;

	/* L�������ꍇ */
	if( lv == PIO_SIGNAL_LV_L )
	{
		port_reg->ODR &= ~( 1 << port_idx );
	}
	/* H�������ꍇ */
	else
	{
		port_reg->ODR |= ( 1 << port_idx );
	}
}

/* PIO�h���C�o�ǂݍ��݋@�\ */
uint8_t PIO_read(PIO_PORT_GROUP_ID port_group_id)
{
	ST_REG_GPIO* port_reg;
	uint8_t      port_idx;
	uint8_t 	 lv;

	/* �|�[�g�O���[�v�̃��W�X�^�A�h���X�ƃ|�[�g�ԍ����擾 */
	port_reg = (ST_REG_GPIO*)s_pio_port_config_table[port_group_id].port_reg_addr;
	port_idx = s_pio_port_config_table[port_group_id].port_idx;

	/* L�������ꍇ */
	if( ( ( port_reg->ODR >> port_idx ) & 0x1 ) == PIO_SIGNAL_LV_L )
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
