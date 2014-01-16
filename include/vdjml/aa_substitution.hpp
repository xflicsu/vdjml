/** @file "/vdjml/include/vdjml/aa_substitution.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef AA_SUBSTITUTION_HPP_
#define AA_SUBSTITUTION_HPP_
#include "vdjml/aa_index.hpp"
#include "vdjml/detail/vector_set.hpp"
#include "vdjml/object_ids.hpp"
#include "vdjml/config.hpp"
#include "vdjml/vdjml_current_version.hpp"

namespace vdjml{
class Xml_writer;

/**@brief 
*******************************************************************************/
struct Gl_position {
   Gl_position(const Gl_seg_match_id id, const unsigned gl_pos)
   : gsm_(id),
     gl_pos_(gl_pos)
   {}

   bool operator<(Gl_position const& gp) const {
      return gsm_ < gp.gsm_;
   }

   Gl_seg_match_id gsm_; /**< germline segment match ID */
   unsigned gl_pos_; /**< 0-based position of first nucleotide in germline DB entry */
};

/**@brief
todo: compact storage
*******************************************************************************/
struct Aa_substitution {
   struct Err : public base_exception {};

   Aa_substitution(
            const unsigned read_pos,
            const char aa_from,
            const char aa_to
   )
   : read_pos_(read_pos),
     from_(aminoacid_index(aa_from)),
     to_(aminoacid_index(aa_to))
   {
   }

   bool operator<(Aa_substitution const& aas) const {
      return read_pos_ < aas.read_pos_;
   }

   void insert(Gl_position const& gp) {
      gl_pos_.insert(gp);
   }

   unsigned read_pos_; /**< 0-based position of first nucleotide in the read */
   Aminoacid from_; /**< amino acid in germline */
   Aminoacid to_; /**< amino acid in read */
   detail::Vector_set<Gl_position> gl_pos_;
};

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Aa_substitution const& aas,
         const unsigned version = VDJML_CURRENT_VERSION
);

}//namespace vdjml
#endif /* AA_SUBSTITUTION_HPP_ */
