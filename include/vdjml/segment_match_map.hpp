/** @file "/vdjml/include/vdjml/segment_match_map.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef SEGMENT_MATCH_MAP_HPP_
#define SEGMENT_MATCH_MAP_HPP_
#include "boost/foreach.hpp"
#include "vdjml/segment_match.hpp"
#include "vdjml/object_ids.hpp"
#include "vdjml/detail/id_map.hpp"
#include "vdjml/detail/id_iterator.hpp"
#include "vdjml/config.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
class VDJML_DECL Segment_match_map {
   typedef detail::Id_map<Seg_match_id, Segment_match> map_t;
public:
   typedef map_t::iterator iterator;
   typedef map_t::const_iterator const_iterator;
   std::size_t size() const {return map_.size();}
   const_iterator begin() const {return map_.begin();}
   const_iterator end() const {return map_.end();}
   bool empty() const {return map_.empty();}
   Segment_match const& operator[](const Seg_match_id id) const {return map_[id];}
   Segment_match& operator[](const Seg_match_id id) {return map_[id];}
   Segment_match const* find(const Seg_match_id id) const {return map_.find(id);}

   Seg_match_id insert(Segment_match const& sm) {
      //only a few segment matches per read result are expected
      BOOST_FOREACH(Segment_match& sm0, map_) {
         if( sm == sm0 ) {
            merge(sm0, sm);
            return sm0.id_;
         }
      }
      const Seg_match_id id = map_.insert(sm);
      map_[id].id_ = id;
      return id;
   }

private:
   map_t map_;
};

}//namespace vdjml
#endif /* SEGMENT_MATCH_MAP_HPP_ */
