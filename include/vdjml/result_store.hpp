/** @file "/vdjml/include/vdjml/result_store.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef RESULT_STORE_HPP_
#define RESULT_STORE_HPP_
#include <string>
#include "vdjml/config.hpp"
#include "vdjml/read_result.hpp"
#include "boost/range.hpp"

namespace vdjml{

/**@brief Store and search analysis results of many sequencing reads
*******************************************************************************/
class VDJML_DECL Result_store {
public:
   typedef void* /*todo:*/ iterator;
   typedef void* /*todo:*/ const_iterator;
   typedef boost::iterator_range<const_iterator> range;

   std::size_t size() const;
   const_iterator begin() const;
   const_iterator end() const;
   Read_result const* find_id(std::string const* id) const;
   void insert(Read_result const& rr);

private:

};

}//namespace vdjml
#endif /* RESULT_STORE_HPP_ */
