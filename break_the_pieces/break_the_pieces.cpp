#include "break_the_pieces.h"

#include <unordered_map>

vector<string> break_piece(const string &shape) { return {}; }

void populate_line(unordered_map<int, Point> &output, const string &line) {
  int index = 0;
  for (auto cha : line) {
    Point toPopulate = Point::Unconnected;
    switch (cha) {
    case '+':
      toPopulate = Point::Vertex;
      break;
    case '|':
    case '-':
      toPopulate = Point::Connected;
      break;
    }
    output[index] = toPopulate;
    ++index;
  }
}

graph_t generate_graph(const string &shape) {
  graph_t graph;
  auto curIter = std::begin(shape);
  auto endIter = std::end(shape);
  string stringBuf;
  unordered_map<int, Point> line_buf;
  for (; curIter != endIter; ++curIter) {
    if (*curIter == '\n') {
      populate_line(line_buf, stringBuf);
      graph.emplace_back(std::move(line_buf));
      line_buf.clear();
      stringBuf.clear();
    } else {
      stringBuf.push_back(*curIter);
    }
  }
  populate_line(line_buf, stringBuf);
  graph.emplace_back(std::move(line_buf));
  return graph;
}

//TODO It's not a great algorithm, I think I need to consider it more abstractly
std::optional<graph_t> Drawer::draw() {
  std::pair<int, int> coor = init_coor;
  if (graph_[coor.first][coor.second] == Point::Vertex) {
    advance_coor(1);
    if (graph_[coor.first][coor.second] == Point::Connected) {
      graph_[coor.first][coor.second] == Point::Unconnected;
      return _finish_the_draw();
    }
  }
  return {};
}

void Drawer::change_dir() {
  switch (curDir) {
  case Direction::Up:
    curDir = Direction::Right;
    break;
  case Direction::Right:
    curDir = Direction::Down;
    break;
  case Direction::Down:
    curDir = Direction::Left;
    break;
  case Direction::Left:
    curDir = Direction::Up;
    break;
  }
}
void Drawer::advance_coor(int steps) {
  switch (curDir) {
  case Direction::Up:
    coor.first -= steps;
    break;
  case Direction::Down:
    coor.first += steps;
    break;
  case Direction::Right:
    coor.second += steps;
    break;
  case Direction::Left:
    coor.second -= steps;
    break;
  }
}
Drawer::Drawer(const graph_t &graph, const std::pair<int, int> init_coor)
    : graph_(graph), init_coor(init_coor) {}

std::optional<graph_t> Drawer::_finish_the_draw() {
  bool finished = false;
  while (!finished) {
//    TODO not finished
  }
  return std::optional<graph_t>();
}
