/** @file "/vdjml/include/vdjml/segment_match.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef SEGMENT_MATCH_HPP_
#define SEGMENT_MATCH_HPP_
#include <string>
#include <vector>
#include "boost/foreach.hpp"
#include "vdjml/object_ids.hpp"
#include "vdjml/btop.hpp"
#include "vdjml/config.hpp"
#include "vdjml/detail/vector_set.hpp"
#include "vdjml/detail/id_map.hpp"
#include "vdjml/detail/comparison_operators_macro.hpp"
#include "vdjml/vdjml_current_version.hpp"
#include "vdjml/gene_segment_type.hpp"
#include "vdjml/interval.hpp"
#include "vdjml/match_metrics.hpp"
#include "vdjml/aa_substitution.hpp"

namespace vdjml{
class Read_result;
class Xml_writer;
class Results_meta;

/**@brief
*******************************************************************************/
struct Gl_segment_match : public Match_metrics {
   Gl_segment_match(
            const Numsys_id numsys,
            const Aligner_id aligner,
            const Gl_seg_id germline_segment,
            interval_short const& range,
            Match_metrics const& mm
   )
   : Match_metrics(mm),
     id_(),
     num_system_(numsys),
     aligner_(aligner),
     gl_segment_(germline_segment),
     range_(range)
   {}

   bool operator==(Gl_segment_match const& gsm) const {
      return
               num_system_ == gsm.num_system_ &&
               aligner_ == gsm.aligner_ &&
               gl_segment_ == gsm.gl_segment_ &&
               range_ == gsm.range_
               ;
   }

   bool operator<(Gl_segment_match const& gsm) const {
      if( num_system_ < gsm.num_system_ ) return true;
      if( gsm.num_system_ < num_system_ ) return false;
      if( aligner_ < gsm.aligner_ ) return true;
      if( gsm.aligner_ < aligner_ ) return false;
      if( gl_segment_ < gsm.gl_segment_ ) return true;
      if( gsm.gl_segment_ < gl_segment_ ) return false;
      return range_ < gsm.range_;
   }

   VDJML_COMPARISON_OPERATOR_MEMBERS(Gl_segment_match)

   Gl_seg_match_id id_;
   Numsys_id num_system_;
   Aligner_id aligner_;
   Gl_seg_id gl_segment_;
   interval_short range_;
};

/**@brief Alignment results for a read segment
@details
*******************************************************************************/
class VDJML_DECL Segment_match {
   friend class Segment_match_map;
public:
   typedef detail::Id_map<Gl_seg_match_id, Gl_segment_match> germline_segment_map;
   typedef detail::Vector_set<Aa_substitution> aa_substitution_set;
   struct Err : public base_exception {};

   Segment_match(
            Btop const& btop,
            interval_short const& read_range
   )
   : btop_(btop),
     range_(read_range)
   {}

   Seg_match_id id() const {return id_;}
   Btop const& btop() const {return btop_;}
   interval_short const& range() const {return range_;}
   germline_segment_map const& germline_segments() const {return gsv_;}
   aa_substitution_set const& aa_substitutions() const {return aass_;}

   Gl_seg_match_id insert(Gl_segment_match const& gsm) {
//      BOOST_FOREACH(Gl_segment_match const& gsm0, gsv_) {
//         if( gsm0 == gsm )
//      }
      //todo:
      const Gl_seg_match_id id = gsv_.insert(gsm);
      gsv_[id].id_ = id;
      return id;
   }

   void insert(Aa_substitution const& aas) {
      aass_.insert(aas);
   }

   bool operator==(Segment_match const& sm) const {
      return btop_ == sm.btop_ && range_ == sm.range_;
   }

private:
   Seg_match_id id_; //may be removed to save space
   Btop btop_;
   interval_short range_;
   germline_segment_map gsv_;
   aa_substitution_set aass_;
};

/**@brief
*******************************************************************************/
VDJML_DECL void merge(Segment_match& sm1, Segment_match const& sm2);

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Gl_segment_match const& gsm,
         Results_meta const& rm,
         const unsigned version = VDJML_CURRENT_VERSION
);

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Segment_match const& sm,
         Results_meta const& rm,
         const unsigned version = VDJML_CURRENT_VERSION
);

}//namespace vdjml
#endif /* SEGMENT_MATCH_HPP_ */
