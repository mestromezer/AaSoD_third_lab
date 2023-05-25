#include <string>

class DoubelingVerticles
{
    std::string message;

public:
    DoubelingVerticles(std::string message = "Given vertex is already in the graph!", std::string sub_str = "") : message(message + sub_str) {}
    std::string get_message() { return message; }
};

class AddEdgeError
{
    std::string message;

public:
    AddEdgeError(std::string message = "No sutable path in the graph", std::string sub_str = "") : message(message + sub_str) {}
    std::string get_message() { return message; }
};

class NoVertFound
{
    std::string message;

public:
    NoVertFound(std::string message = "No such verticle", std::string sub_str = "") : message(message + sub_str) {}
    std::string get_message() { return message; }
};

class PathDoesNotExist
{
    std::string message;

public:
    PathDoesNotExist(std::string message = "No path found", std::string sub_str = "") : message(message + sub_str) {}
    std::string get_message() { return message; }
};