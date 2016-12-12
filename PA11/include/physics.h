#ifndef PHYSICS_H
#define PHYSICS_H

#include "object.h"

class Physics
{  
  public:
    Physics(); // Constructor
    ~Physics(); // Destructor
    bool Initialize(); // Initialize world
    void Pool(); // Create pool game

    // Create objects
    void CreateSphere(std::string objFile, std::string texture, const btVector3 &position); // Create ball
    void CreateStick(std::string objFile, std::string texture); // Create pool stick
    void CreateItem(std::string objFile, std::string texture);
    void CreateTableItem(std::string objFile, std::string texture); // Create item on table

    // Data member gets
    btDiscreteDynamicsWorld *getWorld(); // Get world
    std::vector<Object*> getObjects(); // Get vector of objects
    Object* getObject(int index); // Get object at index

  private:
    // Dynamic world members
    btBroadphaseInterface *broadphase;
    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;
    btDiscreteDynamicsWorld *dynamicsWorld;

    // Objects
    std::vector<Object*> objects;
};

#endif  /* PHYSICS_H */
