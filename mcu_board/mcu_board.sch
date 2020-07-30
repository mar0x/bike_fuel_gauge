EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DCDC-D-SUN:D-SUN PS1
U 1 1 5F19CF59
P 6300 4100
F 0 "PS1" H 6300 4467 50  0000 C CNN
F 1 "D-SUN" H 6300 4376 50  0000 C CNN
F 2 "lib:Converter_DCDC_D_SUN_THT" H 5250 3850 50  0001 L CNN
F 3 "https://www.xppower.com/pdfs/SF_ITX.pdf" H 7350 3800 50  0001 L CNN
	1    6300 4100
	1    0    0    -1  
$EndComp
$Comp
L promicro:ProMicro U1
U 1 1 5F19D56B
P 4050 4500
F 0 "U1" H 4050 5643 60  0000 C CNN
F 1 "ProMicro" H 4050 5537 60  0000 C CNN
F 2 "lib:ProMicro" H 4050 5431 60  0000 C CNN
F 3 "" H 4150 3450 60  0000 C CNN
	1    4050 4500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5F19E49E
P 3400 6000
F 0 "SW1" H 3400 6193 50  0000 C CNN
F 1 "SW_Push" H 3400 6194 50  0001 C CNN
F 2 "Button_Switch_THT:SW_Tactile_SPST_Angled_PTS645Vx58-2LFS" H 3400 6200 50  0001 C CNN
F 3 "~" H 3400 6200 50  0001 C CNN
	1    3400 6000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5F19EA50
P 3150 6100
F 0 "#PWR0101" H 3150 5850 50  0001 C CNN
F 1 "GND" H 3155 5927 50  0000 C CNN
F 2 "" H 3150 6100 50  0001 C CNN
F 3 "" H 3150 6100 50  0001 C CNN
	1    3150 6100
	1    0    0    -1  
$EndComp
Text GLabel 3800 6000 2    50   Output ~ 0
EMPTY
$Comp
L Device:R R1
U 1 1 5F19F1AD
P 3700 5750
F 0 "R1" H 3770 5788 50  0000 L CNN
F 1 "39k" V 3700 5700 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3630 5750 50  0001 C CNN
F 3 "~" H 3700 5750 50  0001 C CNN
	1    3700 5750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 5F19F712
P 3700 5500
F 0 "#PWR0102" H 3700 5350 50  0001 C CNN
F 1 "+5V" H 3715 5673 50  0000 C CNN
F 2 "" H 3700 5500 50  0001 C CNN
F 3 "" H 3700 5500 50  0001 C CNN
	1    3700 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5F19FFEB
P 5800 4350
F 0 "#PWR0103" H 5800 4100 50  0001 C CNN
F 1 "GND" H 5805 4177 50  0000 C CNN
F 2 "" H 5800 4350 50  0001 C CNN
F 3 "" H 5800 4350 50  0001 C CNN
	1    5800 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5F1A03BA
P 6800 4350
F 0 "#PWR0104" H 6800 4100 50  0001 C CNN
F 1 "GND" H 6805 4177 50  0000 C CNN
F 2 "" H 6800 4350 50  0001 C CNN
F 3 "" H 6800 4350 50  0001 C CNN
	1    6800 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 4200 5800 4200
Wire Wire Line
	5800 4200 5800 4350
Wire Wire Line
	6700 4200 6800 4200
Wire Wire Line
	6800 4200 6800 4350
$Comp
L power:+5V #PWR0105
U 1 1 5F1A0936
P 6800 3850
F 0 "#PWR0105" H 6800 3700 50  0001 C CNN
F 1 "+5V" H 6815 4023 50  0000 C CNN
F 2 "" H 6800 3850 50  0001 C CNN
F 3 "" H 6800 3850 50  0001 C CNN
	1    6800 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0106
