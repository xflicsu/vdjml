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

namespace vdjml{
class Results_meta;
class Read_result;

namespace detail{

/**@brief Construct alignment results for one sequencing read
*******************************************************************************/
class Result_factory_impl {
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

   void set_default_gl_database(const Gl_db_id def_gldb) {def_gldb_ = def_gldb;}
   void set_default_aligner(const Aligner_id def_aligner) {def_aligner_ = def_aligner;}
   void set_default_num_system(const Numsys_id def_numsys) {def_numsys_ = def_numsys;}

   Gl_db_id get_default_gl_database() const {return def_gldb_;}
   Aligner_id get_default_aligner() const {return def_aligner_;}
   Numsys_id get_default_num_system() const {return def_numsys_;}

   Results_meta const   & meta() const {return rm_;}
   Results_meta         & meta()       {return rm_;}

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

/**@brief Construct alignment results for one sequencing read
*******************************************************************************/
class VDJML_DECL Result_builder : public detail::Result_factory_impl {
//   typedef boost::shared_ptr<Read_result> result_ptr;
   typedef std::auto_ptr<Read_result> result_ptr;
public:
   Result_builder(detail::Result_factory_impl& rf, std::string const& id);

   Result_builder(Results_meta& rm, std::string const& id);

   Result_builder(Result_builder const& rb)
   : detail::Result_factory_impl(rb),
     r_(const_cast<result_ptr&>(rb.r_).release())
   {}

   Read_result const & get() const  {return *r_;}
   Read_result       & get()        {return *r_;}

   std::auto_ptr<Read_result> release() { return r_;}

private:
   result_ptr r_;
};

/**@brief Construct alignment results for one sequencing read
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
