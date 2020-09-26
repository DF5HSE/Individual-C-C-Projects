#include <memory>
#include <string>

enum RegexpType
{
  EMPTY, EPSILON, CHAR, STAR, ALT, SEQ
};

class Regexp final
{
public:
  Regexp(RegexpType type = EMPTY);
  Regexp(RegexpType type, char c);
  Regexp(RegexpType type, const Regexp &r);
  Regexp(RegexpType type, const Regexp &left, const Regexp &right);

  Regexp(const Regexp &r);
  Regexp(Regexp &&r);

  Regexp & operator=(Regexp r);
  bool isNullable() const;

private:
  RegexpType _type;
  char _cForCHAR; // char for CHAR
  std::unique_ptr<Regexp> _regForSTAR; // regexp for STAR
  std::unique_ptr<Regexp>_left, _right;// regexps for ALT and SEQ
  friend Regexp derivative(char c, const Regexp &regexp);
  friend void Swap(Regexp &a, Regexp &b);
};

Regexp derivative(char c, const Regexp &regexp);
bool match(Regexp regexp, const std::string &str);

// wraps for customer
Regexp Empty();
Regexp Epsilon();
Regexp Star(const Regexp &reg);
Regexp Char(char c);
Regexp Alt(const Regexp &left, const Regexp &right);
Regexp Seq(const Regexp &left, const Regexp &right);

