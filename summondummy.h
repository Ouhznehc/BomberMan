#ifndef SUMMONDUMMY_H_
#define SUMMONDUMMY_H_
#define BEGIN_GAME 1
#define STOP_GAME 2
#define END_GAME 3
#define HELP 4
#define BACK 5
#include <component.h>

class SummonDummy : public Component {
 public:
  SummonDummy();
  void onAttach() override;
  void setType(int type);
  void onClick(QGraphicsSceneMouseEvent *ev) override;
  int type();
private:
  int my_type;
};

#endif  // SUMMONDUMMY_H_
