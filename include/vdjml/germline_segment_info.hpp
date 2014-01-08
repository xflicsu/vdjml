/** @file "/vdjml/include/vdjml/germline_segment_info.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef GERMLINE_SEGMENT_INFO_HPP_
#define GERMLINE_SEGMENT_INFO_HPP_
#include <string>
#include "vdjml/germline_db_id.hpp"
#include "vdjml/gene_segment_type.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
class Gl_segment_info {

public:

   Gl_segment_info(const Gdb_id db, const char vdj, std::string const& name)
   : db_(db),
     gst_(segment_type(vdj)),
     name_(name)
   {}

private:
   Gdb_id db_;
   Gs_type gst_;
   std::string name_;
};

}//namespace vdjml
#endif /* GERMLINE_SEGMENT_INFO_HPP_ */
