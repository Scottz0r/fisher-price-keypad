#ifndef _SCOTTZ0R_LED_MANAGER_INCLUDE_GUARD
#define _SCOTTZ0R_LED_MANAGER_INCLUDE_GUARD

#include "hw_led.h"
#include "look_up_table.h"
#include "prj_generic_types.h"

namespace scottz0r
{
    // TODO - a better name would be LED animator.
    class LedManager
    {
    public:
        LedManager();

        void set(const LookUpTable& table, unsigned long duration);

        void process();

        bool is_animating() const;

    private:
        void reset_state();

        unsigned long m_duration;
        size_type m_index;
        unsigned long m_last_change;
        const LookUpTable* m_table;
    };
}

#endif // _SCOTTZ0R_LED_MANAGER_INCLUDE_GUARD
