REM * PROGRAM INITIALIZATION *
1 S=0 :: F=0
10 INPUT "RANGE: ";R
20 DIM D(16)
21 FOR I=1 to 16
22 INPUT "DIVISOR OR 0: ";D(I)
23 IF D(I)<1 THEN I=17
29 NEXT I

REM * SEARCHING/PROCESSING *
30 PRINT "" :: PRINT "PROCESSING...";
31 FOR I=1 TO R-1
32 FOR J=1 TO 16
33 IF D(J)<1 THEN 48
34 IF (I-D(J)*INT(I/D(J)))=0 THEN GOTO 40
39 GOTO 49
40 S=S+I :: F=F+1
41 IF (F-15*INT(F/15))=0 THEN PRINT "" :: PRINT "PROCESSING...";
42 PRINT ".";
48 J=16
49 NEXT J
59 NEXT I

REM * FINAL PRINTOUT *
90 PRINT ""
95 PRINT "SUM:";S;"FOUND:";F
98 PAUSE
99 END