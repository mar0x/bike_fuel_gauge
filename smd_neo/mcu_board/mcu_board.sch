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
L MCU_Microchip_ATmega:ATmega32U4-AU U3
U 1 1 5F2FFA8D
P 6150 4250
F 0 "U3" H 6800 2500 50  0000 C CNN
F 1 "ATmega32U4-AU" H 6750 2400 50  0000 C CNN
F 2 "Package_QFP:TQFP-44_10x10mm_P0.8mm" H 6150 4250 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7766-8-bit-AVR-ATmega16U4-32U4_Datasheet.pdf" H 6150 4250 50  0001 C CNN
	1    6150 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5F332C5D
P 4650 2850
F 0 "C1" V 4421 2850 50  0000 C CNN
F 1 "22pF" V 4512 2850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4650 2850 50  0001 C CNN
F 3 "~" H 4650 2850 50  0001 C CNN
	1    4650 2850
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5F333A5B
P 4650 3250
F 0 "C2" V 4421 3250 50  0000 C CNN
F 1 "22pF" V 4512 3250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4650 3250 50  0001 C CNN
F 3 "~" H 4650 3250 50  0001 C CNN
	1    4650 3250
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x12_Male J1
U 1 1 5F33BDB1
P 7900 2000
F 0 "J1" H 8008 2681 50  0000 C CNN
F 1 "Conn_01x12_Male" H 8008 2590 50  0000 C CNN
F 2 "lib:PCBEdge_x12" H 7900 2000 50  0001 C CNN
F 3 "~" H 7900 2000 50  0001 C CNN
	1    7900 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 5F341D9F
P 10200 4100
F 0 "L1" V 10390 4100 50  0000 C CNN
F 1 "47uH" V 10299 4100 50  0000 C CNN
F 2 "Inductor_SMD:L_Bourns_SRN6045TA" H 10200 4100 50  0001 C CNN
F 3 "~" H 10200 4100 50  0001 C CNN
	1    10200 4100
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C3
U 1 1 5F342E6F
P 9800 3900
F 0 "C3" V 10029 3900 50  0000 C CNN
F 1 "10nF" V 9938 3900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9800 3900 50  0001 C CNN
F 3 "~" H 9800 3900 50  0001 C CNN
	1    9800 3900
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP_Small C5
U 1 1 5F3437ED
P 10550 4200
F 0 "C5" H 10638 4246 50  0000 L CNN
F 1 "68uF" H 10638 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_2816_7142Metric" H 10550 4200 50  0001 C CNN
F 3 "~" H 10550 4200 50  0001 C CNN
	1    10550 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C4
U 1 1 5F343DEC
P 8400 4200
F 0 "C4" H 8488 4246 50  0000 L CNN
F 1 "100uF" H 8488 4155 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 8400 4200 50  0001 C CNN
F 3 "~" H 8400 4200 50  0001 C CNN
	1    8400 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky D1
U 1 1 5F344CF5
P 9900 4300
F 0 "D1" V 9854 4379 50  0000 L CNN
F 1 "D_Schottky" V 9945 4379 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-323" H 9900 4300 50  0001 C CNN
F 3 "~" H 9900 4300 50  0001 C CNN
	1    9900 4300
	0    1    1    0   
$EndComp
$Comp
L Connector:USB_B_Micro J2
U 1 1 5F346941
P 1850 6050
F 0 "J2" H 1907 6517 50  0000 C CNN
F 1 "USB_B_Micro" H 1907 6426 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex_47346-0001" H 2000 6000 50  0001 C CNN
F 3 "~" H 2000 6000 50  0001 C CNN
	1    1850 6050
	1    0    0    -1  
$EndComp
$Comp
L Power_Protection:USBLC6-2SC6 U4
U 1 1 5F34930C
P 3100 6050
F 0 "U4" V 3500 6300 50  0000 C CNN
F 1 "USBLC6-2SC6" V 3750 6100 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 2350 6450 50  0001 C CNN
F 3 "http://www2.st.com/resource/en/datasheet/CD00050750.pdf" H 3300 6400 50  0001 C CNN
	1    3100 6050
	0    1    -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 5F34A74C
P 4050 5950
F 0 "R1" V 3950 5950 50  0000 C CNN
F 1 "22" V 4050 5950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3980 5950 50  0001 C CNN
F 3 "~" H 4050 5950 50  0001 C CNN
	1    4050 5950
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5F34A836
P 4050 6150
F 0 "R2" V 3950 6150 50  0000 C CNN
F 1 "22" V 4050 6150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3980 6150 50  0001 C CNN
F 3 "~" H 4050 6150 50  0001 C CNN
	1    4050 6150
	0    1    1    0   
