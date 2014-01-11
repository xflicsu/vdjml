/** @file "/vdjml/include/vdjml/result_builder.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef RESULT_BUILDER_HPP_
#define RESULT_BUILDER_HPP_
#include <memory>
#include <string>
#include "vdjml/config.hpp"
#include "vdjml/object_ids.hpp"

namespace vdjml{
class Results_meta;
class Read_result;

/**@brief 
*******************************************************************************/
class VDJML_DECL Result_builder {
   typedef std::auto_ptr<Read_result> result_ptr;
public:
   Result_builder(Results_meta& rm, std::string const& id);

private:
   Results_meta& meta_;
   result_ptr r_;
};

}//namespace vdjml
#endif /* RESULT_BUILDER_HPP_ */
