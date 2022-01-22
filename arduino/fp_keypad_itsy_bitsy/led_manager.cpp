#include "Arduino.h"

#include "led_manager.h"

namespace scottz0r
{
    LedManager::LedManager()
    {
        reset_state();
    }

    void LedManager::set(const LookUpTable& lut, unsigned long duration)
    {
        // TODO: Probably a wrapper for the table.
        m_table = &lut;

        m_duration = duration / lut.size();
        m_index = 0;

        // Set the last to so that the next process will change the state.
        m_last_change = millis();
    }

    void LedManager::process()
    {
        if (m_table == nullptr)
        {
            return;
        }

        if (m_index >= m_table->size())
        {
            reset_state();
            return;
        }

        // Find if enough time has passed to do the next step.
        unsigned long now = millis();
        unsigned long elapsed = now - m_last_change;

        if (elapsed < m_duration)
        {
            return;
        }

        // Change the color to the item at the current index.
        RGB rgb;
        if (m_table->at(m_index, rgb))
        {
            write_led(rgb);
            m_last_change = now;

            // Step to the next color for the next tick.
            ++m_index;

            // Reset to a completed state if all steps completed.
            if (m_index >= m_table->size())
            {
                reset_state();
            }
        }
        else
        {
            // Table lookup failed, so reset state to stop processing.
            reset_state();
            return;
        }
    }

    bool LedManager::is_animating() const
    {
        // A non-null color table indicates that the manager is still processing the current animation.
        return m_table != nullptr;
    }

    void LedManager::reset_state()
    {
        // Clear out color on the LED (otherwise colors that do not start/stop with 0s will leave LED on).
        write_led(RGB{});

        m_duration = 0;
        m_last_change = 0;
        m_index = 0;
        m_table = nullptr;
    }
}
