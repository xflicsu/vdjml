/** @file "/vdjml/include/vdjml/aligner_map.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef ALIGNER_MAP_HPP_
#define ALIGNER_MAP_HPP_
#include <string>
#include "boost/multi_index_container.hpp"
#include "boost/multi_index/hashed_index.hpp"
#include "boost/multi_index/ordered_index.hpp"
#include "boost/multi_index/mem_fun.hpp"
#include "boost/range.hpp"
#include "vdjml/config.hpp"
#include "vdjml/exception.hpp"
#include "vdjml/aligner_info.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
class VDJML_DECL Aligner_map {
   typedef boost::multi_index_container<
      Aligner_info,
      boost::multi_index::indexed_by<
         boost::multi_index::hashed_unique<
            boost::multi_index::tag<struct identity_tag>,
            boost::multi_index::identity<Aligner_info>
         >,
         boost::multi_index::hashed_unique<
            boost::multi_index::tag<struct id_tag>,
            boost::multi_index::const_mem_fun<
            Aligner_info, Aligner_id, &Aligner_info::id
            >
         >
      >
   > map_t;
public:
   struct Err : public base_exception {};
   typedef map_t::const_iterator iterator;
   typedef map_t::const_iterator const_iterator;
   typedef boost::iterator_range<const_iterator> range;

   std::size_t size() const {return map_.size();}
   const_iterator begin() const {return map_.begin();}
   const_iterator end() const {return map_.end();}
   Aligner_info const& front() const {return *map_.begin();}
   bool empty() const {return ! size();}

   Aligner_info const& operator[](const Aligner_id id) const {
      typedef map_t::index<id_tag>::type index;
      index const& ind = map_.get<id_tag>();
      index::const_iterator iter = ind.find(id);
      if( iter == ind.end() ) BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("invalid ID")
               << Err::int1_t(id())
      );
      return *iter;
   }

   /**@param ai accept by value to change the ID */
   Aligner_id insert(Aligner_info ai) {
      typedef map_t::index<identity_tag>::type index;
      index& ind = map_.get<identity_tag>();
      index::const_iterator iter = ind.find(ai);
      if( iter != ind.end() ) {
         return iter->id();
      }
      const Aligner_id id(size() + 1);
      ai.id_ = id;
      ind.insert(ai);
      return id;
   }

private:
   map_t map_;
};

}//namespace vdjml
#endif /* ALIGNER_MAP_HPP_ */
