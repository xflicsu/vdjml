/** @file "/vdjml/binding/python/misc_types.cpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2014 @author Mikhail K Levin
*******************************************************************************/
#include "boost/python.hpp"
namespace bp = boost::python;

#include "vdjml/compression.hpp"
#include "vdjml/xml_writer_options.hpp"
#include "vdjml/interval.hpp"
#include "vdjml/btop.hpp"
#include "vdjml/match_metrics.hpp"
#include "vdjml/aa_index.hpp"
#include "vdjml/numbering_system.hpp"
#include "vdjml/gene_region_type.hpp"
using vdjml::Btop;
using vdjml::Xml_writer_options;
using vdjml::interval_short;
using vdjml::Match_metrics;
using vdjml::Percent;
using vdjml::Num_system;
using vdjml::Gene_region_type;

void export_misc_types() {

   bp::enum_<vdjml::Aminoacid>("Aminoacid")
   .value("Ala", vdjml::Ala)
   .value("Cys", vdjml::Cys)
   .value("Asp", vdjml::Asp)
   .value("Glu", vdjml::Glu)
   .value("Phe", vdjml::Phe)
   .value("Gly", vdjml::Gly)
   .value("His", vdjml::His)
   .value("Ile", vdjml::Ile)
   .value("Lys", vdjml::Lys)
   .value("Leu", vdjml::Leu)
   .value("Met", vdjml::Met)
   .value("Asn", vdjml::Asn)
   .value("Pro", vdjml::Pro)
   .value("Gln", vdjml::Gln)
   .value("Arg", vdjml::Arg)
   .value("Ser", vdjml::Ser)
   .value("Thr", vdjml::Thr)
   .value("Val", vdjml::Val)
   .value("Trp", vdjml::Trp)
   .value("Tyr", vdjml::Tyr)
   .value("Stop", vdjml::Stop)
   ;

   bp::enum_<vdjml::Compression>("Compression")
   .value("Unknown_compression", vdjml::Unknown_compression)
   .value("Uncompressed", vdjml::Uncompressed)
   .value("gzip", vdjml::gzip)
   .value("bzip2", vdjml::bzip2)
   .value("zlib", vdjml::zlib)
   ;

   bp::class_<Xml_writer_options> (
      "Xml_writer_options",
      "Options for XML output",
      bp::init<
         std::string const&,
         std::string const&,
         char,
         std::string const&,
         const std::size_t
      >(
           (
              bp::arg("indent") = "   ",
              bp::arg("encoding") = "UTF-8",
              bp::arg("quote") = '"',
              bp::arg("xml_version") = "1.0",
              bp::arg("buff_size") = 1024
           )
      )
   )
   .def_readwrite("indent", &Xml_writer_options::indent_, "indentation string")
   .def_readwrite("encoding", &Xml_writer_options::encoding_)
   .def_readwrite("quote", &Xml_writer_options::quote_, "quotation character")
   .def_readwrite("xml_version", &Xml_writer_options::xml_version_)
   .def_readwrite("buff_size", &Xml_writer_options::buff_size_, "output buffer size")
   ;

   bp::class_<interval_short>("Interval", "sequence interval", bp::no_init)
   .def(
         "pos0_len",
         &interval_short::pos0_len,
         "create interval from 0-based starting position and length",
         (bp::arg("pos0"), bp::arg("len"))
   )
   .staticmethod("pos0_len")
   .def(
         "first_last_1",
         &interval_short::first_last_1,
         "create interval from 1-based first and last positions",
         (bp::arg("first1"), bp::arg("last1"))
   )
   .staticmethod("first_last_1")
   .def(
         "first_last_0",
         &interval_short::first_last_0,
         "create interval from 0-based first and last positions",
         (bp::arg("first0"), bp::arg("last0"))
   )
   .staticmethod("first_last_0")
   .def("length", &interval_short::length)
   .def("pos_0", &interval_short::pos_0)
   .def("pos_1", &interval_short::pos_1)
   .def("last_0", &interval_short::last_0)
   .def("last_1", &interval_short::last_1)
   .def(str(bp::self))
   .def(boost::python::self < boost::python::self)
   .def(boost::python::self > boost::python::self)
   .def(boost::python::self <= boost::python::self)
   .def(boost::python::self >= boost::python::self)
   .def(boost::python::self == boost::python::self)
   .def(boost::python::self != boost::python::self)
   ;

   bp::class_<Btop>(
      "Btop",
      "Blast trace-back operations, alignment description",
      bp::init<std::string const&>("s")
   )
   .def(str(bp::self))
   .def(boost::python::self < boost::python::self)
   .def(boost::python::self > boost::python::self)
   .def(boost::python::self <= boost::python::self)
   .def(boost::python::self >= boost::python::self)
   .def(boost::python::self == boost::python::self)
   .def(boost::python::self != boost::python::self)
   ;

   bp::class_<Percent>(
      "Percent",
      bp::init<const float>("p")
   )
   .def(str(bp::self))
   .def(boost::python::self < boost::python::self)
   .def(boost::python::self > boost::python::self)
   .def(boost::python::self <= boost::python::self)
   .def(boost::python::self >= boost::python::self)
   .def(boost::python::self == boost::python::self)
   .def(boost::python::self != boost::python::self)
   .def("percent", &Percent::percent)
   .def("fraction", &Percent::fraction)
   ;

   bp::class_<Match_metrics>(
      "Match_metrics",
      "Metrics of sequence alignment",
      bp::init<
         const int,
         const double,
         const unsigned,
         const unsigned,
         const unsigned,
         const bool,
         const bool,
         const bool
      >(
               (
                        bp::arg("score"),
                        bp::arg("identity"),
                        bp::arg("insertions") = 0,
                        bp::arg("deletions") = 0,
                        bp::arg("substitutions") = 0,
                        bp::arg("stop_codon") = false,
                        bp::arg("mutated_invariant") = false,
                        bp::arg("is_inverted") = false
               )
      )
   )
   .def("score", &Match_metrics::score)
   .def("identity", &Match_metrics::identity)
   .def("insertions", &Match_metrics::insertions)
   .def("deletions", &Match_metrics::deletions)
   .def("substitutions", &Match_metrics::stop_codon)
   .def("stop_codon", &Match_metrics::score)
   .def("mutated_invariant", &Match_metrics::mutated_invariant)
   .def("is_inverted", &Match_metrics::is_inverted)
   ;

   bp::object ns = bp::class_<Num_system>("Num_system", bp::no_init);
   ns.attr("imgt") = Num_system::imgt;
   ns.attr("kabat") = Num_system::kabat;

   bp::object grt =
            bp::class_<Gene_region_type>("Gene_region_type", bp::no_init);
   grt.attr("fr1") = Gene_region_type::fr1;
   grt.attr("fr2") = Gene_region_type::fr2;
   grt.attr("fr3") = Gene_region_type::fr3;
   grt.attr("cdr1") = Gene_region_type::cdr1;
   grt.attr("cdr2") = Gene_region_type::cdr2;
   grt.attr("cdr3") = Gene_region_type::cdr3;
   grt.attr("vd_junction") = Gene_region_type::vd_junction;
   grt.attr("dj_junction") = Gene_region_type::dj_junction;
}
