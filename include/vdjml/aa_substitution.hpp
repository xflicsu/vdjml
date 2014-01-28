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

   /**
    @param read_pos_0 0-based position of first nucleotide in the read
    @param aa_read amino acid in read
    @param aa_gl amino acid in germline
    */
   Aa_substitution(
            const unsigned read_pos_0,
            const char aa_read,
            const char aa_gl
   )
   : read_pos_0_(read_pos_0),
     aa_read_(aminoacid_index(aa_read)),
     aa_gl_(aminoacid_index(aa_gl))
   {
   }

   bool operator<(Aa_substitution const& aas) const {
      return read_pos_0_ < aas.read_pos_0_;
   }

   void insert(Gl_position const& gp) {
      gl_pos_.insert(gp);
   }

   unsigned read_pos_0_;   /**< 0-based position of first nucleotide in the read */
   Aminoacid aa_read_;     /**< amino acid in read */
   Aminoacid aa_gl_;       /**< amino acid in germline */
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
