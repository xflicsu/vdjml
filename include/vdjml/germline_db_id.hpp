/** @file "/vdjml/include/vdjml/germline_db_id.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef GERMLINE_DB_ID_HPP_
#define GERMLINE_DB_ID_HPP_
#include "vdjml/detail/object_id_base.hpp"

namespace vdjml{

/**@brief
*******************************************************************************/
class Gdb_id : public detail::Base_id<Gdb_id> {
public:
   explicit Gdb_id(const value_type x) : base(x) {}
   Gdb_id() : base(0) {}
};

}//namespace vdjml
#endif /* GERMLINE_DB_ID_HPP_ */
