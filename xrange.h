/*
  This file contains utility range objects primarily designed for range-based
  `for` loops.

  @Author - A.J. Tan
            https://www.facebook.com/groups/340481293551683/user/100001629957185/
*/

#if !defined(XRANGE_H_)
# define XRANGE_H_

# if !defined(__cplusplus) || __cplusplus < 201103L
#   error "This file requires to be compiled in C++11 or later."
# endif

# include <stdexcept>

namespace sample {

  // This is the type used by `range()` for iterator ranges.
  template <typename Iterator1, typename Iterator2>
  class range_t {
  public:

    range_t(Iterator1 first_, Iterator2 last_)
    : first(first_), last(last_)
    { }

    Iterator1 begin() const {
      return first;
    }

    Iterator2 end() const {
      return last;
    }

  private:
    Iterator1 first;
    Iterator2 last;
  };

  /*
    - brief: creates an iterator range
    - arguments:
      - `first`, `last`: iterators specifying a range
    - return value: a `range_t` containing `first` and `last`

    This implementation allows two different iterator types to increase
    flexibility. However, since iterators had the same type until C++17, this
    feature is only useful in C++17 and later standards.
  */
  template <typename Iterator1, typename Iterator2>
  range_t<Iterator1, Iterator2> range(Iterator1 first, Iterator2 last) {
    return range_t<Iterator1, Iterator2>(first, last);
  }


  // This is the type used by `xrange()` for integer ranges.
  template <typename Integer>
  class xrange_t {
  public:
    /*
      Possible improvements:

      To be more memory-efficent, the current iterator type can be split into
      two, `BeginIterator` and `EndIterator`. `EndIterator` will be a
      `typedef` of `Integer` for storing only the sentinel value (`distance`).

      The only issue about this is that the iterators had the same type until
      C++17. This implementation was done this way to keep things working in
      C++11 and C++14.
    */
    class Iterator {
    public:
      Iterator(const Iterator& x) :
        current(x.current),
        step(x.step),
        distance(x.distance)
      { }

      Iterator(Integer x = 0, Integer step_ = 1,
                         Integer distance_ = 0)
      : current(x),
        step(step_),
        distance(distance_)
      { }

      // The loop uses this to access iterators.
      Integer operator*() const {
        return current;
      }

      // The loop uses this to update iterators.
      Iterator& operator++() {
        current += step;
        ++distance;
        return *this;
      }

      // The loop uses this for the controlling condition.
      bool operator!=(const Iterator& rhs) const {
        // distance travelled != distance to travel
        return distance != rhs.distance;
      }

    private:
      Integer current, step, distance;
    }; // class iterator

    xrange_t(Integer start_, Integer stop_, Integer step_)
    : start(start_),
      stop(stop_),
      step(step_),
      distance()
    {
      if (step == 0) {
        throw std::invalid_argument("`xrange_t::xrange_t()` arg 3 must not be zero");
      }

      if (start < stop) { // ascending
        if (step > 0) {
          Integer difference = stop - start;
          distance = (difference / step) + bool(difference % step);
        }
        else {
          distance = 0; // because `step` cannot be negative
        }
      }
      else if (start > stop) { // descending
        if (step < 0) {
          /* For fix sized signed integers, the behavior is undefined if the
          value of `step` is the minimum for its type. */
          Integer difference = start - stop;
          distance = (difference / -step) + bool(difference % -step);
        }
        else {
          distance = 0; // because `step` cannot be positive
        }
      }
    }

    Iterator begin() const {
      /* In the loop, the `distance` of the begin iterator will be compared with
      the `distance` of the end iterator and is incremented every iteration.
      The loop ends when `distance` from both iterators become equal. */
      return Iterator(start, step, 0);
    }

    Iterator end() const {
      /* In the loop, `distance` is the only member that will be used from an end
      iterator which will serve as a sentinel value. */
      return Iterator(0, 0, distance);
    }

  private:

    Integer start, stop, step, distance;

  }; // class xrange

  /*
    - brief: creates an integer range
    - arguments:
      - `start`: starting value
      - `stop`: sentinel value
      - `step`: value added or subtracted per iteration
    - return value: a `xrange_t` object
    - exception: `std::invalid_argument` if `step == 0`

    For ascending integer ranges, it is required that `start < stop` and
    `step > 0`. If the requirements are satisfied, the function will generate an
    integer range from `start` to a value less than `stop`, with an interval
    equal to `step`, otherwise nothing is generated.

    For descending integer ranges, it is required that `start > stop` and
    `step < 0`. If the requirements are satisfied, the function will generate an
    integer range from `start` to a value greater than `stop`, with an interval
    equal to `step`, otherwise nothing is generated.

    Allowing different integer types for `start`, `stop` and `step` increases
    flexibility but also introduces the risk of conversion problems, so it is
    recommended to use identical types as much as possible. For descending
    integer ranges, it is required that `step` is a signed integer type.

    The implementations are based on `xrange()` function from Python 2.7.16.
  */
  template <typename Integer1, typename Integer2, typename Integer3 = Integer1>
  xrange_t<Integer1> xrange(Integer1 start, Integer2 stop, Integer3 step = 1) {
    return xrange_t<Integer1>(start, stop, step);
  }

  /*
    This version generates an integer range from 0 to `stop - 1`, with an
    interval equal to 1.
  */
  template <typename Integer>
  xrange_t<Integer> xrange(Integer stop) {
    return xrange_t<Integer>(0, stop, 1);
  }

} // namespace test

#endif // !defined(XRANGE_H_)
