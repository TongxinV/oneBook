/**
 *@Description:<p>ImagePlayer</p>
 *@author TongxinV
 *@time 2017-02-10 09:26:09 
 */

#include <stdio.h>

#include <framebuffer.h>


int main(void)
{
	struct framebuffer fb0;

	fb0.fd = -1;
	fb0.pfb= NULL;
	fb0.open  = fb_open;
	fb0.close = fb_close;

	struct draw_info draw_info0;

	draw_info0.width = 1024;
	draw_info0.height=  600;
	draw_info0.color =  RED;
	
	printf("hello world.\n");

	fb0.open(&fb0);

	fb_draw_back(&draw_info0, &fb0);

	fb0.close(&fb0);
	
	return 0;
}



























