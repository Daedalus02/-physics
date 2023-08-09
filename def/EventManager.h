//
// Created by kriptos on 05/07/2023.
//

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <boost/function>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <vector>
#include <memory>

class EventManager{
public:
    // PUBLIC CONSTRUCTORS:
    // Deleted copy constructor.
    EventManager(const EventManager& eventManager) = delete;

    // MEMBER FUNCTIONS/OPERATORS:
    // Deleted copy assignment.
    EventManager& operator=(const EventManager& EventManager) = delete;
    // This function return the single instance of this class in the system.
    static EventManager& getInstance();
    // This function notify all listeners of the recent events.
    void TriggerAllQueuedEvents();
    // This function enqueue a notification function.
    void QueueEvent(const EventNotificationFn&  event);


    // DESTRUCTOR:
    ~EventManager();

    // PUBLIC DEFINITIONS:
    // Defining the callbacks' signature.
    typedef void EventNotificationFnSignature();
    typedef boost::function<EventNotificationFnSignature> EventNotificationFn;

private:
    // PRIVATE CONSTRUCTORS: 
    // Private default constructor. 
    EventManager();

    // PRIVATE DEFINITIONS:
    // This is the definition of a vector for storing notifications.
    typedef std::vector<EventNotificationFn> NotificationVec;

    // MEMBER ATTRIBUTES:
    // This vector stores all the events that are added to this manager.
    NotificationVec queued_notifications_;
    // This variable is a recursive mutex.
    boost::recursive_mutex notification_mutex_;
};

typedef shared_ptr<EventManager> EventManagerPtr;

#endif
