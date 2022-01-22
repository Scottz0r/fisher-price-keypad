#include "look_up_table.h"
#include "avr/pgmspace.h"

namespace scottz0r
{
    LookUpTable::LookUpTable(const color_t* table, size_type color_count)
        : m_table(table)
        , m_size(color_count)
    {

    }

    bool LookUpTable::at(size_type color_idx, RGB& result) const
    {
        // The table is stored with 3 values per color.
        if (color_idx < m_size)
        {
            // The real index into the table is the color * 3.
            const color_t* color_ptr = m_table + (color_idx * 3);

            // Get bytes from the color array.
            result.r = (color_t)pgm_read_byte_near(color_ptr);
            result.g = (color_t)pgm_read_byte_near(color_ptr + 1);
            result.b = (color_t)pgm_read_byte_near(color_ptr + 2);

            return true;
        }

        return false;
    }
}
