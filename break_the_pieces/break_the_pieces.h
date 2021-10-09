#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

enum class Point {
  Unconnected,
  Connected,
  Vertex,
};

enum class RotatingDir {
  Clockwise,
  CounterClockwise,
};

using graph_t = vector<vector<Point>>;

graph_t generate_graph(const string &shape);

enum class Direction { Up, Down, Left, Right };

class Drawer {
public:
  explicit Drawer(graph_t graph, std::pair<int, int> init_coor);

  std::optional<graph_t> draw();
  std::optional<graph_t> _finish_the_draw();
  void point(Point p);
  void advance_coor(int steps);
  void change_dir(RotatingDir rotatingDir);

private:
  graph_t graph_;
  graph_t output;
  std::pair<int, int> cur_coor;
  std::pair<int, int> init_coor;
  Direction curDir = Direction::Right;
  Direction prevDir = Direction::Right;
};

struct Vertex {
  int x;
  int y;
};

class Graph {
public:
  vector<Vertex> Vertices;
  vector<Vertex> connectWith(Vertex ver);
};

vector<string> break_piece(const string &shape);
