/** @file "/vdjml/include/vdjml/detail/vector_set.hpp"
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013-4 @author Mikhail K Levin
*******************************************************************************/
#ifndef VECTOR_SET_HPP_
#define VECTOR_SET_HPP_
#include <vector>
#include <algorithm>

namespace vdjml{ namespace detail{

/**@brief Set of objects stored in an ordered vector
*******************************************************************************/
template<class T, class Alloc = std::allocator<T> >
class Vector_set {
   typedef std::vector<T, Alloc> stor_t;
public:
   typedef Vector_set self_type;
   typedef T value_type;
   typedef typename stor_t::iterator iterator;
   typedef typename stor_t::const_iterator const_iterator;

   iterator begin() {return v_.begin();}
   iterator end() {return v_.end();}
   const_iterator begin() const {return v_.begin();}
   const_iterator end() const {return v_.end();}
   value_type const& front() const {return v_.front();}
   value_type const& back() const {return v_.back();}
   std::size_t size() const {return v_.size();}
   bool empty() const {return v_.empty();}
   void reserve(const std::size_t n) {v_.reserve(n);}
   void pop_back() {v_.pop_back();}
   void clear() {v_.clear();}

   template<class Iter> void insert(Iter i1, Iter i2) {
      for( ; i1 != i2; ++i1 ) {
         const iterator i = std::lower_bound(v_.begin(), v_.end(), *i1);
         if( i == v_.end() || *i1 < *i ) {
            v_.insert(i, *i1);
         }
      }
   }

   std::pair<iterator, bool> insert(value_type const& t) {
      iterator i = std::lower_bound(v_.begin(), v_.end(), t);
      if( i == v_.end() || t < *i ) {
         return std::make_pair(v_.insert(i, t), true);
      }
      return std::make_pair(i, false);
   }

   template<typename CompatType>
   unsigned erase(CompatType const& t) {
      iterator i = std::lower_bound(v_.begin(), v_.end(), t);
      if( i == v_.end() || t < *i ) return 0;
      v_.erase(i);
      return 1;
   }

   /**
    @tparam CompatType less than comparable to @a value_type
    */
   template<typename CompatType>
   value_type const* find(CompatType const& t) const {
      const_iterator i = std::lower_bound(v_.begin(), v_.end(), t);
      //i points to t == *i, to t < *i, or to i == end()
      if( i == v_.end() || t < *i ) return 0;
      return &(*i);
   }

   value_type const& operator[](const std::size_t n) const {return v_[n];}
   value_type const& at(const std::size_t n) const {return v_.at(n);}

   bool operator==(self_type const& vs2) const {return v_ == vs2.v_;}
   bool operator!=(self_type const& vs2) const {return !( (*this) == vs2);}

private:
   stor_t v_;
};

}//namespace detail
}//namespace vdjml
#endif /* VECTOR_SET_HPP_ */
