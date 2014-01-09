/** @file "/vdjml/include/vdjml/interval.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef INTERVAL_HPP_
#define INTERVAL_HPP_
#include <limits>
#include "boost/cstdint.hpp"
#include "vdjml/exception.hpp"
#include "vdjml/detail/comparison_operators_macro.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
template<class T> class Interval {
public:
   typedef T value_type;
   struct Err : public base_exception {};

private:
   Interval(const std::size_t pos, const std::size_t len)
   : pos_(pos), len_(len)
   {
      if( std::numeric_limits<value_type>::max() < pos ) BOOST_THROW_EXCEPTION(
               Err()
               << typename Err::msg_t("position out of range")
               << typename Err::int1_t(pos)
      );
      if( std::numeric_limits<value_type>::max() < len ) BOOST_THROW_EXCEPTION(
               Err()
               << typename Err::msg_t("length out of range")
               << typename Err::int1_t(len)
      );
   }

public:

   static Interval first_length(const std::size_t first, const std::size_t len) {
      return Interval(first, len);
   }

   static Interval first_last(const std::size_t first, const std::size_t last) {
      if( last < first ) BOOST_THROW_EXCEPTION(
               Err()
               << typename Err::msg_t("invalid interval: last < first")
               << typename Err::int1_t(first)
               << typename Err::int2_t(last)
      );

      return Interval(first, last - first + 1);
   }

   Interval() : pos_(0), len_(0) {}

   std::size_t first() const {return pos_;}
   std::size_t last() const {return len_ ? (std::size_t)pos_ + len_ - 1 : pos_;}
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

typedef Interval<boost::uint_least16_t> short_interval; //65,536 max

}//namespace vdjml
#endif /* INTERVAL_HPP_ */
