
/* Name: nums-abstract.h
 * Type: Header 
 * Description: numscale abstracted definition.
 * Header:
 *	<iostream>
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
#include<iostream>
#include<string>
#include<cstdbool>
#include<iterator>
#include<concepts>

 /* Macro */
 /* Data */
namespace nums {

  using std::string;

  // user must match the type for custom interface which will
  // be installed.
template<class T>
  requires std::integral<T> || std::__detail::__class_or_enum<T>
  using combineFunc = long long int (*) (const T &);

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
  requires std::integral<T> || std::__detail::__class_or_enum<T>
  class numscale {
 private:
    long long int value_;
    string transBuffer_;
    int SCALE_;			// This is scale for combine or transform

    combineFunc<T> combine;
    transformFunc transform;

 protected:

    /*
     * Combine function should match to class template with its type.
     * Source data from argument sent by user.
     */
    long long int defaultGeneralCombine(const T &);

    /*
     * Transform function neednt match class template with any type.
     * The default transform function always get middle data from @value_.
     */
    string defaultGeneralTransform(long long int);

    void install_combine(combineFunc<T> theFunc) { combine = theFunc; }
    void uninstall_combine(void) { combine = NULL; }
    void install_transform(transformFunc theFunc) { transform = theFunc; }
    void uninstall_transform(void) { transform = NULL; }

    static char genericNegativePrefixForScale(int x) {
      switch (x) {
      case HEX:
	return 'f';
      case OCT:
	return '0';
      case DEC:
	return '-';
      case BIN:
	return '1';
      default:
	return '0';
      }
    }

    char scaleSymbolMapping(char x) {
      char c(x);

      // In the case of HEX,OCT,DEC,BIN,just HEX should do mapping.
      if (HEX == this->SCALE_)
	switch (x) {
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

	default:
	  switch (c) {
	  case 'a':
	    c = 10;
	    break;

	  case 'b':
	    c = 11;
	    break;

	  case 'c':
	    c = 12;
	    break;

	  case 'd':
	    c = 13;
	    break;

	  case 'e':
	    c = 14;
	    break;

	  case 'f':
	    c = 15;
	    break;

	  default:
	    ;
	  }
	}

      return c;
    }

 public:
    numscale();
    numscale(size_t bufflen);
    virtual ~numscale();

    void install_or_uninstall(int action, combineFunc<T>);
    void install_or_uninstall(int action, transformFunc);
    void doTransform(int sscale, int dscale, const T &target);
    string getResult(void);
  };




}

// Header end
#endif
 /* Function */
