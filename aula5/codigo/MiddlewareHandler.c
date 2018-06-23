/*
 * MiddlewareHandler.c
 *
 *  Created on: 23 de jun de 2018
 *      Author: UCS
 */

#include "MiddlewareHandler.h"

void crop(uint8_t *in_out, uint8_t start, uint8_t count)
{
	uint8_t i;

	if (count > 0)
	{
		for (i = 0; i < count; i++)
		{
			*in_out = *((uint8_t *)(in_out + start));
			in_out++;
		}
	}
}


