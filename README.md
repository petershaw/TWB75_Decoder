Peter Shaw’sAnalyzerDude
==================

Hardware
------------------
Die Hardware stellt eine Referenzimplementierung dar. Sie ist mit zwei analogen Eingängen, 2 direkten digitalen Eingängen und 4 galvanisch getrennten Eingängen ausgestttet.  Auf der Frontseite befinden sich 4 Druckknöpfe für die Eingabe und Steuerung der Firmware. En Reset Button, zwei steuerbaren LED’s, sowie einer Betrienbsanzeige. Das Display stellt ein Menu und aktuelle Werte dar. Die Software muss der jeweiligen Hardwareimplementierung angepasst werden. Die Referenzimplementierung ist für den ATMega328p entwickelt worden.

Software
------------------
Die Firmeware zum AnalyzerDude (vers. 1.0) ist freeware. Sie kann ohne Einschränkungen genutzt werden. Für die jeweis verwendeten Hardwarekomponenten wird im Manual/Wiki beschreiben welche Anpassungen vorgenommen werden müssen. Die Software ist in C geschrieben und kann mit avr-gcc compailiert werden. Unit-tests sind mit dem CU Framework verfasst worden. (http://cu.danfis.cz)

Libraries
------------------
Folgende third-party libraries wurden verwendet:-lcd	Peter Fleury	C include file for the HD44780U LCD library (lcd.c)
-uart	Peter Fleury	Interrupt UART library with receive/transmit circular buffers


