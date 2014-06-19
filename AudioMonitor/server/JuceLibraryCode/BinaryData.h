/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_20665613_INCLUDED
#define BINARYDATA_H_20665613_INCLUDED

namespace BinaryData
{
    extern const char*   IpEndpointName_o;
    const int            IpEndpointName_oSize = 2272;

    extern const char*   NetworkingUtils_o;
    const int            NetworkingUtils_oSize = 1784;

    extern const char*   UdpSocket_o;
    const int            UdpSocket_oSize = 27976;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 3;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
