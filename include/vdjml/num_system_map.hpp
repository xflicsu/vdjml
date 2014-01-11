/** @file "/vdjml/include/vdjml/num_system_map.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef NUM_SYSTEM_MAP_HPP_
#define NUM_SYSTEM_MAP_HPP_
#include <string>
#include <utility>
#include "boost/array.hpp"
#include "vdjml/detail/id_bimap.hpp"
#include "vdjml/object_ids.hpp"

namespace vdjml{

const Numsys_id imgt;
const Numsys_id kabat;

/**@brief 
*******************************************************************************/
class Num_system_map {
   typedef detail::Id_bimap<Numsys_id, std::string> map_t;
   typedef boost::array<std::string,3> name_array;
   static name_array const& list() {
      static const name_array na = {{
               "",
               "IMGT", "Kabat"
      }};
      return na;
   }

public:
   typedef std::pair<Numsys_id, std::string> num_system;
   static num_system imgt() {return num_system(Numsys_id(1), list()[1]);}
   static num_system kabat() {return num_system(Numsys_id(2), list()[2]);}

   Num_system_map()
   : map_(Numsys_id(1))
   {
      for(std::size_t n = 1; n != name_array::size(); ++n) {
         map_.insert(Numsys_id(n), list()[n]);
      }
   }

   typedef map_t::const_iterator iterator;
   typedef map_t::const_iterator const_iterator;
   std::size_t size() const {return map_.size();}
   const_iterator begin() const {return map_.begin();}
   const_iterator end() const {return map_.end();}
   bool empty() const {return ! size();}
   std::string const& operator[](const Numsys_id id) const {return map_[id];}
   Numsys_id insert(std::string const& name) {return map_.insert(name).first;}

private:
   map_t map_;
};

}//namespace vdjml
#endif /* NUM_SYSTEM_MAP_HPP_ */