$EndComp
$Comp
L Device:Polyfuse_Small F1
U 1 1 5F34B3A8
P 2200 5600
F 0 "F1" H 2268 5646 50  0000 L CNN
F 1 "Polyfuse_Small" H 2268 5555 50  0000 L CNN
F 2 "Fuse:Fuse_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 2250 5400 50  0001 L CNN
F 3 "~" H 2200 5600 50  0001 C CNN
	1    2200 5600
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5F34D040
P 9600 1850
F 0 "SW1" H 9600 2135 50  0000 C CNN
F 1 "SW_Push" H 9600 2044 50  0000 C CNN
F 2 "Button_Switch_THT:SW_Tactile_SPST_Angled_PTS645Vx58-2LFS" H 9600 2050 50  0001 C CNN
F 3 "~" H 9600 2050 50  0001 C CNN
	1    9600 1850
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 5F34D557
P 9600 2600
F 0 "SW2" H 9600 2885 50  0000 C CNN
F 1 "SW_Push" H 9600 2794 50  0000 C CNN
F 2 "Button_Switch_THT:SW_Tactile_SPST_Angled_PTS645Vx58-2LFS" H 9600 2800 50  0001 C CNN
F 3 "~" H 9600 2800 50  0001 C CNN
	1    9600 2600
	1    0    0    -1  
$EndComp
$Comp
L power:VBUS #PWR0101
U 1 1 5F3EFB49
P 2200 5400
F 0 "#PWR0101" H 2200 5250 50  0001 C CNN
F 1 "VBUS" H 2215 5573 50  0000 C CNN
F 2 "" H 2200 5400 50  0001 C CNN
F 3 "" H 2200 5400 50  0001 C CNN
	1    2200 5400
	1    0    0    -1  
$EndComp
$Comp
L power:VBUS #PWR0102
U 1 1 5F3F07E6
P 3600 5850
F 0 "#PWR0102" H 3600 5700 50  0001 C CNN
F 1 "VBUS" H 3615 6023 50  0000 C CNN
F 2 "" H 3600 5850 50  0001 C CNN
F 3 "" H 3600 5850 50  0001 C CNN
	1    3600 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5F3F1320
P 1850 6550
F 0 "#PWR0103" H 1850 6300 50  0001 C CNN
F 1 "GND" H 1855 6377 50  0000 C CNN
F 2 "" H 1850 6550 50  0001 C CNN
F 3 "" H 1850 6550 50  0001 C CNN
	1    1850 6550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5F3F15DA
P 2600 6150
F 0 "#PWR0104" H 2600 5900 50  0001 C CNN
F 1 "GND" H 2605 5977 50  0000 C CNN
F 2 "" H 2600 6150 50  0001 C CNN
F 3 "" H 2600 6150 50  0001 C CNN
	1    2600 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 6450 1850 6550
Wire Wire Line
	2600 6150 2600 6050
Wire Wire Line
	3600 6050 3600 5850
Wire Wire Line
	3200 5550 3900 5550
Wire Wire Line
	3900 5550 3900 5950
Wire Wire Line
	3200 6550 3900 6550
Wire Wire Line
	3900 6550 3900 6150
Wire Wire Line
	2150 6150 2400 6150
Wire Wire Line
	2400 6150 2400 6550
Wire Wire Line
	2400 6550 3000 6550
Wire Wire Line
	2150 6050 2400 6050
Wire Wire Line
	2400 6050 2400 5550
Wire Wire Line
	2400 5550 3000 5550
Wire Wire Line
	2150 5850 2200 5850
Wire Wire Line
	2200 5850 2200 5700
Wire Wire Line
	2200 5500 2200 5400
$Comp
L Regulator_Switching:LM2675M-5 U1
U 1 1 5F515233
P 9200 3900
F 0 "U1" H 9200 4367 50  0000 C CNN
F 1 "LM2675M-5" H 9200 4276 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9250 3550 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2675.pdf" H 9200 3900 50  0001 C CNN
	1    9200 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5F517D92
P 9900 4450
F 0 "#PWR0105" H 9900 4200 50  0001 C CNN
F 1 "GND" H 9905 4277 50  0000 C CNN
F 2 "" H 9900 4450 50  0001 C CNN
F 3 "" H 9900 4450 50  0001 C CNN
	1    9900 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5F518C3D
P 9200 4450
F 0 "#PWR0106" H 9200 4200 50  0001 C CNN
F 1 "GND" H 9205 4277 50  0000 C CNN
F 2 "" H 9200 4450 50  0001 C CNN
F 3 "" H 9200 4450 50  0001 C CNN
	1    9200 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5F518F62
