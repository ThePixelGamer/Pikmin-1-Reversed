#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef ID32_H
#define ID32_H

class AgeServer;
class RandomAccessStream;

class SYSCORE_API ID32 {
public:
  unsigned __int32 id;
  char sId[5]; // 0h

  ID32();
  ID32(unsigned __int32);

  void ageChangeID();
  void genAge(AgeServer &, char *);
  bool match(unsigned __int32, char);
  void print();
  void read(RandomAccessStream &);
  void setID(unsigned __int32);
  void sprint(char *);
  void updateID();
  void updateString();
  void write(RandomAccessStream &);

  void operator=(unsigned __int32);
  bool operator!=(unsigned __int32);
  bool operator==(unsigned __int32);
};

#endif
