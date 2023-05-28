#include <vector>
#include <string>
#include <algorithm>
#include "ErrorLib.hpp"
#include "../SecondLab/AaSoD_lab_2_sem_2/Sorters.hpp"
#include <queue>
#include <memory>

template <typename Vertex, typename Distance = double>
class Graph
{
private:
    std::vector<Vertex> verts;

    void set_cost_inf()
    {
        for (auto vert = verts.begin(); vert != verts.end(); vert++)
        {
            vert->cost = INT32_MAX;
        }
    }

    void set_visited_false()
    {
        for (auto vert = verts.begin(); vert != verts.end(); vert++)
        {
            vert->visited = false;
        }
    }

public:
    struct Edge
    {
        Vertex to;
        Distance weight;

        Edge(Vertex to, Distance weight = 0) : to(to), weight(weight) {}
        Edge(const Edge &src) : to(src.to), weight(src.weight) {}

        bool operator==(const Edge &src) { return (this->to == src.to && this->weight == src.weight); }

        void operator=(const Edge &src)
        {
            this->to = src.to;
            this->weight = src.weight;
        }
    };

private:
    std::vector<Edge> find_path(const Vertex &from, const Vertex &to)
    {
        std::vector<Edge> path;
        auto pt_to = std::find(verts.begin(), verts.end(), from);
        auto pt_from = std::find(verts.begin(), verts.end(), *(pt_to->parrent));
        while (pt_to != std::find(verts.begin(), verts.end(), to))
        {
            auto edge = std::find_if(pt_from->edges.begin(), pt_from->edges.end(), [pt_to](const Edge &e_from)
                                     { return e_from.to == (*pt_to); });
            path.push_back((*edge));
            pt_to = std::find(verts.begin(), verts.end(), (*pt_from));
            pt_from = std::find(verts.begin(), verts.end(), *(pt_to->parrent));
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

public:
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
        if (!has_vertex(v))
        {
            verts.push_back(v);
        }
        else
        {
            throw DoubelingVerticles();
        }
    }
    bool remove_vertex(const Vertex &v)
    {
        if (!has_vertex(v))
        {
            return false;
        }

        for (auto vert = verts.begin(); vert != verts.end(); vert++)
        {
            auto condidate = std::find_if(vert->edges.begin(), vert->edges.end(), [v](const Edge &obj)
                                          { return obj.to == v; });
            if (condidate != vert->edges.end())
                vert->edges.erase(condidate); // удалили в списках смежности
        }

        verts.erase(std::find(verts.begin(), verts.end(), v)); // удалили вершину

        return true;
    }
    /*std::vector<Vertex> vertices() const
    {
        std::vector<Vertex> res = verts;
        return res;
    }*/
    auto vertices_begin() const
    {
        auto it = verts.cbegin();
        return it;
    }
    auto vertices_end() const
    {
        auto it = verts.cend();
        return it;
    }

    // проверка-добавление-удаление ребер
    void add_edge(const Vertex &from, const Vertex &to,
                  const Distance &d)
    {
        if (!has_vertex(from) || !has_vertex(to))
            throw NoVertFound();

        auto _from = std::find(verts.begin(), verts.end(), from);
        auto edge = Edge(to, d);
        _from->edges.push_back(edge);
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
        for (auto v = verts.begin(); v != verts.end(); v++)
        {
            auto it = std::find(v->edges.begin(), v->edges.end(), e);
            if ((*it) == e)
            {
                v->edges.erase(it);
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
        for (auto v = verts.begin(); v != verts.end(); v++)
        {
            if (std::find(v->edges.begin(), v->edges.end(), e) == v->edges.end())
                return true;
        }
        return false;
    }

    /*std::vector<Edge> edges(const Vertex &vertex)
    {
        std::vector<Edge> data;
        auto vert = std::find(verts.begin(), verts.end(), vertex);
        for (auto edge = vert->edges.begin(); edge != vert->edges.end(); edge++)
            data.push_back((*edge));
        return data;
    }*/

    int order() const // порядок
    {
        return verts.size();
    }
    int degree() const // степень
    {
        std::vector<int> degrees;
        for (auto vert = verts.begin(); vert != verts.end(); vert++)
        {
            int cur = 0;
            cur += vert->edges.size();
            if (std::find_if(vert->edges.begin(), vert->edges.end(), [vert](const Edge &edge)
                             { return edge.to == (*vert); }) != vert->edges.end())
            {
                cur += 1;
            }
            degrees.push_back(cur);
        }
        insertion_sort(&degrees);
        return degrees.at(degrees.size() - 1);
    }

    /*Distance count_direct_path(const Vertex &from,
                               const Vertex &to) const
    {
        auto vert_from = std::find(verts.begin(), verts.end(), from);
        auto pt = std::find_if(vert_from->edges.begin(), vert_from->edges.end(), [to](const Edge &edge)
                               { return edge.to == to; });
        if (pt == vert_from->edges.end())
            throw PathDoesNotExist();
        else
            return pt->weight;
    }*/

    // получение всех ребер, выходящих из вершины
    auto edges_begin(const Vertex &vert) const
    {
        auto vertex = std::find(verts.begin(), verts.end(), vert);
        return vertex->edges.cbegin();
    }
    auto edges_end(const Vertex &vert) const
    {
        auto vertex = std::find(verts.begin(), verts.end(), vert);
        return vertex->edges.cend();
    }

    std::vector<Edge> shortest_path(const Vertex &from, const Vertex &to)
    {
        if (!has_vertex(from) || !has_vertex(to))
        {
            throw NoVertFound();
        }

        // preparing
        set_visited_false();
        set_cost_inf();

        auto ptr = std::find(verts.begin(), verts.end(), from); // vert to start
        ptr->parrent = std::make_shared<Vertex>((*ptr));
        ptr->cost = 0;

        std::queue<Vertex> q; // in queue => grey color
        q.push(*ptr);

        while (!q.empty())
        {
            auto verts_copy = q.front();
            auto vert = std::find(verts.begin(), verts.end(), verts_copy);
            vert->visited = true; // exclude circles

            q.pop(); // delete from queue to visit

            for (auto edge = vert->edges.begin(); edge != vert->edges.end(); edge++)
            {
                auto newbie = std::find(verts.begin(), verts.end(), edge->to);
                if (!(newbie->visited))
                {
                    if (newbie->cost > vert->cost + edge->weight)
                    {
                        newbie->cost = vert->cost + edge->weight;
                        (newbie->parrent) = std::make_shared<Vertex>(*vert);
                    }
                    q.push(edge->to); // paint in grey
                }
            }
        }

        std::vector<Edge> path(find_path(to, from));
        return path;
    }

    // обход
    /*std::vector<Vertex> walk(const Vertex &start_vertex)
    {
        if (!has_vertex(start_vertex))
        {
            throw NoVertFound();
        }
        set_visited_false();

        auto ptr = std::find(verts.begin(), verts.end(), start_vertex);

        std::vector<Vertex> spreadly_walked;

        std::queue<Vertex> q; // in queue => grey color
        q.push(*ptr);

        while (!q.empty())
        {
            auto verts_copy = q.front();
            auto vert = std::find(verts.begin(), verts.end(), verts_copy);
            vert->visited = true; // exclude circles

            spreadly_walked.push_back(*vert); // in the vector => black color
            q.pop();                          // delete from queue to visit

            for (auto edge = vert->edges.begin(); edge != vert->edges.end(); edge++)
            {
                auto newbie = std::find(verts.begin(), verts.end(), edge->to);
                if (!(newbie->visited))
                {
                    q.push(edge->to); // paint in grey
                }
            }
        }
        return spreadly_walked;
    }*/

    void spread_walk(const Vertex &v, std::shared_ptr<queue<Vertex>> q_pt)
    {
        auto vert = std::find(verts.begin(), verts.end(), v);
        vert->visited = true; // exclude circles
        for (auto edge = vert->edges.begin(); edge != vert->edges.end(); edge++)
        {
            auto newbie = std::find(verts.begin(), verts.end(), edge->to);
            if (!(newbie->visited))
            {
                q_pt->push(edge->to); // paint in grey
            }
        }
    }

    std::vector<Vertex> walk(const Vertex &start_vertex,
                             std::function<void(const Vertex &, std::shared_ptr<queue<Vertex>>)> action)
    {
        if (!has_vertex(start_vertex))
        {
            throw NoVertFound();
        }
        set_visited_false();

        auto ptr = std::find(verts.begin(), verts.end(), start_vertex);

        std::vector<Vertex> spreadly_walked;

        std::queue<Vertex> q; // in queue => grey color
        auto q_pt = std::make_shared<std::queue<Vertex>>(q);
        q_pt->push(*ptr);

        while (!q_pt->empty())
        {
            auto verts_copy = q_pt->front();
            auto vert = std::find(verts.begin(), verts.end(), verts_copy);
            spreadly_walked.push_back(*vert);

            q_pt->pop(); // delete from queue to visit

            action(*vert, q_pt);
        }
        return spreadly_walked;
    }

    int complete_task()
    {
        if (verts.size() == 0)
            throw EmptyGraph();

        int max = INT32_MIN;
        int max_id = verts[0].id;
        for (auto i = verts.begin(); i != verts.end(); i++)
        {
            int sum = 0;
            for (auto j = i->edges.begin(); j != i->edges.end(); j++)
            {
                sum += j->weight;
            }
            for (auto j = verts.begin(); j != verts.end(); j++)
            {
                if (has_edge(j->id, i->id))
                    sum += std::find_if(j->edges.begin(), j->edges.end(), [i](const Edge &edge)
                                        { return edge.to == (*i); })
                               ->weight;
            }
            if (max < sum)
            {
                max = sum;
                max_id = i->id;
            }
        }
        return max_id;
    }
};

struct FirstAidStation
{
    int id;
    int cost;
    bool visited;

    std::shared_ptr<FirstAidStation> parrent;
    std::vector<Graph<FirstAidStation, double>::Edge> edges;

    FirstAidStation()
    {
        this->id = -1;
        this->parrent = nullptr;
        this->cost = 0;
        this->visited = false;
    }

    FirstAidStation(int id)
    {
        if (id > 0)
        {
            this->id = id;
            this->parrent = nullptr;
            this->cost = 0;
            this->visited = false;
        }
        else
            throw NotValidID();
    }
    FirstAidStation(const FirstAidStation &src)
    {
        this->cost = src.cost;
        this->edges = src.edges;
        this->id = src.id;
        this->parrent = src.parrent;
        this->visited = src.visited;
    }

    FirstAidStation operator=(const FirstAidStation &src)
    {
        this->cost = src.cost;
        this->edges = src.edges;
        this->id = src.id;
        this->parrent = src.parrent;
        this->visited = src.visited;
        return *this;
    }

    bool operator==(const FirstAidStation &src) const
    {
        return (this->id == src.id);
    }
    bool operator!=(const FirstAidStation &src) const
    {
        return (this->id != src.id);
    }
};