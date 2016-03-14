#ifndef BYTES_H
#define BYTES_H

#include <stdio.h>
#include <stdint.h>

void fgetb(uint8_t *bytes, int size, FILE *stream);
void printb(uint8_t *bytes, int size, int pkng);

#endif