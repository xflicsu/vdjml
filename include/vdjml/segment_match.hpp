/** @file "/vdjml/include/vdjml/segment_match.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef SEGMENT_MATCH_HPP_
#define SEGMENT_MATCH_HPP_
#include <string>
#include <vector>
#include "vdjml/object_ids.hpp"
#include "vdjml/btop.hpp"
#include "vdjml/config.hpp"
#include "vdjml/detail/vector_set.hpp"
#include "vdjml/detail/comparison_operators_macro.hpp"
#include "vdjml/format_version.hpp"
#include "vdjml/gene_segment_type.hpp"
#include "vdjml/interval.hpp"
#include "vdjml/match_metrics.hpp"

namespace vdjml{
class Read_result;
class Xml_writer;
class Results_meta;

/**@brief 
*******************************************************************************/
struct Germline_position {
   Germline_position(
            const Gl_db_id gdb,
            const Numsys_id num_sys,
            const unsigned pos,
            std::string gene
   )
   : gdb_id_(gdb),
     num_sys_id_(num_sys),
     pos_(pos),
     gene_(gene)
   {}

   Gl_db_id gdb_id_;
   Numsys_id num_sys_id_;
   unsigned pos_;
   std::string gene_;
};

/**@brief
*******************************************************************************/
struct Aa_substitution {

   Aa_substitution(
            const char from,
            const char to,
            const unsigned read_pos,
            Germline_position const& gp
   )
   : from_(from), to_(to), r_pos_(read_pos)
   {
      gpv_.push_back(gp);
   }

//   void insert_gp(Germline_position const& gp) {gpv_

   char from_;
   char to_;
   unsigned r_pos_;
   std::vector<Germline_position> gpv_;
};

/**@brief
*******************************************************************************/
struct Germline_segment_match : public Match_metrics {
   Germline_segment_match(
            const Numsys_id numsys,
            const Aligner_id aligner,
            const Gl_seg_id germline_segment,
            interval_65k const& range,
            Match_metrics const& mm
   )
   : Match_metrics(mm),
     num_system_(numsys),
     aligner_(aligner),
     gl_segment_(germline_segment),
     range_(range)
   {}

   bool operator==(Germline_segment_match const& gsm) const {
      return
               num_system_ == gsm.num_system_ &&
               aligner_ == gsm.aligner_ &&
               gl_segment_ == gsm.gl_segment_ &&
               range_ == gsm.range_
               ;
   }

   bool operator<(Germline_segment_match const& gsm) const {
      if( num_system_ < gsm.num_system_ ) return true;
      if( gsm.num_system_ < num_system_ ) return false;
      if( aligner_ < gsm.aligner_ ) return true;
      if( gsm.aligner_ < aligner_ ) return false;
      if( gl_segment_ < gsm.gl_segment_ ) return true;
      if( gsm.gl_segment_ < gl_segment_ ) return false;
      return range_ < gsm.range_;
   }

   VDJML_COMPARISON_OPERATOR_MEMBERS(Germline_segment_match)

   Numsys_id num_system_;
   Aligner_id aligner_;
   Gl_seg_id gl_segment_;
   interval_65k range_;
};



/**@brief Alignment results for a read segment
@details
*******************************************************************************/
class VDJML_DECL Segment_match {
   friend class Segment_match_map;
   typedef detail::Vector_set<Germline_segment_match> germline_segment_set;
public:
   Segment_match(
            Btop const& btop,
            interval_65k const& read_range
   )
   : btop_(btop),
     range_(read_range)
   {}

   Seg_match_id id() const {return id_;}
   Btop const& btop() const {return btop_;}
   interval_65k const& range() const {return range_;}
   germline_segment_set const& germline_segments() const {return gsv_;}
   void insert(Germline_segment_match const& gsm) {gsv_.insert(gsm);}

private:
   Seg_match_id id_; //may be removed to save space
   Btop btop_;
   interval_65k range_;
   detail::Vector_set<Germline_segment_match> gsv_;
};

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Germline_segment_match const& gsm,
         Results_meta const& rm,
         const unsigned version = current_version
);

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Segment_match const& sm,
         Results_meta const& rm,
         const unsigned version = current_version
);

}//namespace vdjml
#endif /* SEGMENT_MATCH_HPP_ */
