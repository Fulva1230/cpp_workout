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

using graph_t = vector<unordered_map<int, Point>>;

enum class Direction { Up, Down, Left, Right };

class Drawer {
public:
  explicit Drawer(const graph_t& graph, std::pair<int, int> init_coor);

  std::optional<graph_t> draw();
  std::optional<graph_t> _finish_the_draw();
  void advance_coor(int steps);
  void change_dir();

  graph_t graph_;
  const std::pair<int, int> init_coor;

private:
  Direction curDir = Direction::Right;
};

vector<string> break_piece(const string &shape);

graph_t generate_graph(const string &shape);