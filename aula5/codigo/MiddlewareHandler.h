/*
 * MiddlewareHandler.h
 *
 *  Created on: 23 de jun de 2018
 *      Author: UCS
 */


#include <stdint.h>

#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

typedef int8_t (*MiddlewareFunc) (uint8_t *in, uint8_t size);

void crop(uint8_t *in_out, uint8_t start, uint8_t count);

#endif
