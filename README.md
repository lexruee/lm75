# LM75

Raspberry Pi C driver for the sensor LM75.


## Example Usage

### C language

```c
#include "lm75.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
	char *i2c_device = "/dev/i2c-1";
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


```

## Python language

```python
import time
from tentacle_pi.LM75 import LM75
lm = LM75(0x48,"/dev/i2c-1")

for x in range(0,10):
        temperature = lm.temperature()
        print "temperature: %0.2f" % temperature
        time.sleep(2)


```


## Dependencies

* i2c-tools 
* libi2c-dev
* python-dev
