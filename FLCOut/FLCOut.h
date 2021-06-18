/*This code defines the output FLC sets.
Singleton membership functions are used to keep the defuzzyfication
process simple and less intensive on the controller (arduino) */

//#include"../FLCSet/FLCSet.h"


class FLCOut{
protected:

public:
  FLCOut(){}

};

class ChangeInPos : public FLCOut{
private:
/*
SingleFLCSet moveRight(-10);
SingleFLCSet noChange(0);
SingleFLCSet moveLeft(10);
*/
  SingleFLCSet moveRight;
  SingleFLCSet noChange;
  SingleFLCSet moveLeft;

public:
    float indexR, indexN, indexL;    //make these member variables public
    float moveRightvalue, noChangeValue, moveLeftValue;

  ChangeInPos(){moveRightvalue, noChangeValue, moveLeftValue=0;}

  ChangeInPos(SingleFLCSet r, SingleFLCSet n, SingleFLCSet l ){
    moveRight = r; noChange = n; moveLeft = l;
    moveRightvalue = moveRight.getValueAtIndex1();
    noChangeValue = noChange.getValueAtIndex1();
    moveLeftValue = moveLeft.getValueAtIndex1();
  }

  void findIndex(float a){
    indexR = moveRight.getIndex(a);
    indexN = noChange.getIndex(a);
    indexL = moveLeft.getIndex(a);
  }




};
