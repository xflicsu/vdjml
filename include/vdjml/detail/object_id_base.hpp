/** @file "/vdjml/include/vdjml/detail/object_id_base.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013-4 @author Mikhail K Levin
*******************************************************************************/
#ifndef OBJECT_ID_BASE_HPP_
#define OBJECT_ID_BASE_HPP_
#include <iosfwd>
#include "boost/cstdint.hpp"
#include "vdjml/detail/comparison_operators_macro.hpp"

namespace vdjml{
template<class Id> class Id_iterator;
namespace detail{

/**@brief 
*******************************************************************************/
template<class Super, class Val = boost::uint_least32_t> class Base_id {
   friend class Id_iterator<Super>;
   typedef Base_id self_type;
protected:
   typedef Base_id base;
public:
   typedef Val value_type;
   explicit Base_id(const value_type val) : val_(val) {}
   Base_id(Super const& s) : val_(s.val_) {}
   bool operator==(const Super& t) const {return val_ == t.val_;}
   bool operator<(const Super& t) const {return val_< t.val_;}
   VDJML_COMPARISON_OPERATOR_MEMBERS(Super)
   value_type operator()() const {return val_;}
private:
   typedef value_type self_type::*unspecified_bool_type; //ptr to member
public:
   //"safe bool idiom"
   operator unspecified_bool_type() const {return val_ == 0 ? 0 : &self_type::val_;}
protected:
   value_type val_;
};

/**
*******************************************************************************/
template<class ChT, class Tr, class S, class V> inline
std::basic_ostream<ChT,Tr>& operator<<(
      std::basic_ostream<ChT,Tr>& os,
      Base_id<S,V> const& id
) {
   return os << id();
}

/**
*******************************************************************************/
template<class S,class V> inline std::size_t hash_value(Base_id<S,V> const& id) {
   return id();
}

#define VDJML_OBJECT_ID(name)                               \
   struct name : public ::vdjml::detail::Base_id<name> {    \
   explicit name(const value_type x) : base(x) {}           \
   name() : base(0) {}                                      \
   }                                                        \
/* */

}//namespace detail
}//namespace vdjml
#endif /* OBJECT_ID_BASE_HPP_ */
