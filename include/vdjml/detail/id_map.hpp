/** @file "/vdjml/include/vdjml/detail/id_map.hpp"
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef ID_MAP_HPP_
#define ID_MAP_HPP_
#include <vector>
#include "boost/assert.hpp"
#include "vdjml/exception.hpp"

namespace vdjml{ namespace detail{

/**@brief 
*******************************************************************************/
template<class Id, class Obj, template<class,class> class Stor = std::vector >
class Id_map{
   typedef Stor<Obj, std::allocator<Obj> > vector_t;

public:
   typedef Id_map self_type;
   typedef Id id_type;
   typedef Obj value_type;
   typedef typename vector_t::iterator iterator;
   typedef typename vector_t::const_iterator const_iterator;
   typedef base_exception Err;

   std::size_t size() const { return vid_.size(); }
   const_iterator begin() const {return vid_.begin();}
   const_iterator end() const {return vid_.end();}
   bool empty() const {return !(vid_.size());}
   id_type min_id() const {return id_type(1);}
   id_type max_id() const {return pos2id(vid_.size()-1);}
   void reserve(const id_type id) {vid_.reserve(vpos(id) + 1);}

   value_type const& operator[](const id_type id) const {
      BOOST_ASSERT( check_range(id) && "invalid ID" );
      return vid_[vpos(id)];
   }

   value_type& operator[](const id_type id) {
      BOOST_ASSERT( check_range(id) && "invalid ID" );
      return vid_[vpos(id)];
   }

   value_type const& at(const id_type id) const {
      if( ! check_range(id) ) BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("invalid ID")
               << Err::int1_t(id())
      );
      return vid_[vpos(id)];
   }

   value_type& at(const id_type id) {
      if( ! check_range(id) ) BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("invalid ID")
               << Err::int1_t(id())
      );
      return vid_[vpos(id)];
   }

   id_type insert(value_type const& obj) {
         const id_type id = pos2id(vid_.size());
         vid_.push_back(obj);
         return id;
   }

   /**
    @return reference to object mapped to id;
    the object is default constructed if needed
    */
   value_type& insert(const id_type id) {
      const std::size_t n = vpos(id);
      if( n >= vid_.size() ) {
         vid_.resize(n + 1);
      }
      return vid_[n];
   }

   void erase(const id_type id) {
      BOOST_ASSERT( check_range(id) );
      const std::size_t pos = vpos(id);
      vid_[pos] = value_type();
   }

   void clear() {
      vid_.clear();
   }

private:
   vector_t vid_;

   std::size_t vpos(const id_type id) const {
      BOOST_ASSERT(id() >= 1 && "invalid ID");
      return id() - 1;
   }

   id_type pos2id(const std::size_t n) const {return id_type(n + 1);}

   bool check_range(const id_type id) const {
      return id() >= 1 && vpos(id) < vid_.size();
   }
};

}//namespace detail
}//namespace vdjml
#endif /* ID_MAP_HPP_ */
