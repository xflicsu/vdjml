/** @file "/vdjml/include/vdjml/aligner_map.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef ALIGNER_MAP_HPP_
#define ALIGNER_MAP_HPP_
#include <string>
#include "boost/range.hpp"
#include "vdjml/config.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
class VDJML_DECL Aligner_map {
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
#endif /* ALIGNER_MAP_HPP_ */
