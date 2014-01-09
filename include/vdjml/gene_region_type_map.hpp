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

namespace vdjml{

/**@brief 
*******************************************************************************/
class Gene_region_map {
   typedef detail::Id_bimap<Region_id, std::string> map_t;
   typedef boost::array<std::string,9> name_array;
   static name_array const& list() {
      static const name_array na = {{
               "",
               "FR1", "FR2", "FR3",
               "CDR1", "CDR2", "CDR3",
               "VD-junction", "DJ-junction"
      }};
      return na;
   }

public:
   typedef std::pair<Region_id, std::string> region;
   static region fr1() {return region(Region_id(1), list()[1]);}
   static region fr2() {return region(Region_id(2), list()[2]);}
   static region fr3() {return region(Region_id(3), list()[3]);}
   static region cdr1() {return region(Region_id(4), list()[4]);}
   static region cdr2() {return region(Region_id(5), list()[5]);}
   static region cdr3() {return region(Region_id(6), list()[6]);}
   static region v_d() {return region(Region_id(7), list()[7]);}
   static region d_j() {return region(Region_id(8), list()[8]);}

   typedef map_t::const_iterator iterator;
   typedef map_t::const_iterator const_iterator;

   Gene_region_map()
   : map_(Region_id(1))
   {
      for(std::size_t n = 1; n != name_array::size(); ++n) {
         map_.insert(Region_id(n), list()[n]);
      }
   }

   std::size_t size() const {return map_.size();}
   const_iterator begin() const {return map_.begin();}
   const_iterator end() const {return map_.end();}
   bool empty() const {return ! size();}
   std::string const& operator[](const Region_id id) const {return map_[id];}
   Region_id insert(std::string const& name) {return map_.insert(name).first;}

private:
   map_t map_;
};

}//namespace vdjml
#endif /* GENE_REGION_TYPE_MAP_HPP_ */
