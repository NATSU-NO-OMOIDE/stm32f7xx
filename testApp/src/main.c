#include "PIOdriver.h"
#include "type.h"

int main(void)
{
	uint8_t status  = PIO_PORT_GROUP_D_12;
	uint8_t gpio_lv = PIO_SIGNAL_LV_L;

	/* �|�[�g�h���C�o�������� */
	PIO_init();

	while(1)
	{
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

		/* wait 1s�̂���*/
		for(int i = 0; i < 16000000; i++)
		{
			__asm("nop");
		}
	}

	return (0);
}
