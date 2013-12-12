/** @file "/vdjml/include/vdjml/read_result.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef READ_RESULT_HPP_
#define READ_RESULT_HPP_
#include <string>

namespace vdjml{

/**@brief Analysis results of a single sequencing read
*******************************************************************************/
class Read_result {
public:

   explicit Read_result(std::string const& id)
   : id_(id)
   {}

   std::string const& id() const {return id_;}

private:
   std::string id_;
};

}//namespace vdjml
#endif /* READ_RESULT_HPP_ */
