#include "PIOdriver.h"
#include "SysTick.h"
#include "type.h"

extern uint8_t tick_1ms_flag;

int main(void)
{
	uint8_t status  = PIO_PORT_GROUP_D_12;
	uint8_t gpio_lv = PIO_SIGNAL_LV_L;
	static uint32_t tick_1sec_flag = 0;

	/* �|�[�g�h���C�o�������� */
	PIO_init();
	/* OS�^�C�}�h���C�o������ */
	SysTick_init();

	/* OS�^�C�}�J�n */
	SysTick_start();

	while(1)
	{
		/* 1msTick���荞�݂��������ꍇ */
		if(tick_1ms_flag == 1)
		{
			tick_1ms_flag = 0;
			tick_1sec_flag++;
		}

		/* 1sec�o�߂��Ă��Ȃ������ꍇ */
		if(tick_1sec_flag != 1000)
		{
			continue;
		}
		tick_1sec_flag =  0;

		switch(status)
		{
		case PIO_PORT_GROUP_D_12:
			status = PIO_PORT_GROUP_D_13;
			break;
		case PIO_PORT_GROUP_D_13:
			status = PIO_PORT_GROUP_D_14;
			break;
		case PIO_PORT_GROUP_D_14:
			status = PIO_PORT_GROUP_D_15;
			break;
		case PIO_PORT_GROUP_D_15:
			status = PIO_PORT_GROUP_D_12;
			break;
		defualt:
			break;
		}

		/* �|�[�g�ǂݍ��� */
		gpio_lv = PIO_read(status);

		/* �ǂݍ��񂾃|�[�g�̒l�𔽓]�����ď������� */
		PIO_write(status, ~gpio_lv);
	}

	return (0);
}
