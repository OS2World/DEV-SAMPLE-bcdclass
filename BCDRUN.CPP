// bcdrun.cpp  Test BCD Class
#include <time.h>
#include <fstream.h>
#include "bcd.h"
int main(void)
{
   struct tm *newtime;
   time_t ltime; 
   time(&ltime);                 /* Get the time in seconds */
   newtime = localtime(&ltime);  /* Convert it to the structure tm */
   char * st;            // gen purpose string for bcd's
   st = new char[35];   // 32 digits + sign + decimal pt + '\0'
 ofstream dout("bcdrun.log");
   bcd numa("1234567890987654.123");  // fraction will be dropped
   bcd numb(4321.6789);               // ditto - we are using integer rules
   bcd numc(-24681357L);
   bcd numd = numa + numb;
   bcd e(0.0);
   bcd f(0L);
   bcd g(-0.0);
   bcd h(-0L);
   bcd w(1L);
   bcd x(-1.0);
   bcd y("-2.0");
   bcd z("300.");
   bcd aa("99999999999999999999999999999999");
   bcd bb("1");
   bcd cc("10000000000000000");
   bcd dd(".00000000000000001");
   bcd m1(12L);
   bcd m2(2L);
   bcd m3(123456789L);
   bcd m4(4096L);
   bcd m5(748345987654321.0);
   bcd m6(288834570200345.0);
   bcd m7("8599238847786248452455563809");
   bcd d1("8765432109876");
   bcd d2(24687L);
   bcd d3(75237L);
   bcd d4(45263L);
   bcd d5 ("92732081006447");
   bcd s1("1234567890987654");

   dout << "                 Regression Log for " << asctime(newtime) << endl;

   dout << "significant digits test: 1 = " << w.sigD() << ", 3 = " << z.sigD()
        << ", 32 = " << aa.sigD() << ", 0 = " << dd.sigD() << "\n" << endl;

   int rc = numa.bcdToString(st); // convert numa to string no decimal point
   dout << "bcd to string test = " << st << "\n"
        << "          expected:  +1234567890987654" << endl;
   rc = numa.bcdToString(st,1);   // numa to str with 1 psn to right of dec pt
   dout << "bcd to string test = " << st << "\n"
        << "          expected:  +123456789098765.4" << endl;
   rc = numa.bcdToString(st,6);   // numa to str with 6 psns to rt of decimal pt
   dout << "bcd to string test = " << st << "\n"
        << "          expected:  +1234567890.987654" << "\n" << endl;

   rc = m3.bcdToString(st); // convert m3 to string no decimal point
   dout << "bcd to string test  = " << st << "\n"
        << "          expected:   +123456789" << endl;
   rc = m3.bcdToString(st,1);   // m3 to str with 1 psn to right of dec pt
   dout << "bcd to string test  = " << st << "\n"
        << "          expected:   +12345678.9" << endl;
   rc = m3.bcdToString(st,6);   // m3 to str with 6 psns to rt of decimal pt
   dout << "bcd to string test  = " << st << "\n"
        << "          expected:   +123.456789" << "\n" << endl;

   rc = h.bcdToString(st); // convert h to string no decimal point
   dout << "bcd to string test  = " << st << "\n"
        << "          expected:   +0" << endl;
   rc = h.bcdToString(st,1);   // convert h to str with 1 psn to right of dec pt
   dout << "bcd to string test  = " << st << "\n"
        << "          expected:   +0.0" << endl;
   rc = h.bcdToString(st,6);   // h to str with 6 psns to rt of decimal pt
   dout << "bcd to string test  = " << st << "\n"
        << "          expected:   +0.0" << "\n" << endl;

   rc = m2.bcdToString(st); // convert m2 to string no decimal point
   dout << "bcd to string test  = " << st << "\n"
        << "          expected:   +2" << endl;
   rc = m2.bcdToString(st,1);   // m2 to str with 1 psn to right of dec pt
   dout << "bcd to string test  = " << st << "\n"
        << "          expected:   +0.2" << endl;
   rc = m2.bcdToString(st,6);   // m2 to str with 6 psns to rt of decimal pt
   dout << "bcd to string test  = " << st << "\n"
        << "          expected:   +0.000002" << "\n" << endl;

   s1.shl(1);
   dout << "shift test 1234567890987654 shifted left 1 = " << s1 
        << "   expected                                = +00000000000000012345678909876540 cc: 0\n" << endl;
   s1.shl(2);
   dout << "shift test 1234567890987654 shifted left 2 = " << s1 
        << "   expected                                = +00000000000001234567890987654000 cc: 0\n" << endl;
   s1.shl(3);
   dout << "shift test 1234567890987654 shifted left 3 = " << s1 
        << "   expected                                = +00000000001234567890987654000000 cc: 0\n" << endl;
   s1.shl(13);
   dout << "shift test 1234567890987654 shfted left 13 = " << s1 
        << "   expected                                = +00000000001234567890987654000000 cc: 16\n" << endl;
   s1.shr(1);
   dout << "shift test 1234567890987654 shifted rt 1 = " << s1 
        << "   expected                              = +00000000000123456789098765400000 cc: 0\n" << endl;
   s1.shr(2);
   dout << "shift test 1234567890987654 shifted rt 2 = " << s1 
        << "   expected                              = +00000000000001234567890987654000 cc: 0\n" << endl;
   s1.shr(5);
   dout << "shift test 1234567890987654 shifted rt 5 = " << s1 
        << "   expected                              = +00000000000000000012345678909876 cc: 0\n" << endl;
   s1.shrRnd(4);
   dout << "shift test 12345678909876 sh rt 4 & rnd  = " << s1
        << "   expected                              = +00000000000000000000001234567891 cc: 0\n" << endl;
   s1.shrRnd(4);
   dout << "shift test 12345678909876 sh rt 4 & rnd  = " << s1
        << "   expected                              = +00000000000000000000000000123457 cc: 0\n" << endl;
   s1.shrRnd(5);
   dout << "shift test 12345678909876 sh rt 5 & rnd  = " << s1
        << "   expected                              = +00000000000000000000000000000001 cc: 0\n" << endl;
   s1.shl(31);
   dout << "shift test 12345678909876 sh lt 31       = " << s1
        << "   expected                              = +10000000000000000000000000000000 cc: 0\n" << endl;

   bcd s2("1234567890987654321");
   s2.shrCpld(s1,6);               // odd shift even
   dout << "coupled shift s2 > s1,   s1 = " << s1
        << "                expected s1 = +00000000000000000000000000654321 cc: 0\n"
        << "                         s2 = " << s2
        << "                expected s2 = +00000000000000000001234567890987 cc: 0\n" << endl;
   s2.shrCpld(s1,5);               // odd shift odd
   dout << "coupled shift s2 > s1,   s1 = " << s1
        << "                expected s1 = +00000000000000000000000000090987 cc: 0\n"
        << "                         s2 = " << s2
        << "                expected s2 = +00000000000000000000000012345678 cc: 0\n" << endl;
   s2.shrCpld(s1,4);               // even shift even
   dout << "coupled shift s2 > s1,   s1 = " << s1
        << "                expected s1 = +00000000000000000000000000005678 cc: 0\n"
        << "                         s2 = " << s2
        << "                expected s2 = +00000000000000000000000000001234 cc: 0\n" << endl;
   s2.shrCpld(s1,3);               // odd shift odd
   dout << "coupled shift s2 > s1,   s1 = " << s1
        << "                expected s1 = +00000000000000000000000000000234 cc: 0\n"
        << "                         s2 = " << s2
        << "                expected s2 = +00000000000000000000000000000001 cc: 0\n" << endl;

   dout << "logical test 1 < 2   = " << int(bb<m2) << "\n"
        << "expected             = 1 \n" << endl;
   dout << "logical test 1 > 2   = " << int(bb>m2) << "\n"
        << "expected             = 0 \n" << endl;
   dout << "logical test 1 = 2   = " << int(bb==m2) << "\n"
        << "expected             = 0 \n" << endl;
   dout << "logical test 2 < 1   = " << int(m2<bb) << "\n"
        << "expected             = 0 \n" << endl;
   dout << "logical test 2 > 1   = " << int(m2>bb) << "\n"
        << "expected             = 1 \n" << endl;
   dout << "logical test 2 = 1   = " << int(m2==bb) << "\n"
        << "expected             = 0 \n" << endl;
   dout << "logical test 1 < 12  = " << int(bb<m1) << "\n"
        << "expected             = 1 \n" << endl;
   dout << "logical test 1 > 12  = " << int(bb>m1) << "\n"
        << "expected             = 0 \n" << endl;
   dout << "logical test 1 = 12  = " << int(bb==m1) << "\n"
        << "expected             = 0 \n" << endl;
   dout << "logical test 12 < 1  = " << int(m1<bb) << "\n"
        << "expected             = 0 \n" << endl;
   dout << "logical test 12 > 1  = " << int(m1>bb) << "\n"
        << "expected             = 1 \n" << endl;
   dout << "logical test 12 = 1  = " << int(m1==bb) << "\n"
        << "expected             = 0 \n" << endl;
   dout << "logical test -1 < 2  = " << int(x<m2) << "\n"
        << "expected             = 1 \n" << endl;
   dout << "logical test -1 > 2  = " << int(x>m2) << "\n"
        << "expected             = 0 \n" << endl;
   dout << "logical test -1 = 2  = " << int(x==m2) << "\n"
        << "expected             = 0 \n" << endl;
   dout << "logical test 2 < -1  = " << int(m2<x) << "\n"
        << "expected             = 0 \n" << endl;
   dout << "logical test -1 != 2  = " << int(x!=m2) << "\n"
        << "expected              = 1 \n" << endl;
   dout << "logical test 2 != -1  = " << int(m2!=x) << "\n"
        << "expected              = 1 \n" << endl;
   dout << "logical test 2 != 2   = " << int(m2!=m2) << "\n"
        << "expected              = 0 \n" << endl;
   dout << "logical test 2 > -1  = " << int(m2>x) << "\n"
        << "expected             = 1 \n" << endl;
   dout << "logical test 2 = -1  = " << int(m2==x) << "\n"
        << "expected             = 0 \n" << endl;
   dout << "logical test d1 = d1 = " << int(d1==d1) << "\n"
        << "expected             = 1 \n" << endl;
   dout << "logical test 0 = -0  = " << int(f==h) << "\n"
        << "expected             = 1 \n" << endl;
   dout << "logical test -0 = 0  = " << int(h==f) << "\n"
        << "expected             = 1 \n" << endl;
   dout << "logical test 0 = 0   = " << int(f==f) << "\n"
        << "expected             = 1 \n" << endl;
   dout << "logical test -0 = -0 = " << int(h==h) << "\n"
        << "expected             = 1 \n" << endl;
   dout << "divide test 8765432109876/24687 = " << d1/d2
        << "expected                        = +00000000000000000000000355062669 cc: 0\n" << endl;
   dout << "divide tst 92732081006447/45263 = " << d5/d4
        << "expected                        = +00000000000000000000002048739169 cc: 0\n" << endl;
   dout << "divide test 8765432109876/75237 = " << d1/d3
        << "expected                        = +00000000000000000000000116504274 cc: 0\n" << endl;
   dout << "divide test 1/24687             = " << bb/d2
        << "expected                        = +00000000000000000000000000000000 cc: 0\n" << endl;
   dout << "   test 10000000000000000/24687 = " << cc/d2
        << "expected                        = +00000000000000000000405071495118 cc: 0\n" << endl;
   dout << "   test 10000000000000000/3     = " << cc/3L
        << "expected                        = +00000000000000003333333333333333 cc: 0\n" << endl;
   dout << "   test 10000000000000000/6     = " << cc/6L
        << "expected                        = +00000000000000001666666666666666 cc: 0\n" << endl;
   dout << "   test 10000000000000000/7     = " << cc/7L
        << "expected                        = +00000000000000001428571428571428 cc: 0\n" << endl;
   dout << " div test 22000000000000000/7   = " << (cc*22L)/7L
        << "expected                        = +00000000000000031428571428571428 cc: 0\n" << endl;
   dout << "modulus test 24687%1000         = " << d2%1000L
        << "expected                        = +00000000000000000000000000000687 cc: 0\n" << endl;
   dout << "divide by zero test 75237/0     = " << d3/0L
        << "expected                        = +00000000000000000000000000075237 cc: 16\n" << endl;
   dout << "divide d1/d1 test               = " << d1/d1
        << "expected                        = +00000000000000000000000000000001 cc: 0\n" << endl;
   dout << "re-subtract test: 12345 - 12346 = " << bcd(12345L) - 12346L
        << "expected                        = -00000000000000000000000000000001 cc: 0\n"
        << " reverse opnds:   12346 - 12345 = " << bcd(12346L) - 12345L
        << "expected                        = +00000000000000000000000000000001 cc: 0\n" << endl;
   dout << "8599238847786248452455563809*45263       = " << m7 * d4
        << "                               expected:   +00008599238847786248452455563809 cc: 15\n" << endl;
   dout << "748345987654321 x 288834570200345        = " << m5 * m6
        << "                               expected:   +00216148191705288491573574940745 cc: 0\n" << endl;
   dout << "748345987654321 x 288834570200345 x 10   = " << m5 * m6 * 10.0
        << "                               expected:   +02161481917052884915735749407450 cc: 0\n" << endl;
   dout << "748345987654321 x 288834570200345 x 100  = " << m5 * m6 * 100.0
        << "                               expected:   +21614819170528849157357494074500 cc: 0\n" << endl;
   dout << "748345987654321 x 288834570200345 x 1000 = " << m5 * m6 * 1000.0
        << "                               expected:   +00216148191705288491573574940745 cc: 16\n" << endl;
   dout << "123456789 x 123456789 x 123456789        = " << m3 * m3 * m3
        << "                               expected:   +00000001881676371789154860897069 cc: 0\n" << endl;
   dout << "123456789 x 123456789 x 123456789 x 123456789 = " << m3 * m3 * m3 * m3
        << "                                    expected:   +00000001881676371789154860897069 cc: 16\n" << endl;
   dout << "                                        2 x 2 = " << m2*m2
        << "                                    expected:   +00000000000000000000000000000004 cc: 0\n" << endl;
   dout << "                                       2 x 12 = " << m2*m1
        << "                                    expected:   +00000000000000000000000000000024 cc: 0\n" << endl;
   dout << "                                2 x 123456789 = " << m2 * m3
        << "                                    expected:   +00000000000000000000000246913578 cc: 0\n" << endl;
   dout << "                                123456789 x 2 = " << m3 * m2
        << "                                    expected:   +00000000000000000000000246913578 cc: 0\n" << endl;
   dout << " 4096 x 2 = " << m4 * m2
        << "expected:   +00000000000000000000000000008192 cc: 0\n" << endl;
   dout << " 2 x 4096 = " << m2 * m4
        << "expected:   +00000000000000000000000000008192 cc: 0\n" << endl;
   dout << " 2 x 12 x 4096 = " << m2 * m1 * m4
        << "expected:        +00000000000000000000000000098304 cc: 0\n" << endl;
   dout << "    aa = " << aa
        << "    bb = " << bb
        << " aa-bb = " << aa-bb
        << "expected:+99999999999999999999999999999998 cc: 0\n"
        << " aa+bb = " << aa+bb 
        << "expected:+00000000000000000000000000000000 cc: 1\n" << endl;
   dout << "     e = " << e
        << "     f = " << f
        << " e + f = " << e+f
        << "expected:+00000000000000000000000000000000 cc: 0\n" 
        << " e - f = " << e-f 
        << "expected:+00000000000000000000000000000000 cc: 0\n" << endl;
   dout << "     g = " << g
        << "     h = " << h
        << " g + h = " << g+h
        << "expected:+00000000000000000000000000000000 cc: 0\n"
        << " g - h = " << g-h 
        << "expected:+00000000000000000000000000000000 cc: 0\n" << endl;
   dout << "     w = " << w
        << "     x = " << x
        << " w + x = " << w+x
        << "expected:+00000000000000000000000000000000 cc: 0\n"
        << " w - x = " << w-x 
        << "expected:+00000000000000000000000000000002 cc: 0\n" << endl;
   dout << "     y = " << y
        << "     z = " << z
        << " y + z = " << y+z
        << "expected:+00000000000000000000000000000298 cc: 0\n"
        << " y - z = " << y-z 
        << "expected:-00000000000000000000000000000302 cc: 0\n" << endl;
   dout << "numa =      " << numa 
        << "numb =      " << numb
        << "numa+numb = " << numd
        << "expected:   +00000000000000001234567890991975 cc: 0\n"
        << "numb+numa = " << numb+numa 
        << "expected:   +00000000000000001234567890991975 cc: 0\n" << endl;
   dout << "numa =      " << numa 
        << "numc =      " << numc
        << "numa+numc = " << numa+numc 
        << "expected:   +00000000000000001234567866306297 cc: 0\n"
        << "numc+numa = " << numc+numa
        << "expected:   +00000000000000001234567866306297 cc: 0\n" << endl;
   dout << "numb =      " << numb
        << "numc =      " << numc
        << "numb+numc = " << numb+numc 
        << "expected:   -00000000000000000000000024677036 cc: 0\n"
        << "numc+numb = " << numc+numb 
        << "expected:   -00000000000000000000000024677036 cc: 0\n" << endl;
   dout << "numa =      " << numa 
        << "numb =      " << numb
        << "numa-numb = " << numa-numb 
        << "expected:   +00000000000000001234567890983333 cc: 0\n" 
        << "numb-numa = " << numb-numa 
        << "expected:   -00000000000000001234567890983333 cc: 0\n" << endl;
   dout << "numa =      " << numa 
        << "numc =      " << numc
        << "numa-numc = " << numa-numc 
        << "expected:   +00000000000000001234567915669011 cc: 0\n"
        << "numc-numa = " << numc-numa 
        << "expected:   -00000000000000001234567915669011 cc: 0\n" << endl;
   dout << "numb =      " << numb
        << "numc =      " << numc
        << "numb-numc = " << numb-numc 
        << "expected:   +00000000000000000000000024685678 cc: 0\n"
        << "numc-numb = " << numc-numb
        << "expected:   -00000000000000000000000024685678 cc: 0\n" << endl;
   dout.close();
   delete st;
   return 0;
}
