#!/bin/bash
./test /GlucoseAnalyzer/dataoutput.txt /GlucoseAnalyzer/settings.txt
sleep 3
gnuplot plot
