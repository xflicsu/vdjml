/** @file "/vdjml/include/vdjml/segment_match_map.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef SEGMENT_MATCH_MAP_HPP_
#define SEGMENT_MATCH_MAP_HPP_
#include "vdjml/segment_match.hpp"
#include "vdjml/object_ids.hpp"
#include "vdjml/detail/id_map.hpp"
#include "vdjml/detail/id_iterator.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
class Segment_match_map {
   typedef detail::Id_map<Seg_match_id, Segment_match> map_t;
public:
   typedef Id_iterator<Seg_match_id> iterator;
   typedef iterator const_iterator;
   std::size_t size() const {return map_.size();}
   const_iterator begin() const {return iterator(map_.min_id());}
   const_iterator end() const {return iterator(map_.max_id());}
   bool empty() const {return ! size();}
   Segment_match const& operator[](const Seg_match_id id) const {return map_[id];}
   Seg_match_id insert(Segment_match const& sm) {return map_.insert(sm);}

private:
   map_t map_;
};

}//namespace vdjml
#endif /* SEGMENT_MATCH_MAP_HPP_ */