U 1 1 5F1A10F8
P 5800 3850
F 0 "#PWR0106" H 5800 3700 50  0001 C CNN
F 1 "+12V" H 5815 4023 50  0000 C CNN
F 2 "" H 5800 3850 50  0001 C CNN
F 3 "" H 5800 3850 50  0001 C CNN
	1    5800 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3850 5800 4000
Wire Wire Line
	5800 4000 5900 4000
Wire Wire Line
	6700 4000 6800 4000
Wire Wire Line
	6800 4000 6800 3850
Wire Wire Line
	3150 6100 3150 6000
Wire Wire Line
	3150 6000 3200 6000
Wire Wire Line
	3600 6000 3700 6000
Wire Wire Line
	3700 5900 3700 6000
Connection ~ 3700 6000
Wire Wire Line
	3700 6000 3800 6000
Wire Wire Line
	3700 5500 3700 5600
$Comp
L Switch:SW_Push SW2
U 1 1 5F1A41D7
P 4550 6000
F 0 "SW2" H 4550 6193 50  0000 C CNN
F 1 "SW_Push" H 4550 6194 50  0001 C CNN
F 2 "Button_Switch_THT:SW_Tactile_SPST_Angled_PTS645Vx58-2LFS" H 4550 6200 50  0001 C CNN
F 3 "~" H 4550 6200 50  0001 C CNN
	1    4550 6000
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5F1A41E1
P 4300 6100
F 0 "#PWR0107" H 4300 5850 50  0001 C CNN
F 1 "GND" H 4305 5927 50  0000 C CNN
F 2 "" H 4300 6100 50  0001 C CNN
F 3 "" H 4300 6100 50  0001 C CNN
	1    4300 6100
	1    0    0    -1  
$EndComp
Text GLabel 4950 6000 2    50   Output ~ 0
FULL
$Comp
L Device:R R2
U 1 1 5F1A41EC
P 4850 5750
F 0 "R2" H 4920 5788 50  0000 L CNN
F 1 "39k" V 4850 5700 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4780 5750 50  0001 C CNN
F 3 "~" H 4850 5750 50  0001 C CNN
	1    4850 5750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 5F1A41F6
P 4850 5500
F 0 "#PWR0108" H 4850 5350 50  0001 C CNN
F 1 "+5V" H 4865 5673 50  0000 C CNN
F 2 "" H 4850 5500 50  0001 C CNN
F 3 "" H 4850 5500 50  0001 C CNN
	1    4850 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 6100 4300 6000
Wire Wire Line
	4300 6000 4350 6000
Wire Wire Line
	4750 6000 4850 6000
Wire Wire Line
	4850 5900 4850 6000
Connection ~ 4850 6000
Wire Wire Line
	4850 6000 4950 6000
Wire Wire Line
	4850 5500 4850 5600
$Comp
L Connector:Conn_01x11_Male J1
U 1 1 5F1A5AD5
P 1350 4200
F 0 "J1" H 1350 4850 50  0000 C CNN
F 1 "Conn_01x11_Male" H 1458 4790 50  0001 C CNN
F 2 "led_lib:PCBEdge_x11" H 1350 4200 50  0001 C CNN
F 3 "~" H 1350 4200 50  0001 C CNN
	1    1350 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5F1A6A6D
P 1700 4750
F 0 "#PWR0109" H 1700 4500 50  0001 C CNN
F 1 "GND" H 1705 4577 50  0000 C CNN
F 2 "" H 1700 4750 50  0001 C CNN
F 3 "" H 1700 4750 50  0001 C CNN
	1    1700 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 4700 1700 4700
Wire Wire Line
	1700 4700 1700 4750
