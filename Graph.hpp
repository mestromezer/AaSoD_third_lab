#include <vector>
#include <string>
#include <algorithm>

enum Color
{
    white = 1,
    grey = 2,
    black = 3
};

class AddEdgeError
{
    std::string message;

public:
    AddEdgeError(std::string message) : message(message) {}
};

template <typename Vertex, typename Distance = double>
class Graph
{
    std::vector<Vertex> verts;

public:
    struct Edge
    {
        Vertex to;
        Distance weight;

        Edge(Vertex to, Distance weight = Distance(0)) : to(to), weight(weight) {}

        bool operator==(const Edge &src) { return (this->to == src.to && this->weight == src.weight); }
    };

    // проверка-добавление-удаление вершин
    bool has_vertex(const Vertex &v) const
    {
        for (auto el : verts)
        {
            if (el == v)
                return true;
        }
        return false;
    }
    void add_vertex(const Vertex &v)
    {
        verts.push_back(v);
    }
    bool remove_vertex(const Vertex &v)
    {
        if (!has_vertex(v))
        {
            return false;
        }

        verts.erase(std::find(verts.begin(), verts.end(), v)); // удалили вершину

        auto it = verts.begin();

        for (auto vert = verts.begin(); vert != verts.end(); vert++)
        {
            vert->edges.erase(std::find_if(vert->edges.begin(), vert->edges.end(), [v](const Edge &obj)
                                           { return obj.to == v; })); // удалили в списках смежности
        }

        return true;
    }
    std::vector<Vertex> vertices() const
    {
        std::vector<Vertex> data;
        for (auto el : verts)
            data.push_back(el);
        return data;
    }

    // проверка-добавление-удаление ребер
    void add_edge(const Vertex &from, const Vertex &to,
                  const Distance &d)
    {
        if (has_edge(from, to))
            throw AddEdgeError("Edge already exists");
        for (auto el = verts.begin(); el != verts.end(); el++)
        {
            if ((*el) == from)
            {
                el->edges.push_back(Edge(to, d));
            }
        }
    }
    bool remove_edge(const Vertex &from, const Vertex &to)
    {
        auto pt_from = std::find(verts.begin(), verts.end(), from);
        if (pt_from == verts.end())
            return false; // нету вершины from

        for (auto pt_to = pt_from->edges.begin(); pt_to != pt_from->edges.end(); pt_to++)
        {
            if (pt_to->to == to)
            {
                pt_from->edges.erase(pt_to);
                return true;
            }
        }
        return false; // нету вершины куда
    }
    bool remove_edge(const Edge &e) // c учетом расстояния
    {
        for (auto v : verts)
        {
            auto it = v.edges.begin();
            std::find(it, v.edges.end(), e);
            if (it != v.edges.end())
            {
                v.edges.erase(it);
                return true;
            }
        }
        return false;
    }
    bool has_edge(const Vertex &from, const Vertex &to) const
    {
        auto pt_from = std::find(verts.cbegin(), verts.cend(), from);
        if (pt_from == verts.cend())
            return false; // нету вершины from

        for (auto pt_to = pt_from->edges.cbegin(); pt_to != pt_from->edges.cend(); pt_to++)
        {
            if (pt_to->to == to)
                return true;
        }
        return false; // нету вершины куда
    }
    bool has_edge(const Edge &e) // с учетом расстояния
    {
        for (auto v : verts)
        {
            if (std::find(v.edges.begin(), v.edges.end(), e) == v.edges.end())
                return true;
        }
        return false;
    }

    // получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex &vertex)
    {
        std::vector<Edge> data;
        auto vert = std::find(verts.begin(), verts.end(), vertex);
        for (auto edge = vert->edges.begin(); edge != vert->edges.end(); edge++)
            data.push_back((*edge));
        return data;
    }

    int order() const;  // порядок
    int degree() const; // степень

    // поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex &from,
                                    const Vertex &to) const;
    // обход
    std::vector<Vertex> walk(const Vertex &start_vertex) const;
};

struct FirstAidStation
{
    int id;
    std::vector<Graph<FirstAidStation, double>::Edge> edges;
    FirstAidStation(int id) : id(id) {}
    FirstAidStation(const FirstAidStation &src) : id(src.id), edges(src.edges) {}

    bool operator==(const FirstAidStation &src) const
    {
        return (this->id == src.id);
    }
};