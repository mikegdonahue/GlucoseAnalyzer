#!/bin/bash
sleep 0.5
mv -f index.html /GlucoseAnalyzer/site/
aws s3 sync /GlucoseAnalyzer/site/ s3://michaelgdonahue.com/
sleep 0.5
