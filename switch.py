import Adafruit_BBIO.GPIO as GPIO
import time
import subprocess
import os

GPIO.setup("P8_8", GPIO.IN)
GPIO.setup("P8_18", GPIO.OUT)
GPIO.setup("P8_17",GPIO.OUT)
GPIO.output("P8_17",GPIO.LOW)
GPIO.output("P8_18", GPIO.LOW)

old_switch_state = 0

while True:
	new_switch_state = GPIO.input("P8_8")
	if new_switch_state == 1 and old_switch_state == 0 :
		print('You pressed the button!')
		GPIO.output("P8_17",GPIO.HIGH)
		p = subprocess.check_call(['/GlucoseAnalyzer/run.sh'])
		print p
		if p == 0 :
			GPIO.output("P8_17",GPIO.LOW)
			GPIO.output("P8_18",GPIO.HIGH)
			time.sleep(5)
			GPIO.output("P8_18",GPIO.LOW)
	new_switch_state = old_switch_state
