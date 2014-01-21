/** @file "/vdjml/include/vdjml/gene_region_type_map.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef GENE_REGION_TYPE_MAP_HPP_
#define GENE_REGION_TYPE_MAP_HPP_
#include <string>
#include <utility>
#include "boost/array.hpp"
#include "vdjml/detail/id_bimap.hpp"
#include "vdjml/object_ids.hpp"
#include "vdjml/gene_region_type.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
class Gene_region_map {
   typedef detail::Id_bimap<Region_id, std::string> map_t;

public:
   typedef map_t::const_iterator iterator;
   typedef map_t::const_iterator const_iterator;

   Gene_region_map()
   : map_(Region_id(1))
   {
      init();
   }

   std::size_t size() const {return map_.size();}
   const_iterator begin() const {return map_.begin();}
   const_iterator end() const {return map_.end();}
   bool empty() const {return ! size();}
   std::string const& operator[](const Region_id id) const {return map_[id];}
   Region_id insert(std::string const& name) {return map_.insert(name).first;}

private:
   map_t map_;

   void init() {
      map_.insert(Gene_region_type::fr1, "FR1");
      map_.insert(Gene_region_type::fr2, "FR2");
      map_.insert(Gene_region_type::fr3, "FR3");
      map_.insert(Gene_region_type::cdr1, "CDR1");
      map_.insert(Gene_region_type::cdr2, "CDR2");
      map_.insert(Gene_region_type::cdr3, "CDR3");
      map_.insert(Gene_region_type::vd_junction, "VD-junction");
      map_.insert(Gene_region_type::dj_junction, "DJ-junction");
   }
};

}//namespace vdjml
#endif /* GENE_REGION_TYPE_MAP_HPP_ */
