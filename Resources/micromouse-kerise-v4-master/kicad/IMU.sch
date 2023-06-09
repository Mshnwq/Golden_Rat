EESchema Schematic File Version 4
LIBS:KERISE-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 13 15
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 4200 2400 0    100  ~ 0
AXIS Sensor
$Comp
L KERISE:ICM-20602 U6
U 1 1 592C611A
P 5600 3400
AR Path="/57CC33F6/592C611A" Ref="U6"  Part="1" 
AR Path="/5A18D4D6/592C611A" Ref="U7"  Part="1" 
F 0 "U7" H 5600 4150 60  0000 C CNN
F 1 "ICM-20602" H 5600 4000 60  0000 C CNN
F 2 "mouse:ICM-20602" H 5600 4000 60  0001 C CNN
F 3 "" H 5600 4000 60  0000 C CNN
	1    5600 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C17
U 1 1 592C613A
P 4800 3700
AR Path="/57CC33F6/592C613A" Ref="C17"  Part="1" 
AR Path="/5A18D4D6/592C613A" Ref="C23"  Part="1" 
F 0 "C23" H 4810 3770 50  0000 L CNN
F 1 "0.1u" H 4810 3620 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 4800 3700 50  0001 C CNN
F 3 "" H 4800 3700 50  0000 C CNN
	1    4800 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C16
U 1 1 592C6186
P 4600 3700
AR Path="/57CC33F6/592C6186" Ref="C16"  Part="1" 
AR Path="/5A18D4D6/592C6186" Ref="C22"  Part="1" 
F 0 "C22" H 4610 3770 50  0000 L CNN
F 1 "0.1u" H 4610 3620 50  0000 L CNN
F 2 "Capacitor_SMD:C_0201_0603Metric" H 4600 3700 50  0001 C CNN
F 3 "" H 4600 3700 50  0000 C CNN
	1    4600 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR058
U 1 1 592C63E1
P 5000 4200
AR Path="/57CC33F6/592C63E1" Ref="#PWR058"  Part="1" 
AR Path="/5A18D4D6/592C63E1" Ref="#PWR069"  Part="1" 
F 0 "#PWR069" H 5000 3950 50  0001 C CNN
F 1 "GND" H 5000 4050 50  0000 C CNN
F 2 "" H 5000 4200 50  0000 C CNN
F 3 "" H 5000 4200 50  0000 C CNN
	1    5000 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR056
U 1 1 592C640D
P 4800 4200
AR Path="/57CC33F6/592C640D" Ref="#PWR056"  Part="1" 
AR Path="/5A18D4D6/592C640D" Ref="#PWR067"  Part="1" 
F 0 "#PWR067" H 4800 3950 50  0001 C CNN
F 1 "GND" H 4800 4050 50  0000 C CNN
F 2 "" H 4800 4200 50  0000 C CNN
F 3 "" H 4800 4200 50  0000 C CNN
	1    4800 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR055
U 1 1 592C6444
P 4600 4200
AR Path="/57CC33F6/592C6444" Ref="#PWR055"  Part="1" 
AR Path="/5A18D4D6/592C6444" Ref="#PWR066"  Part="1" 
F 0 "#PWR066" H 4600 3950 50  0001 C CNN
F 1 "GND" H 4600 4050 50  0000 C CNN
F 2 "" H 4600 4200 50  0000 C CNN
F 3 "" H 4600 4200 50  0000 C CNN
	1    4600 4200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR057
U 1 1 592C64FB
P 5000 2800
AR Path="/57CC33F6/592C64FB" Ref="#PWR057"  Part="1" 
AR Path="/5A18D4D6/592C64FB" Ref="#PWR068"  Part="1" 
F 0 "#PWR068" H 5000 2650 50  0001 C CNN
F 1 "+3.3V" H 5000 2940 50  0000 C CNN
F 2 "" H 5000 2800 50  0000 C CNN
F 3 "" H 5000 2800 50  0000 C CNN
	1    5000 2800
	1    0    0    -1  
$EndComp
Text HLabel 6100 3100 2    60   Input ~ 0
MISO
NoConn ~ 6100 3300
$Comp
L power:GND #PWR059
U 1 1 592C6B85
P 6200 3500
AR Path="/57CC33F6/592C6B85" Ref="#PWR059"  Part="1" 
AR Path="/5A18D4D6/592C6B85" Ref="#PWR070"  Part="1" 
F 0 "#PWR070" H 6200 3250 50  0001 C CNN
F 1 "GND" H 6200 3350 50  0000 C CNN
F 2 "" H 6200 3500 50  0000 C CNN
F 3 "" H 6200 3500 50  0000 C CNN
	1    6200 3500
	1    0    0    -1  
$EndComp
Text HLabel 6100 3000 2    60   Input ~ 0
MOSI
Text HLabel 6100 3200 2    60   Input ~ 0
CS
Text HLabel 6100 2900 2    60   Input ~ 0
SCLK
Wire Wire Line
	4600 3000 5000 3000
Wire Wire Line
	4600 4200 4600 3800
Wire Wire Line
	4800 3200 5100 3200
Wire Wire Line
	4800 3600 4800 3200
Wire Wire Line
	4800 4200 4800 3800
Connection ~ 5000 4100
Connection ~ 5000 3600
Wire Wire Line
	5000 3500 5100 3500
Connection ~ 5000 3700
Wire Wire Line
	5000 3600 5100 3600
Connection ~ 5000 3800
Wire Wire Line
	5000 3700 5100 3700
Connection ~ 5000 3900
Wire Wire Line
	5100 3800 5000 3800
Wire Wire Line
	5000 3900 5100 3900
Wire Wire Line
	5000 3500 5000 3600
Wire Wire Line
	5000 4100 5100 4100
Wire Wire Line
	4600 3000 4600 3600
Wire Wire Line
	6100 3400 6200 3400
Wire Wire Line
	6200 3400 6200 3500
Connection ~ 5000 2900
Wire Wire Line
	5000 2900 5100 2900
Connection ~ 5000 3000
Wire Wire Line
	5000 2800 5000 2900
Wire Wire Line
	5000 4100 5000 4200
Wire Wire Line
	5000 3600 5000 3700
Wire Wire Line
	5000 3700 5000 3800
Wire Wire Line
	5000 3800 5000 3900
Wire Wire Line
	5000 3900 5000 4100
Wire Wire Line
	5000 2900 5000 3000
Wire Wire Line
	5000 3000 5100 3000
$EndSCHEMATC
