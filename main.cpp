#include "Graph.hpp"
#include <iostream>

std::ostream &operator<<(std::ostream &s, std::vector<FirstAidStation> verts)
{
    for (auto el : verts)
        s << "Verticle id = " << el.id << '\n';
    return s;
}

std::ostream &operator<<(std::ostream &s, std::vector<Graph<FirstAidStation>::Edge> edges)
{
    for (auto el : edges)
        s << "Weight:" << el.weight << " , "
          << "To:" << el.to.id << ' ';
    return s;
}

int main()
{
    Graph<FirstAidStation> my_graph;
    FirstAidStation first(1);
    FirstAidStation second(2);

    my_graph.add_vertex(first);
    my_graph.add_vertex(second);
    my_graph.add_edge(first, second, 10);

    // my_graph.remove_vertex(second);
    std::cout << my_graph.vertices() << std::endl;
    std::cout << my_graph.edges(first);

    return 0;
}