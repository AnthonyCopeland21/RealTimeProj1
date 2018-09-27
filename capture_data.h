#ifndef CAPTUREDATA_H
#define CAPTUREDATA_H

#include "startup.h"
#include <stdio.h>


int capture_data(void);
uint32_t convert_to_time(uint32_t data_point);
void print_data(uint32_t *data);


#endif // CAPTUREDATA_H
