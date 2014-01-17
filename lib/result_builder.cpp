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

/*
*******************************************************************************/
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

/*
*******************************************************************************/
Numsys_id Result_factory_impl::set_default_num_system(std::string const& name) {
   def_numsys_ = rm_.num_system_map().insert(name);
   return def_numsys_;
}

/*
*******************************************************************************/
Gl_db_id Result_factory_impl::get_default_gl_database() const {
   if( def_gldb_ ) return def_gldb_;
   if( rm_.germline_db_map().size() == 1U ) {
      return rm_.germline_db_map().front().id();
   }
   return Gl_db_id();
}

/*
*******************************************************************************/
Aligner_id Result_factory_impl::get_default_aligner() const {
   if( def_aligner_ ) return def_aligner_;
   if( rm_.aligner_map().size() == 1U ) {
      return rm_.aligner_map().front().id();
   }
   return Aligner_id();
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
   BOOST_FOREACH(const Seg_match_id id, sc.segments()) {
      if( ! rr_.segment_matches().find(id) ) {
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
         Match_metrics const& mm,
         Numsys_id num_system
) {
   if( ! num_system ) num_system = get_default_num_system();
   if( ! num_system ) BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("set default or specify the numbering system")
   );
   const Region_id rid = meta().gene_region_map().insert(name);
   add_region(rid, read_range, mm, num_system);
}

/*
*******************************************************************************/
void Segment_combination_builder::add_region(
         const Region_id region,
         interval_short const& read_range,
         Match_metrics const& mm,
         Numsys_id num_system
) {
   if( ! num_system ) num_system = get_default_num_system();
   if( ! num_system ) BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("set default or specify the numbering system")
   );

   rr_.segment_combinations()[n_].insert_region(
            num_system, region, read_range, mm
   );
}

/*
*******************************************************************************/
Gl_seg_match_id Segment_match_builder::add_gl_segment(
         const Gl_seg_id gl_segment_id,
         interval_short const& gl_range,
         Match_metrics const& mm,
         Numsys_id num_system,
         Aligner_id aligner
) {
   if( ! num_system ) num_system = get_default_num_system();
   if( ! num_system ) BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("set default or specify the numbering system")
   );
   if( ! aligner ) aligner = get_default_aligner();
   if( ! aligner ) BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("set default or specify the aligner")
   );

   return sm_.insert(
            Gl_segment_match(
                     num_system, aligner, gl_segment_id, gl_range, mm
            )
   );
}

/*
*******************************************************************************/
Gl_seg_match_id Segment_match_builder::add_gl_segment(
         const char vdj,
         std::string const& seg_name,
         interval_short const& gl_range,
         Match_metrics const& mm,
         Gl_db_id gl_database,
         Numsys_id num_system,
         Aligner_id aligner
) {
   if( ! gl_database ) gl_database = get_default_gl_database();

   if( ! num_system ) num_system = get_default_num_system();
   if( ! num_system ) BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("set default or specify the numbering system")
   );

   if( ! aligner ) aligner = get_default_aligner();
   if( ! aligner ) BOOST_THROW_EXCEPTION(
            Err()
            << Err::msg_t("set default or specify the aligner")
   );

   Gl_seg_id gs_id;
   if( gl_database ) {
      gs_id = meta().add_segment(gl_database, vdj, seg_name);
   } else { //guess germline segment ID
      const Gl_segment_map::name_range nr =
               meta().germline_segment_map().find(seg_name);
      if( boost::distance(nr) == 1U ) gs_id = nr.front().id_;
      else BOOST_THROW_EXCEPTION(
               Err()
               << Err::msg_t("set default or specify germline DB")
      );
   }
   return add_gl_segment(
            gs_id,
            gl_range,
            mm,
            num_system,
            aligner
   );
}

/*
*******************************************************************************/
void Segment_match_builder::add_aa_substitution(
         const unsigned read_pos,
         const char aa_from,
         const char aa_to,
         Gl_seg_match_id gls_match,
         const unsigned gl_pos
) {
   Aa_substitution aas(read_pos, aa_from, aa_to);
   aas.insert(Gl_position(gls_match, gl_pos));
   sm_.insert(aas);
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
Segment_combination_builder Result_builder::add_segment_combination(
         const Seg_match_id id1,
         const Seg_match_id id2,
         const Seg_match_id id3,
         const Seg_match_id id4,
         const Seg_match_id id5
) {
   return Segment_combination_builder(
            *this,
            get(),
            Segment_combination(id1, id2, id3, id4, id5)
   );
}

/*
*******************************************************************************/

}//namespace vdjml
