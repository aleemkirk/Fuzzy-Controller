/*Base class for all Fuzzy Logic Controler Sets. This is the base class for:
Triangular Fuzzy Logic Sets
Trapizoidal Fuzzy Logic Sets
Singleton Fuzzy Logic Sets */


class FLCSet{
protected:
  float index;                      //Fuzzy Index for any input
  float x, y, z;                    //points in the universe of discorse that define the Fuzzy Sets
  float i_x, i_y, i_z;              //the index values for each of the points x, y and z respectively

public:
  FLCSet(){}                        //default constructor


  float getIndex(float a){            //returns the index for any value 'a' in the universe of discorse
    return index;
  }




};


class TriFLCSet : public FLCSet{  //Triangular Fuzzy Set class
private:
  float gradXY;
  float gradYZ;

public:
  TriFLCSet(){}                                         //default constructor

  TriFLCSet(float a, float b, float c){                 //overloaded constructor NOTE that a != b != c !!!!
    if (a != b && b != c && a != c){
      x = a; y=b; z=c;
      i_x=0; i_y=1; i_z=0;
      gradXY = (i_y-i_x)/(y-x);
      gradYZ = (i_z-i_y)/(z-y);
    }else{
      x = 0; y=0; z=0;
      i_x=0; i_y=0; i_z=0;
      gradXY = 0;
      gradYZ = 0;
    }
  }

  float getIndex(float a){

    if (a >= x && a <= y){
      index = gradXY*(a-x);
    } else if (a >= y && a <= z){
      index = gradYZ*(a-z);
    }
    else{
      index =0;
    }
    return index;

  }                                                  //end of getIndex



};


class TrapFLCSet : public FLCSet{  //Trapizoidal Fuzzy Set class
private:
  float gradXY;
  float gradYZ;
public:
  TrapFLCSet(){}                                         //default constructor

  TrapFLCSet(float a, float b, float c){                 //overloaded constructor NOTE b != c !!!!
    if (b != c && a != b){
      x = a; y=b; z=c;
      i_x=1; i_y=1; i_z=0;
      gradXY = 0;
      gradYZ = (i_z-i_y)/(z-y);
    }else{
      x = 0; y=0; z=0;
      i_x=0; i_y=0; i_z=0;
      gradXY = 0;
      gradYZ = 0;
    }
  }

  float getIndex(float a){

    if(z > x){
      if (a <= y){
        index = 1;
      } else if (a >= y && a <= z){
        index = gradYZ*(a-z);
      }
      else{
        index =0;
      }
    }else{
      if (a >= y ){
        index = 1;
      } else if (a >= z && a <= y){
        index = gradYZ*(a-z);
      }
      else{
        index =0;
      }
    }

    return index;

  }                                                  //end of getIndex


};


class SingleFLCSet : public FLCSet{  //Singleton Fuzzy Set class
private:

public:
  SingleFLCSet(){}                                         //default constructor

  SingleFLCSet(float a){                 //overloaded constructor NOTE that a == b !!!!

      x = y = z = a;
      i_x = i_y = i_z = 1;

  }

  float getIndex(float a){

    if (a >= x-1 && a <= x+1){
      index = 1;
    }else{
      index =0;
    }
    return index;

  }                                                  //end of getIndex

  float getValueAtIndex1(){
    return x;
  }

};
