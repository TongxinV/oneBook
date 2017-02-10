#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_



// 宏定义
#define FBDEVICE	"/dev/fb0"
 
#define WIDTH		1024	
#define HEIGHT		600
 
 
#define WHITE		0xffffffff			// test ok
#define BLACK		0x00000000
#define RED			0xffff0000
#define GREEN		0xff00ff00			// test ok
#define BLUE		0xff0000ff			

#define GREENP		0x0000ff00			// 一样，说明前2个ff透明位不起作用
 

struct framebuffer{
	int fd;
	unsigned int *pfb;
	int  (*open)(struct framebuffer *fb);
	void (*close)(struct framebuffer *fb);
};

struct draw_info{
	unsigned int width;
	unsigned int height;
	unsigned int color;
};

// 函数声明
int  fb_open(struct framebuffer *fb);
void fb_close(struct framebuffer *fb);
void fb_draw_back(struct draw_info *draw_info, struct framebuffer *fb);




#endif /*_FRAMEBUFFER_H_*/





















