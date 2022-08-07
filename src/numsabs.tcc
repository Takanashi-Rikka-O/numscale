
/* Name: numsabs.cc
 * Type: C++ program code file
 * Description:
 * 	Class definitions.
 * Header:
 *	"nums-abstract.h"
 * Function prototype:
 *	Class member methods.
 * Last modified date:
 * Fix:
 */

 /* Feature */
 /* Header */
#include"nums-abstract.h"

 /* Macro */
 /* Data */
 /* Function */

namespace nums {

  // Constructor and Destructor
  template<class T>
  numscale<T>::numscale() : transBuffer_(128) {
    value_ = 0;
    SCALE_ = 2;
    combine = NULL;
    transform = NULL;
  }

  template<class T>
  numscale<T>::numscale(size_t bufflen) : transBuffer_(bufflen) {
    value_ = 0;
    SCALE_ = 2;
    combine = NULL;
    transform = NULL;
  }

  template<class T>
  numscale<T>::~numscale() { }

  // protected members
  template<class T>
  long long int numscale<T>::defaultGeneralCombine(const T &target) {
    long long int mulI(1);
    long long int result(0);
    char negative_prefix(genericNegativePrefixForScale(SCALE_));
    auto first(target.begin());

    // count bits of target number.
    for (auto index(target.end()); index > first; --index, mulI *= SCALE_)
      result += static_cast<long long int>(scaleSymbolMapping((*index))) * mulI;

    // computer use the most taller bit as negative or positive indicator.
    if (*first == negative_prefix)
      result *= -1;
    else
      result += static_cast<long long int>(scaleSymbolMapping(*first)) * mulI;

    return result;
  }

  template<class T>
  string numscale<T>::defaultGeneralTransform(long long int target) {
    string tempbuff(transBuffer_);
    string result(transBuffer_);
    char negative_prefix(genericNegativePrefixForScale(SCALE_));
    unsigned long long int tempValue = target;				// transform to positive number.
    long long int quotient(1);
    const long long int divI(SCALE_);
    string::iterator it_of_result(result.begin());

    auto remainder = [tempValue, divI](void) -> long long int {
      return tempValue - tempValue / divI * divI;
    };
    auto quotientor = [tempValue, divI](void) -> long long int {
      return tempValue / divI;
    };

    // transform number scale with remainder.
    for (auto index(tempbuff.begin()); quotient != 0; ++index) {
      *index = scaleSymbolMapping(static_cast<char>(remainder()));
      tempValue = quotientor();
    } 

    // complete buffer.
    for (auto it_of_temp(string::iterator{tempbuff.end()}); it_of_temp >= tempbuff.begin(); --it_of_temp)
      *it_of_result++ = *it_of_temp;

    return result;
  }

  /*
  // specifically implement of string
  template<>
  long long int numscale<string>::defaultGeneralCombine(const string &target) {
    long long int result(0);
    long long int mulI(SCALE_);
    bool posi_or_nega(true);
    char negative(genericNegativePrefixForScale(SCALE_));
    for (auto index(target.end()); index >= target.begin(); --index, mulI *= SCALE_) {
      if (*index == negative) {
	posi_or_nega = false;
	break;
      }
      result += static_cast<long long int>(scaleSymbolMapping((*index))) * mulI;
    }

    return (!posi_or_nega) : covertNegaToPosi(result) : result;
  }
  */

  // specifically implement of int
  template<>
  long long int numscale<int>::defaultGeneralCombine(const int &target) {
    /*
    long long int decal_scale(10);
    long long int tempValue = target;
    long long int result(0);
    long long int mulI(SCALE_);
    bool positive_negative((tempValue < 0) ? true : false);
    auto remainder = [tempValue, decal_scale](void) -> long long int {
      return tempValue - tempValue / decal_scale * decal_scale;
    };
    auto quotientor = [tempValue, decal_scale](void) -> long long int {
      return tempValue / decal_scale;
    };

    if (!positive_negative)
      tempValue *= -1;

    for (long long int quotient(1); quotient != 0; decal_scale *= 10, mulI *= SCALE_) {
      quotient = quotientor();
      result += remainder() * mulI;
    }

    return (positive_negative) ? result : result * -1;
    */

    return target;

  }

  // public members

  template<class T>
  void numscale<T>::install_or_uninstall(int action, combineFunc<T> theFunc) {
    switch (action) {
    case INSTALL_COMBINE:
      if (!theFunc)
	return;
      else
	install_combine(theFunc);
      break;

    case UNINSTALL_COMBINE:
      uninstall_combine();
      break;

    default:
      // unknown type.
      return;
    }

  }

  template<class T>
  void numscale<T>::install_or_uninstall(int action, transformFunc theFunc) {
    switch (action) {
    case INSTALL_TRANSFORM:
      if (!theFunc)
	return;
      else
	install_transform(theFunc);
      break;

    case UNINSTALL_TRANSFORM:
      uninstall_transform();

    default:
      // unknown type.
      return;
    }
  }

  template<class T>
  void numscale<T>::doTransform(int sscale, int dscale, const T &target) {
    if (!combine)
      combine = defaultGeneralCombine;
    if (!transform)
      transform = defaultGeneralTransform;

    SCALE_ = sscale;	// use enum type as SCALE.
    value_ = combine(target);

    SCALE_ = dscale;
    transBuffer_ = transform(value_);
  }

  template<class T>
  string numscale<T>::getResult(void) { return this->transBuffer_; }


  // END OF NAMESPACE
}
