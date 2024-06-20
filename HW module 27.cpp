#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class Logger {
private:
    std::ofstream logfile;
public:
    Logger(const std::string& filename) {
        logfile.open(filename, std::ios::app);
    }

    ~Logger() {
        if (logfile.is_open()) {
            logfile.close();
        }
    }

    void log(const std::string& message) {
        if (logfile.is_open()) {
            logfile << message << std::endl;
        }
    }
};

class User {
private:
    std::string username;
    std::string password;
    std::string name;
    Logger logger;
public:
    User(const std::string& username, const std::string& password, const std::string& name)
        : username(username), password(password), name(name), logger(username + "_log.txt") {}

    const std::string& getUsername() const {
        return username;
    }

    const std::string& getPassword() const {
        return password;
    }

    const std::string& getName() const {
        return name;
    }

    void logMessage(const std::string& message) {
        logger.log(message);
    }
};

class ChatRoom {
private:
    std::vector<User> users;
    Logger chatLogger;
public:
    ChatRoom() : chatLogger("chat_log.txt") {}

    void registerUser(const User& user) {
        users.push_back(user);
    }

    User* loginUser(const std::string& username, const std::string& password) {
        for (User& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                return &user;
            }
        }
        return nullptr;
    }

    void sendMessageToUser(const User& sender, const std::string& receiverUsername, const std::string& message) {
        for (const User& user : users) {
            if (user.getUsername() == receiverUsername) {
                user.logMessage("Message from " + sender.getName() + ": " + message);
                chatLogger.log("Message from " + sender.getName() + " to " + user.getName() + ": " + message);
                std::cout << "Message sent successfully." << std::endl;
                return;
            }
        }
        std::cout << "User not found." << std::endl;
    }
};

int main() {
    ChatRoom chatRoom;

    User user1("user1", "password1", "Alice");
    User user2("user2", "password2", "Bob");

    chatRoom.registerUser(user1);
    chatRoom.registerUser(user2);

    User* loggedInUser = chatRoom.loginUser("user1", "password1");

    if (loggedInUser) {
        chatRoom.sendMessageToUser(*loggedInUser, "user2", "Hello, Bob! How are you?");
    }

    return 0;
}