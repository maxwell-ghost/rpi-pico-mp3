#ifndef _OLED_H
#define _OLED_H

/*
----------------------------------------------------------------
关于屏幕的各种功能在此模块内实现，底层接口是hal库。
向上层提供抽象
----------------------------------------------------------------
*/

#include "hal.h"
#include "pinmap.h"
#include "audio.h"
#include "rpi_time.h"

struct item {
    char name[10]; // 最多为9个字符加一个'\0'
    uint8_t name_len; // name长度，最大为9
    struct music m;

};

/*
oled reset，初始化之前必须调用
*/
void oled_reset();

/*
oled初始化，在GPIO管脚初始化完成后调用
*/ 
void oled_init();

/*
这个函数应该被定时调用，16ms调用一次来刷新屏幕
在系统定时中断中调用
*/
void oled_refresh();

/*
用颜色填充整个屏幕
*/
void oled_fill(bool white);

/*
用颜色填充一个矩形
*/
void oled_fill_rect(bool white, uint8_t x, uint8_t y, uint8_t w, uint8_t h);

/*
绘制图片，格式和字体格式一样
x:0-127 y:0-63
w:1-15 y:1-7, 
*/
void oled_draw_img(bool white, uint8_t *img, uint8_t x, uint8_t y, uint8_t w, uint8_t h);

void oled_draw_img_block(bool white, uint8_t *img, uint8_t x, uint8_t y);

/*
展示8x8的所有的字体，屏幕为128x64 -> 16x8个字
*/ 
void oled_show_font(bool white);

/*
绘制固定大小(8x8)的字。 x: 0~15, y: 0-7 
*/
void oled_draw_fix_text(const char* str, uint8_t len, uint8_t x, uint8_t y);

/*
绘制点。x: 0~127, y: 0-63
white如果为false则绘制黑色的点
*/
void oled_draw_point(bool white, uint8_t x, uint8_t y);

/*
绘制任意大小的字。x: 0~127, y: 0-63
size为1表示8x8
size为2表示16x16
size为3表示24x24
x与y表示字的左上角
*/
void oled_draw_char(bool white, const char c, uint8_t size, uint8_t x, uint8_t y);

/*
绘制文本，任意大小。x: 0到(127-8), y: 0到(63-8)
*/
void oled_draw_text(bool white, const char *str, uint8_t len, uint8_t size, uint8_t x, uint8_t y);

/*
绘制有间距的固定大小(8x8)的文本，间距为1
x: 0~16 y: 0-6
*/
void oled_draw_spacing_fix_text(bool white, const char *str, uint8_t len, uint8_t x, uint8_t y);

/*
绘制size大小的矩形点
size为1表示1x1
size为2表示2x2
*/
void oled_draw_rect_point(bool white, uint8_t size, uint8_t x, uint8_t y);


static inline int abs(int x) {return (x > 0) ? x : -x; }

/*
绘制线段
x0 y0 表示起始
x1 y1 表示结束
*/
void oled_draw_line(bool white, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);


/*
----------------------------------------------------------------
以下为UI功能
*/

/*
绘制列表, 会擦去 8,0(像素点) -> 79,63 矩形区域内的内容
list_len最大不超过7
*/
void ui_draw_list(bool white, uint8_t list_len, struct item *item_p);

/*
绘制cursor, cursor_pos 为 0-6
*/

void ui_draw_cursor(bool white, uint8_t cursor_pos);

/*
绘制icon, '.mp3'
*/

void ui_draw_icon();


#endif