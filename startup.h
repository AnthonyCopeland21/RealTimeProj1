#ifndef STARTUP_H
#define STARTUP_H

#include "capture_data.h"
#include "LED.h"
#include "stm32l476xx.h"
#include "SysClock.h"
#include "UART.h"

// define constants PASS and FAIL for returning from functions
#define PASS 1
#define FAIL 0

void timer_startup(void);
int post(void);

#endif // STARTUP_H