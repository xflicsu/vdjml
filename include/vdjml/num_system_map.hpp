/** @file "/vdjml/include/vdjml/num_system_map.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef NUM_SYSTEM_MAP_HPP_
#define NUM_SYSTEM_MAP_HPP_
#include "boost/multi_index_container.hpp"
#include "boost/multi_index/ordered_index.hpp"
#include "boost/multi_index/member.hpp"
#include "vdjml/num_system.hpp"
#include "vdjml/exception.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
class Num_system_map {

   typedef boost::multi_index_container<
      Num_system,
      boost::multi_index::indexed_by<
         boost::multi_index::ordered_unique<
            boost::multi_index::tag<struct name_tag>,
            boost::multi_index::member<Num_system, std::string, &Num_system::name_>
         >,
         boost::multi_index::ordered_unique<
            boost::multi_index::tag<struct id_tag>,
            boost::multi_index::member<Num_system, Numsys_id, &Num_system::id_>
         >
      >
   > map_t;

public:
   struct Err : public base_exception {};
   typedef map_t::const_iterator iterator;
   typedef map_t::const_iterator const_iterator;
   typedef boost::iterator_range<const_iterator> range;

   static Num_system const& imgt() {
      static const Num_system ns = {Numsys_id(1), "IMGT"};
      return ns;
   }
   static Num_system const& kabat() {
      static const Num_system ns = {Numsys_id(2), "Kabat"};
      return ns;
   }

   Num_system_map() {
      map_.insert(imgt());
      map_.insert(kabat());
   }

   std::size_t size() const {return map_.size();}
   const_iterator begin() const {return map_.begin();}
   const_iterator end() const {return map_.end();}
   bool empty() const {return ! size();}

   Num_system const& operator[](const Numsys_id id) const {
      typedef map_t::index<id_tag>::type index;
      index const& ind = map_.get<id_tag>();
      index::const_iterator iter = ind.find(id);
      if( iter != ind.end() ) return *iter;
      BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("invalid numbering system ID")
               << Err::int1_t(id())
      );
   }

   /**@param name accept by value to change the ID */
   Numsys_id insert(std::string const& name) {
      typedef map_t::index<name_tag>::type index;
      index& ind = map_.get<name_tag>();
      index::const_iterator iter = ind.find(name);
      if( iter != ind.end() ) {
         return iter->id_;
      }
      const Numsys_id id(size() + 1);
      Num_system ns = {id, name};
      ind.insert(ns);
      return id;
   }

private:
   map_t map_;
};

}//namespace vdjml
#endif /* NUM_SYSTEM_MAP_HPP_ */
