#!/bin/bash
sleep 2
mount /dev/sda /media/usb0
sleep 2
./newtest dataoutput.txt settings.txt
sleep 2
umount /media/usb0