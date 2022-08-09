 
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

  template<class T>
  requires must_be_container<T>
  using getIterator = T::iterator;

  // Constructor and Destructor

  /* try to alloc memory ahead class object
   * was used.
   */
  template<class T>
  numscale<T>::numscale() : transBuffer_(64,'\0') {
    value_ = 0;
    SCALE_ = 2;
    combine = NULL;
    transform = NULL;
    transBuffer_.clear();
  }

  template<class T>
  numscale<T>::numscale(size_t bufflen) : transBuffer_(128,'\0') {
    value_ = 0;
    SCALE_ = 2;
    combine = NULL;
    transform = NULL;
    transBuffer_.clear();
  }

  template<class T>
  numscale<T>::~numscale() { }

  // protected members
  template<class T>
  long long int numscale<T>::defaultGeneralCombine(T &target)const {
    long long int mulI(1);
    long long int result(0);
    char negative_prefix(generateNegativePrefixForScale(SCALE_));
    getIterator<T> first(target.begin());

    // count bits of target number.
    for (getIterator<T> index(target.end() - 1); index > first; --index, mulI *= SCALE_)
      result += static_cast<long long int>(scaleSymbolMapping(*index)) * mulI;

    // computer use the most taller bit as negative or positive indicator.
    if (*first == negative_prefix)
      result *= -1;
    else
      result += static_cast<long long int>(scaleSymbolMapping(*first)) * mulI;

    return result;
  }

  template<class T>
  string numscale<T>::defaultGeneralTransform(long long int target)const {
    string tempbuff(transBuffer_);
    string result(transBuffer_);
    char negative_prefix(generateNegativePrefixForScale(SCALE_));
    long long int quotient((target < 0) ? target * -1 : target);
    bool if_negative((target < 0) ? true : false);
    const long long int divI(SCALE_);

    auto remainder = [divI](unsigned long long int x) -> long long int {
      return x - x / divI * divI;
    };
    auto quotientor = [divI](unsigned long long int x) -> long long int {
      return x / divI;
    };

    // transform number scale with remainder.
    for ( ; quotient != 0; ) {
      tempbuff += scaleSymbolMapping(static_cast<int>(remainder(quotient)));
      quotient = quotientor(quotient);
    } 

    // complete buffer.
    // if target is a negative value,the result must be contains the negative prefix
    // which same as the symbol of SCALE_ scale.
    if (if_negative)
      result += negative_prefix;

    for (auto it_of_temp(tempbuff.end() - 1); it_of_temp >= tempbuff.begin(); --it_of_temp) {
      result += *it_of_temp;
    }

    return result;
  }

  // specifically implement of int
  template<>
  long long int numscale<int>::defaultGeneralCombine(int &target)const {
    return target;
  }

  // public members

  /* install_or_uninstall()
   * if got a unknown type,
   * either of overloaded instance do nothing.
   */
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
  void numscale<T>::doTransform(int sscale, int dscale,T &target) {
    SCALE_ = sscale;	// use enum type as SCALE.
    if (!combine)
      value_ = defaultGeneralCombine(target);
    else
      value_ = combine(target);
    SCALE_ = dscale;
    if (!transform)
      transBuffer_ = defaultGeneralTransform(value_);
    else
      transBuffer_ = transform(value_);
  }

  // clear once before next transform.
  template<class T>
  string numscale<T>::getResult(void) { auto ret(this->transBuffer_); this->transBuffer_.clear(); return ret; }

  // END OF NAMESPACE
}
