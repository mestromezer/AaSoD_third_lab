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
          << "To:" << el.to.id << '\n';
    return s;
}

int main()
{
    Graph<FirstAidStation> my_graph;
    FirstAidStation v_1(1);
    FirstAidStation v_2(2);
    FirstAidStation v_3(3);
    FirstAidStation v_4(4);
    FirstAidStation v_5(5);
    FirstAidStation v_6(6);

    my_graph.add_vertex(v_1);
    my_graph.add_vertex(v_2);
    my_graph.add_vertex(v_3);
    my_graph.add_vertex(v_4);
    my_graph.add_vertex(v_5);
    my_graph.add_vertex(v_6);

    my_graph.add_edge(v_1, v_5, 500);
    my_graph.add_edge(v_1, v_2, 200);
    my_graph.add_edge(v_2, v_3, 300);
    my_graph.add_edge(v_2, v_4, 400);
    my_graph.add_edge(v_3, v_6, 600);
    my_graph.add_edge(v_4, v_6, 600);

    /*my_graph.add_edge(v_1, v_2, 10);
    my_graph.add_edge(v_1, v_5, 100);
    my_graph.add_edge(v_1, v_4, 30);
    my_graph.add_edge(v_2, v_3, 50);
    my_graph.add_edge(v_3, v_5, 10);
    my_graph.add_edge(v_4, v_3, 20);
    my_graph.add_edge(v_4, v_5, 60);*/

    // my_graph.remove_vertex(v_4);
    // my_graph.remove_edge(v_1, v_2);

    // std::cout << &v_1 << ' ' << &(v[0]);

    //    std::vector<FirstAidStation> v = my_graph.walk(v_1);
    // std::cout << v;
    std::cout << my_graph.shortest_path(v_1, v_6);

    // my_graph.shortest_path(v_1, v_4);

    return 0;
}