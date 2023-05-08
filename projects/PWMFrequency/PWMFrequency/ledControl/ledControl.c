/*
 * ledControl.c
 *
 * Created: 08.05.2023 20:19:35
 *  Author: Adrian
 */ 

#include "ledControl.h"

void change_pattern(int* pattern, int* direction)
{
	if (*direction == 1)
	{
		(*pattern)++;
		if (*pattern > 3)
		{
			*pattern = 3;
			*direction = 0;
		}
	}
	else
	{
		(*pattern)--;
		if (*pattern < 1)
		{
			*pattern = 1;
			*direction = 1;
		}
	}
}