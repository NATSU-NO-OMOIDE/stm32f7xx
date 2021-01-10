#ifndef PIO_DRIVER_H
#define PIO_DRIVER_H

/*********************************************************************
 * include files.
*********************************************************************/
#include "type.h"

/*********************************************************************
 * defines.
*********************************************************************/
#define PIO_SIGNAL_LV_H	( 255u )	/* 信号レベル ： H */
#define PIO_SIGNAL_LV_L	(   0u )	/* 信号レベル ： L */

/*********************************************************************
 * enumeration.
*********************************************************************/
typedef enum
{
	PIO_PORT_GROUP_D_12 = 0,
	PIO_PORT_GROUP_D_13,
	PIO_PORT_GROUP_D_14,
	PIO_PORT_GROUP_D_15,
	PIO_PORT_GROUP_NUM
} PIO_PORT_GROUP_ID;

/*********************************************************************
 * prototypes.
*********************************************************************/
extern void PIO_init(void);							/* ドライバ初期化機能 */
extern void PIO_write(PIO_PORT_GROUP_ID, uint8_t);	/* ポート書き込み機能 */
extern uint8_t PIO_read(PIO_PORT_GROUP_ID);			/* ポート読み込み機能 */

#endif
