#ifndef _SCOTTZ0R_LOOK_UP_TABLE_INCLUDE_GUARD
#define _SCOTTZ0R_LOOK_UP_TABLE_INCLUDE_GUARD

#include "hw_led.h"
#include "prj_generic_types.h"

namespace scottz0r
{
    #define color_count(tbl) ((sizeof(tbl) / sizeof(tbl[0])) / 3)

    // TODO - a better name would be ColorTable

    // Wrapper around a table of colors. Colors are assumed to be stored in a single array, with 3 values per
    // color. The index shall be divisible by 3.
    class LookUpTable
    {
    public:
        LookUpTable(const color_t* table, size_type color_count);

        bool at(size_type color_idx, RGB& result) const;

        inline size_type size() const { return m_size; }

    private:
        const color_t* m_table;
        size_type m_size;
    };
}

#endif // _SCOTTZ0R_LOOK_UP_TABLE_INCLUDE_GUARD
