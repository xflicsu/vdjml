/** @file "/vdjml/include/vdjml/detail/object_id_base.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013-4 @author Mikhail K Levin
*******************************************************************************/
#ifndef OBJECT_ID_BASE_HPP_
#define OBJECT_ID_BASE_HPP_
#include <iosfwd>
#include "boost/cstdint.hpp"

namespace vdjml{ namespace detail{

/**@brief 
*******************************************************************************/
template<class Super, class Val = boost::uint_least32_t> class Base_id {
   typedef Base_id self_type;
protected:
   typedef Base_id base;
public:
   typedef Val value_type;
   explicit Base_id(const value_type val) : val_(val) {}
   Base_id(Super const& s) : val_(s.val_) {}
   bool operator==(const Super& t) const {return val_ == t.val_;}
   bool operator<(const Super& t) const {return val_< t.val_;}
   bool operator<=(const Super& t) const {return val_<= t.val_;}
   bool operator>(const Super& t) const {return val_ > t.val_;}
   bool operator>=(const Super& t) const {return val_ >= t.val_;}
   bool operator!=(const Super& t) const {return val_ != t.val_;}
   value_type operator()() const {return val_;}
private:
   typedef value_type self_type::*unspecified_bool_type; //ptr to member
public:
   //"safe bool idiom"
   operator unspecified_bool_type() const {return val_ == 0 ? 0 : &self_type::val_;}
protected:
   value_type val_;
};

}//namespace detail
}//namespace vdjml
#endif /* OBJECT_ID_BASE_HPP_ */
