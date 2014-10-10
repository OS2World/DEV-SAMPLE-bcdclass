// bcd.h  Binary Coded Decimal Class ****************  W. D. Connors 7/29/95
typedef unsigned short USHORT;
class bcd
{
private:
   char intgl[16];       // yields 32 digits of precision
   char sign;            // char sign
   int condcode;         // indicator for underflow, overflow, divide by zero

// private methods
 
int decAdd(char * rslt, const char * src, int digofs, int bytofs, int swap, int sub);
int sigd(char * igl, int expn);
bcd opadd(const bcd & a, const bcd & b, char tsign);
bcd opdiv(const bcd & a, const bcd & b, char ret);
int opshr(bcd & a, USHORT sa);
int opcmp(const bcd & a, const bcd & b);

public:
   bcd(void);                          // default constructor - initialize to zero
   bcd(const bcd & b);                 // construct from another bcd
   bcd(const char * sz);               // constructor from numeric string
   bcd(const double x);                // constructor from floating point number
   bcd(const long num);                // constructor from long integer
   bcd(char * rslt, char sg, int cc);  // constructor from discreet pieces
   ~bcd();                             // destructor

// public methods
   int bcdToString(char * st, USHORT dp = 0); // str returned w/decimal point at dp
   int rcc();             // returns condition code from bcd structure
   int shr(USHORT decdg);    // shift right decdg decimal digits
   int shrRnd(USHORT decdg); // shift right decdg decimal digits and round
   int shrCpld(bcd & dest, USHORT decdg); // shift decdg digits into dest (lo order)
   int shl(USHORT decdg);    // shift left decdg decimal digits
   int sigD();  // returns the number of significant digits - quick bcd zero test

// operator overloading
   bcd operator=(const bcd & b);    // assignment
   bcd operator+(const bcd & b);    // addition
   bcd operator-(const bcd & b);    // subtraction
   bcd operator-(void);             // unary negator
   bcd operator*(const bcd & b);    // multiplication
   bcd operator/(const bcd & b);    // division
   bcd operator%(const bcd & b);    // modulus
   int operator<(const bcd & b);    // logical ops
   int operator>(const bcd & b);    // et cetera
   int operator==(const bcd & b);
   int operator!=(const bcd & b);
   friend ostream & operator<<(ostream & os, const bcd &b);
};
