/** @file "/vdjml/include/vdjml/germline_db_map.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef GERMLINE_DB_MAP_HPP_
#define GERMLINE_DB_MAP_HPP_
#include <string>
#include "boost/range.hpp"
#include "vdjml/config.hpp"
#include "vdjml/germline_db_info.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
class VDJML_DECL Germline_db_map {
public:
   typedef void* /*todo:*/ iterator;
   typedef void* /*todo:*/ const_iterator;
   typedef boost::iterator_range<const_iterator> range;

   std::size_t size() const;
   const_iterator begin() const;
   const_iterator end() const;

private:

};

}//namespace vdjml
#endif /* GERMLINE_DB_MAP_HPP_ */
