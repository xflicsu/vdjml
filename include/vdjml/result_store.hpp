/** @file "/vdjml/include/vdjml/result_store.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013-4 @author Mikhail K Levin
*******************************************************************************/
#ifndef RESULT_STORE_HPP_
#define RESULT_STORE_HPP_
#include <string>
#include <memory>
#include "boost/ptr_container/ptr_vector.hpp"
#include "boost/range.hpp"
#include "vdjml/config.hpp"
#include "vdjml/read_result.hpp"
#include "vdjml/results_meta.hpp"

namespace vdjml{
class Xml_reader;
class Xml_writer;

/**@brief Store and search analysis results of many sequencing reads
*******************************************************************************/
class VDJML_DECL Result_store {
   typedef boost::ptr_vector<Read_result> store_t;
public:
   struct Err : public base_exception {};
   typedef store_t::iterator iterator;
   typedef store_t::const_iterator const_iterator;
   typedef boost::iterator_range<const_iterator> range;

   Result_store() {}

   /**@brief Read VDJ alignment results from XML reader stream
   @param xr XML writer
   @param version format version of the results;
   the version found in the stream has precedence
   */
   explicit Result_store(
            Xml_reader& xr,
            const unsigned version = current_version
   );

   std::size_t size() const {return v_.size();}
   const_iterator begin() const {return v_.begin();}
   const_iterator end() const {return v_.end();}

//   Read_result const* find_id(std::string const* id) const;

   void insert(std::auto_ptr<Read_result> rr);

   Results_meta const& meta() const {return rm_;}
   Results_meta& meta() {return rm_;}

private:
   Results_meta rm_;
   store_t v_;
};

/**@brief
@param xw XML writer
@param rs result store
@param version format version
*******************************************************************************/
VDJML_DECL void write(
         Xml_writer& xw,
         Result_store const& rs,
         const unsigned version = current_version
);

}//namespace vdjml
#endif /* RESULT_STORE_HPP_ */
