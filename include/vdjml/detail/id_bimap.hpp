/** @file "/vdjml/include/vdjml/detail/id_bimap.hpp"
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013-4 @author Mikhail K Levin
*******************************************************************************/
#ifndef ID_BIMAP_HPP_
#define ID_BIMAP_HPP_
#include <vector>
#include "boost/assert.hpp"
#include "boost/foreach.hpp"
#include "boost/functional/hash_fwd.hpp"
#include "boost/unordered_set.hpp"
#include "vdjml/exception.hpp"

namespace vdjml{ namespace detail{

/**@brief 
*******************************************************************************/
template<class Id, class Obj> class Id_bimap{
public:
   typedef Id_bimap self_type;
   typedef Obj obj_type;
   typedef Id id_type;

private:
   class Hash_id : std::unary_function<id_type, std::size_t> {
   public:
      explicit Hash_id(self_type const& v) : m_(v) {}

      std::size_t operator()(const id_type id) const {
         using boost::hash_value;
         return hash_value(m_[id]);
      }

      std::size_t operator()(obj_type const& obj) const {
         using boost::hash_value;
         return hash_value(obj);
      }

   private:
      self_type const& m_;
   };

   class Equal_id : public std::binary_function<id_type, id_type, bool>{
   public:
      explicit Equal_id(self_type const& m) : m_(m) {}

      bool operator()(id_type id1, id_type id2) const{
         return m_[id1] == m_[id2];
      }

      template<class ObjCompat>
      bool operator()(id_type id1, ObjCompat const& obj) const{
         return m_[id1] == obj;
      }

      template<class ObjCompat>
      bool operator()(ObjCompat const& obj, id_type id2) const{
         return obj == m_[id2];
      }

   private:
      self_type const& m_;
   };

   template<class ObjCompat> class Equal_obj {
   public:
      explicit Equal_obj(self_type const& m) : m_(m) {}

      bool operator()(id_type id1, ObjCompat const& obj) const{
         return m_[id1] == obj;
      }

      bool operator()(ObjCompat const& obj, id_type id2) const{
         return obj == m_[id2];
      }

   private:
      self_type const& m_;
   };

   typedef boost::unordered_set<id_type, Hash_id, Equal_id> map_t;
   typedef std::vector<obj_type> vector_t;

public:
   typedef typename map_t::value_type value_type;
   typedef typename map_t::iterator iterator;
   typedef typename map_t::const_iterator const_iterator;
   typedef base_exception Err;

   explicit Id_bimap(const id_type id0)
   : vid_(),
     map_(boost::unordered::detail::default_bucket_count, Hash_id(*this), Equal_id(*this)),
     erased_(),
     id0_(id0)
   {}

   explicit Id_bimap(self_type const& bm)
   : vid_(bm.vid_.size()),
     map_(boost::unordered::detail::default_bucket_count, Hash_id(*this), Equal_id(*this)),
     erased_(bm.erased_.size()),
     id0_(bm.id0_)
   {
      copy(bm);
   }

   self_type& operator=(self_type const& bm) {
      clear();
      copy(bm);
      return *this;
   }

   std::size_t size() const { return map_.size(); }
   const_iterator begin() const {return map_.begin();}
   const_iterator end() const {return map_.end();}
   bool empty() const {return map_.empty();}
   id_type min_id() const {return id0_;}
   id_type max_id() const {return pos2id(vid_.size()-1);}

   obj_type const& operator[](const id_type id) const {
      BOOST_ASSERT( vpos(id) < vid_.size() );
      return vid_[vpos(id)];
   }

   obj_type& operator[](const id_type id) {
      BOOST_ASSERT( vpos(id) < vid_.size() );
      return vid_[vpos(id)];
   }

   obj_type const& at(const id_type id) const {
      if( id < id0_ || vpos(id) >= vid_.size() ) BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("invalid ID")
               << Err::int1_t(id())
      );
      return vid_[vpos(id)];
   }

   obj_type& at(const id_type id) {
      if( id < id0_ || vpos(id) >= vid_.size() ) BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("invalid ID")
               << Err::int1_t(id())
      );
      return vid_[vpos(id)];
   }

   obj_type const* find(const id_type id) const {
      if( id < id0_ || vpos(id) >= vid_.size() ) return 0;
      return &vid_[vpos(id)];
   }

   obj_type* find(const id_type id) {
      if( id < id0_ || vpos(id) >= vid_.size() ) return 0;
      return &vid_[vpos(id)];
   }

   template<class ObjCompat>
   id_type const* find(ObjCompat const& obj) const {
      const const_iterator i = map_.find(
               obj,
               boost::hash<ObjCompat>(),
               Equal_obj<ObjCompat>(*this)
      );
      return i == map_.end() ? 0 : &(*i);
   }

   std::pair<id_type, bool> insert(obj_type const& obj) {
      if( id_type const* idp = find(obj) ) return std::make_pair(*idp, false);
      if( erased_.empty() ) {
         const id_type id = pos2id(vid_.size());
         vid_.push_back(obj);
         map_.insert(id);
         return std::make_pair(id, true);
      }

      const id_type id = erased_.back();
      erased_.pop_back();
      const std::size_t n = vpos(id);
      BOOST_ASSERT(vid_.size() > n);
      vid_[n] = obj;
      map_.insert(id);
      return std::make_pair(id, true);
   }

   void insert(const id_type id, obj_type const& obj) {
      if( id < id0_ ) BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("invalid ID")
               << Err::int1_t(id())
      );

      if( id_type const* id0 = find(obj) ) {
         if( *id0 == id ) return;
         BOOST_THROW_EXCEPTION(
                  Err()
                  << Err::msg_t("object already mapped to different ID")
                  << Err::int1_t(id())
                  << Err::int2_t((*id0)())
         );
      }
      //ignore erased_
      const std::size_t n = vpos(id);
      if( n >= vid_.size() ) {
         vid_.resize(n + 1);
      }
      vid_[n] = obj;
      map_.insert(id);
   }

   void erase(const id_type id) {
      BOOST_ASSERT( vpos(id) < vid_.size() );
      const std::size_t pos = vpos(id);
      map_.erase(id);
      erased_.push_back(id);
      vid_[pos] = obj_type();
   }

   void clear() {
      erased_.clear();
      map_.clear();
      vid_.clear();
   }

private:
   vector_t vid_;
   map_t map_;
   std::vector<id_type> erased_;
   id_type id0_;

   std::size_t vpos(const id_type id) const {
      BOOST_ASSERT(id >= id0_ && "invalid ID");
      return id() - id0_();
   }

   id_type pos2id(const std::size_t n) const {return id_type(n + id0_());}

   void copy(self_type const& bm) {
      vid_.resize(bm.vid_.size());
      id0_ = bm.id0_;
      erased_ = bm.erased_;
      BOOST_FOREACH(const id_type id, bm) {
         (*this)[id] = bm[id];
         map_.insert(id);
      }
   }

};

}//namespace detail
}//namespace vdjml
#endif /* ID_BIMAP_HPP_ */
