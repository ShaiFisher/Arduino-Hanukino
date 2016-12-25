#ifndef MYLED_H
#define MYLED_H

#include "Switchable.h"

class MyLed : public Switchable
{
	public:
		MyLed(const int pin);
};

#endif //__LED_H
