/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   bg_png;
    const int            bg_pngSize = 44584;

    extern const char*   bg_psd;
    const int            bg_psdSize = 1449940;

    extern const char*   bg2_psd;
    const int            bg2_psdSize = 1559598;

    extern const char*   luluby_png;
    const int            luluby_pngSize = 677900;

    extern const char*   tourniquet_png;
    const int            tourniquet_pngSize = 56441;

    extern const char*   tourniquet_psd;
    const int            tourniquet_psdSize = 1179920;

    extern const char*   tourniquet2_png;
    const int            tourniquet2_pngSize = 56441;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 7;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
