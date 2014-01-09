/** @file "/vdjml/include/vdjml/germline_segment_info.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef GERMLINE_SEGMENT_INFO_HPP_
#define GERMLINE_SEGMENT_INFO_HPP_
#include <string>
#include "vdjml/config.hpp"
#include "boost/functional/hash.hpp"
#include "vdjml/object_ids.hpp"
#include "vdjml/gene_segment_type.hpp"
#include "vdjml/format_version.hpp"
#include "vdjml/detail/comparison_operators_macro.hpp"

namespace vdjml{
class Xml_writer;
class Results_meta;

/**@brief 
*******************************************************************************/
struct Gl_segment_info {

   Gl_segment_info(const Gl_db_id db, const char vdj, std::string const& name)
   : db_(db),
     gst_(segment_type(vdj)),
     name_(name)
   {}

   bool operator==(Gl_segment_info const& gsi) const {
      return db_ == gsi.db_ && name_ == gsi.name_;
   }

   bool operator<(Gl_segment_info const& gsi) const {
      if( db_ < gsi.db_ ) return true;
      if( gsi.db_ < db_ ) return false;
      return name_ < gsi.name_;
   }

   VDJML_COMPARISON_OPERATOR_MEMBERS(Gl_segment_info)

   Gl_seg_id id_;
   Gl_db_id db_;
   Gs_type gst_;
   std::string name_;
};

/**@brief
*******************************************************************************/
inline std::size_t hash_value(Gl_segment_info const& gsi) {
   std::size_t h = 0;
   boost::hash_combine(h, gsi.db_);
   boost::hash_combine(h, gsi.name_);
   return h;
}

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Gl_segment_info const& gsm,
         Results_meta const& rm,
         const unsigned version = current_version
);

}//namespace vdjml
#endif /* GERMLINE_SEGMENT_INFO_HPP_ */
