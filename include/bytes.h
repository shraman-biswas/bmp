#ifndef BYTES_H
#define BYTES_H

#include <stdio.h>
#include <stdint.h>

void fgetb(uint8_t *s, uint32_t size, FILE *stream);
void printb(uint8_t *s, uint32_t size, int pkng);

#endif