Text GLabel 1550 3700 2    50   Input ~ 0
LED1
Text GLabel 1550 3800 2    50   Input ~ 0
LED2
Text GLabel 1550 3900 2    50   Input ~ 0
LED3
Text GLabel 1550 4000 2    50   Input ~ 0
LED4
Text GLabel 1550 4100 2    50   Input ~ 0
LED5
Text GLabel 1550 4200 2    50   Input ~ 0
LED6
Text GLabel 1550 4300 2    50   Input ~ 0
LED7
Text GLabel 1550 4400 2    50   Input ~ 0
LED8
Text GLabel 1550 4500 2    50   Input ~ 0
LED9
Text GLabel 1550 4600 2    50   Input ~ 0
LED10
$Comp
L Device:R R11
U 1 1 5F1ACCF3
P 3100 4850
F 0 "R11" V 3150 4950 50  0000 L CNN
F 1 "330" V 3100 4800 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3030 4850 50  0001 C CNN
F 3 "~" H 3100 4850 50  0001 C CNN
	1    3100 4850
	0    1    1    0   
$EndComp
Text GLabel 2850 4850 0    50   Output ~ 0
LED1
$Comp
L Device:R R9
U 1 1 5F1AE00E
P 3100 4750
F 0 "R9" V 3150 4850 50  0000 L CNN
F 1 "330" V 3100 4700 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3030 4750 50  0001 C CNN
F 3 "~" H 3100 4750 50  0001 C CNN
	1    3100 4750
	0    1    1    0   
$EndComp
Text GLabel 2850 4750 0    50   Output ~ 0
LED2
$Comp
L Device:R R7
U 1 1 5F1AE597
P 3100 4650
F 0 "R7" V 3150 4750 50  0000 L CNN
F 1 "330" V 3100 4600 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3030 4650 50  0001 C CNN
F 3 "~" H 3100 4650 50  0001 C CNN
	1    3100 4650
	0    1    1    0   
$EndComp
Text GLabel 2850 4650 0    50   Output ~ 0
LED3
$Comp
L Device:R R5
U 1 1 5F1AE5A2
P 3100 4550
F 0 "R5" V 3150 4650 50  0000 L CNN
F 1 "330" V 3100 4500 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3030 4550 50  0001 C CNN
F 3 "~" H 3100 4550 50  0001 C CNN
	1    3100 4550
	0    1    1    0   
$EndComp
Text GLabel 2850 4550 0    50   Output ~ 0
LED4
$Comp
L Device:R R4
U 1 1 5F1AEBEB
P 3100 4450
F 0 "R4" V 3150 4550 50  0000 L CNN
F 1 "330" V 3100 4400 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3030 4450 50  0001 C CNN
F 3 "~" H 3100 4450 50  0001 C CNN
	1    3100 4450
	0    1    1    0   
$EndComp
Text GLabel 2850 4450 0    50   Output ~ 0
LED5
$Comp
L Device:R R3
U 1 1 5F1AEBF6
P 5000 4850
F 0 "R3" V 5050 4950 50  0000 L CNN
F 1 "330" V 5000 4800 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4930 4850 50  0001 C CNN
F 3 "~" H 5000 4850 50  0001 C CNN
	1    5000 4850
	0    -1   -1   0   
$EndComp
Text GLabel 5250 4850 2    50   Output ~ 0
LED6
Wire Wire Line
	3350 4850 3250 4850
Wire Wire Line
	3350 4750 3250 4750
Wire Wire Line
	3350 4650 3250 4650
Wire Wire Line
	3350 4550 3250 4550
Wire Wire Line
	3350 4450 3250 4450
Wire Wire Line
	4750 4850 4850 4850
Wire Wire Line
	5150 4850 5250 4850
Wire Wire Line
	2850 4450 2950 4450
Wire Wire Line
	2950 4550 2850 4550
Wire Wire Line
	2850 4650 2950 4650
Wire Wire Line
	2950 4750 2850 4750
Wire Wire Line
	2850 4850 2950 4850
$Comp
L Device:R R6
U 1 1 5F1B47D7
P 5000 4750
F 0 "R6" V 5050 4850 50  0000 L CNN
F 1 "330" V 5000 4700 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4930 4750 50  0001 C CNN
F 3 "~" H 5000 4750 50  0001 C CNN
	1    5000 4750
	0    -1   -1   0   
