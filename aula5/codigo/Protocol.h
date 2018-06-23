/*
 * Protocol.h
 *
 *  Created on: 23 de jun de 2018
 *      Author: UCS
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "MiddlewareHandler.h"
#include "usbd_cdc_if.h"
#include <string.h>

typedef uint32_t (*VarIOCallback)(uint8_t op, uint8_t var, uint32_t data);

// Integrity
#define PROTOCOL_START	0x02 // STX
#define PROTOCOL_END	0x03 // ETX

// Operation
#define OP_READ			0x01
#define OP_WRITE		0x02

// Variables
#define VAR_INPUTS		0x01
#define VAR_OUPUTS		0x02
#define VAR_PARAM		0x03
#define VAR_ADC			0x04

void Protocol_Init(VarIOCallback callback);
void Protocol_Receive(uint8_t *data, uint8_t size);

#endif /* PROTOCOL_H_ */
