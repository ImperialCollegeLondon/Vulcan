#include <iostream>
int main ()
{
using std:: cout;
cout << "The size of an int is: \t\t"
<< sizeof (int)
<< " bytes. \n";
cout << "The size of a short int is: \t" << sizeof (short) << " bytes. \n"; cout << "The size of a long int is:\t"
<< sizeof (long)
<< " bytes. \n";
cout << "The size of a char is:\t\t"
<< sizeof (char)
<< " bytes. \n";
cout << "The size of a float is:\t\t" << sizeof (float) << " bytes. \n";
cout << "The size of a double is: \t" << sizeof (double) << " bytes. \n";
cout << "The size of a bool is: \t"
<< sizeof (bool)
<< " bytes. \n";
return 0;
}
