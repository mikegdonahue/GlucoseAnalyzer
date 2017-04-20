# GlucoseAnalyzer
Glucose Data Analysis for Beagle Bone Black
Developed by: Justin Schmidt and Michael Donahue

# Important Notes:
Beagle Bone requires a USB mount for the device to be recognized when plugged in.
This could be developed manually or with various packages available for download.
However, the program will not work if the device is not mounted properly.
Also note the settings file provided with the files, this is vital for allowing the program to run and more user friendly than hardcoding everything the user may want to do.
Below (by line) is what the settings could do:
1.	Number of days to pull and calculate (note this cannot be above 120 days) (Default: 30)
2.	The exact path of the data file (data.csv)
# USING THE PROGRAM WITHOUT PUSH BUTTON…
You could run this program where ever you have it placed by running the command:
./test dataoutput.txt settings.txt
The program should run normally.
# USING THE PROGRAM WITH PUSH BUTTON…
This is a bit more complicated but you would need to start the switch.py by:
python switch.py
Once the button is pressed it should call another script called run.sh which will launch the program as usual. 

