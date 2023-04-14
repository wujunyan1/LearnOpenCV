#pragma once
#include "Core.h"

namespace Core
{
#define SAFE_RETAIN(ptr) { if(ptr) { ptr->retain(); } }
#define SAFE_RELEASE(ptr) { if(ptr) { ptr->release(); } }

    class Ref;

    /**
      * Interface that defines how to clone an Ref.
      * @lua NA
      * @js NA
      */
    class Clonable
    {
    public:
        /** Returns a copy of the Ref. */
        virtual Clonable* clone() const = 0;

        /**
         * @js NA
         * @lua NA
         */
        virtual ~Clonable() {};
    };

    /**
     * Ref is used for reference count management. If a class inherits from Ref,
     * then it is easy to be shared in different places.
     * @js NA
     */
    class Ref
    {
    public:
        /**
         * Retains the ownership.
         *
         * This increases the Ref's reference count.
         *
         * @see release, autorelease
         * @js NA
         */
        void retain();

        /**
         * Releases the ownership immediately.
         *
         * This decrements the Ref's reference count.
         *
         * If the reference count reaches 0 after the decrement, this Ref is
         * destructed.
         *
         * @see retain, autorelease
         * @js NA
         */
        void release();

        /**
         * Releases the ownership sometime soon automatically.
         *
         * This decrements the Ref's reference count at the end of current
         * autorelease pool block.
         *
         * If the reference count reaches 0 after the decrement, this Ref is
         * destructed.
         *
         * @returns The Ref itself.
         *
         * @see AutoreleasePool, retain, release
         * @js NA
         * @lua NA
         */
        Ref* autorelease();

        /**
         * Returns the Ref's current reference count.
         *
         * @returns The Ref's reference count.
         * @js NA
         */
        unsigned int getReferenceCount() const;

    protected:
        /**
         * Constructor
         *
         * The Ref's reference count is 1 after construction.
         * @js NA
         */
        Ref();

    public:
        /**
         * Destructor
         *
         * @js NA
         * @lua NA
         */
        virtual ~Ref();

        ui64 getId() { return id; };

    protected:
        /// count of references
        unsigned int _referenceCount;

        ui64 id;

        friend class AutoreleasePool;

    private:
        static ui64 _id;

#if ENABLE_SCRIPT_BINDING
    public:
        /// object id, ScriptSupport need public _ID
        unsigned int        _ID;
        /// Lua reference id
        int                 _luaID;
        /// scriptObject, support for swift
        void* _scriptObject;

        /**
         When true, it means that the object was already rooted.
         */
        bool _rooted;
#endif

        // Memory leak diagnostic data (only included when CC_REF_LEAK_DETECTION is defined and its value isn't zero)
#if REF_LEAK_DETECTION
    public:
        static void printLeaks();
#endif
    };
}