P 8400 4450
F 0 "#PWR0107" H 8400 4200 50  0001 C CNN
F 1 "GND" H 8405 4277 50  0000 C CNN
F 2 "" H 8400 4450 50  0001 C CNN
F 3 "" H 8400 4450 50  0001 C CNN
	1    8400 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5F519265
P 10550 4450
F 0 "#PWR0108" H 10550 4200 50  0001 C CNN
F 1 "GND" H 10555 4277 50  0000 C CNN
F 2 "" H 10550 4450 50  0001 C CNN
F 3 "" H 10550 4450 50  0001 C CNN
	1    10550 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	10550 4300 10550 4450
Wire Wire Line
	9200 4300 9200 4450
Wire Wire Line
	8400 4450 8400 4300
Wire Wire Line
	8400 4100 8400 3700
Wire Wire Line
	8400 3700 8700 3700
Wire Wire Line
	9700 4100 9900 4100
Wire Wire Line
	9900 4150 9900 4100
Connection ~ 9900 4100
Wire Wire Line
	9900 4100 10050 4100
Wire Wire Line
	10350 4100 10550 4100
Wire Wire Line
	9900 3900 9900 4100
Wire Wire Line
	9700 3700 10550 3700
Wire Wire Line
	10550 3700 10550 4100
Connection ~ 10550 4100
$Comp
L Device:C_Small C7
U 1 1 5F51C782
P 6500 2100
F 0 "C7" V 6271 2100 50  0000 C CNN
F 1 "0.1uF" V 6362 2100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6500 2100 50  0001 C CNN
F 3 "~" H 6500 2100 50  0001 C CNN
	1    6500 2100
	0    1    1    0   
$EndComp
Text GLabel 4300 5950 2    50   Output ~ 0
D+
Text GLabel 4300 6150 2    50   Output ~ 0
D-
Wire Wire Line
	4200 5950 4300 5950
Wire Wire Line
	4200 6150 4300 6150
Text GLabel 5450 3750 0    50   Input ~ 0
D+
Text GLabel 5450 3850 0    50   Input ~ 0
D-
Wire Wire Line
	5450 3750 5550 3750
Wire Wire Line
	5450 3850 5550 3850
$Comp
L power:VBUS #PWR0109
U 1 1 5F5205BD
P 5300 3550
F 0 "#PWR0109" H 5300 3400 50  0001 C CNN
F 1 "VBUS" H 5300 3650 50  0000 C CNN
F 2 "" H 5300 3550 50  0001 C CNN
F 3 "" H 5300 3550 50  0001 C CNN
	1    5300 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3550 5550 3550
$Comp
L power:GND #PWR0110
U 1 1 5F521618
P 6150 6150
F 0 "#PWR0110" H 6150 5900 50  0001 C CNN
F 1 "GND" H 6155 5977 50  0000 C CNN
F 2 "" H 6150 6150 50  0001 C CNN
F 3 "" H 6150 6150 50  0001 C CNN
	1    6150 6150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5F522AF1
P 4350 3400
F 0 "#PWR0111" H 4350 3150 50  0001 C CNN
F 1 "GND" H 4355 3227 50  0000 C CNN
F 2 "" H 4350 3400 50  0001 C CNN
F 3 "" H 4350 3400 50  0001 C CNN
	1    4350 3400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5F523036
P 4900 3550
F 0 "#PWR0112" H 4900 3300 50  0001 C CNN
F 1 "GND" H 4905 3377 50  0000 C CNN
F 2 "" H 4900 3550 50  0001 C CNN
F 3 "" H 4900 3550 50  0001 C CNN
	1    4900 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C9
U 1 1 5F5239B8
P 4900 3450
F 0 "C9" H 4750 3400 50  0000 C CNN
F 1 "0.1uF" H 4700 3500 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4900 3450 50  0001 C CNN
F 3 "~" H 4900 3450 50  0001 C CNN
	1    4900 3450
	-1   0    0    1   
$EndComp
Wire Wire Line
	4900 3350 5550 3350
Wire Wire Line
	4750 2850 5000 2850
Wire Wire Line
	5000 2850 5000 2950
Wire Wire Line
	4750 3250 5000 3250
Wire Wire Line
	5000 3250 5000 3150
Wire Wire Line
	4550 3250 4350 3250
Wire Wire Line
	4350 3250 4350 3400
Wire Wire Line
	4550 2850 4350 2850
Wire Wire Line
	4350 2850 4350 3250
Connection ~ 4350 3250
$Comp
L Device:C_Small C10
U 1 1 5F52A15B
P 5200 4250
F 0 "C10" H 5050 4200 50  0000 C CNN
F 1 "1uF" H 5000 4300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5200 4250 50  0001 C CNN
F 3 "~" H 5200 4250 50  0001 C CNN
	1    5200 4250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5F52A607
