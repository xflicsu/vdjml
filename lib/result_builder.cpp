/** @file "/vdjml/lib/result_builder.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#ifndef VDJML_SOURCE
#define VDJML_SOURCE
#endif
#include "vdjml/result_builder.hpp"

#include "boost/foreach.hpp"

#include "vdjml/results_meta.hpp"

namespace vdjml{ namespace detail {

/*
*******************************************************************************/
Gl_db_id Result_factory_impl::set_default_gl_database(
         std::string const& name,
         std::string const& version,
         std::string const& species,
         std::string const& url
) {
   def_gldb_ =
            rm_.germline_db_map().insert(
                     Gl_db_info(name, version, species, url)
            );
   return def_gldb_;
}

Aligner_id Result_factory_impl::set_default_aligner(
         std::string const& name,
         std::string const& version,
         std::string const& parameters,
         const unsigned run_id
) {
   def_aligner_ =
            rm_.aligner_map().insert(
                     Aligner_info(name, version, parameters, run_id)
            );
   return def_aligner_;
}

Numsys_id Result_factory_impl::set_default_num_system(std::string const& name) {
   def_numsys_ = rm_.num_system_map().insert(name);
   return def_numsys_;
}


}//namespace detail

/*
*******************************************************************************/
Segment_combination_builder::Segment_combination_builder(
         detail::Result_factory_impl& rf,
         Read_result& rr,
         Segment_combination const& sc
)
: detail::Result_factory_impl(rf),
  rr_(rr),
  n_(rr_.segment_combinations().size())
{
   BOOST_FOREACH(const Seg_match_id id, sc.smv_) {
      if( ! rr_.segment_match_map().find(id) ) {
         BOOST_THROW_EXCEPTION(
                  Err()
                  << Err::msg_t("invalid segment match ID")
                  << Err::int1_t(id())
         );
      }
   }
   rr_.insert(sc);
}

/*
*******************************************************************************/
void Segment_combination_builder::add_region(
         std::string const& name,
         interval_short read_range,
         Match_metrics const& mm
) {

}

/*
*******************************************************************************/
void Segment_combination_builder::add_region(
         const Numsys_id num_system,
         const Region_id region,
         interval_short const& read_range,
         Match_metrics const& mm
) {
   const Gene_region gr(num_system, region, read_range, mm);
   rr_.segment_combinations()[n_].grv_.push_back(gr);
}

/*
*******************************************************************************/
void Segment_match_builder::add_gl_segment(
         const Numsys_id numsys_id,
         const Aligner_id aligner_id,
         const Gl_seg_id gl_segment_id,
         interval_short const& gl_range,
         Match_metrics const& mm
) {
   sm_.insert(
            Gl_segment_match(
                     numsys_id, aligner_id, gl_segment_id, gl_range, mm
            )
   );
}

/*
*******************************************************************************/
void Segment_match_builder::add_gl_segment(
         const char vdj,
         std::string const& seg_name,
         interval_short const& gl_range,
         Match_metrics const& mm
) {
   if( ! get_default_num_system() ) BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("set default or specify numbering system")
   );

   if( ! get_default_aligner() ) BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("set default or specify aligner")
   );

   Gl_seg_id gs_id;
   //guess germline segment ID
   const Gl_segment_map::name_range nr =
            meta().germline_segment_map().find(seg_name);
   if( boost::distance(nr) == 1U ) gs_id = nr.front().id_;
   else {//if not found or not unique
      if( ! get_default_gl_database() ) BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("set default or specify germline DB")
      );
      gs_id = meta().add_segment(get_default_gl_database(), vdj, seg_name);
   }
   add_gl_segment(
            get_default_num_system(),
            get_default_aligner(),
            gs_id,
            gl_range,
            mm
   );
}

/*
*******************************************************************************/
Result_builder::Result_builder(
         detail::Result_factory_impl& rf,
         std::string const& id
)
: detail::Result_factory_impl(rf), r_(new Read_result(id))
{}

/*
*******************************************************************************/
Result_builder::Result_builder(Results_meta& rm, std::string const& id)
: detail::Result_factory_impl(rm), r_(new Read_result(id))
{}

/*
*******************************************************************************/
Segment_match_builder Result_builder::add_segment_match(
         std::string const& btop,
         interval_short const& read_range,
         const char vdj,
         std::string const& seg_name,
         interval_short const& gl_range,
         Match_metrics const& mm
) {
   const Seg_match_id id = get().insert(Segment_match(Btop(btop), read_range));
   Segment_match_builder smb(*this, get()[id]);
   smb.add_gl_segment(vdj, seg_name, gl_range, mm);
   return smb;
}


/*
*******************************************************************************/

}//namespace vdjml
