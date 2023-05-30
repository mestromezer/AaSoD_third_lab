#include <iostream>

#include "Graph.hpp"

#include <termios.h>
#include <unistd.h>
#include <vector>

char _getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

ostream &operator<<(ostream &s, std::vector<SeilingPoint> v)
{
    for (auto el : v)
    {
        s << "[Id вершины: " << el.id << "] " << std::endl;
    }
    s << '\n';
    return s;
}

ostream &operator<<(ostream &s, std::vector<Graph<SeilingPoint>::Edge> edges)
{
    for (auto el : edges)
    {
        s << "Ведет в вершину: " << el.to.id << " Вес: " << el.weight << std::endl;
    }
    s << '\n';
    return s;
}

class Menu
{
    SeilingPoint create_FirstAidStation()
    {
        int id = 0;
        std::cout << "Input ID for first aid station to add: ";
        std::cin >> id;
        return SeilingPoint(id);
    }
    void remove_edge_weight()
    {
        SeilingPoint A, B;
        double weight;
        std::cout << "Point A:" << std::endl;
        A = create_FirstAidStation();

        std::cout << "Point B:" << std::endl;
        B = create_FirstAidStation();

        std::cout << "Give weight: ";
        cin >> weight;

        for (auto it = my_graph.edges_begin(A); it != my_graph.edges_end(A); it++)
        {
            if (it->to == B && it->weight == weight)
                my_graph.remove_edge(*it);
        }
    }
    bool has_edge_weight()
    {
        SeilingPoint A, B;
        double weight;
        std::cout << "Point A:" << std::endl;
        A = create_FirstAidStation();

        std::cout << "Point B:" << std::endl;
        B = create_FirstAidStation();

        std::cout << "Give weight: ";
        cin >> weight;

        for (auto it = my_graph.edges_begin(A); it != my_graph.edges_end(A); it++)
        {
            if (it->to == B && it->weight == weight)
                return my_graph.has_edge(*it);
        }
        throw NoEdgeFound();
    }
    void print_graph()
    {
        std::cout << "Graph: " << std::endl;
        for (auto vert = my_graph.vertices_begin(); vert != my_graph.vertices_end(); vert++)
        {
            auto edges_it = my_graph.edges_begin(*vert);
            if (edges_it != my_graph.edges_end(*vert))
            {
                for (edges_it; edges_it != my_graph.edges_end(*vert); edges_it++)
                {
                    std::cout << '[' << vert->id << ']' << '-' << edges_it->weight << "->" << '[' << edges_it->to.id << ']' << std::endl;
                }
            }
            else
            {
                std::cout << '[' << vert->id << ']' << std::endl;
            }
        }
    }
    Graph<SeilingPoint> my_graph;

public:
    void displayOptions()
    {
        system("clear");
        print_graph();

        std::cout << "Меню:" << std::endl;
        std::cout << "[1] Check if first aid station in the graph" << std::endl;
        std::cout << "[2] Add first aid station" << std::endl;
        std::cout << "[3] Remove first aid station from the graph" << std::endl;
        std::cout << "[4] Connect two first aid stations" << std::endl;
        std::cout << "[5] Remove path between A and B first aid stations" << std::endl;
        std::cout << "[6] Remove path between A and B with weight d" << std::endl;
        std::cout << "[7] Check if first aid stations connected" << std::endl;
        std::cout << "[8] Find path between A and B with propper weight" << std::endl;
        std::cout << "[9] Order of the graph" << std::endl;
        std::cout << "[q] Degree of the graph" << std::endl;
        std::cout << "[w] Find best path from A to B" << std::endl;
        std::cout << "[e] Walk spreadly from the first aid station" << std::endl;
        std::cout << "[r] Complete task" << std::endl;
        std::cout << "[BACKSPACE] Exit" << std::endl;
    }

    void handleOption(int option)
    {
        SeilingPoint A, B;
        double weight;
        system("clear");
        try
        {
            switch (option)
            {
            case 49:
                std::cout << "Check if first aid station in the graph" << std::endl;
                if (my_graph.has_vertex(create_FirstAidStation()))
                    std::cout << "FAS found!" << std ::endl;
                else
                {
                    std::cout << "FAS NOT found" << std::endl;
                }
                break;
            case 50:
                std::cout << "Add first aid station" << std::endl;
                my_graph.add_vertex(create_FirstAidStation());
                break;
            case 51:
                std::cout << "Remove first aid station from the graph" << std::endl;
                my_graph.remove_vertex(create_FirstAidStation());
                break;
            case 52:
                std::cout << "Connect two first aid stations" << std::endl;
                std::cout << "Point A:" << std::endl;
                A = create_FirstAidStation();
                std::cout << "Point B:" << std::endl;
                B = create_FirstAidStation();
                std::cout << "Give weight: ";
                cin >> weight;

                my_graph.add_edge(A, B, weight);
                break;
            case 53:
                std::cout << "Remove path between A and B first aid stations" << std::endl;
                std::cout << "Point A:" << std::endl;
                A = create_FirstAidStation();
                std::cout << "Point B:" << std::endl;
                B = create_FirstAidStation();
                my_graph.remove_edge(A, B);
                break;
            case 54:
                std::cout << "Remove path between A and B with weight d" << std::endl;
                remove_edge_weight();
                std::cout << "Removed successfully!" << std::endl;
                break;
            case 55:
                std::cout << "Check if first aid stations connected" << std::endl;
                std::cout << "Point A:" << std::endl;
                A = create_FirstAidStation();
                std::cout << "Point B:" << std::endl;
                std::cout << my_graph.has_edge(A, B) << std::endl;
                break;
            case 56:
                std::cout << "Find path between A and B with propper weight" << std::endl;
                std::cout << has_edge_weight();
                break;
            case 57:
                std::cout << "Order of the graph" << std::endl;
                std::cout << my_graph.order();
                break;
            case 113:
                std::cout << "Degree of the graph" << std::endl;
                std::cout << my_graph.degree();
                break;
            case 119:
                std::cout << "Find best path from A to B" << std::endl;
                std::cout << "Point A:" << std::endl;
                A = create_FirstAidStation();
                std::cout << "Point B:" << std::endl;
                B = create_FirstAidStation();

                std::cout << my_graph.shortest_path(A, B);
                break;
            case 101:
                std::cout << "Walk spreadly from the first aid station" << std::endl;
                std::cout << "Give id of the FAS:" << std::endl;
                A = create_FirstAidStation();
                std::cout << my_graph.walk(A, std::bind(&Graph<SeilingPoint>::spread_walk, my_graph, std::placeholders::_1, std::placeholders::_2));
                break;
            case 114:
                std::cout << "Complete task" << std::endl;
                std::cout << "Best varriant's id is : " << my_graph.complete_task() << std::endl;
                break;
            default:
                std::cout << "Invalid option selected." << std::endl;
                break;
            }
        }
        catch (Error e)
        {
            std::cout << e.get_message() << std::endl;
        }
        std::cout << "Press any button";
        _getch();
    }
};

int main()
{
    Menu menu;
    while (true)
    {
        menu.displayOptions();

        int option = _getch();

        std::cout << option;

        if (option == 8)
            return 0;

        menu.handleOption(option);
    }
}