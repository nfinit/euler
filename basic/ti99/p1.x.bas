REM * PROJECT EULER - 01 *
REM  MULTIPLES OF 3 AND 5
REM **********************
REM SOLUTION FOR TI 99/4A
REM EXTENDED BASIC ONLY

1 CALL CLEAR :: CALL SCREEN(15)
2 S=0 :: F=0 :: P=0 :: K=0
3 PRINT "PRINT SEARCH (Y/N)"
4 CALL SOUND(100,932,10) :: CALL SOUND (400,740,10)
5 CALL KEY(0,P,K)
6 IF K=0 THEN 5
7 IF P=78 THEN P=0
9 CALL CLEAR

10 INPUT "ENTER RANGE: ":RANGE
11 IF RANGE=0 THEN 999
12 IF RANGE<0 THEN 10

20 PRINT "ENTER DIVISORS TO TEST:"
21 DIM DIVISORS(16)
22 FOR I=1 TO 16
23 INPUT "(DIVISOR OR 0)=>":IN
24 IF IN=0 THEN I=16
25 IF IN<0 THEN DIVISORS(I)=ABS(IN)
26 IF IN>0 THEN DIVISORS(I)=IN
29 NEXT I

30 CALL CLEAR :: CALL SCREEN(12)
31 PRINT "SEARCHING IN RANGE:"
32 PRINT " 0 < N <";RANGE
33 PRINT "FOR VALUES DIVISIBLE BY:"
34 GOSUB 1010 :: PRINT ""
40 FOR I=1 TO RANGE-1
41 FOR J=1 TO 16
42 IF DIVISORS(J)<1 THEN 47
44 IF I-DIVISORS(J)*INT(I/DIVISORS(J))>0 THEN 49
45 S=S+I :: F=F+1
46 IF P>1 THEN PRINT I;
47 J=16
49 NEXT J
59 NEXT I

90 PRINT "" :: PRINT "" :: CALL SCREEN(4)
91 IF P<1 THEN CALL CLEAR 
92 CALL SOUND(100,932,10) :: CALL SOUND (400,1175,10)
93 PRINT "SEARCH COMPLETE"
95 PRINT "RANGE: 0 < N <";RANGE
96 PRINT "FOUND:",F
97 PRINT "SUM:",S
98 PRINT ""

991 CALL KEY(0,P,K)
992 IF K=0 THEN 991
993 CALL CLEAR :: CALL SCREEN(8)
994 PRINT "LAST SEARCH:"
995 PRINT "0 < N <";RANGE
996 PRINT "DIVISORS:";
997 GOSUB 1010
998 PRINT "FOUND:";F;"SUM:";S
999 END

REM * DIVISOR PRINT SUBPROGRAM *
1010 FOR I=1 TO 16
1011 IF DIVISORS(I)<1 THEN 1018
1013 IF I>1 THEN PRINT ",";
1014 PRINT DIVISORS(I);
1015 NEXT I
1018 PRINT ""
1019 RETURN
