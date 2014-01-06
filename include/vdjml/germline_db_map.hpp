/** @file "/vdjml/include/vdjml/germline_db_map.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef GERMLINE_DB_MAP_HPP_
#define GERMLINE_DB_MAP_HPP_
#include <string>
#include "boost/multi_index_container.hpp"
#include "boost/multi_index/hashed_index.hpp"
#include "boost/multi_index/mem_fun.hpp"
#include "boost/multi_index/composite_key.hpp"
#include "boost/range.hpp"
#include "vdjml/config.hpp"
#include "vdjml/germline_db_info.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
class VDJML_DECL Germline_db_map {

   typedef boost::multi_index_container<
      Germline_db_info,
      boost::multi_index::indexed_by<
         boost::multi_index::hashed_unique<
            boost::multi_index::tag<struct id_tag>,
            boost::multi_index::const_mem_fun<
               Germline_db_info, Gdb_id, &Germline_db_info::id
            >
         >,
         boost::multi_index::hashed_unique<
            boost::multi_index::composite_key<
               Germline_db_info,
               boost::multi_index::const_mem_fun<
                  Germline_db_info, std::string const&, &Germline_db_info::name
               >,
               boost::multi_index::const_mem_fun<
                  Germline_db_info, std::string const&, &Germline_db_info::version
               >,
               boost::multi_index::const_mem_fun<
                  Germline_db_info, std::string const&, &Germline_db_info::num_system
               >,
               boost::multi_index::const_mem_fun<
                  Germline_db_info, std::string const&, &Germline_db_info::species
               >
            >
         >
      >
   > map_t;
public:
   typedef map_t::const_iterator iterator;
   typedef map_t::const_iterator const_iterator;
   typedef boost::iterator_range<const_iterator> range;

   std::size_t size() const {return map_.size();}
   const_iterator begin() const {return map_.begin();}
   const_iterator end() const {return map_.end();}

private:
   map_t map_;
};

}//namespace vdjml
#endif /* GERMLINE_DB_MAP_HPP_ */
