#!/usr/bin/python
# -*- coding: utf8 -*-

import matplotlib.pyplot as plt
import numpy as np
import serial

# Comand line argument parser
import argparse

# Constants
pulsesPerTurn = 2
data = []

# Arguments configuration
parser = argparse.ArgumentParser()
parser.add_argument('port', help='The serial port to communicate.')
parser.add_argument('baud', help='Baudrate in the serial port to communicate.')

args = parser.parse_args()

# Serial port configuration
ser = serial.Serial(args.port, args.baud) # Serial port configuration

for i in range(0,20):
    data.append(int(ser.readline().rstrip()))

    print "Received. value = ", data[i]

i+=1
j = int(max(data))+1

plt.plot(data, drawstyle='steps-pre')
plt.axhline(y=25, color='r', linestyle='-')
plt.ylabel("Pulsos por 600 ms")
plt.xlabel("Tempo (s)")
plt.axis([0, i, 0, j])
plt.show()