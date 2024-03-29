/** @file "/vdjml/include/vdjml/segment_combination.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef SEGMENT_COMBINATION_HPP_
#define SEGMENT_COMBINATION_HPP_
#include "vdjml/config.hpp"
#include "vdjml/vdjml_current_version.hpp"
#include "vdjml/object_ids.hpp"
#include "vdjml/interval.hpp"
#include "vdjml/detail/vector_set.hpp"
#include "vdjml/match_metrics.hpp"
#include "vdjml/detail/comparison_operators_macro.hpp"

namespace vdjml{
class Xml_writer;
class Results_meta;

/**@brief 
*******************************************************************************/
struct Gene_region : public Match_metrics {
   Gene_region(
            const Numsys_id num_system,
            const Region_id region,
            interval_short const& range,
            Match_metrics const& mm
   )
   : Match_metrics(mm),
     num_system_(num_system),
     region_(region),
     range_(range)
   {}

   bool operator==(Gene_region const& gr) const {
      return num_system_ == gr.num_system_ && region_ == gr.region_;
   }

   bool operator<(Gene_region const& gr) const {
      if( num_system_ < gr.num_system_ ) return true;
      if( gr.num_system_ < num_system_ ) return false;
      return region_ < gr.region_;
   }

   VDJML_COMPARISON_OPERATOR_MEMBERS(Gene_region)

   Numsys_id num_system_;
   Region_id region_;
   interval_short range_; ///< read positions aligned
};

/**@brief
*******************************************************************************/
class Segment_combination {

public:
   typedef detail::Vector_set<Seg_match_id> segment_set;
   typedef detail::Vector_set<Gene_region> gene_region_set;

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

   segment_set const& segments() const {return smv_;}
   gene_region_set const& regions() const {return grv_;}

   void insert_region(
            const Numsys_id num_system,
            const Region_id region,
            interval_short const& range,
            Match_metrics const& mm
   ) {
      grv_.insert(Gene_region(num_system, region, range, mm));
   }

private:
   segment_set smv_;
   gene_region_set grv_;
};

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Segment_combination const& sc,
         Results_meta const& rm,
         const unsigned version = VDJML_CURRENT_VERSION
);

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Gene_region const& gr,
         Results_meta const& rm,
         const unsigned version = VDJML_CURRENT_VERSION
);

}//namespace vdjml
#endif /* SEGMENT_COMBINATION_HPP_ */