$EndComp
Text GLabel 5250 4750 2    50   Output ~ 0
LED7
$Comp
L Device:R R8
U 1 1 5F1B47E2
P 5000 4650
F 0 "R8" V 5050 4750 50  0000 L CNN
F 1 "330" V 5000 4600 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4930 4650 50  0001 C CNN
F 3 "~" H 5000 4650 50  0001 C CNN
	1    5000 4650
	0    -1   -1   0   
$EndComp
Text GLabel 5250 4650 2    50   Output ~ 0
LED8
$Comp
L Device:R R10
U 1 1 5F1B47ED
P 5000 4550
F 0 "R10" V 5050 4650 50  0000 L CNN
F 1 "330" V 5000 4500 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4930 4550 50  0001 C CNN
F 3 "~" H 5000 4550 50  0001 C CNN
	1    5000 4550
	0    -1   -1   0   
$EndComp
Text GLabel 5250 4550 2    50   Output ~ 0
LED9
$Comp
L Device:R R12
U 1 1 5F1B47F8
P 5000 4450
F 0 "R12" V 5050 4550 50  0000 L CNN
F 1 "330" V 5000 4400 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4930 4450 50  0001 C CNN
F 3 "~" H 5000 4450 50  0001 C CNN
	1    5000 4450
	0    -1   -1   0   
$EndComp
Text GLabel 5250 4450 2    50   Output ~ 0
LED10
Wire Wire Line
	4750 4750 4850 4750
Wire Wire Line
	4750 4650 4850 4650
Wire Wire Line
	4750 4550 4850 4550
Wire Wire Line
	4750 4450 4850 4450
Wire Wire Line
	5150 4450 5250 4450
Wire Wire Line
	5250 4550 5150 4550
Wire Wire Line
	5150 4650 5250 4650
Wire Wire Line
	5250 4750 5150 4750
$Comp
L power:+5V #PWR0110
U 1 1 5F1BFF32
P 5050 3650
F 0 "#PWR0110" H 5050 3500 50  0001 C CNN
F 1 "+5V" H 5065 3823 50  0000 C CNN
F 2 "" H 5050 3650 50  0001 C CNN
F 3 "" H 5050 3650 50  0001 C CNN
	1    5050 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 4050 5050 4050
Wire Wire Line
	5050 4050 5050 3650
$Comp
L power:GND #PWR0111
U 1 1 5F1C170B
P 4900 3850
F 0 "#PWR0111" H 4900 3600 50  0001 C CNN
F 1 "GND" H 4905 3677 50  0001 C CNN
F 2 "" H 4900 3850 50  0001 C CNN
F 3 "" H 4900 3850 50  0001 C CNN
	1    4900 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 3850 4900 3850
$Comp
L power:GND #PWR0112
U 1 1 5F1C2B30
P 3150 4050
F 0 "#PWR0112" H 3150 3800 50  0001 C CNN
F 1 "GND" H 3155 3877 50  0001 C CNN
F 2 "" H 3150 4050 50  0001 C CNN
F 3 "" H 3150 4050 50  0001 C CNN
	1    3150 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 4050 3150 4050
Wire Wire Line
	3350 3950 3150 3950
Wire Wire Line
	3150 3950 3150 4050
Connection ~ 3150 4050
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 5F177973
P 1350 5400
F 0 "J2" H 1458 5589 50  0000 C CNN
F 1 "Conn_01x03_Male" H 1458 5590 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1350 5400 50  0001 C CNN
F 3 "~" H 1350 5400 50  0001 C CNN
	1    1350 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0113
U 1 1 5F177FEE
P 1700 5250
F 0 "#PWR0113" H 1700 5100 50  0001 C CNN
F 1 "+12V" H 1715 5423 50  0000 C CNN
F 2 "" H 1700 5250 50  0001 C CNN
F 3 "" H 1700 5250 50  0001 C CNN
	1    1700 5250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5F178645
