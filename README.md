# Glucose Data Analysis for Beagle Bone Black

Developed by: Justin Schmidt and Michael Donahue

Overview

This project was developed on the Beagle Bone Black  Rev C using:

Description:    Debian GNU/Linux 8.7 (jessie) Release:        8.7 Codename:       jessie

We also used the following hardware for the push button/LEDS:

•	Half Breadboard

•	Jumper Cables (7 needed minimal for input/grnd/power)

•	4-220 resistors (alternatively you could use two 440 or above for LEDS)

•	1-1K resistor (for push button setup)

•	1-Pushbutton

•	2-LEDS(1-Green/1-Red)

The schematic for the breadboard could be found in the project files as schematic.
There was also a lot of apt-get installs for this project some important ones are GNU Plot and Amazon Web Services. GNU Plot is needed regardless (this usually comes pre-installed in newer Debian versions). The line in the run.sh which pushes to the amazon website will not work unless you have a proper setup see (http://docs.aws.amazon.com/gettingstarted/latest/awsgsg-intro/gsg-aws-tutorials.html).  However if you wish to still try the output without pushing to an amazon website you could just remove this line in the run.sh. This will still output the data to the local repository as well as the plot graph.

##### Also note that significant power is needed to prevent errors, we recommend using the BB with an AC Adapter and not power from the USB port, especially if you are using a USB Hub or Wi-Fi adapter. 

# Important Notes:
Beagle Bone requires a USB mount for the device to be recognized when plugged in.
This could be developed manually or with various packages available for download.
However, the program will not work if the device is not mounted properly.
Also note the settings file provided with the files, this is vital for allowing the program to run and more user friendly than hardcoding everything the user may want to do.
Below (by line) is what the settings could do:
1.	Number of days to pull and calculate (note this cannot be above 120 days) (Default: 30)
2.	The exact path of the data file (dariy.csv)


Note that if the settings file is left blank/null/empty it will default to 30 days and the current directory for the data file. One could also set the settings file to 0 and null for line 1 & 2 this will also use default settings. All other inputs will be considered valid and may result in the program not working properly. Ensure you only have an integer for the first line and a path name or file name for the second line.
#### USING THE PROGRAM WITHOUT PUSH BUTTON…
You could run this program where ever you have it placed by running the command:
test dataoutput.txt settings.txt
The program should run normally.
#### USING THE PROGRAM WITH PUSH BUTTON…
This is a bit more complicated but could be done with necessary hardware. 
Your pins need to be set up by the shown schematic and your board must support Adafruit.BBIO.GPIO. A python package most commonly available in newer python versions.

python switch.py

Once the button is pressed it should call another script called run.sh which will launch the program as usual.
Run.sh will mount any sda1 USB plugged into the Beagle Bone or hub. And will mount this USB to /media/usb0 after the script has fully run (without errors) it will then unmount this USB. 
