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

typedef struct
{
	uint32_t CTRL;
	uint32_t LOAD;
	uint32_t VAL;
	uint32_t CALIB;
} ST_REG_STK;

/*********************************************************************
 * defines.
*********************************************************************/
#define REG_REG_RCC_AHB1ENR_BASE_ADDR	(0x40023830)
#define REG_GPIO_D_BASE_ADDR			(0x40020C00)
#define REG_STK_BASE_ADDR				(0xE000E010)

#define REG_RCC_AHB1ENR	( *( ( uint32_t* )REG_REG_RCC_AHB1ENR_BASE_ADDR ) )
#define REG_GPIO_D		( *( ( ST_REG_GPIO* )REG_GPIO_D_BASE_ADDR ) )
#define REG_STK			( *( ( ST_REG_STK* )REG_STK_BASE_ADDR ) )

#endif /* SRC_COMMON_IODEFINE_H_ */
