#!/bin/bash
./test data.csv dataoutput.txt settings.txt
sleep 3
gnuplot plot
