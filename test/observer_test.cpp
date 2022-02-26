#include <iostream>
#include <Subject.h>
#include <Observer.h>

int main(int argc, char* argv[]){
    Subject subject = Subject();
    std::shared_ptr<Observer> ob0 = std::make_shared<Observer>("ob0");
    std::shared_ptr<Observer> ob1 = std::make_shared<Observer>("ob1");
    std::shared_ptr<Observer> ob2 = std::make_shared<Observer>("ob2");

    std::string topic = "test_topic";

    subject.add_observer(topic, ob0);

    subject.notify(topic, "Hello there");
    return 0;
}
