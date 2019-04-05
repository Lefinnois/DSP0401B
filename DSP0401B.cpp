/*
 * Copyright (C) 2015 Denis Bodor
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */


#include "DSP0401B.h"

DSP0401B::DSP0401B() {
}

void DSP0401B::begin(unsigned int num_disp, unsigned int sdi_pin,
		unsigned int clk_pin, unsigned int le_pin, unsigned int oe_pin) {

	SDI = sdi_pin;
	CLK = clk_pin;
	LE = le_pin;
	OE = oe_pin;
	NUM = num_disp;

	pinMode(CLK, OUTPUT);
	digitalWrite(CLK, LOW);

	pinMode(SDI, OUTPUT);

	pinMode(LE, OUTPUT);
	digitalWrite(LE, LOW);

	pinMode(OE, OUTPUT);
	analogWrite(OE,255);

	clear();
}

void DSP0401B::clear() {
	for(unsigned int i=0; i<NUM*4; i++) {
		shiftcharmap(' ');
	}
	latch_pulse();
}

void DSP0401B::shiftcharmap(uint8_t idx) {
	shift(pgm_read_word(charmap+idx));
}

void DSP0401B::brightness(unsigned char brightlvl) {
	analogWrite(OE, ~(brightlvl));
}

void DSP0401B::shift(unsigned int pattern) {
//	shiftOut(SDI, CLK, MSBFIRST, pattern >> 8);
	shiftOut(SDI, CLK, MSBFIRST, highByte(pattern));
	shiftOut(SDI, CLK, MSBFIRST, lowByte(pattern));
}

void DSP0401B::latch_pulse() {
	delayMicroseconds(50);
	digitalWrite(LE, HIGH);
	delayMicroseconds(50);
	digitalWrite(LE, LOW);
	delayMicroseconds(50);
}

void DSP0401B::sendtext(String text) {
	for(unsigned int i=0; i<NUM*4; i++) {
		if(i<text.length()) {
			shiftcharmap(text.charAt(i));
//			shiftcharmap((uint8_t)text[i]);
		} else {
			shiftcharmap(' ');
		}
	}
	latch_pulse();
}

void DSP0401B::slidetext(String text, unsigned long pause) {
	clear();
	for(unsigned int i=0; i<text.length(); i++) {
		shiftcharmap(text.charAt(i));
		latch_pulse();
		delay(pause);
	}
	for(unsigned int i=0; i<NUM*4; i++) {
		shiftcharmap(' ');
		latch_pulse();
		delay(pause);
	}
}

void DSP0401B::sendpattern(int num, ...) {
	va_list arguments;
	va_start (arguments, num);
	for (int x = 0; x<num; x++) {
		shift(va_arg(arguments, unsigned int));
	}
	va_end(arguments);
	latch_pulse();
}
