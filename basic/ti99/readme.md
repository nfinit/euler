TI BASIC solutions for the Texas Instruments TI-99/4
--------------------------------------------------------------------------------
Solutions in this directory are implemented in [TI BASIC], an ANSI-compliant
implementation of [BASIC] developed for Texas Instruments' [TI-99/4] and later 
/4A home computers, a family of 16-bit systems based on the TI's own [TMS9900]
microprocessor, a unique design derived from TI's larger 16-bit TI-990 
minicomputer.

While most competing home computers featured a BASIC interpreter built on top
of a licensed Microsoft implementation, TI BASIC was based directly on the
sixth edition of the original [Dartmouth BASIC], implementing most of the
features of that language along with some additional commands and subprograms
specific to the 99/4's hardware.

In a move best described as "ahead of its time", TI BASIC was implemented on
the 99/4 in an interpreted low-level intermediary language known as [GPL], or 
Graphic Programming Language, which can be considered a parallel to the modern
Java Virtual Machine or the contemporary [UCSD p-Machine] bytecode interpreters.
Very forward-thinking for such an early and underpowered system, however this
decision came at quite a cost, as the "doubly interpreted" TI BASIC was
considered by many to be one of the slowest on the market as a result of this
implementation, which may have been a reaction to the uncertainty surrounding
the 99/4's architecture (originally expected to be a conventional 8-bit system) 
early in its development.

Soon after the 99/4's release, TI began selling an "extended" BASIC with a
variety of useful enhancements, including multiple-statement lines, boolean
logic support in `IF...THEN` statements, and even speech synthesis with an
optional TMS5200 add-on module. TI Extended BASIC also implemented a number of
routines and other functionality in pure assembly rather than interpreted GPL,
producing significant speed-up in many applications. Most of the solutions in
this repository are implemented in Extended BASIC with the file extension 
`.x.bas`.

|  #  | Status | Solutions                                                     |
|-----|--------|---------------------------------------------------------------|
| [1] | Solved | Brute force                                                   |
| [2] | Solved | Brute force                                                   |

[//]: # ( Links and references // Links and references // Links and references )

[//]: # ( General links ====================================================== )

[BASIC]: https://en.wikipedia.org/wiki/BASIC

[TI BASIC]: https://en.wikipedia.org/wiki/TI_BASIC_(TI_99/4A)

[TI-99/4]: https://en.wikipedia.org/wiki/Texas_Instruments_TI-99/4

[TMS9900]: https://en.wikipedia.org/wiki/Texas_Instruments_TMS9900

[Dartmouth BASIC]: https://en.wikipedia.org/wiki/Dartmouth_BASIC

[DTSS]: https://en.wikipedia.org/wiki/Dartmouth_Time_Sharing_System

[GPL]: http://www.unige.ch/medecine/nouspikel/ti99/gpl.htm

[UCSD p-Machine]: https://en.wikipedia.org/wiki/P-code_machine#UCSD_p-Machine

[//]: # ( Problems =========================================================== )

[1]: https://github.com/nfinit/euler/wiki/Problem-1
(Multiples of 3 and 5)

[2]: https://github.com/nfinit/euler/wiki/Problem-2
(Even Fibonacci numbers)

[//]: # ( Links and sources ================================================== )