P 5200 4450
F 0 "#PWR0113" H 5200 4200 50  0001 C CNN
F 1 "GND" H 5205 4277 50  0000 C CNN
F 2 "" H 5200 4450 50  0001 C CNN
F 3 "" H 5200 4450 50  0001 C CNN
	1    5200 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 4050 5200 4050
Wire Wire Line
	5200 4050 5200 4150
Wire Wire Line
	5200 4350 5200 4450
$Comp
L power:GND #PWR0114
U 1 1 5F52C47A
P 6950 2150
F 0 "#PWR0114" H 6950 1900 50  0001 C CNN
F 1 "GND" H 6955 1977 50  0000 C CNN
F 2 "" H 6950 2150 50  0001 C CNN
F 3 "" H 6950 2150 50  0001 C CNN
	1    6950 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 2100 6950 2100
Wire Wire Line
	6950 2100 6950 2150
$Comp
L Device:C_Small C6
U 1 1 5F52D649
P 6500 1700
F 0 "C6" V 6271 1700 50  0000 C CNN
F 1 "0.1uF" V 6362 1700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6500 1700 50  0001 C CNN
F 3 "~" H 6500 1700 50  0001 C CNN
	1    6500 1700
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C8
U 1 1 5F52DA5A
P 6500 2400
F 0 "C8" V 6271 2400 50  0000 C CNN
F 1 "0.1uF" V 6362 2400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6500 2400 50  0001 C CNN
F 3 "~" H 6500 2400 50  0001 C CNN
	1    6500 2400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5F52DF7F
P 6950 1700
F 0 "#PWR0115" H 6950 1450 50  0001 C CNN
F 1 "GND" H 6955 1527 50  0000 C CNN
F 2 "" H 6950 1700 50  0001 C CNN
F 3 "" H 6950 1700 50  0001 C CNN
	1    6950 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5F52E150
P 6950 2500
F 0 "#PWR0116" H 6950 2250 50  0001 C CNN
F 1 "GND" H 6955 2327 50  0000 C CNN
F 2 "" H 6950 2500 50  0001 C CNN
F 3 "" H 6950 2500 50  0001 C CNN
	1    6950 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 1700 6950 1700
Wire Wire Line
	6600 2400 6950 2400
Wire Wire Line
	6950 2400 6950 2500
$Comp
L power:+5V #PWR0117
U 1 1 5F53255A
P 6150 1500
F 0 "#PWR0117" H 6150 1350 50  0001 C CNN
F 1 "+5V" H 6165 1673 50  0000 C CNN
F 2 "" H 6150 1500 50  0001 C CNN
F 3 "" H 6150 1500 50  0001 C CNN
	1    6150 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 1500 6150 1700
Wire Wire Line
	6050 2450 6050 2400
Wire Wire Line
	6050 2400 6150 2400
Connection ~ 6150 2400
Wire Wire Line
	6150 2400 6150 2450
Wire Wire Line
	6250 2450 6250 2400
Wire Wire Line
	6250 2400 6150 2400
Wire Wire Line
	6400 2400 6250 2400
Connection ~ 6250 2400
Wire Wire Line
	6150 2100 6400 2100
Connection ~ 6150 2100
Wire Wire Line
	6150 2100 6150 2400
Wire Wire Line
	6400 1700 6150 1700
Connection ~ 6150 1700
Wire Wire Line
	6150 1700 6150 2100
$Comp
L Device:R R4
U 1 1 5F53E53B
P 5350 2250
F 0 "R4" V 5250 2250 50  0000 C CNN
F 1 "10k" V 5350 2250 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5280 2250 50  0001 C CNN
F 3 "~" H 5350 2250 50  0001 C CNN
	1    5350 2250
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR0118
U 1 1 5F53EC37
P 5350 1500
F 0 "#PWR0118" H 5350 1350 50  0001 C CNN
F 1 "+5V" H 5365 1673 50  0000 C CNN
F 2 "" H 5350 1500 50  0001 C CNN
F 3 "" H 5350 1500 50  0001 C CNN
	1    5350 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 1500 5350 2100
Wire Wire Line
	5350 2400 5350 2750
Wire Wire Line
	5350 2750 5550 2750
$Comp
L Device:R R7
U 1 1 5F541EE9
P 7400 5050
F 0 "R7" V 7300 5050 50  0000 C CNN
F 1 "10k" V 7400 5050 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7330 5050 50  0001 C CNN
F 3 "~" H 7400 5050 50  0001 C CNN
	1    7400 5050
	-1   0    0    1   
$EndComp
Wire Wire Line
	6050 6050 6050 6150
Wire Wire Line
	6050 6150 6150 6150
