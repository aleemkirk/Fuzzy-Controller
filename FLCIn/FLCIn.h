/*Defines classes for inputs to the FLC*/
//#include"../FLCSet/FLCSet.h"

class FLCIn{                                      //base class for input to FLC
protected:

public:
  FLCIn(){}                                       //default constructor

};


class LoadAngleErr : public FLCIn{                //input to FLC
private:
/*
  TrapFLCSet left(-90, -60, 0);
  TriFLCSet center(-5, 0, 5);
  TrapFLCSet right(90, 60, 0);
*/
  TrapFLCSet left;
  TriFLCSet center;
  TrapFLCSet right;


public:

  float indexL, indexC, indexR; //make these member variables public

  LoadAngleErr(TrapFLCSet l, TriFLCSet c, TrapFLCSet r){                                 //default constructor

     left = l; center = c; right = r;
    indexL, indexC, indexR = 0;

  }


  void findIndex(float a){                         //gets index for a value 'a' in the universe of discorse for each fuzzy set
    indexL = left.getIndex(a);
    indexC = center.getIndex(a);
    indexR = right.getIndex(a);
  }


};


class PosAngleErr : public FLCIn{                 //input to FLC
private:
  /*
    TrapFLCSet left(-180, -150, 0);
    TriFLCSet none(-5, 0, 5);
    TrapFLCSet right(180, 150, 0);
  */
  TrapFLCSet left;
  TriFLCSet none;
  TrapFLCSet right;

public:
  float indexL, indexN, indexR;

  PosAngleErr(TrapFLCSet l, TriFLCSet n, TrapFLCSet r){
    left = l; none = n; right = r;
    indexL = indexN = indexR = 0;
  }

  void findIndex(float a){
    indexL = left.getIndex(a);
    indexN = none.getIndex(a);
    indexR = right.getIndex(a);
  }

};
