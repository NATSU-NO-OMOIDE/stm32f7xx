#include "PIOdriver.h"
#include "SysTick.h"
#include "type.h"

extern uint8_t tick_1ms_flag;

int main(void)
{
	uint8_t status  = PIO_PORT_GROUP_D_12;
	uint8_t gpio_lv = PIO_SIGNAL_LV_L;
	static uint32_t tick_1sec_flag = 0;

	/* ポートドライバを初期化 */
	PIO_init();
	/* OSタイマドライバを初期 */
	SysTick_init();

	/* OSタイマ開始 */
	SysTick_start();

	while(1)
	{
		/* 1msTick割り込みがあった場合 */
		if(tick_1ms_flag == 1)
		{
			tick_1ms_flag = 0;
			tick_1sec_flag++;
		}

		/* 1sec経過していなかった場合 */
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

		/* ポート読み込み */
		gpio_lv = PIO_read(status);

		/* 読み込んだポートの値を反転させて書き込み */
		PIO_write(status, ~gpio_lv);
	}

	return (0);
}
