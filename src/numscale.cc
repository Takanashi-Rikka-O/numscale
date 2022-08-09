
/* Name: numscale.cc
 * Type: C++ program code file
 * Description: Main program file of numscale.
 * Header:
 *	"nums-abstract.h"
 *	<iostream>
 *	<unistd.h>
 *	<cstdlib>
 *	<cstring>
 * Function prototype:
 * Last modified date:
 * Fix:
 */

 /* Feature */
 /* Header */
#include"nums-abstract.h"
#include<iostream>
#include<unistd.h>
#include<cstdlib>
#include<cstring>

extern "C" {
  size_t strlen(const char *);
  int strncmp(const char *, const char *, size_t);
  void exit(int);
};

 /* Macro */
#define SRCSCALE_OPTION 's'
#define DESSCALE_OPTION 'd'
#define HELP_OPTION 	'h'

#define SCALE_HEX	nums::HEX
#define SCALE_DEC	nums::DEC
#define SCALE_OCT	nums::OCT
#define SCALE_BIN	nums::BIN

#define PROPER_CMDOPT_N	6

using std::cerr;
using std::cout;
using std::endl;

 /* Data */
 /* Function */

static int defined_scales(const char *defs) {
  int rets(-1);
  if (strncmp(defs, "2", 1) == 0)
    rets = SCALE_BIN;
  else if (strncmp(defs, "8", 1) == 0)
    rets = SCALE_OCT;
  else if (strncmp(defs, "10", 2) == 0)
    rets = SCALE_DEC;
  else if (strncmp(defs, "16", 2) == 0)
    rets = SCALE_HEX;
  /*
   * addition
   */

  return rets;
}

static void numscale_help(void);

int main(int argc,char *argv[]) {
  using namespace nums;
  string result(64,'\0');
  string tempbuff(result);
  int sscale(0), dscale(0);
  char theopt('\0');

  numscale<string> ns(64);

  if (argc < PROPER_CMDOPT_N)
    numscale_help();

  while ((theopt = getopt(argc, argv, "s:d:h")) != -1 ) {
    switch (theopt) {
    case SRCSCALE_OPTION:
      sscale = defined_scales(optarg);
      if (sscale < 0) {
	cerr<<"unsupported scale - "<<optarg<<endl;
	numscale_help();	// numscale_help() will causes process exit.
      }
      break;
	
    case DESSCALE_OPTION:
      dscale = defined_scales(optarg);
      if (dscale < 0) {
	cerr<<"unsupported scale - "<<optarg<<endl;
	numscale_help();
      }
      break;

    case HELP_OPTION:
      numscale_help();

    default:
      cerr<<"error occur : "<<static_cast<char>(optopt)<<" "<<strerror(opterr)<<endl;
      numscale_help();
    }
  }

  tempbuff.assign(argv[argc - 1], strlen(argv[argc - 1]));	// copy data string to temp c++string

  ns.doTransform(sscale, dscale, tempbuff);	// do transform.
  result = ns.getResult();
  cout<<result<<endl;

  return 0;
}

static void numscale_help(void) {
  cout<<"Usage: numscale -s <srcscale> -d <desscale> <--> <data string>"<<endl;
  cout<<"# Program dont care the order of options apperance except <data string>"<<endl;
  cout<<"# Attention: if pre-transform data is a negative value,should add shutdown-seq\'--\' before <data string>"<<endl;
  exit(0);
}
