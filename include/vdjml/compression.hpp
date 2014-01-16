/** @file "/vdjml/include/vdjml/compression.hpp" 
part of vdjml project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@date 2013 @author Mikhail K Levin
*******************************************************************************/
#ifndef COMPRESSION_HPP_
#define COMPRESSION_HPP_

namespace vdjml{

/**@brief 
*******************************************************************************/
enum Compression {
   Uncompressed, Unknown_compression, gzip,
   bzip2, zlib
};


}//namespace vdjml
#endif /* COMPRESSION_HPP_ */
