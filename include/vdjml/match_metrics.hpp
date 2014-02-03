/** @file "/vdjml/include/vdjml/match_metrics.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef MATCH_METRICS_HPP_
#define MATCH_METRICS_HPP_
#include "boost/cstdint.hpp"
#include "vdjml/config.hpp"
#include "vdjml/vdjml_current_version.hpp"
#include "vdjml/percent.hpp"

namespace vdjml{
class Xml_writer;

/**@brief 
*******************************************************************************/
class VDJML_DECL Match_metrics {
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

   typedef boost::int_least16_t score_t;

public:
   /** alignment score value indicating that it is undefined */
   static const int unscore;

   /**
    @param score
    */
   Match_metrics(
            const double identity,
            const int score               = unscore,
            const unsigned substitutions  = 0,
            const unsigned insertions     = 0,
            const unsigned deletions      = 0,
            const bool stop_codon         = false,
            const bool mutated_invariant  = false,
            const bool is_inverted        = false
   )
   : identity_(identity),
     score_(score),
     substitutions_(substitutions),
     insertions_(insertions),
     deletions_(deletions),
     v_(set(stop_codon, mutated_invariant, is_inverted))
   {}

   score_t score() const {return score_;}
   Percent identity() const {return identity_;}
   unsigned insertions() const {return insertions_;}
   unsigned deletions() const {return deletions_;}
   unsigned substitutions() const {return substitutions_;}
   bool stop_codon() const {return v_ & 1 << 2;}
   bool mutated_invariant() const {return v_ & 1 << 1;}
   bool is_inverted() const {return v_ & 1;}

private:
   Percent identity_;
   score_t score_;
   unsigned char substitutions_;
   unsigned char insertions_;
   unsigned char deletions_;
   unsigned char v_;
};

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Match_metrics const& mm,
         const unsigned version = VDJML_CURRENT_VERSION
);

}//namespace vdjml
#endif /* MATCH_METRICS_HPP_ */
