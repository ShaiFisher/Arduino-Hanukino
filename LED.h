#ifndef LED_H
#define LED_H

#include "Switchable.h"

class LED : public Switchable
{
	public:
		LED(const int pin);
};

#endif //__LED_H
