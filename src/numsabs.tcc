
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
  
  using std::cout;
  using std::endl;


  template<class T>
  requires must_be_container<T>
  using getIterator = T::iterator;


  // Constructor and Destructor
  template<class T>
  numscale<T>::numscale() : transBuffer_() {
    value_ = 0;
    SCALE_ = 2;
    combine = NULL;
    transform = NULL;
  }

  template<class T>
  numscale<T>::numscale(size_t bufflen) : transBuffer_() {
    value_ = 0;
    SCALE_ = 2;
    combine = NULL;
    transform = NULL;
  }

  template<class T>
  numscale<T>::~numscale() { }

  // protected members
  template<class T>
  long long int numscale<T>::defaultGeneralCombine(T &target) {
    long long int mulI(1);
    long long int result(0);
    char negative_prefix(generateNegativePrefixForScale(SCALE_));
    getIterator<T> first(target.begin());

    // count bits of target number.
    for (getIterator<T> index(target.end() - 1); index > first; --index, mulI *= SCALE_)
      result += static_cast<long long int>(scaleSymbolMappingCTV(*index)) * mulI;

    // computer use the most taller bit as negative or positive indicator.
    if (*first == negative_prefix)
      result *= -1;
    else
      result += static_cast<long long int>(scaleSymbolMappingCTV(*first)) * mulI;

    return result;
  }

  template<class T>
  string numscale<T>::defaultGeneralTransform(long long int target) {
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
      tempbuff += scaleSymbolMappingVTC(remainder(quotient));
      quotient = quotientor(quotient);
    } 

    // complete buffer.
    if (if_negative)
      result += negative_prefix;

    for (auto it_of_temp(tempbuff.end() - 1); it_of_temp >= tempbuff.begin(); --it_of_temp) {
      result += *it_of_temp;
    }

#if defined DEBUG
    cout<<tempbuff.length()<<" "<<tempbuff.size()<<endl;
    cout<<result.length()<<" "<<tempbuff.size()<<endl;
    cout<<tempbuff.empty()<<endl;
    cout<<result.empty()<<endl;
    cout<<tempbuff.substr(0,3)<<endl;
    cout<<result.substr(0,3)<<endl;
#endif

    return result;
  }

  /*
  // specifically implement of string
  template<>
  long long int numscale<string>::defaultGeneralCombine(const string &target) {
    long long int result(0);
    long long int mulI(SCALE_);
    bool posi_or_nega(true);
    char negative(generateNegativePrefixForScale(SCALE_));
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
  long long int numscale<int>::defaultGeneralCombine(int &target) {
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
  void numscale<T>::doTransform(int sscale, int dscale,T &target) {

//    Nums_cf<T> cf(defaultGeneralCombine);
//    nums_tf tf(defaultGeneralTransform);

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

  template<class T>
  string numscale<T>::getResult(void) { auto ret(this->transBuffer_); this->transBuffer_.clear(); return ret; }


  // END OF NAMESPACE
}