Wire Wire Line
	6150 6050 6150 6150
Connection ~ 6150 6150
$Comp
L power:GND #PWR0119
U 1 1 5F54557D
P 7400 5300
F 0 "#PWR0119" H 7400 5050 50  0001 C CNN
F 1 "GND" H 7405 5127 50  0000 C CNN
F 2 "" H 7400 5300 50  0001 C CNN
F 3 "" H 7400 5300 50  0001 C CNN
	1    7400 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 4850 7400 4850
Wire Wire Line
	7400 4850 7400 4900
Wire Wire Line
	7400 5200 7400 5300
Text GLabel 6750 2950 2    50   Output ~ 0
MOSI
Text GLabel 6750 2850 2    50   Input ~ 0
SCK
Text GLabel 6750 3050 2    50   Input ~ 0
MISO
Text GLabel 5250 2750 0    50   Input ~ 0
~RST
Wire Wire Line
	5250 2750 5350 2750
Connection ~ 5350 2750
$Comp
L power:+5V #PWR0120
U 1 1 5F54D78C
P 10800 3550
F 0 "#PWR0120" H 10800 3400 50  0001 C CNN
F 1 "+5V" H 10815 3723 50  0000 C CNN
F 2 "" H 10800 3550 50  0001 C CNN
F 3 "" H 10800 3550 50  0001 C CNN
	1    10800 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10550 4100 10800 4100
Wire Wire Line
	10800 4100 10800 3550
$Comp
L power:+12V #PWR0121
U 1 1 5F5503C9
P 7750 3500
F 0 "#PWR0121" H 7750 3350 50  0001 C CNN
F 1 "+12V" H 7765 3673 50  0000 C CNN
F 2 "" H 7750 3500 50  0001 C CNN
F 3 "" H 7750 3500 50  0001 C CNN
	1    7750 3500
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSS84 Q2
U 1 1 5F5531A0
P 3300 2750
F 0 "Q2" V 3549 2750 50  0000 C CNN
F 1 "BSS84" V 3640 2750 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3500 2675 50  0001 L CIN
F 3 "http://assets.nexperia.com/documents/data-sheet/BSS84.pdf" H 3300 2750 50  0001 L CNN
	1    3300 2750
	0    -1   1    0   
$EndComp
$Comp
L Transistor_FET:BSS84 Q1
U 1 1 5F555CCF
P 8100 3600
F 0 "Q1" V 8349 3600 50  0000 C CNN
F 1 "BSS84" V 8440 3600 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8300 3525 50  0001 L CIN
F 3 "http://assets.nexperia.com/documents/data-sheet/BSS84.pdf" H 8100 3600 50  0001 L CNN
	1    8100 3600
	0    -1   1    0   
$EndComp
$Comp
L power:VBUS #PWR0122
U 1 1 5F557421
P 2950 2600
F 0 "#PWR0122" H 2950 2450 50  0001 C CNN
F 1 "VBUS" H 2965 2773 50  0000 C CNN
F 2 "" H 2950 2600 50  0001 C CNN
F 3 "" H 2950 2600 50  0001 C CNN
	1    2950 2600
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0123
U 1 1 5F557CE4
P 3300 2550
F 0 "#PWR0123" H 3300 2400 50  0001 C CNN
F 1 "+12V" H 3315 2723 50  0000 C CNN
F 2 "" H 3300 2550 50  0001 C CNN
F 3 "" H 3300 2550 50  0001 C CNN
	1    3300 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0124
U 1 1 5F55833B
P 3600 2600
F 0 "#PWR0124" H 3600 2450 50  0001 C CNN
F 1 "+5V" H 3615 2773 50  0000 C CNN
F 2 "" H 3600 2600 50  0001 C CNN
F 3 "" H 3600 2600 50  0001 C CNN
	1    3600 2600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0125
U 1 1 5F55D219
P 8100 3400
F 0 "#PWR0125" H 8100 3250 50  0001 C CNN
F 1 "+5V" H 8115 3573 50  0000 C CNN
F 2 "" H 8100 3400 50  0001 C CNN
F 3 "" H 8100 3400 50  0001 C CNN
	1    8100 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5F55DA3D
P 7750 3900
F 0 "R6" V 7650 3900 50  0000 C CNN
F 1 "100k" V 7750 3900 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7680 3900 50  0001 C CNN
F 3 "~" H 7750 3900 50  0001 C CNN
	1    7750 3900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0126
U 1 1 5F55DF05
P 7750 4100
F 0 "#PWR0126" H 7750 3850 50  0001 C CNN
F 1 "GND" H 7755 3927 50  0000 C CNN
F 2 "" H 7750 4100 50  0001 C CNN
F 3 "" H 7750 4100 50  0001 C CNN
	1    7750 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3500 7750 3700
