/** @file "/vdjml/include/vdjml/result_builder.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef RESULT_BUILDER_HPP_
#define RESULT_BUILDER_HPP_
#include <memory>
#include <string>
#include "vdjml/config.hpp"
#include "vdjml/object_ids.hpp"
#include "vdjml/exception.hpp"
#include "vdjml/read_result.hpp"

namespace vdjml{ namespace detail{

/**@brief Construct alignment results for one sequencing read
*******************************************************************************/
class VDJML_DECL Result_factory_impl {
public:
   Result_factory_impl(
            Results_meta& rm,
            const Gl_db_id def_gldb = Gl_db_id(),
            const Aligner_id def_aligner = Aligner_id(),
            const Numsys_id def_numsys = Numsys_id()
   )
   : rm_(rm),
     def_gldb_(def_gldb),
     def_aligner_(def_aligner),
     def_numsys_(def_numsys)
   {}

   Gl_db_id get_default_gl_database() const;
   Aligner_id get_default_aligner() const;
   Numsys_id get_default_num_system() const {return def_numsys_;}

   Results_meta const   & meta() const {return rm_;}
   Results_meta         & meta()       {return rm_;}

   void set_default_gl_database(const Gl_db_id def_gldb) {def_gldb_ = def_gldb;}
   void set_default_aligner(const Aligner_id def_aligner) {def_aligner_ = def_aligner;}
   void set_default_num_system(const Numsys_id def_numsys) {def_numsys_ = def_numsys;}

   Gl_db_id set_default_gl_database(
            std::string const& name,
            std::string const& version,
            std::string const& species,
            std::string const& url = ""
   );

   Aligner_id set_default_aligner(
            std::string const& name,
            std::string const& version,
            std::string const& parameters,
            const unsigned run_id
   );

   Numsys_id set_default_num_system(std::string const& name);

private:
   Results_meta& rm_;
   Gl_db_id def_gldb_;
   Aligner_id def_aligner_;
   Numsys_id def_numsys_;
};

}//namespace detail

/**@brief Construct alignment results for a combination of germline gene segments
*******************************************************************************/
class VDJML_DECL Segment_combination_builder :
   public detail::Result_factory_impl {
public:
   struct Err : public base_exception {};

   Segment_combination_builder(
            detail::Result_factory_impl& rf,
            Read_result& rr,
            Segment_combination const& sc
   );

   /** add gene region alignment info */
   void add_region(
            std::string const& name,
            interval_short const& read_range,
            Match_metrics const& mm,
            Numsys_id num_system = Numsys_id()
   );

   /** add gene region alignment info */
   void add_region(
            const Region_id region,
            interval_short const& read_range,
            Match_metrics const& mm,
            Numsys_id num_system = Numsys_id()
   );

private:
   Read_result& rr_;
   std::size_t n_;
};

/**@brief Construct alignment results for one sequencing read segment match
*******************************************************************************/
class VDJML_DECL Segment_match_builder : public detail::Result_factory_impl {

public:
   struct Err : public base_exception {};

   Segment_match_builder(detail::Result_factory_impl& rf, Segment_match& sm)
   : detail::Result_factory_impl(rf),
     sm_(sm),
     last_gl_seg_()
   {}

   Gl_seg_match_id add_gl_segment(
            const Gl_seg_id gl_segment_id,
            interval_short const& gl_range,
            Match_metrics const& mm,
            Numsys_id num_system = Numsys_id(),
            Aligner_id aligner = Aligner_id()
   );

   Gl_seg_match_id add_gl_segment(
            const char vdj,
            std::string const& seg_name,
            interval_short const& gl_range,
            Match_metrics const& mm,
            Gl_db_id gl_database = Gl_db_id(),
            Numsys_id num_system = Numsys_id(),
            Aligner_id aligner = Aligner_id()
   );

   void add_aa_substitution(
            const unsigned read_pos,
            const char aa_from,
            const char aa_to,
            const unsigned gl_pos,
            Gl_seg_match_id gls_match = Gl_seg_match_id()
   );

   Segment_match const  & get() const  {return sm_;}
   Segment_match        & get()        {return sm_;}

private:
   Segment_match& sm_;
   Gl_seg_match_id last_gl_seg_;
};

/**@brief Construct alignment results for one sequencing read
*******************************************************************************/
class VDJML_DECL Result_builder : public detail::Result_factory_impl {
//   typedef boost::shared_ptr<Read_result> result_ptr;
   typedef std::auto_ptr<Read_result> result_ptr;
public:
   struct Err : public base_exception {};

   Result_builder(detail::Result_factory_impl& rf, std::string const& id);

   Result_builder(Results_meta& rm, std::string const& id);

   Result_builder(Result_builder const& rb)
   : detail::Result_factory_impl(rb),
     r_(const_cast<result_ptr&>(rb.r_).release())
   {}

   Read_result const& get() const {
      if( ! r_.get() ) BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("invalid builder")
      );
      return *r_;
   }

   Read_result& get(){
      if( ! r_.get() ) BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("invalid builder")
      );
      return *r_;
   }

   Segment_match_builder add_segment_match(
            std::string const& btop,
            interval_short const& read_range,
            const char vdj,
            std::string const& seg_name,
            interval_short const& gl_range,
            Match_metrics const& mm
   );

   Segment_combination_builder add_segment_combination(
            const Seg_match_id id1,
            const Seg_match_id id2 = Seg_match_id(),
            const Seg_match_id id3 = Seg_match_id(),
            const Seg_match_id id4 = Seg_match_id(),
            const Seg_match_id id5 = Seg_match_id()
   );

   std::auto_ptr<Read_result> release() { return r_;}

private:
   result_ptr r_;
};

/**@brief Construct alignment results for many sequencing reads
*******************************************************************************/
struct Result_factory : public detail::Result_factory_impl {
   Result_factory(Results_meta& meta) : detail::Result_factory_impl(meta) {}

   Result_builder new_result(std::string const& id) {
      Result_builder rb(*this, id);
      return rb;
   }
};

}//namespace vdjml
#endif /* RESULT_BUILDER_HPP_ */
