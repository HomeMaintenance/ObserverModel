#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <Observer.h>

/**
 * @brief Subject for ObserverPattern
 *
 */
class Subject {
    public:
        /**
         * @brief Construct a new Subject object
         *
         */
        explicit Subject();
        virtual ~Subject() = default;
        /**
         * @brief Add a observer to the notification list
         *
         * @param observer
         */
        virtual void add_observer(std::weak_ptr<Observer> observer);
        virtual void add_observer(std::string topic, std::weak_ptr<Observer> observer);
        /**
         * @brief Remove a observer from the notification list
         *
         * @param observer
         */
        virtual void remove_observer(std::weak_ptr<Observer> observer);
        virtual void remove_observer(std::string topic, std::weak_ptr<Observer> observer);
        /**
         * @brief Notify all topic_map from the notification list
         *
         */
        virtual void notify_default(std::string message = "");
        virtual void notify(std::string topic, std::string message = "");
        /**
         * @brief Return all the names of topic_map from the notification list
         *
         * @return std::list<std::string>
         */
        std::unordered_map<std::string, std::vector<std::string>> observerMap() const;
        std::vector<std::string> topics() const;
        std::vector<std::string> observers_of_topic(std::string topic = "default") const;

    private:
        /**
         * @brief Notification list
         * The update function will be called of the observes from the notification list when notify() is called.
         */
        std::unordered_map<std::string, std::vector<std::weak_ptr<Observer>>> topic_map;
};