Wire Wire Line
	7900 3700 7750 3700
Connection ~ 7750 3700
Wire Wire Line
	7750 3700 7750 3750
Wire Wire Line
	8300 3700 8400 3700
Connection ~ 8400 3700
Wire Wire Line
	2950 2600 2950 2850
Wire Wire Line
	2950 2850 3100 2850
Wire Wire Line
	3500 2850 3600 2850
Wire Wire Line
	3600 2850 3600 2600
Wire Wire Line
	7750 4050 7750 4100
$Comp
L power:GND #PWR0127
U 1 1 5F577A35
P 9800 2750
F 0 "#PWR0127" H 9800 2500 50  0001 C CNN
F 1 "GND" H 9805 2577 50  0000 C CNN
F 2 "" H 9800 2750 50  0001 C CNN
F 3 "" H 9800 2750 50  0001 C CNN
	1    9800 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 2750 9800 2600
Text GLabel 9250 1850 0    50   Output ~ 0
SW1
Text GLabel 9250 2600 0    50   Output ~ 0
SW2
Wire Wire Line
	9250 1850 9300 1850
Wire Wire Line
	9250 2600 9300 2600
$Comp
L Device:R R3
U 1 1 5F586A53
P 9300 1550
F 0 "R3" V 9200 1550 50  0000 C CNN
F 1 "47k" V 9300 1550 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9230 1550 50  0001 C CNN
F 3 "~" H 9300 1550 50  0001 C CNN
	1    9300 1550
	-1   0    0    1   
$EndComp
$Comp
L Device:R R5
U 1 1 5F5877CE
P 9300 2300
F 0 "R5" V 9200 2300 50  0000 C CNN
F 1 "47k" V 9300 2300 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9230 2300 50  0001 C CNN
F 3 "~" H 9300 2300 50  0001 C CNN
	1    9300 2300
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR0128
U 1 1 5F587DA7
P 9300 2150
F 0 "#PWR0128" H 9300 2000 50  0001 C CNN
F 1 "+5V" H 9315 2323 50  0000 C CNN
F 2 "" H 9300 2150 50  0001 C CNN
F 3 "" H 9300 2150 50  0001 C CNN
	1    9300 2150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0129
U 1 1 5F588377
P 9300 1400
F 0 "#PWR0129" H 9300 1250 50  0001 C CNN
F 1 "+5V" H 9315 1573 50  0000 C CNN
F 2 "" H 9300 1400 50  0001 C CNN
F 3 "" H 9300 1400 50  0001 C CNN
	1    9300 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 1700 9300 1850
Connection ~ 9300 1850
Wire Wire Line
	9300 1850 9400 1850
Wire Wire Line
	9300 2450 9300 2600
Connection ~ 9300 2600
Wire Wire Line
	9300 2600 9400 2600
Wire Wire Line
	9800 1850 9800 2600
Connection ~ 9800 2600
Wire Wire Line
	1750 6450 1850 6450
Connection ~ 1850 6450
$Comp
L Device:Crystal_GND24_Small Y1
U 1 1 5F6D0BF1
P 5000 3050
F 0 "Y1" V 4954 3194 50  0000 L CNN
F 1 "Crystal_GND24_Small" V 5045 3194 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_EuroQuartz_MJ-4Pin_5.0x3.2mm_HandSoldering" H 5000 3050 50  0001 C CNN
F 3 "~" H 5000 3050 50  0001 C CNN
	1    5000 3050
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0130
U 1 1 5F6D5425
P 4800 3050
F 0 "#PWR0130" H 4800 2800 50  0001 C CNN
F 1 "GND" H 4805 2877 50  0000 C CNN
F 2 "" H 4800 3050 50  0001 C CNN
F 3 "" H 4800 3050 50  0001 C CNN
	1    4800 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0131
U 1 1 5F6DDE03
P 5200 3050
F 0 "#PWR0131" H 5200 2800 50  0001 C CNN
F 1 "GND" H 5205 2877 50  0000 C CNN
F 2 "" H 5200 3050 50  0001 C CNN
F 3 "" H 5200 3050 50  0001 C CNN
	1    5200 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3050 4900 3050
Wire Wire Line
	5100 3050 5200 3050
Wire Wire Line
	5550 2950 5000 2950
Connection ~ 5000 2950
Wire Wire Line
	5550 3150 5000 3150
Connection ~ 5000 3150
$Comp
L power:GND #PWR0132
U 1 1 5F6E9832
P 8350 2750
F 0 "#PWR0132" H 8350 2500 50  0001 C CNN
F 1 "GND" H 8355 2577 50  0000 C CNN
F 2 "" H 8350 2750 50  0001 C CNN
F 3 "" H 8350 2750 50  0001 C CNN
	1    8350 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 1600 8350 1600
