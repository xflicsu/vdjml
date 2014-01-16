/** @file "/vdjml/include/vdjml/interval.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef INTERVAL_HPP_
#define INTERVAL_HPP_
#include <limits>
#include "boost/cstdint.hpp"
#include "vdjml/config.hpp"
#include "vdjml/exception.hpp"
#include "vdjml/detail/comparison_operators_macro.hpp"
#include "vdjml/vdjml_current_version.hpp"

namespace vdjml{
class Xml_writer;

struct Interval_err : public base_exception {};

/**@brief 
*******************************************************************************/
template<class T> class Interval {
public:
   typedef T value_type;

private:
   Interval(const std::size_t pos, const std::size_t len)
   : pos_(pos), len_(len)
   {
      if( std::numeric_limits<value_type>::max() < pos ) BOOST_THROW_EXCEPTION(
               Interval_err()
               << Interval_err::msg_t("position out of range")
               << Interval_err::int1_t(pos)
      );
      if( std::numeric_limits<value_type>::max() < len ) BOOST_THROW_EXCEPTION(
               Interval_err()
               << Interval_err::msg_t("length out of range")
               << Interval_err::int1_t(len)
      );
   }

public:

   /**
    @param pos0 zero-based interval starting position
    @param len interval length
    */
   static Interval pos0_len(const std::size_t pos0, const std::size_t len) {
      return Interval(pos0, len);
   }

   /**
    @param first1 one-based interval starting position
    @param last1 one-based last position of interval
    */
   static Interval first_last_1(const std::size_t first1, const std::size_t last1) {
      if( first1 == 0 || last1 == 0 ) BOOST_THROW_EXCEPTION(
               Interval_err()
               << Interval_err::msg_t("one-based position is expected")
               << Interval_err::int1_t(first1)
               << Interval_err::int2_t(last1)
      );

      if( last1 < first1 ) BOOST_THROW_EXCEPTION(
               Interval_err()
               << Interval_err::msg_t("invalid interval: last < first")
               << Interval_err::int1_t(first1)
               << Interval_err::int2_t(last1)
      );

      return Interval(first1 - 1, last1 - first1 + 1);
   }

   /**
    @param first1 zero-based interval starting position
    @param last1 zero-based last position of interval
    */
   static Interval first_last_0(const std::size_t first0, const std::size_t last0) {
      if( last0 < first0 ) BOOST_THROW_EXCEPTION(
               Interval_err()
               << Interval_err::msg_t("invalid interval: last < first")
               << Interval_err::int1_t(first0)
               << Interval_err::int2_t(last0)
      );

      return Interval(first0, last0 - first0 + 1);
   }

   Interval() : pos_(0), len_(0) {}

   /**@return zero-based start position of interval */
   std::size_t pos_0() const {return pos_;}

   /**@return one-based start position of interval */
   std::size_t pos_1() const {return pos_ + 1;}

   /**@return zero-based start position of interval */
   std::size_t last_0() const {return len_ ? (std::size_t)pos_ + len_ - 1 : pos_;}

   /**@return one-based start position of interval */
   std::size_t last_1() const {return len_ ? (std::size_t)pos_ + len_ : pos_;}

   /**@return interval length */
   std::size_t length() const {return len_;}

   bool operator==(Interval const& i) const {
      return pos_ == i.pos_ && len_ == i.len_;
   }

   bool operator<(Interval const& i) const {
      if( pos_ < i.pos_ ) return true;
      if( i.pos_ < pos_ ) return false;
      return len_ < i.len_;
   }

   VDJML_COMPARISON_OPERATOR_MEMBERS(Interval)

private:
   value_type pos_;
   value_type len_;
};

/** interval with 65,536 max position and length */
typedef Interval<boost::uint_least16_t> interval_short;


/**
@param xw XML writer
@param range interval
@param version format version
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         interval_short const& range,
         const unsigned version = VDJML_CURRENT_VERSION
);

}//namespace vdjml
#endif /* INTERVAL_HPP_ */
