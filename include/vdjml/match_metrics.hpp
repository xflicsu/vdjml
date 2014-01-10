/** @file "/vdjml/include/vdjml/match_metrics.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef MATCH_METRICS_HPP_
#define MATCH_METRICS_HPP_
#include "vdjml/config.hpp"
#include "vdjml/format_version.hpp"
#include "vdjml/percent.hpp"

namespace vdjml{
class Xml_writer;

/**@brief 
*******************************************************************************/
class Match_metrics {
   static unsigned char set(
            const bool stop_codon,
            const bool mutated_invariant,
            const bool is_inverted
   ) {
      return (unsigned char) 0 |
               stop_codon << 2 |
               mutated_invariant << 1 |
               is_inverted
               ;
   }

public:
   Match_metrics(
            const int score,
            const float identity,
            const unsigned insertions,
            const unsigned deletions,
            const unsigned substitutions,
            const bool stop_codon = false,
            const bool mutated_invariant = false,
            const bool is_inverted = false
   )
   : score_(score),
   identity_(identity),
   insertions_(),
   deletions_(),
   substitutions_(),
   v_(set(stop_codon, mutated_invariant, is_inverted))
   {}

   int score() const {return score_;}
   Percent identity() const {return identity_;}
   unsigned insertions() const {return insertions_;}
   unsigned deletions() const {return deletions_;}
   unsigned substitutions() const {return substitutions_;}
   bool stop_codon() const {return v_ & 1 << 2;}
   bool mutated_invariant() const {return v_ & 1 << 1;}
   bool is_inverted() const {return v_ & 1;}

private:
   int score_;
   Percent identity_;
   unsigned char insertions_;
   unsigned char deletions_;
   unsigned char substitutions_;
   unsigned char v_;
};

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Match_metrics const& mm,
         const unsigned version = current_version
);

}//namespace vdjml
#endif /* MATCH_METRICS_HPP_ */
