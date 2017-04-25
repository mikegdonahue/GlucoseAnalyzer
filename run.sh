#!/bin/bash
sleep 0.1
mount /dev/sda1 /media/usb0
sleep 1
./test dataoutput.txt settings.txt
sleep 3
gnuplot plot
mv -f index.html /GlucoseAnalyzer/site/
aws s3 sync /GlucoseAnalyzer/site/ s3://michaelgdonahue.com/
sleep 0.2
umount /media/usb0
