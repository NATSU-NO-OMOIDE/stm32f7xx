#include "PIOdriver.h"
#include "type.h"

int main(void)
{
	/* ポートドライバを初期化 */
	PIO_init();

	while(1)
	{
		/* 読み込んだポートの値を反転させて書き込み */
		PIO_write( ~PIO_read() );

		/* wait 1sのつもり*/
		for(int i = 0; i < 16000000; i++)
		{
			__asm("nop");
		}
	}

	return (0);
}
