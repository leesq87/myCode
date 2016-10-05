#include "ContactListener.h"

ContactListener::ContactListener() {

}
ContactListener::~ContactListener() {

}

void ContactListener::BeginContact(b2Contact* contact) {
	log("Contact:Begin");
}
void ContactListener::EndContact(b2Contact* contact){
	log("Contact:End");
}
void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
	log("Contact:PreSolve");
}
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
	log("Contact:PostSolve ..1");
	b2Fixture *fixA = contact->GetFixtureA();
	b2Fixture *fixB = contact->GetFixtureB();

	b2Body* bodyA = fixA->GetBody();
	b2Body* bodyB = fixB->GetBody();

	if (bodyA->GetType() == b2_dynamicBody || bodyB->GetType() == b2_dynamicBody) {
		log("Contact:impulse.. %f", impulse->normalImpulses[0]);
	}
}
