/** @file "/vdjml/include/vdjml/germline_segment_map.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef GERMLINE_SEGMENT_MAP_HPP_
#define GERMLINE_SEGMENT_MAP_HPP_
#include "boost/multi_index_container.hpp"
#include "boost/multi_index/hashed_index.hpp"
#include "boost/multi_index/ordered_index.hpp"
#include "boost/multi_index/member.hpp"
#include "boost/range.hpp"
#include "vdjml/germline_segment_info.hpp"
#include "vdjml/exception.hpp"

namespace vdjml{

/**@brief 
*******************************************************************************/
class Gl_segment_map {
   typedef boost::multi_index_container<
      Gl_segment_info,
      boost::multi_index::indexed_by<
         boost::multi_index::hashed_unique<
            boost::multi_index::tag<struct identity_tag>,
            boost::multi_index::identity<Gl_segment_info>
         >,
         boost::multi_index::hashed_unique<
            boost::multi_index::tag<struct id_tag>,
            boost::multi_index::member<
               Gl_segment_info, Gl_seg_id, &Gl_segment_info::id_
            >
         >,
         boost::multi_index::hashed_non_unique<
            boost::multi_index::tag<struct db_tag>,
            boost::multi_index::member<
               Gl_segment_info, Gl_db_id, &Gl_segment_info::db_
            >
         >,
         boost::multi_index::hashed_non_unique<
            boost::multi_index::tag<struct name_tag>,
            boost::multi_index::member<
               Gl_segment_info, std::string, &Gl_segment_info::name_
            >
         >
      >
   > map_t;

   typedef map_t::index<identity_tag>::type identity_index;
   typedef map_t::index<name_tag>::type name_index;
public:
   struct Err : public base_exception {};

   typedef map_t::const_iterator iterator;
   typedef map_t::const_iterator const_iterator;
   typedef boost::iterator_range<const_iterator> range;
   typedef name_index::const_iterator name_iterator;
   typedef boost::iterator_range<name_iterator> name_range;

   std::size_t size() const {return map_.size();}
   const_iterator begin() const {return map_.begin();}
   const_iterator end() const {return map_.end();}
   bool empty() const {return ! size();}

   Gl_segment_info const& operator[](const Gl_seg_id id) const {
      typedef map_t::index<id_tag>::type index;
      index const& ind = map_.get<id_tag>();
      const index::const_iterator iter = ind.find(id);
      if( iter == ind.end() )  BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("invalid germline segment ID")
               << Err::int1_t(id())
      );
      return *iter;
   }

   /**@param ai accept by value to change the ID */
   Gl_seg_id insert(Gl_segment_info gsi) {
      identity_index& ind = map_.get<identity_tag>();
      identity_index::const_iterator iter = ind.find(gsi);
      if( iter != ind.end() ) {
         if( gsi.gst_ != iter->gst_ ) BOOST_THROW_EXCEPTION(
                  Err()
                  << Err::msg_t("same segment name, different VDJ type")
                  << Err::str1_t(segment_type_str(gsi.gst_))
                  << Err::str2_t(segment_type_str(iter->gst_))
         );
         return iter->id_;
      }
      const Gl_seg_id id(size() + 1);
      gsi.id_ = id;
      ind.insert(gsi);
      return id;
   }

   Gl_seg_id insert(const Gl_db_id db, const char vdj, std::string const& name) {
      return insert(Gl_segment_info(db, vdj, name));
   }

   name_range find(std::string const& name) const {
      return map_.get<name_tag>().equal_range(name);
   }

   Gl_segment_info const* find(const Gl_db_id db, std::string const& name) const {
      const Gl_segment_info gsi(db, 'V', name);
      identity_index const& ind = map_.get<identity_tag>();
      identity_index::const_iterator iter = ind.find(gsi);
      return iter == ind.end() ? 0 : &*iter;
   }

private:
   map_t map_;
};

}//namespace vdjml
#endif /* GERMLINE_SEGMENT_MAP_HPP_ */
