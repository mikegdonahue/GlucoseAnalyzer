#!/bin/bash
./test dataoutput.txt settings.txt
sleep 3
gnuplot plot
mv -f index.html /GlucoseAnalyzer/site/
aws s3 sync /GlucoseAnalyzer/site/ s3://michaelgdonahue.com/
