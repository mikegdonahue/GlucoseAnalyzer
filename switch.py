import Adafruit_BBIO.GPIO as GPIO
import time
import subprocess
import os

GPIO.setup("P8_10", GPIO.IN)
GPIO.setup("P8_18", GPIO.OUT)
GPIO.output("P8_18", GPIO.LOW)

old_switch_state = 0

while True:
	new_switch_state = GPIO.input("P8_10")
	if new_switch_state == 1 and old_switch_state == 0 :
		print('You pressed the button!')
		p = subprocess.check_call(['/GlucoseAnalyzer/run.sh'])
		print p
		if p == 0 :
			GPIO.output("P8_18",GPIO.HIGH)
			time.sleep(5)
			GPIO.output("P8_18",GPIO.LOW)
	new_switch_state = old_switch_state
