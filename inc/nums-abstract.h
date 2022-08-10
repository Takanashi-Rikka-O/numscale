
/* Name: nums-abstract.h
 * Type: Header 
 * Description: numscale abstracted definition.
 * Header:
 *	<string>
 *	<cstdbool>
 *	<iterator>
 * Function prototype:
 * Last modified date:
 * Fix:
 */

#ifndef _NUMS_ABSTRACT_H_
#define _NUMS_ABSTRACT_H_

 /* Feature */
 /* Header */
#include<string>
#include<cstdbool>
#include<iterator>
#include<concepts>

 /* Macro */
 /* Data */
namespace nums {

  using std::string;

  // requirement of templates,T must be a container.
  template<class T>
  concept must_be_container = requires(T a) {
    typename T::iterator;
    a.begin();
    a.end();
  };

  // user must match the type for custom interface which will
  // be installed.
  template<class T>
  requires std::integral<T> || must_be_container<T>
  using combineFunc = long long int (*) (T &);

  using transformFunc = string (*) (long long int);

  enum {
    INSTALL_COMBINE,
    UNINSTALL_COMBINE,
    INSTALL_TRANSFORM,
    UNINSTALL_TRANSFORM
  };

  enum {
    HEX = 16,
    OCT = 8,
    DEC = 10,
    BIN = 2
  };

  // T is type of argument.It should be string or integer.
  // User is possible to install custom interface into this class.
  // But numscale is just receive several type interface to be installed.
  // The types of interfaces was defined by @combineFunc and @transformFunc.
  // Dont allow install the interface that has not same type of numscale.
  template<class T>
  requires std::integral<T> || must_be_container<T>
  class numscale {
  private:
    long long int value_;
    string transBuffer_;
    int SCALE_;			// This is scale for combine or transform
    				// this variable just be used by defaultFunctions.

    combineFunc<T> combine;
    transformFunc transform;

  protected:
    /*
     * Combine function should match to class template with its type.
     * Source data from argument sent by user.
     */
    virtual long long int defaultGeneralCombine(T &)const;

    /*
     * Transform function neednt match class template with any type.
     * The default transform function always get middle data from @value_.
     */
    virtual string defaultGeneralTransform(long long int)const;

    void install_combine(combineFunc<T> theFunc) { combine = theFunc; }
    void uninstall_combine(void) { combine = NULL; }
    void install_transform(transformFunc theFunc) { transform = theFunc; }
    void uninstall_transform(void) { transform = NULL; }

    static char generateNegativePrefixForScale(int x) {
      char c('\0');
      switch (x) {
      case HEX:
	c = 'f';
	break;

      case OCT:
	c = '7';
	break;

      case DEC:
	c = '-';
	break;

      case BIN:
	c = '1';
	break;

      default:;	
      }

      return c;
    }

    // mapping procedure overload.

    char scaleSymbolMapping(int v)const {
      char c(v + '0');		// convert value to character
      if (HEX == this->SCALE_)
	switch (v) {
	case 10:
	  c = 'a';
	  break;

	case 11:
	  c = 'b';
	  break;

	case 12:
	  c = 'c';
	  break;

	case 13:
	  c = 'd';
	  break;

	case 14:
	  c = 'e';
	  break;

	case 15:
	  c = 'f';
	  break;

	default:;
	}

      return c;
    }

    /* these two procedures just do examine for HEX scale. */
    /* because there just HEX scale has char-value mapping. */
    /* program default defined DEC,OCT,HEX,BIN */

    int scaleSymbolMapping(char c)const {
      int v(c - '0');	// cover character to value
      if (HEX == this->SCALE_)
	switch (c) {
	case 'a':
	  v = 10;
	  break;

	case 'b':
	  v = 11;
	  break;

	case 'c':
	  v = 12;
	  break;

	case 'd':
	  v = 13;
	  break;

	case 'e':
	  v = 14;
	  break;

	case 'f':
	  v = 15;
	  break;

	default:;
	}

      return v;
    }


  public:
    numscale();
    numscale(size_t);
    virtual ~numscale();

    void install_or_uninstall(int action, combineFunc<T>);
    void install_or_uninstall(int action, transformFunc);
    virtual void doTransform(int sscale, int dscale,T &target);
    string getResult(void);
  };

  // END OF NAMESPACE
}

#include"numsabs.tcc"

// END OF HEADER
#endif
 /* Function */

