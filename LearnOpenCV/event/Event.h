#pragma once

namespace Core
{
    class TreeNode;

    class Event
    {
    public:
        /** Type Event type.*/
        enum class Type
        {
            TOUCH,
            KEYBOARD,
            MOUSE,
            FOCUS,
            GAME_CONTROLLER,
            CUSTOM
        };

        /** Constructor */
        Event(Type type);
    public:
        /** Destructor.
         */
        virtual ~Event();

        /** Gets the event type.
         *
         * @return The event type.
         */
        Type getType() const { return _type; }

        /** Stops propagation for current event.
         */
        void stopPropagation() { _isStopped = true; }

        /** Checks whether the event has been stopped.
         *
         * @return True if the event has been stopped.
         */
        bool isStopped() const { return _isStopped; }

        /** Gets current target of the event.
         * @return The target with which the event associates.
         * @note It's only available when the event listener is associated with node.
         *        It returns 0 when the listener is associated with fixed priority.
         */
        TreeNode* getCurrentTarget() { return _currentTarget; }

    protected:
        /** Sets current target */
        void setCurrentTarget(TreeNode* target) { _currentTarget = target; }

        Type _type;     ///< Event type

        bool _isStopped;       ///< whether the event has been stopped.
        TreeNode* _currentTarget;  ///< Current target

        friend class EventDispatcher;
    };
}
