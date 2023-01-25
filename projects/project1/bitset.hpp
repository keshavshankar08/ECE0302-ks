#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>


class Bitset{
public:

  // bit set default constructor
  Bitset();

  // bit set overload constructor
  Bitset(intmax_t size);

  // bit set overload constructor
  Bitset(const std::string & value);

  // TODO COMMENT
  ~Bitset();

  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

  // TODO COMMENT
  intmax_t size() const;

  // TODO COMMENT
  bool good() const;

  // TODO COMMENT
  void set(intmax_t index);

  // TODO COMMENT
  void reset(intmax_t index);

  // TODO COMMENT
  void toggle(intmax_t index);

  // TODO COMMENT
  bool test(intmax_t index);

  // TODO COMMENT
  std::string asString() const;

private:
  intmax_t N;
  int *bits;
  bool valid = true;
};

#endif
