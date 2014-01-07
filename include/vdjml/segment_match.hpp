/** @file "/vdjml/include/vdjml/segment_match.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef SEGMENT_MATCH_HPP_
#define SEGMENT_MATCH_HPP_
#include <string>
#include <vector>
#include "vdjml/config.hpp"
#include "vdjml/btop.hpp"
#include "vdjml/aligner_id.hpp"
#include "vdjml/segment_match_id.hpp"
#include "vdjml/gene_segment_type.hpp"
#include "vdjml/interval.hpp"
#include "vdjml/germline_db_id.hpp"
#include "vdjml/detail/vector_set.hpp"

namespace vdjml{
class Read_result;
class Xml_writer;

/**@brief 
*******************************************************************************/
struct Germline_position {
   Germline_position(
            const Gdb_id gdb,
            const Numsys_id num_sys,
            const unsigned pos,
            std::string gene
   )
   : gdb_id_(gdb),
     num_sys_id_(num_sys),
     pos_(pos),
     gene_(gene)
   {}

   Gdb_id gdb_id_;
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
struct Germline_segment {
   Gdb_id gdb_id_;
   Numsys_id num_sys_id_;
   short_interval range_;
   std::string gene_;
};

/**@brief
*******************************************************************************/
struct VDJML_DECL Segment_match {
   Segment_match()
   : gs_type_(V_gs),
     score_(0),
     identity_(0.0),
     is_inverted_(false),
     stop_codon_(false),
     mutated_invariant_(false)
   {}

   Segment_match(
            const Aligner_id aligner_id,
            const Gs_type segment_type,
            Btop const& btop,
            const int score,
            const float identity,
            short_interval const& read_range
   )
   : aligner_id_(aligner_id),
     gs_type_(segment_type),
     btop_(btop),
     score_(score),
     identity_(identity),
     r_range_(read_range),
     is_inverted_(false),
     stop_codon_(false),
     mutated_invariant_(false)
   {}

   Sm_id id_;
   Aligner_id aligner_id_;
   Gs_type gs_type_;
   Btop btop_;
   int score_;
   float identity_;
   short_interval r_range_;
   bool is_inverted_;
   bool stop_codon_;
   bool mutated_invariant_;
   std::vector<Germline_segment> gsv_;
};

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Segment_match const& sm,
         const unsigned version = current_version
);

}//namespace vdjml
#endif /* SEGMENT_MATCH_HPP_ */
