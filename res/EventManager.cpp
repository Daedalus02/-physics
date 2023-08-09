#include "../def/EventManager.h"

#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
EventManager::EventManager(){
    // Empty constructor.
}

EventManager &EventManager::getInstance(){
    static EventManager eventManager();
    return eventManager;
}

void EventManager::TriggerAllQueuedEvents() {
    NotificationVec vecNotification;
    {
        boost::recursive_mutex::scoped_lock lock(notification_mutex_);
        std::swap(vecNotification, queued_notifications_);
    }
    BOOST_FOREACH(const EventNotificationFn& fn, vecNotification){
        fn();
    }
}
void EventManager::QueueEvent(const EventNotificationFn &event) {
    {
        // One thread at time supported int this function.
        boost::recursive_mutex::scoped_lock lock(notification_mutex_);
        NotificationVec.push_back(event);
    }
}
EventManager::~EventManager() {
    // Empty destructor.
}