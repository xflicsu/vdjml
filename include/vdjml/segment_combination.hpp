/** @file "/vdjml/include/vdjml/segment_combination.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef SEGMENT_COMBINATION_HPP_
#define SEGMENT_COMBINATION_HPP_
#include "vdjml/config.hpp"
#include "vdjml/format_version.hpp"
#include "vdjml/object_ids.hpp"
#include "vdjml/interval.hpp"
#include "vdjml/detail/vector_set.hpp"
#include "vdjml/match_metrics.hpp"

namespace vdjml{
class Xml_writer;

/**@brief 
*******************************************************************************/
struct Gene_region : public Match_metrics {
   Gene_region(
            const Numsys_id num_system,
            const Region_id region,
            short_interval const& range,
            Match_metrics const& mm
   )
   : Match_metrics(mm),
     num_system_(num_system),
     region_(region),
     range_(range)
   {}

   Numsys_id num_system_;
   Region_id region_;
   short_interval range_;
};

/**@brief
*******************************************************************************/
struct Segment_combination {
   explicit Segment_combination(
            const Seg_match_id id1,
            const Seg_match_id id2 = Seg_match_id(),
            const Seg_match_id id3 = Seg_match_id(),
            const Seg_match_id id4 = Seg_match_id(),
            const Seg_match_id id5 = Seg_match_id()
   )
   : smv_()
   {
      if( id1 ) smv_.insert(id1);
      if( id2 ) smv_.insert(id2);
      if( id3 ) smv_.insert(id3);
      if( id4 ) smv_.insert(id4);
      if( id5 ) smv_.insert(id5);
   }

   detail::Vector_set<Seg_match_id> smv_;
   std::vector<Gene_region> grv_;
};

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Segment_combination const& sc,
         const unsigned version = current_version
);

}//namespace vdjml
#endif /* SEGMENT_COMBINATION_HPP_ */
