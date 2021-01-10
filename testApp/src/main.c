#include "PIOdriver.h"
#include "type.h"

int main(void)
{
	uint8_t status  = PIO_PORT_GROUP_D_12;
	uint8_t gpio_lv = PIO_SIGNAL_LV_L;

	/* ポートドライバを初期化 */
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

		/* ポート読み込み */
		gpio_lv = PIO_read(status);

		/* 読み込んだポートの値を反転させて書き込み */
		PIO_write(status, ~gpio_lv);

		/* wait 1sのつもり*/
		for(int i = 0; i < 16000000; i++)
		{
			__asm("nop");
		}
	}

	return (0);
}
