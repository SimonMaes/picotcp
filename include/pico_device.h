/*********************************************************************
PicoTCP. Copyright (c) 2012 TASS Belgium NV. Some rights reserved.
See LICENSE and COPYING for usage.
Do not redistribute without a written permission by the Copyright
holders.

*********************************************************************/
#ifndef _INCLUDE_PICO_DEVICE 
#define _INCLUDE_PICO_DEVICE 
#include "pico_queue.h"
#include "pico_frame.h"
#include "pico_addressing.h"
#include "rb.h"

#define MAX_DEVICE_NAME 16


struct pico_ethdev {
  struct pico_eth mac;
};

struct pico_device {
  char name[MAX_DEVICE_NAME];
  RB_ENTRY(pico_device) node;
  uint32_t hash;
  uint32_t overhead;
  struct pico_ethdev *eth; /* Null if non-ethernet */
  struct pico_queue *q_in;
  struct pico_queue *q_out;
  int (*send)(struct pico_device *self, void *buf, int len); /* Send function. Return 0 if busy */
  int (*poll)(struct pico_device *self, int loop_score);
  void(*destroy)(struct pico_device *self);
};

int pico_device_init(struct pico_device *dev, char *name, uint8_t *mac);
void pico_device_destroy(struct pico_device *dev);
int pico_devices_loop(int loop_score);
struct pico_device* pico_get_device(char* name);

#endif
