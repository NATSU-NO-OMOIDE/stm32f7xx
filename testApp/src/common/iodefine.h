/*
 * iodefine.h
 *
 *  Created on: 2021/01/03
 *      Author: NATSU_NO_OMOIDE
 */

#ifndef SRC_COMMON_IODEFINE_H_
#define SRC_COMMON_IODEFINE_H_

/*********************************************************************
 * include files.
*********************************************************************/
#include "type.h"

/*********************************************************************
 * structures.
*********************************************************************/
typedef struct	/* GPIOレジスタ構造 */
{
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;
} ST_REG_GPIO;

/*********************************************************************
 * defines.
*********************************************************************/
#define REG_RCC_AHB1ENR	( *( ( uint32_t* )0x40023830 ) )
#define REG_GPIO_D		( *( ( ST_REG_GPIO* )0x40020C00 ) )

#endif /* SRC_COMMON_IODEFINE_H_ */