Wire Wire Line
	8350 1600 8350 1800
Wire Wire Line
	8100 1800 8350 1800
Connection ~ 8350 1800
Wire Wire Line
	8350 1800 8350 2000
Wire Wire Line
	8100 2000 8350 2000
Connection ~ 8350 2000
Wire Wire Line
	8350 2000 8350 2200
Wire Wire Line
	8100 2200 8350 2200
Connection ~ 8350 2200
Wire Wire Line
	8350 2200 8350 2400
Wire Wire Line
	8100 2400 8350 2400
Connection ~ 8350 2400
Wire Wire Line
	8350 2400 8350 2750
$Comp
L power:+5V #PWR0133
U 1 1 5F6F7BC5
P 8550 1350
F 0 "#PWR0133" H 8550 1200 50  0001 C CNN
F 1 "+5V" H 8565 1523 50  0000 C CNN
F 2 "" H 8550 1350 50  0001 C CNN
F 3 "" H 8550 1350 50  0001 C CNN
	1    8550 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 1700 8550 1700
Wire Wire Line
	8550 1700 8550 1350
Wire Wire Line
	8100 1900 8550 1900
Wire Wire Line
	8550 1900 8550 1700
Connection ~ 8550 1700
Wire Wire Line
	8100 2100 8550 2100
Wire Wire Line
	8550 2100 8550 1900
Connection ~ 8550 1900
Wire Wire Line
	8100 2300 8550 2300
Wire Wire Line
	8550 2300 8550 2100
Connection ~ 8550 2100
Wire Wire Line
	8100 2500 8550 2500
Wire Wire Line
	8550 2500 8550 2300
Connection ~ 8550 2300
$Comp
L Device:C_Small C11
U 1 1 5F73660D
P 5900 1700
F 0 "C11" V 5671 1700 50  0000 C CNN
F 1 "0.1uF" V 5762 1700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5900 1700 50  0001 C CNN
F 3 "~" H 5900 1700 50  0001 C CNN
	1    5900 1700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0135
U 1 1 5F7375B1
P 5650 1750
F 0 "#PWR0135" H 5650 1500 50  0001 C CNN
F 1 "GND" H 5655 1577 50  0000 C CNN
F 2 "" H 5650 1750 50  0001 C CNN
F 3 "" H 5650 1750 50  0001 C CNN
	1    5650 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 1700 6000 1700
Wire Wire Line
	5800 1700 5650 1700
Wire Wire Line
	5650 1700 5650 1750
$Comp
L Connector:Conn_01x03_Male J4
U 1 1 5F79554A
P 1800 3750
F 0 "J4" H 1908 4031 50  0000 C CNN
F 1 "Conn_01x03_Male" H 1908 3940 50  0000 C CNN
F 2 "Connector_JST:JST_PH_S3B-PH-K_1x03_P2.00mm_Horizontal" H 1800 3750 50  0001 C CNN
F 3 "~" H 1800 3750 50  0001 C CNN
	1    1800 3750
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0134
U 1 1 5F79654B
P 2350 3600
F 0 "#PWR0134" H 2350 3450 50  0001 C CNN
F 1 "+12V" H 2365 3773 50  0000 C CNN
F 2 "" H 2350 3600 50  0001 C CNN
F 3 "" H 2350 3600 50  0001 C CNN
	1    2350 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0136
U 1 1 5F79685A
P 2350 3900
F 0 "#PWR0136" H 2350 3650 50  0001 C CNN
F 1 "GND" H 2355 3727 50  0000 C CNN
F 2 "" H 2350 3900 50  0001 C CNN
F 3 "" H 2350 3900 50  0001 C CNN
	1    2350 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 3650 2350 3650
Wire Wire Line
	2350 3650 2350 3600
Wire Wire Line
	2000 3850 2350 3850
Wire Wire Line
	2350 3850 2350 3900
$Comp
L Device:R R8
U 1 1 5F79EE6C
P 2750 3900
F 0 "R8" V 2650 3900 50  0000 C CNN
F 1 "100k" V 2750 3900 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2680 3900 50  0001 C CNN
F 3 "~" H 2750 3900 50  0001 C CNN
	1    2750 3900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0137
U 1 1 5F79F7D8
P 2750 4500
F 0 "#PWR0137" H 2750 4250 50  0001 C CNN
F 1 "GND" H 2755 4327 50  0000 C CNN
F 2 "" H 2750 4500 50  0001 C CNN
F 3 "" H 2750 4500 50  0001 C CNN
	1    2750 4500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5F7ABFA2
