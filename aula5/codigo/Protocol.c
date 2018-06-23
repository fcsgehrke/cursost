/*
 * Protocol.c
 *
 *  Created on: 23 de jun de 2018
 *      Author: UCS
 */

#include "Protocol.h"

#define MIDDLEWARE_COUNT 3

uint8_t rx_data_buffer[255];
uint8_t tx_data_buffer[255];

uint8_t operation;

MiddlewareFunc middlewares[MIDDLEWARE_COUNT];
VarIOCallback _callback;

int8_t Integrity_Middleware  (uint8_t *in, uint8_t size);
int8_t Operation_Middleware  (uint8_t *in, uint8_t size);
int8_t Data_Middleware  (uint8_t *in, uint8_t size);

void Protocol_Init(VarIOCallback callback)
{
	// vai aqui
	middlewares[0] = Integrity_Middleware;
	middlewares[1] = Operation_Middleware;
	middlewares[2] = Data_Middleware;

	_callback = callback;
}

uint8_t Protocol_BuildFrame(int8_t error_code, uint32_t value, uint8_t *out)
{
	int8_t i, size = 0;

	*out = PROTOCOL_START;
	out++;
	size++;

	*out = error_code;
	out++;
	size++;


	if (error_code >= 0)
	{
		for (i = 3; i >= 0; i--)
		{
			*out = ((uint8_t *)&value)[i];
			out++;
			size++;
		}
	}

	*out = PROTOCOL_END;
	size++;

	return size;
}

void Protocol_Receive(uint8_t *data, uint8_t size)
{
	uint8_t i;
	int8_t err;


	// Copy Data
	strncpy(rx_data_buffer, data, size);
	err = size;

	for (i = 0; i < MIDDLEWARE_COUNT; i++)
	{
		err = middlewares[i](rx_data_buffer, err);

		if (err < 0)
			break;
	}
}

int8_t Integrity_Middleware  (uint8_t *in, uint8_t size)
{
	if (in[0] == PROTOCOL_START && in[size - 1] == PROTOCOL_END)
	{
		crop(in, 1, size - 2);
		return size - 2;
	}
	return -1;
}

int8_t Operation_Middleware  (uint8_t *in, uint8_t size)
{
	if (in[0] == OP_READ || in[0] == OP_WRITE)
	{
		operation = in[0];
		crop(in, 1, size - 1);
		return size - 1;
	}
	return -1;
}

int8_t Data_Middleware  (uint8_t *in, uint8_t size)
{
	uint8_t i, var;
	uint32_t data = 0;

	var = *in;

	if (operation == OP_WRITE)
	{
		in++;
		for (i = 0; i < 4; i++)
		{
			data += *in;
			data <<= 8;
			in++;
		}

		_callback(operation, var, data);

		return 0;
	}
	else if (operation == OP_READ)
	{
		data = _callback(operation, var, 0);

		size = Protocol_BuildFrame(0, 8, tx_data_buffer);
		CDC_Transmit_FS(tx_data_buffer, size);
	}
	return -1;
}

