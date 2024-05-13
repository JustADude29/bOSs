#ifndef _KERNEL_PIC_H
#define _KERNEL_PIC_H

#include <stdint.h>

void PIC_Configure(unsigned char offsetPIC1, unsigned char offsetPIC2);
void PIC_SendEndOfInterrupt(int irq);
void PIC_Disable();
void PIC_Mask(int irq);
void PIC_Unmask(int irq);
unsigned short PIC_ReadIrqRequestRegister();
unsigned short PIC_ReadInServiceRegister();

#endif // !_KERNEL_PIC_H
