
Announcing a Binary Coded Decimal Class for C++ applications requiring arithmetic
operations on large integers.

Features:
o  32 decimal digits
o  Object construtors from string, double and long types
o  Object contains sign and condition code in addition to 32 digit integer
o  Overloaded cout << operator prints object contents with sign and condition code
o  Add, Subtract, Multiply, Modulus and Divide supported via overloaded operators
o  Overloaded Logical operators <, >, ==, != are supported
o  Assignment operator, =, is supported.
o  bcdToString function suppresses leading zeros and inserts decimal point
o  Shift Left, Shift Right, Shift Right Rounded and Shift Right Coupled
   are supported.
o  sigD() function returns number of significant digits - quick bcd zero test
o  Package now includes a simple PM calculator to demonstrate and test the 
   arithmetic and shift functions of the bcd class.

BCD Arithmetic is not for everyone, primarily because it is serial and therefore
slower than the fixed and floating point instructions embodied on the hardware
chip.  In addition, the current version of the BCD class is implemented as a big
integer so fractional data will be lost unless the operands are scaled
appropriately.

The BCD register size can be set to any arbitrary length, within practical
limits of course.  I chose 32 digits for the bcd class because it is about
twice the capacity of a double floating point number and can be expected to
operate at a reasonable performance.  

I am including my regression test bucket, bcdrun.cpp, in the package as a
demonstration run and to give you some usage examples.  These tests produce
the bcdrun.log which you should take time to review before embarking on your
own experiments. Feel free to contribute to the test cases and I will include
them in the next update.

The BCD Class is provided without warrantee for your personal use and is not
licensed for inclusion in any commercial application or for subsequent resale.
Fully licensed copies of the BCD Class, including source, users guide, and 
technical support are available from JBC Enterprises, Inc.  

I am in the process of building floating point support which will be released
later as a separate class object.


Condition Codes:

 16 Non-zero condition code on resubtract.  When the significant digits are the
    same, I make a guess about which operand is the larger so I can subtract
    the smaller from the larger.  If I am wrong, I have to swap the operands
    and repeat the subtraction.  If the cc is still non-zero on the resubtract
    something is wrong.

 16 Shift out of range - On Shift Left, if significant digits plus shift amount
    are greater than 32.  On all Shift Right operations, if shift amount is
    greater than 32.

 16 Divide by zero.

 16 Add overflow detected by significant digits test.  This is a quick check
    that is done early in the operation.  There is an ambiguity on the 33rd
    digit which is covered later during the add.

 15 Add overflow detected by the adder.  If the destination digits have been
    exhausted but there are still unprocessed source digits.  This picks up
    the ambiguity that is missed by the significant digits test.

 14 Adder error: swap/digofs are something other than 0 or 1.  This is an 
    internal issue and is probably overkill in the checking. (:}

 12 Multiply error:  Non-decimal digit encountered during multiply operation.

  1 Carry out of the high order digit of the adder returned on an addition.  This
    is not quite the same as cond code 15 since all of the source and destination
    digits are accommodated but there is still a carry left in the adder.

Bill Connors
JBC Enterprises, Inc.
17820 Stoneridge Drive
Gaithersburg, MD  20878
1(800)249-8223 voice/fax

Beta.1   8/26/95
==================================================================================
1. Original distribution to 2 persons on Compuserve who expressed interest in
   having a bcd class.

Files:
 8-26-95   1:26p      1989           0  BCD.H
 8-26-95   5:51p     37812           0  bcd.obj
 8-26-95   5:37p     15141           0  bcdrun.cpp
 8-26-95   5:52p    153496          49  BCDRUN.EXE
 8-26-95   5:52p     10953           0  bcdrun.log
 8-26-95   5:29p      1934           0  readme.bcd


Beta.2   9/12/95, 9/13/95, 9/14/95, 9/24/95
=================================================================================
1. Changed multiply so that overflow returns the original multiplicand and sign
   on multiply overflow.  Overflow is determined by adding the number of signi-
   ficant digits in the multiplicand and multiplier, or as a result of a high
   order carry out during the multiply-add operations.  In the case of cascaded
   multiply ops, A * B * C ... etc., the returned value is the product of the
   last successful multiply.

2. Changed divide so that the original dividend and sign are returned on a
   divide by zero error.  Since modulus is a divide in disguise it is affected
   also.

3. Created a simple BCD Calculator as a test and demonstration tool.  It is not
   intended for everyday use mainly because it is an integer calculator and has
   some suprising attributes.  For example, you might expect 1/3 to be .333333
   or something.  Instead the answer is 0 because fractions are truncated.  On
   the other hand, if you divide 1000 by 3 the result is 333.  Personally, I
   prefer my pocket calculator to manage the decimal points for me.

4. Fixed a divide "incorrect output" error revealed by the BCD Calculator.
   (I knew the calculator would turn out to be useful). ;^)

5. Changed multiply to detect overflow errors at the end of each multiplier
   digit case.

6. Changed the adder to detect overflows when the result digits are exhausted
   but there are still unprocessed source digits.

7. Added Shift Right Coupled.

8. Deleted bcdrun.exe from distribution zip file - saves about 50% of the space.


Beta.2 Files:

 9-24-95  12:50p      2338           0  BCD.H
 9-24-95  12:51p     42342           0  bcd.obj      precompiled bcd class
 9-24-95   1:38p     61984           0  BCDCALC.EXE  PM applette demo/test
 9-12-95  11:38a       874          22  BCDCalc.ICO
 9-25-95  10:13a      5106           0  BCDCalc.INF
 9-24-95  10:23a     17833           0  bcdrun.cpp          | to recreate bcdrun.exe
 9-24-95  12:52p    149977          49  BCDRUN.EXE  deleted:| compile bcdrun.cpp and
 9-24-95  12:52p     13205           0  bcdrun.log          | link with bcd.obj
 9-25-95  11:01a      6499           0  readme.bcd
