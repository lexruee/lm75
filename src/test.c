#include "lm75.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
	char *i2c_device = "/dev/i2c-2";
	int address = 0x48;
	
	void *lm = lm75_init(address, i2c_device);
	
	if(lm != NULL){
		int i;
		for(i = 0; i < 10; i++) {
			float t = lm75_temperature(lm);
			printf("t = %f\n", t);
			usleep(2 * 1000 * 1000);
		}
	
		lm75_close(lm);
	}
	
	return 0;
}
