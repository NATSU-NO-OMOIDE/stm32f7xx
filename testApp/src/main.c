#include "PIOdriver.h"
#include "type.h"

int main(void)
{
	/* �|�[�g�h���C�o�������� */
	PIO_init();

	while(1)
	{
		/* �ǂݍ��񂾃|�[�g�̒l�𔽓]�����ď������� */
		PIO_write( ~PIO_read() );

		/* wait 1s�̂���*/
		for(int i = 0; i < 16000000; i++)
		{
			__asm("nop");
		}
	}

	return (0);
}
