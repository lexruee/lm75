/*
 * @author 	Alexander Rüedlinger <a.rueedlinger@gmail.com>
 * @date 	12.03.2015
 *
 * A C driver for the sensor lm75.
 *  
 */

#ifndef __LM75__
#define __LM75__
#include <stdint.h>
#include "lm75.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <time.h>
#include <math.h>
#endif

typedef struct {
	/* file descriptor */
	int file;
	
	/* i2c device address */
	int address;
	
	/* i2c device file path */
	char *i2c_device;
	
} lm75_t;


#define TO_S(x)	(lm75_t*) x

#define __LM75__DEBUG__
#ifdef __LM75__DEBUG__				
#define DEBUG(...)	printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif



/*
 * Prototypes for helper functions
 */

int lm75_set_addr(void *_s);
 

/*
 * Implemetation of the helper functions
 */
 


/*
 * Sets the address for the i2c device file.
 * 
 * @param lm75 sensor
 */
int lm75_set_addr(void *_s) {
	lm75_t* s = TO_S(_s);
	int error;

	if((error = ioctl(s->file, I2C_SLAVE, s->address)) < 0)
		DEBUG("error: ioctl() failed\n");

	return error;
}


/*
 * Implementation of the interface functions.
 */
 


/**
 * Creates a lm75 sensor object.
 *
 * @param i2c device address
 * @param i2c device file path
 * @return lm75 sensor
 */
void *lm75_init(int address, const char* i2c_device_filepath) {
	DEBUG("device: init using address %#x and i2cbus %s\n", address, i2c_device_filepath);
	
	void *_s = malloc(sizeof(lm75_t));
	if(_s == NULL)  {
		DEBUG("error: malloc returns NULL pointer\n");
		return NULL;
	}

	lm75_t *s = TO_S(_s);
	s->address = address;

	s->i2c_device = (char*) malloc(strlen(i2c_device_filepath) * sizeof(char));
	if(s->i2c_device == NULL) {
		DEBUG("error: malloc returns NULL pointer!\n");
		return NULL;
	}

	// copy string
	strcpy(s->i2c_device, i2c_device_filepath);
	
	// open i2c device
	int file;
	if((file = open(s->i2c_device, O_RDWR)) < 0) {
		DEBUG("error: %s open() failed\n", s->i2c_device);
		return NULL;
	}
	s->file = file;
	if(lm75_set_addr(s) < 0)
		return NULL;
	
	DEBUG("device: open ok\n");
	return _s;
}



/**
 * Closes a lm75 object.
 * 
 * @param lm75 sensor
 */
void lm75_close(void *_s) {
	DEBUG("close device\n");
	lm75_t *s = TO_S(_s);
	
	if(close(s->file) < 0)
		DEBUG("error: %s close() failed\n", s->i2c_device);
	
	free(s->i2c_device); // free string
	s->i2c_device = NULL;
	free(s); // free structure
	_s = NULL;
}



/**
 * Returns the measured temperature in celsius.
 * 
 * @param lm75 sensor
 * @return temperature
 */
float lm75_temperature(void *_s) {
	// TODO
	return 0.0;
}
