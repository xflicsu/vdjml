/** @file "/vdjml/include/vdjml/read_result.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef READ_RESULT_HPP_
#define READ_RESULT_HPP_
#include <string>
#include <vector>
#include "vdjml/config.hpp"
#include "vdjml/format_version.hpp"
#include "vdjml/segment_match_map.hpp"
#include "vdjml/segment_combination.hpp"

namespace vdjml{
class Xml_reader;
class Xml_writer;
class Results_meta;

/**@brief Analysis results of a single sequencing read
*******************************************************************************/
class VDJML_DECL Read_result {
   typedef std::vector<Segment_combination> seg_comb_store;
public:

   explicit Read_result(std::string const& id)
   : id_(id)
   {}

   explicit Read_result(
            Xml_reader& xr,
            const unsigned version
   );

   Seg_match_id insert(Segment_match const& rsm) {
      return smm_.insert(rsm);
   }

   void insert(Segment_combination const& sc) {
      scm_.push_back(sc);
   }

   std::string const& id() const {return id_;}

private:
   std::string id_;
   Segment_match_map smm_;
   seg_comb_store scm_;
};

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Read_result const& rr,
         Results_meta const& rm,
         const unsigned version = current_version
);

}//namespace vdjml
#endif /* READ_RESULT_HPP_ */
