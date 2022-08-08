
/* Name: numsabs-test.cc
 * Type: C++ program code file
 * Description:
 * Header:
 * Function prototype:
 * Last modified date:
 * Fix:
 */

 /* Feature */
 /* Header */
 /* Macro */
 /* Data */
 /* Function */

#include"nums-abstract.h"

int main(void) {

  using namespace nums;
  using namespace std;
  numscale<string> ns;
  string hexvalue("fffac18");
  string result;
  string binvalue("11110110");
  int binvalue_(0b11110110);
  int hexvalue_(0xfffac18);

  string octvalue("7332");
  int octvalue_(07332);

  int decvalue(32);
  numscale<int> ns2;

  ns.doTransform(HEX, DEC, hexvalue);
  result = ns.getResult();

  cout<<hexvalue<<endl;
  cout<<hexvalue_<<endl;
  cout<<result<<endl;

  ns.doTransform(BIN, DEC, binvalue);
  result = ns.getResult();

  cout<<binvalue<<endl;
  cout<<binvalue_<<endl;
  cout<<result<<endl;

  ns.doTransform(OCT, DEC, octvalue);
  result = ns.getResult();

  cout<<octvalue<<endl;
  cout<<octvalue_<<endl;
  cout<<result<<endl;

  ns2.doTransform(DEC, HEX, decvalue);
  result = ns2.getResult();

  cout<<decvalue<<endl;
  cout<<result<<endl;


  return 0;
}
