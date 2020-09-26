#include "cassert"
#include "Regexp.h"

Regexp::Regexp(RegexpType type) : _type(type)
{
  assert((_type == EMPTY || _type == EPSILON) && "Wrong arguments for this regexp type");
}

Regexp::Regexp(RegexpType type, char cForCHAR) : _type(type), _cForCHAR(cForCHAR)
{
  assert(_type == CHAR && "Wrong arguments for this regexp type");
}

Regexp::Regexp(RegexpType type, const Regexp &regForSTAR)
  : _type(type), _regForSTAR(std::make_unique<Regexp>(regForSTAR))
{
  assert(_type == STAR && "Wrong arguments for this regexp type");
}

Regexp::Regexp(RegexpType type, const Regexp &left, const Regexp &right)
  : _type(type), _left(std::make_unique<Regexp>(left)), _right(std::make_unique<Regexp>(right))
{
  assert((_type == ALT || _type == SEQ) && "Wrong arguments for this regexp type");
}

Regexp::Regexp(const Regexp &r) : _type(r._type), _cForCHAR(r._cForCHAR)
{
  switch (r._type)
  {
  case EMPTY:
  case EPSILON:
  case CHAR:
    return; 
  case STAR:
    _regForSTAR = std::move(std::make_unique<Regexp>(*r._regForSTAR));
    return;
  case ALT:
  case SEQ:
    _left = std::move(std::make_unique<Regexp>(*r._left));
    _right = std::move(std::make_unique<Regexp>(*r._right));
    return;
  default:
    assert(0 && "Something went wrong, there isn't this type of regexp");
  }
}

Regexp::Regexp(Regexp &&r) : _type(r._type), _cForCHAR(r._cForCHAR), _regForSTAR(std::move(r._regForSTAR)), 
  _left(std::move(r._left)), _right(std::move(r._right))
{
}

void Swap(Regexp &a, Regexp &b)
{
  std::swap(a._type, b._type);
  std::swap(a._left, b._left);
  std::swap(a._right, b._right);
  std::swap(a._cForCHAR, b._cForCHAR);
  std::swap(a._regForSTAR, b._regForSTAR);
}

Regexp & Regexp::operator=(Regexp r)
{
  Swap(*this, r);
  return *this;
}


bool Regexp::isNullable() const
{
  switch (_type)
  {
  case EMPTY:
  case CHAR:
    return false;
  case EPSILON:
  case STAR:
    return true;
  case ALT:
    return _left->isNullable() || _right->isNullable();
  case SEQ:
    return _left->isNullable() && _right->isNullable();
  default:
    assert(0 && "Something went wrong, there isn't this type of regexp");
    return false;
  }
  assert(0 && "Something went wrong, there isn't this type of regexp");
  return false;
}

Regexp derivative(char c, const Regexp &regexp)
{
  switch (regexp._type)
  {
  case EMPTY:
  case EPSILON:
    return Regexp(EMPTY);
  case CHAR:
    return c == regexp._cForCHAR ? Regexp(EPSILON) : Regexp(EMPTY);
  case STAR:
    return Regexp(SEQ, derivative(c, *regexp._regForSTAR), Regexp(STAR, *regexp._regForSTAR));
  case ALT:
    return Regexp(ALT, derivative(c, *regexp._left), derivative(c, *regexp._right));
  case SEQ:
    return regexp._left->isNullable() ?
      Regexp(ALT, Regexp(SEQ, derivative(c, *regexp._left), *regexp._right), derivative(c, *regexp._right)) :
      Regexp(SEQ, derivative(c, *regexp._left), *regexp._right);
  default:
    assert(0 && "Something went wrong, there isn't this type of regexp");
  }
  assert(0 && "Something went wrong, there isn't this type of regexp");
}

bool match(Regexp regexp, const std::string &str)
{
  for (size_t i = 0; i < str.length(); i++)
    regexp = std::move(derivative(str[i], regexp));
  return regexp.isNullable();
}

// wraps for customer
Regexp Empty()
{
  return Regexp(EMPTY);
}

Regexp Epsilon()
{
  return Regexp(EPSILON);
}

Regexp Star(const Regexp &reg)
{
  return Regexp(STAR, reg);
}

Regexp Char(char c)
{
  return Regexp(CHAR, c);
}
Regexp Alt(const Regexp &left, const Regexp &right)
{
  return Regexp(ALT, left, right);
}

Regexp Seq(const Regexp &left, const Regexp &right)
{
  return Regexp(SEQ, left, right);
}