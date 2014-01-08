/** @file "/vdjml/include/vdjml/segment_combination.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef SEGMENT_COMBINATION_HPP_
#define SEGMENT_COMBINATION_HPP_
#include <vector>
#include "vdjml/config.hpp"
#include "vdjml/format_version.hpp"
#include "vdjml/segment_match_id.hpp"

namespace vdjml{
class Xml_writer;

/**@brief 
*******************************************************************************/
class Gene_region {
public:

private:
};

/**@brief
*******************************************************************************/
class Segment_combination {
public:

private:
   std::vector<Sm_id> smv_;
};

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Segment_combination const& sc,
         const unsigned version = current_version
);

}//namespace vdjml
#endif /* SEGMENT_COMBINATION_HPP_ */
