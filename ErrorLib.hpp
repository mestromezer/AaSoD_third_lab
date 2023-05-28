#include <string>

class Error
{
    std::string message;

public:
    std::string get_message()
    {
        return message;
    }
};

class DoubelingVerticles : private Error
{
    std::string message;

public:
    DoubelingVerticles(std::string message = "Given vertex is already in the graph!", std::string sub_str = "") : message(message + sub_str) {}
    std::string get_message() { return message; }
};

class AddEdgeError : private Error
{
    std::string message;

public:
    AddEdgeError(std::string message = "No sutable path in the graph", std::string sub_str = "") : message(message + sub_str) {}
    std::string get_message() { return message; }
};

class NoVertFound : private Error
{
    std::string message;

public:
    NoVertFound(std::string message = "No such verticle", std::string sub_str = "") : message(message + sub_str) {}
    std::string get_message() { return message; }
};

class NoEdgeFound : private Error
{
    std::string message;

public:
    NoEdgeFound(std::string message = "No such edge", std::string sub_str = "") : message(message + sub_str) {}
    std::string get_message() { return message; }
};

class PathDoesNotExist : private Error
{
    std::string message;

public:
    PathDoesNotExist(std::string message = "No path found", std::string sub_str = "") : message(message + sub_str) {}
    std::string get_message() { return message; }
};

class NotValidID : private Error
{
    std::string message;

public:
    NotValidID(std::string message = "Id < 0", std::string sub_str = "") : message(message + sub_str) {}
    std::string get_message() { return message; }
};

class EmptyGraph : private Error
{
    std::string message;

public:
    EmptyGraph(std::string message = "Graph has no verts!", std::string sub_str = "") : message(message + sub_str) {}
    std::string get_message() { return message; }
};