#ifndef DSP0401B_h
#define DSP0401B_h

#define SEG_Z 0x0000
#define SEG_A 0x0080
#define SEG_B 0x0400
#define SEG_C 0x0020
#define SEG_D 0x0040
#define SEG_E 0x0100
#define SEG_F 0x0200
#define SEG_G 0x0800
#define SEG_H 0x0010
#define SEG_I 0x0100
#define SEG_J 0x0008
#define SEG_K 0x0002
#define SEG_L 0x0001
#define SEG_M 0x4000
#define SEG_N 0x2000
#define SEG_O 0x0004
#define SEG_P 0x8000

#include "Arduino.h"
#include "charmap.h"

class DSP0401B {
	public:
		DSP0401B();
		void begin(unsigned int num_disp, unsigned int sdi_pin, 
				unsigned int clk_pin, unsigned int le_pin, unsigned int oe_pin);
		void brightness(unsigned char brightlvl);
		void clear();
		void sendtext(String text);
		void slidetext(String text, unsigned long pause);

	private:
		void shiftcharmap(uint8_t idx);
		void latch_pulse();
		void shift(unsigned int pattern);
		unsigned int SDI;
		unsigned int CLK;
		unsigned int LE;
		unsigned int OE;
		unsigned int NUM;
		
};

#endif

