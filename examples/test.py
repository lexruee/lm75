import time
from tentacle_pi.LM75 import LM75
lm = LM75(0x48,"/dev/i2c-2")

for x in range(0,10):
        temperature = lm.temperature()
        print "temperature: %0.2f" % temperature
        time.sleep(2)

