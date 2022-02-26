#include <Subject.h>
#include <algorithm>
#include <regex>

Subject::Subject()
{
    topic_map["default"] = {};
}

void Subject::add_observer(std::weak_ptr<Observer> observer){
    topic_map["default"].push_back(observer);
}

void Subject::add_observer(std::string topic, std::weak_ptr<Observer> observer)
{
    topic_map[topic].push_back(observer);
}

void Subject::remove_observer(std::string topic, std::weak_ptr<Observer> observer)
{
    auto iter = topic_map.find(topic);
    if(iter == topic_map.end())
        return;

    std::vector<std::weak_ptr<Observer>>& observer_vector = iter->second;

    auto findIter = std::find_if(observer_vector.begin(), observer_vector.end(), [&observer](const std::weak_ptr<Observer> ptr) {
        return ptr.lock() == observer.lock();
    });

    if(findIter == observer_vector.end())
        return;

    observer_vector.erase(findIter);
}

void Subject::remove_observer(std::weak_ptr<Observer> observer){
    for(const auto& ob: topic_map){
        remove_observer(ob.first, observer);
    }
}

void Subject::notify_default(std::string message){
    notify("default", message);
}

void Subject::notify(std::string topic, std::string message)
{
    for(const auto& ob_map: topic_map){
        std::regex e (ob_map.first);
        if(!std::regex_search(topic,e))
            continue;
        std::vector<std::weak_ptr<Observer>> observers = ob_map.second;
        for(const auto& ob: observers){
            if(auto observer = ob.lock())
                observer->update(message);
        }
    }
}

std::unordered_map<std::string, std::vector<std::string>> Subject::observerMap() const
{
    std::unordered_map<std::string, std::vector<std::string>> result{};
    for(const auto& topic: topic_map){
        for(const auto& it: topic.second){
            if(auto observer = it.lock())
                result[topic.first].push_back(observer->observer_name);
        }
    }
    return result;
}

std::vector<std::string> Subject::topics() const {
    std::vector<std::string> result;
    for(const auto& topic: topic_map){
        result.push_back(topic.first);
    }
    return result;
}

std::vector<std::string> Subject::observers_of_topic(std::string topic /* = default */) const {
    auto iter = topic_map.find(topic);
    if(iter == topic_map.end())
        return{};

    std::vector<std::string> result;
    for(const auto& obs_iter: iter->second){
        if(auto observer = obs_iter.lock())
            result.push_back(observer->observer_name);
    }
    return result;
}