P 2750 4300
F 0 "R9" V 2650 4300 50  0000 C CNN
F 1 "50k" V 2750 4300 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2680 4300 50  0001 C CNN
F 3 "~" H 2750 4300 50  0001 C CNN
	1    2750 4300
	-1   0    0    1   
$EndComp
Wire Wire Line
	2000 3750 2750 3750
Wire Wire Line
	2750 4050 2750 4100
Wire Wire Line
	2750 4450 2750 4500
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J3
U 1 1 5F7BC140
P 3650 1500
F 0 "J3" H 3700 1817 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 3700 1726 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x03_P2.54mm_Vertical" H 3650 1500 50  0001 C CNN
F 3 "~" H 3650 1500 50  0001 C CNN
	1    3650 1500
	1    0    0    -1  
$EndComp
Text GLabel 3950 1500 2    50   Input ~ 0
MOSI
$Comp
L power:GND #PWR0138
U 1 1 5F7BD843
P 4200 1650
F 0 "#PWR0138" H 4200 1400 50  0001 C CNN
F 1 "GND" H 4205 1477 50  0000 C CNN
F 2 "" H 4200 1650 50  0001 C CNN
F 3 "" H 4200 1650 50  0001 C CNN
	1    4200 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0139
U 1 1 5F7BDC01
P 4200 1350
F 0 "#PWR0139" H 4200 1200 50  0001 C CNN
F 1 "+5V" H 4215 1523 50  0000 C CNN
F 2 "" H 4200 1350 50  0001 C CNN
F 3 "" H 4200 1350 50  0001 C CNN
	1    4200 1350
	1    0    0    -1  
$EndComp
Text GLabel 3450 1600 0    50   Output ~ 0
~RST
Text GLabel 3450 1500 0    50   Output ~ 0
SCK
Text GLabel 3450 1400 0    50   Output ~ 0
MISO
Wire Wire Line
	3950 1600 4200 1600
Wire Wire Line
	4200 1600 4200 1650
Wire Wire Line
	3950 1400 4200 1400
Wire Wire Line
	4200 1400 4200 1350
Text GLabel 2950 4100 2    50   Output ~ 0
SENSOR
Wire Wire Line
	2750 4100 2950 4100
Connection ~ 2750 4100
Wire Wire Line
	2750 4100 2750 4150
Text GLabel 8200 1500 2    50   Input ~ 0
NEO
Wire Wire Line
	8100 1500 8200 1500
Text GLabel 8450 2600 2    50   Output ~ 0
ROPT
$Comp
L Device:C_Small C12
U 1 1 5F81F53C
P 5900 2100
F 0 "C12" V 5671 2100 50  0000 C CNN
F 1 "0.1uF" V 5762 2100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5900 2100 50  0001 C CNN
F 3 "~" H 5900 2100 50  0001 C CNN
	1    5900 2100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0140
U 1 1 5F81FAD4
P 5650 2150
F 0 "#PWR0140" H 5650 1900 50  0001 C CNN
F 1 "GND" H 5655 1977 50  0000 C CNN
F 2 "" H 5650 2150 50  0001 C CNN
F 3 "" H 5650 2150 50  0001 C CNN
	1    5650 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 2100 6000 2100
Wire Wire Line
	5800 2100 5650 2100
Wire Wire Line
	5650 2100 5650 2150
Text GLabel 6750 3350 2    50   Output ~ 0
NEO
Text GLabel 6750 3450 2    50   Input ~ 0
SENSOR
Text GLabel 6750 3250 2    50   Input ~ 0
ROPT
$Comp
L Device:R R10
U 1 1 5F85203D
P 8150 2800
F 0 "R10" V 8050 2800 50  0000 C CNN
F 1 "47k" V 8150 2800 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8080 2800 50  0001 C CNN
F 3 "~" H 8150 2800 50  0001 C CNN
	1    8150 2800
	-1   0    0    1   
$EndComp
Wire Wire Line
	8100 2600 8150 2600
Wire Wire Line
	8150 2650 8150 2600
Connection ~ 8150 2600
Wire Wire Line
	8150 2600 8450 2600
$Comp
L power:GND #PWR0141
U 1 1 5F85D35D
P 8150 2950
F 0 "#PWR0141" H 8150 2700 50  0001 C CNN
F 1 "GND" H 8155 2777 50  0000 C CNN
F 2 "" H 8150 2950 50  0001 C CNN
F 3 "" H 8150 2950 50  0001 C CNN
	1    8150 2950
	1    0    0    -1  
$EndComp
Text GLabel 6750 4450 2    50   Input ~ 0
SW1
Text GLabel 6750 4250 2    50   Input ~ 0
SW2
$EndSCHEMATC