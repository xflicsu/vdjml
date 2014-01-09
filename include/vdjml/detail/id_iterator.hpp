/** @file "/vdjml/include/vdjml/detail/id_iterator.hpp"
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef ID_ITERATOR_HPP_
#define ID_ITERATOR_HPP_
#include "boost/iterator/iterator_facade.hpp"
#include "boost/range.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
template<class Id> class Id_iterator
         : public boost::iterator_facade<
              Id_iterator<Id>, Id, boost::forward_traversal_tag, Id
           > {

   friend class boost::iterator_core_access;
public:
   typedef Id_iterator self_type;
   Id_iterator() : id_() {}
   explicit Id_iterator(const Id id) : id_(id) {}

private:
   Id id_;
   Id dereference() const {return id_;}
   void increment() {++id_.val_;}
   bool equal(self_type const& i) const {return i.id_ == id_;}
};

/**@brief
*******************************************************************************/
template<class Id> inline boost::iterator_range<Id_iterator<Id> >
id_range(const Id id1, const Id id2) {
   typedef Id_iterator<Id> iter_t;
   return boost::iterator_range<Id_iterator<Id> >(iter_t(id1), iter_t(id2));
}

}//namespace vdjml
#endif /* ID_ITERATOR_HPP_ */
