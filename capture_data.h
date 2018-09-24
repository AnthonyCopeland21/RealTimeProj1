#ifndef CAPTUREDATA_H
#define CAPTUREDATA_H

#include "startup.h"
#include <stdio.h>


int capture_data(void);
int convert_to_time(int data_point);
int get_data();
void print_data(int *data);


#endif // CAPTUREDATA_H