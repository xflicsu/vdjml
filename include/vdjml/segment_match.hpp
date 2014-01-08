/** @file "/vdjml/include/vdjml/segment_match.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef SEGMENT_MATCH_HPP_
#define SEGMENT_MATCH_HPP_
#include <string>
#include <vector>
#include "vdjml/aligner_id.hpp"
#include "vdjml/btop.hpp"
#include "vdjml/config.hpp"
#include "vdjml/detail/vector_set.hpp"
#include "vdjml/format_version.hpp"
#include "vdjml/gene_segment_type.hpp"
#include "vdjml/germline_db_id.hpp"
#include "vdjml/germline_segment_id.hpp"
#include "vdjml/interval.hpp"
#include "vdjml/segment_match_id.hpp"

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
struct Germline_segment_match {
   Germline_segment_match(
            const Gdb_id gdb,
            const Numsys_id numsys,
            const Aligner_id aligner,
            short_interval const& range,
            const Gls_id germline_segment,
            const int score,
            const float identity
   )
   : gdb_(gdb),
     numsys_(numsys),
     aligner_(aligner),
     range_(range),
     gl_segment_(germline_segment),
     score_(score),
     identity_(identity)
   {}

   bool operator==(Germline_segment_match const& gsm) const {
//      return
   }

   Gdb_id gdb_;
   Numsys_id numsys_;
   Aligner_id aligner_;
   short_interval range_;
   Gls_id gl_segment_;
   int score_;
   float identity_;
};



/**@brief Alignment results for a read segment
@details
*******************************************************************************/
class VDJML_DECL Read_segment_match {
   friend class Read_result;

public:
   Read_segment_match(
            Btop const& btop,
            short_interval const& read_range
   )
   : btop_(btop),
     r_range_(read_range),
     is_inverted_(false),
     stop_codon_(false),
     mutated_invariant_(false)
   {}

private:
   Sm_id id_;
   Btop btop_;
   short_interval r_range_;
   bool is_inverted_;
   bool stop_codon_;
   bool mutated_invariant_;
   detail::Vector_set<Germline_segment_match> gsv_;
};

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Read_segment_match const& sm,
         const unsigned version = current_version
);

}//namespace vdjml
#endif /* SEGMENT_MATCH_HPP_ */
