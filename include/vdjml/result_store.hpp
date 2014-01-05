/** @file "/vdjml/include/vdjml/result_store.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013-4 @author Mikhail K Levin
*******************************************************************************/
#ifndef RESULT_STORE_HPP_
#define RESULT_STORE_HPP_
#include <string>
#include "boost/range.hpp"
#include "vdjml/config.hpp"
#include "vdjml/read_result.hpp"
#include "vdjml/aligner_map.hpp"
#include "vdjml/germline_db_map.hpp"
#include "vdjml/format_version.hpp"
#include "vdjml/exception.hpp"

namespace vdjml{
class Xml_reader;
class Xml_writer;

/**@brief Store and search analysis results of many sequencing reads
*******************************************************************************/
class VDJML_DECL Result_store {
public:
   struct Err : public base_exception {};
   typedef void* /*todo:*/ iterator;
   typedef void* /*todo:*/ const_iterator;
   typedef boost::iterator_range<const_iterator> range;

   std::size_t size() const;
   const_iterator begin() const;
   const_iterator end() const;
   Read_result const* find_id(std::string const* id) const;
   void insert(Read_result const& rr);

   Aligner_map const & aligner_map() const;
   Aligner_map       & aligner_map();
   Germline_db_map const   & germline_db_map() const;
   Germline_db_map         & germline_db_map();

private:

};

/**@brief
@param xr
@param version format version
*******************************************************************************/
VDJML_DECL Result_store read(
         Xml_reader& xr,
         const unsigned version = current_version
);

/**@brief
@param xw
@param rs
@param version format version
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Result_store const& rs,
         const unsigned version = current_version
);

}//namespace vdjml
#endif /* RESULT_STORE_HPP_ */
