/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Body/PhysicsBody.h"

namespace cave
{
  PhysicsBody::PhysicsBody()
  {

  }
  PhysicsBody::~PhysicsBody()
  {

  }
  ePhysicsBodyType PhysicsBody::GetType()
  {
	  b2BodyType type = mBodyDef.type;
	  if (type == b2_staticBody) return ePhysicsBodyType::Static;
	  else if (type == b2_dynamicBody) return ePhysicsBodyType::Dynamic;
	  else if (type == b2_kinematicBody) return ePhysicsBodyType::Kinematic;
  }
  void PhysicsBody::SetType(ePhysicsBodyType type)
  {
	  if (type == ePhysicsBodyType::Static) mBodyDef.type = b2_staticBody;
	  else if (type == ePhysicsBodyType::Dynamic) mBodyDef.type = b2_dynamicBody;
	  else if (type == ePhysicsBodyType::Kinematic) mBodyDef.type = b2_kinematicBody;
  }
  ePhysicsBodyType PhysicsBody::GetType()
  {
	  return ePhysicsBodyType();
  }
  b2Vec2 PhysicsBody::GetPosition()
  {
	  return mBody->GetPosition();
  }
  void PhysicsBody::SetPosition(float x, float y)
  {
	  mBodyDef.position.Set(x, y);
  }
  void PhysicsBody::SetPosition(b2Vec2 position)
  {
	  mBodyDef.position = position;
  }
  b2BodyDef* PhysicsBody::GetBodyDef()
  {
	  return &mBodyDef;
  }
  b2Body* PhysicsBody::GetBody()
  {
	  return mBody;
  }
  void PhysicsBody::SetBody(b2Body* body)
  {
  }
}