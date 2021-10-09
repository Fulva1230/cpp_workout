//
// Created by fulva on 10/9/2021.
//

#ifndef CPP_WORKOUT_MAGIC_COMPARE_MAGIC_COMPARE_H_
#define CPP_WORKOUT_MAGIC_COMPARE_MAGIC_COMPARE_H_

#include <functional>
#include <vector>

template <class T> class MagicCompare {
public:
  MagicCompare(T value) : rvalue(value), lvalue(value) {}

  template <class RhsType> MagicCompare<T> operator<(RhsType rhs) {
    return compare(std::less<T>(), MagicCompare<T>(rhs));
  }

  template <class RhsType> MagicCompare<T> operator>(RhsType rhs) {
    return compare(std::greater<T>(), MagicCompare<T>(rhs));
  }

  template <class RhsType> MagicCompare<T> operator<=(RhsType rhs) {
    return compare(std::less_equal<T>{}, MagicCompare<T>(rhs));
  }

  template <class RhsType> MagicCompare<T> operator>=(RhsType rhs) {
    return compare(std::greater_equal<T>{}, MagicCompare<T>(rhs));
  }

  template <class RhsType> MagicCompare<T> operator==(RhsType rhs) {
    return compare(std::equal_to<T>{}, MagicCompare<T>(rhs));
  }

  template <class RhsType> MagicCompare<T> operator!=(RhsType rhs) {
    return compare(std::not_equal_to<T>{}, MagicCompare<T>(rhs));
  }

  template <class RhsType> MagicCompare<T> &operator+=(RhsType rhs) {
    rvalue += rhs;
    lvalue += rhs;
    return *this;
  }

  MagicCompare<T> &operator++() {
    *this += 1;
    return *this;
  }

  template <class RhsType> MagicCompare<T> operator*(RhsType rhs) {
    MagicCompare<T> result = rhs;
    result.comparedRes = this->comparedRes;
    result.rvalue = this->rvalue * result.rvalue;
    result.lvalue = this->lvalue * result.lvalue;
    return result;
  }

  MagicCompare<T> operator++(int) {
    MagicCompare<T> res = *this;
    *this += 1;
    return res;
  }

  MagicCompare<T> compare(std::function<bool(T lhs, T rhs)> comparator,
                          const MagicCompare<T> &rhs) {
    MagicCompare<T> res = *this;
    if (!(comparator(this->rvalue, rhs.lvalue))) {
      res.comparedRes = false;
    }
    res.rvalue = rhs.rvalue;
    return res;
  }

  operator bool() { return comparedRes; }

  operator T() { return lvalue; }

  bool comparedRes = true;
  T lvalue;
  T rvalue;
};

template <class RhsType>
MagicCompare<RhsType> operator<(RhsType lhs, const MagicCompare<RhsType> &rhs) {
  return MagicCompare<RhsType>(lhs) < rhs;
}

template <class RhsType>
MagicCompare<RhsType> operator>(RhsType lhs, const MagicCompare<RhsType> &rhs) {
  return MagicCompare<RhsType>(lhs) > rhs;
}

template <class RhsType>
MagicCompare<RhsType> operator<=(RhsType lhs,
                                 const MagicCompare<RhsType> &rhs) {
  return MagicCompare<RhsType>(lhs) <= rhs;
}

template <class RhsType>
MagicCompare<RhsType> operator>=(RhsType lhs,
                                 const MagicCompare<RhsType> &rhs) {
  return MagicCompare<RhsType>(lhs) >= rhs;
}

template <class RhsType>
MagicCompare<RhsType> operator==(RhsType lhs,
                                 const MagicCompare<RhsType> &rhs) {
  return MagicCompare<RhsType>(lhs) == rhs;
}

template <class RhsType>
MagicCompare<RhsType> operator!=(RhsType lhs,
                                 const MagicCompare<RhsType> &rhs) {
  return MagicCompare<RhsType>(lhs) != rhs;
}

template <class RhsType>
MagicCompare<RhsType> operator*(RhsType lhs, const MagicCompare<RhsType> &rhs) {
  return MagicCompare<RhsType>(lhs) * rhs;
}

#endif // CPP_WORKOUT_MAGIC_COMPARE_MAGIC_COMPARE_H_
