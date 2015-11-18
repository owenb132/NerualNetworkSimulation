#include <string>#include <cmath>#include "ObjectManager.h"#include "Functions.h"#include "AbstractFactory.h"ObjectManager * ObjectManager::p = NULL;void handleCollisions(Object* a, Object* b) {  // collect the id of object  std::string aid, bid;  aid = a->id(); bid = b->id();  // find the shooter: give rewards  Object* shooter = NULL;  if (aid == "robot" && bid == "bullet")    shooter = b->whoShotMe();  else if (aid == "bullet" && bid == "robot")    shooter = a->whoShotMe();  if (shooter) {    shooter->score() += 1;    shooter->energy() += 100;  }}bool collides(Object* a, Object* b) {  std::string aid, bid;  aid = a->id(); bid = b->id();  // make sure the robot does not kill him self with his own bullet  if (aid == "robot" && bid == "bullet")    if (b->whoShotMe() == a)      return false;  else if (bid == "robot" && aid == "bullet")    if (a->whoShotMe() == b)      return false;  bool rem = circleCollisionCheck(a, b);  return rem;}void ObjectManager::collision() {  if (list.size() < 2)     return;  // find the removed indexes  std::vector<int> posToRemove;  for (int i = 0; i < list.size(); ++i) {    for (int j = i + 1; j < list.size(); ++j) {      bool rem = collides(list[i], list[j]);      if (rem) {        handleCollisions(list[i], list[j]);        if (!inList(i, posToRemove))          posToRemove.push_back(i);        if (!inList(j, posToRemove))          posToRemove.push_back(j);      }    }  }  // put the object pointers in a vector for removal  std::vector<Object *> v;  for (int i = 0; i < posToRemove.size(); ++i)    v.push_back(list[posToRemove[i]]);  // remove the objects  ObjectManager * manager = ObjectManager::getInstance();  for (int i = 0; i < v.size(); ++i)    manager->remove(v[i]);}void ObjectManager::insert(Object* o) {  list.push_back(o);}void ObjectManager::remove(Object* o) {  // remove from the list  list.erase(std::remove(list.begin(), list.end(), o), list.end());  // remove the bullet pointer to this robot  // place robot brain in the learner  if (o->id() == "robot") {    // set id to null for bullets shot    for(int i = 0; i < list.size(); ++i) {      if (list[i]->id() == "bullet") {        if(list[i]->whoShotMe() == o) {          list[i]->setWhoShotMe(NULL);        }      }    }    // place info into learner    Object * r = AbstractFactory::createRobot(o);    learn_.insert(r);  }  delete o;}void ObjectManager::clear() {  for (int i = 0; i < list.size(); ++i)    delete list[i];    list.clear();}bool ObjectManager::execute() {  if (list.size() == 0)    return false;  ObjectManager * manager = ObjectManager::getInstance();  for(int i = 0; i < list.size(); ++i) {    bool alive = list[i]->execute();    if (!alive) {      manager->remove(list[i]);    }  }  collision();  return true;}void ObjectManager::draw() {  if (list.size() == 0)    return;  for (int i = 0; i < list.size(); ++i) {    list[i]->draw();  }}