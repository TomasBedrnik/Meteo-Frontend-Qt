#!/bin/bash
for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 40 41 42 43 44 45 46 47 48 49 50
do
  wget -O ./App/images/$i.png http://api.met.no/weatherapi/weathericon/1.1/?symbol=$i\;content_type=image/png
done