#pragma once
#include "Event.h"
#include "../math/Vector2.h"

/**
 * @addtogroup base
 * @{
 */

namespace Core
{

    /** @class EventMouse
     * @brief The mouse event.
     */
    class EventMouse : public Event
    {
    public:
        /**
        * MouseEventType Different types of MouseEvent.
        * @js NA
        */
        enum class MouseEventType
        {
            MOUSE_NONE,
            MOUSE_DOWN,
            MOUSE_UP,
            MOUSE_MOVE,
            MOUSE_SCROLL,
        };

        enum class MouseButton
        {
          BUTTON_UNSET   = -1,
          BUTTON_LEFT    =  0,
          BUTTON_RIGHT   =  1,
          BUTTON_MIDDLE  =  2,
          BUTTON_4       =  3,
          BUTTON_5       =  4,
          BUTTON_6       =  5,
          BUTTON_7       =  6,
          BUTTON_8       =  7
        };


        /** Constructor.
         *
         * @param mouseEventCode A given mouse event type.
         * @js ctor
         */
        EventMouse(MouseEventType mouseEventCode);

        /** Set mouse scroll data.
         * 
         * @param scrollX The scroll data of x axis.
         * @param scrollY The scroll data of y axis.
         */
        void setScrollData(float scrollX, float scrollY) { _scrollX = scrollX; _scrollY = scrollY; }
        /** Get mouse scroll data of x axis.
         * 
         * @return The scroll data of x axis.
         */
        float getScrollX() const { return _scrollX; }
        /** Get mouse scroll data of y axis.
         *
         * @return The scroll data of y axis.
         */
        float getScrollY() const { return _scrollY; }

        /** Set the cursor position.
         *
         * @param x The x coordinate of cursor position.
         * @param y The y coordinate of cursor position.
         * @js setLocation
         */
        void setCursorPosition(float x, float y) { 
            _x = x;
            _y = y;
            _prevPoint = _point;
            _point.x = x;
            _point.y = y;
            if (!_startPointCaptured)
            {
                _startPoint = _point;
                _startPointCaptured = true;
            }
        }

        /** Set mouse button.
         * 
         * @param button a given mouse button.
         * @js setButton
         */
        void setMouseButton(MouseButton button) { _mouseButton = button; }
        /** Get mouse button.
         *
         * @return The mouse button.
         * @js getButton
         */
        MouseButton getMouseButton() const { return _mouseButton; }
        /** Get the cursor position of x axis.
         *
         * @return The x coordinate of cursor position.
         * @js getLocationX
         */
        float getCursorX() const { return _x; }
        /** Get the cursor position of y axis.
         *
         * @return The y coordinate of cursor position.
         * @js getLocationY
         */
        float getCursorY() const { return _y; }

        /** Returns the current touch location in OpenGL coordinates.
         *
         * @return The current touch location in OpenGL coordinates.
         */
        Math::Vector2 getLocation() const;
        /** Returns the previous touch location in OpenGL coordinates.
         *
         * @return The previous touch location in OpenGL coordinates.
         * @js NA
         */
        Math::Vector2 getPreviousLocation() const;
        /** Returns the start touch location in OpenGL coordinates.
         *
         * @return The start touch location in OpenGL coordinates.
         * @js NA
         */
        Math::Vector2 getStartLocation() const;
        /** Returns the delta of 2 current touches locations in screen coordinates.
         *
         * @return The delta of 2 current touches locations in screen coordinates.
         */
        Math::Vector2 getDelta() const;
        /** Returns the current touch location in screen coordinates.
         *
         * @return The current touch location in screen coordinates.
         */
        Math::Vector2 getLocationInView() const;
        /** Returns the previous touch location in screen coordinates.
         *
         * @return The previous touch location in screen coordinates.
         * @js NA
         */
        Math::Vector2 getPreviousLocationInView() const;
        /** Returns the start touch location in screen coordinates.
         *
         * @return The start touch location in screen coordinates.
         * @js NA
         */
        Math::Vector2 getStartLocationInView() const;


    private:
        MouseEventType _mouseEventType;
        MouseButton _mouseButton;
        float _x;
        float _y;
        float _scrollX;
        float _scrollY;

        bool _startPointCaptured;
        Math::Vector2 _startPoint;
        Math::Vector2 _point;
        Math::Vector2 _prevPoint;

        friend class EventListenerMouse;
    };
}