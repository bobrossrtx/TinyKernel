/**
 * @file errno.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <drivers/vga/vga.h>
#include <kernel/errno.h>
#include <kernel/stdio.h>
#include <sys/utils.h>

void kprint_error(char* errcode, char* errmsg)
{
	char* out[7] = {"[", "X", "] ", errmsg, " ", errcode, "\n"};
	
	for (uint16 i = 0; i < 7; ++i)
	{
		if (strcmp(out[i], "X") == 0)
			vga_set_default_color(vga_create_color(BLACK, RED));
		kprint(out[i]);
		vga_set_default_color(vga_create_color(BLACK, WHITE));
	}
}

/*
 * hlt = TRUE || FALSE*/
int kpanic(int errcode, char* errmsg, int hlt)
{
	vga_set_default_color(vga_create_color(BLACK, WHITE));
	vga_putchar('\n');
  char code[16];
  itoa(errcode, code);
  kprint_error(code, errmsg);

  if (hlt == TRUE)
  {
    kprint("Halting kernel processes. Please restart system.\n");
    for(;;) {}
  }
  
  return errcode;
}
