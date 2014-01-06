/** @file "/vdjml/include/vdjml/result_writer.hpp" 
part of vdjml project.
@n @n Distributed under GNU General Public License, Version 3;
see doc/license.txt.
@n Copyright Mikhail K Levin 2014
*******************************************************************************/
#ifndef RESULT_WRITER_HPP_
#define RESULT_WRITER_HPP_
#include <iostream>
#include "vdjml/config.hpp"
#include "vdjml/xml_writer.hpp"
#include "vdjml/format_version.hpp"
#include "vdjml/read_result.hpp"

namespace vdjml{
class Result_store;

/**@brief Incrementally serialize VDJ alignment results
*******************************************************************************/
class VDJML_DECL Result_writer {
public:
   Result_writer(
            std::ostream& os,
            Result_store const& rs,
            const unsigned version = current_version,
            Xml_writer_options const& opts = Xml_writer_options()
   );

   void write(Read_result const& rr);
   void operator()(Read_result const& rr) {write(rr);}
   void close();
   ~Result_writer() {close();}

private:
   Xml_writer xw_;
};

}//namespace vdjml
#endif /* RESULT_WRITER_HPP_ */
