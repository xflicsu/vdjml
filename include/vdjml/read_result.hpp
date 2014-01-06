/** @file "/vdjml/include/vdjml/read_result.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef READ_RESULT_HPP_
#define READ_RESULT_HPP_
#include <string>
#include "vdjml/config.hpp"
#include "vdjml/format_version.hpp"

namespace vdjml{
class Xml_reader;
class Xml_writer;

/**@brief Analysis results of a single sequencing read
*******************************************************************************/
class VDJML_DECL Read_result {
public:

   explicit Read_result(std::string const& id)
   : id_(id)
   {}

   explicit Read_result(
            Xml_reader& xr,
            const unsigned version
   );

   std::string const& id() const {return id_;}

private:
   std::string id_;
};

/**@brief
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Read_result const& rr,
         const unsigned version = current_version
);

}//namespace vdjml
#endif /* READ_RESULT_HPP_ */
