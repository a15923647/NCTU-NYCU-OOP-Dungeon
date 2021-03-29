#include "Object.h"
Object::Object() : name(""), tag(""){
  
}
Object::Object(string inpname, string inptag) : name(inpname), tag(inptag){

}

void Object::setName(string inpName){
  name = inpName;
}

void Object::setTag(string inpTag){
  tag = inpTag;
}

string Object::getName(){
  return name;
}

string Object::getTag(){
  return tag;
}

