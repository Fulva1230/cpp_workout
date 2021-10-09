#include "break_the_pieces.h"

#include <unordered_map>
#include <utility>

vector<string> break_piece(const string &shape) { return {}; }

void populate_line(vector<Point> &output, const string &line) {
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
    output.emplace_back(toPopulate);
  }
}

graph_t generate_graph(const string &shape) {
  graph_t graph;
  auto curIter = std::begin(shape);
  auto endIter = std::end(shape);
  string stringBuf;
  vector<Point> line_buf;
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

Drawer::Drawer(graph_t graph, const std::pair<int, int> init_coor)
    : graph_(std::move(graph)), cur_coor(init_coor), init_coor(init_coor) {}

std::optional<graph_t> Drawer::draw() {
  if (graph_[cur_coor.first][cur_coor.second] == Point::Vertex) {
    point(Point::Vertex);
    advance_coor(1);
    if (graph_[cur_coor.first][cur_coor.second] == Point::Connected) {
      point(Point::Connected);
      graph_[cur_coor.first][cur_coor.second] == Point::Unconnected;
      return _finish_the_draw();
    }
  }
  return {};
}

void Drawer::advance_coor(int steps) {
  switch (curDir) {
  case Direction::Up:
    cur_coor.first -= steps;
    break;
  case Direction::Down:
    cur_coor.first += steps;
    break;
  case Direction::Right:
    cur_coor.second += steps;
    break;
  case Direction::Left:
    cur_coor.second -= steps;
    break;
  }
}
std::optional<graph_t> Drawer::_finish_the_draw() {
  bool finished = false;
  while (!finished) {
    advance_coor(1);
    if (cur_coor.first < init_coor.first ||
        (cur_coor.first == init_coor.first &&
         cur_coor.second < init_coor.second)) {
      return {};
    }
    if (graph_.size() > cur_coor.first &&
        graph_[cur_coor.first].size() > cur_coor.second) {
      switch (graph_[cur_coor.first][cur_coor.second]) {
      case Point::Vertex:
        prevDir = curDir;
        point(Point::Vertex);
        change_dir(RotatingDir::Clockwise);
        if (cur_coor == init_coor) {
          finished = true;
        }
        break;
      case Point::Connected:
        if (prevDir == curDir) {
          advance_coor(-1);
          point(Point::Connected);
          advance_coor(1);
        }
        prevDir = curDir;
        point(Point::Connected);
        graph_[cur_coor.first][cur_coor.second] = Point::Unconnected;
        break;
      case Point::Unconnected:
        advance_coor(-1);
        change_dir(RotatingDir::CounterClockwise);
        break;
      }
    } else {
      advance_coor(-1);
      change_dir(RotatingDir::CounterClockwise);
    }
  }
  return output;
}

void Drawer::change_dir(RotatingDir rotatingDir) {
  switch (curDir) {
  case Direction::Up:
    switch (rotatingDir) {
    case RotatingDir::CounterClockwise:
      curDir = Direction::Left;
      break;
    case RotatingDir::Clockwise:
      curDir = Direction::Right;
      break;
    }
    break;
  case Direction::Right:
    switch (rotatingDir) {
    case RotatingDir::CounterClockwise:
      curDir = Direction::Up;
      break;
    case RotatingDir::Clockwise:
      curDir = Direction::Down;
      break;
    }
    break;
  case Direction::Down:
    switch (rotatingDir) {
    case RotatingDir::CounterClockwise:
      curDir = Direction::Right;
      break;
    case RotatingDir::Clockwise:
      curDir = Direction::Left;
      break;
    }
    break;
  case Direction::Left:
    switch (rotatingDir) {
    case RotatingDir::CounterClockwise:
      curDir = Direction::Down;
      break;
    case RotatingDir::Clockwise:
      curDir = Direction::Up;
      break;
    }
    break;
  }
}
//TODO The output graph may out of size because of the initial point is not the right up most one in the graph.
void Drawer::point(Point p) {
  int row = cur_coor.first - init_coor.first;
  int col = cur_coor.second - init_coor.second;
  while (row + 1 > output.size()) {
    output.emplace_back();
  }
  while (col + 1 > output[row].size()) {
    output[row].emplace_back(Point::Unconnected);
  }
  output[row][col] = p;
}
