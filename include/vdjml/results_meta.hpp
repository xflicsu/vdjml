/** @file "/vdjml/include/vdjml/results_meta.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef RESULTS_META_HPP_
#define RESULTS_META_HPP_
#include "vdjml/config.hpp"
#include "vdjml/aligner_map.hpp"
#include "vdjml/germline_db_map.hpp"
#include "vdjml/num_system_map.hpp"
#include "vdjml/format_version.hpp"
#include "vdjml/exception.hpp"
#include "vdjml/germline_segment_map.hpp"
#include "vdjml/gene_region_type_map.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
class VDJML_DECL Results_meta {
public:
   struct Err : public base_exception {};

   Results_meta() {}

   /**@brief Read VDJ alignment results from XML reader stream
   @param xr XML writer
   @param version format version of the results;
   the version found in the stream has precedence
   */
   explicit Results_meta(
            Xml_reader& xr,
            const unsigned version = current_version
   );

   Aligner_map const & aligner_map() const {return am_;}
   Aligner_map       & aligner_map() {return am_;}

   Germline_db_map const   & germline_db_map() const {return gm_;}
   Germline_db_map         & germline_db_map() {return gm_;}

   Num_system_map const & num_system_map() const {return nsm_;}
   Num_system_map       & num_system_map() {return nsm_;}

   Germline_segment_map const & germline_segment_map() const {return gsm_;}
   Germline_segment_map       & germline_segment_map() {return gsm_;}

   Gene_region_map const & gene_region_map() const {return grm_;}
   Gene_region_map       & gene_region_map() {return grm_;}

private:
   Aligner_map am_;
   Germline_db_map gm_;
   Num_system_map nsm_;
   Germline_segment_map gsm_;
   Gene_region_map grm_;
};

/**@brief
@param xw XML writer
@param rs result store
@param version format version
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Results_meta const& rs,
         const unsigned version = current_version
);

}//namespace vdjml
#endif /* RESULTS_META_HPP_ */
