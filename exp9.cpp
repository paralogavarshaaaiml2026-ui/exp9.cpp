#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// Observer Interface
class Observer
{
public:
    virtual void notify(const string& message) = 0;
    virtual ~Observer() {}
};

// Email Notification Observer
class EmailNotification : public Observer
{
private:
    string email;

public:
    EmailNotification(string e)
    {
        email = e;
    }

    void notify(const string& message) override
    {
        cout << "Email sent to " << email
             << ": " << message << endl;
    }
};

// SMS Notification Observer
class SMSNotification : public Observer
{
private:
    string phoneNumber;

public:
    SMSNotification(string number)
    {
        phoneNumber = number;
    }

    void notify(const string& message) override
    {
        cout << "SMS sent to " << phoneNumber
             << ": " << message << endl;
    }
};

// Factory Class
class NotificationFactory
{
public:
    static shared_ptr<Observer> createNotification(
        const string& type,
        const string& receiver)
    {
        if (type == "EMAIL")
        {
            return make_shared<EmailNotification>(receiver);
        }
        else if (type == "SMS")
        {
            return make_shared<SMSNotification>(receiver);
        }

        return nullptr;
    }
};

// Singleton Event Manager
class EventManager
{
private:
    vector<shared_ptr<Observer>> observers;

    EventManager()
    {
    }

public:
    EventManager(const EventManager&) = delete;

    EventManager& operator=(const EventManager&) = delete;

    static EventManager& getInstance()
    {
        static EventManager instance;
        return instance;
    }

    void subscribe(shared_ptr<Observer> observer)
    {
        observers.push_back(observer);
    }

    void triggerEvent(const string& message)
    {
        cout << "Event Triggered: "
             << message << endl;

        cout << "Sending Notifications..." << endl;

        for (auto observer : observers)
        {
            observer->notify(message);
        }
    }
};

int main()
{
    // Access Singleton Event Manager
    EventManager& manager = EventManager::getInstance();

    // Create observers using Factory Pattern
    shared_ptr<Observer> emailUser =
        NotificationFactory::createNotification(
            "EMAIL",
            "student@gmail.com");

    shared_ptr<Observer> smsUser =
        NotificationFactory::createNotification(
            "SMS",
            "9876543210");

    // Subscribe observers
    manager.subscribe(emailUser);
    manager.subscribe(smsUser);

    // Trigger event
    manager.triggerEvent(
        "University examination starts tomorrow!");

    return 0;
}