P 1700 5550
F 0 "#PWR0114" H 1700 5300 50  0001 C CNN
F 1 "GND" H 1705 5377 50  0000 C CNN
F 2 "" H 1700 5550 50  0001 C CNN
F 3 "" H 1700 5550 50  0001 C CNN
	1    1700 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 5300 1700 5300
Wire Wire Line
	1700 5300 1700 5250
Wire Wire Line
	1550 5500 1700 5500
Wire Wire Line
	1700 5500 1700 5550
Text GLabel 2150 5750 2    50   Output ~ 0
SENSOR
Text GLabel 2950 3850 0    50   Input ~ 0
SENSOR
Text GLabel 2950 4350 0    50   Input ~ 0
EMPTY
Text GLabel 2950 4150 0    50   Input ~ 0
FULL
Wire Wire Line
	2950 4350 3350 4350
Wire Wire Line
	2950 3850 3350 3850
Wire Wire Line
	2950 4150 3350 4150
$Comp
L power:+5V #PWR0115
U 1 1 5F18FADF
P 2500 4200
F 0 "#PWR0115" H 2500 4050 50  0001 C CNN
F 1 "+5V" H 2515 4373 50  0000 C CNN
F 2 "" H 2500 4200 50  0001 C CNN
F 3 "" H 2500 4200 50  0001 C CNN
	1    2500 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 4200 2500 4250
Wire Wire Line
	2500 4250 3350 4250
$Comp
L Device:R R13
U 1 1 5F191FF0
P 1950 5550
F 0 "R13" H 2020 5588 50  0000 L CNN
F 1 "100k" V 1950 5500 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1880 5550 50  0001 C CNN
F 3 "~" H 1950 5550 50  0001 C CNN
	1    1950 5550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R14
U 1 1 5F196E2C
P 1950 5950
F 0 "R14" H 1750 6000 50  0000 L CNN
F 1 "100k" V 1950 5900 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1880 5950 50  0001 C CNN
F 3 "~" H 1950 5950 50  0001 C CNN
	1    1950 5950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5F197762
P 1950 6100
F 0 "#PWR0116" H 1950 5850 50  0001 C CNN
F 1 "GND" H 1955 5927 50  0000 C CNN
F 2 "" H 1950 6100 50  0001 C CNN
F 3 "" H 1950 6100 50  0001 C CNN
	1    1950 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 5400 1950 5400
Wire Wire Line
	1950 5700 1950 5750
Wire Wire Line
	1950 5750 2100 5750
Connection ~ 1950 5750
Wire Wire Line
	1950 5750 1950 5800
$Comp
L power:GND #PWR0117
U 1 1 5F1A0E64
P 5650 4350
F 0 "#PWR0117" H 5650 4100 50  0001 C CNN
F 1 "GND" H 5655 4177 50  0001 C CNN
F 2 "" H 5650 4350 50  0001 C CNN
F 3 "" H 5650 4350 50  0001 C CNN
	1    5650 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 4350 5650 4350
Wire Wire Line
	4750 4250 5650 4250
Wire Wire Line
	5650 4250 5650 4350
Connection ~ 5650 4350
Wire Wire Line
	4750 4150 5650 4150
Wire Wire Line
	5650 4150 5650 4250
Connection ~ 5650 4250
$Comp
L Device:R R15
U 1 1 5F1B6B25
P 2100 5950
F 0 "R15" H 2150 6000 50  0000 L CNN
F 1 "100k" V 2100 5900 39  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2030 5950 50  0001 C CNN
F 3 "~" H 2100 5950 50  0001 C CNN
	1    2100 5950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F1B7AD7
P 2100 6100
F 0 "#PWR?" H 2100 5850 50  0001 C CNN
F 1 "GND" H 2105 5927 50  0000 C CNN
F 2 "" H 2100 6100 50  0001 C CNN
F 3 "" H 2100 6100 50  0001 C CNN
	1    2100 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 5800 2100 5750
Connection ~ 2100 5750
Wire Wire Line
	2100 5750 2150 5750
$EndSCHEMATC