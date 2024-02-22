/**
 * @file MachineComponent.cpp
 * @author Noor M.
 */


#include "pch.h"
#include "Component.h"
#include "MachineComponent.h"
#include "b2_world.h"
#include "ContactListener.h"
#include "DebugDraw.h"


void MachineComponent::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for(auto components : mComponentVector)
    {
        components->Draw(graphics, components->GetPosition().x, components->GetPosition().y);
    }

}

void MachineComponent::Update(double elapsed)
{
    // Call Update on all of our components so they can advance in time
    for(auto components : mComponentVector)
    {
        components->Update(elapsed);
    }
    // Advance the physics system one frame in time
    mWorld->Step(elapsed, VelocityIterations, PositionIterations);
}

void MachineComponent::AddComponent(std::shared_ptr<Component> components)
{
    mComponentVector.push_back(components);
    components->SetMachine(this);
}


void MachineComponent::Reset()
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));;
    // Create and install the contact filter
    mContactListener = std::make_shared<ContactListener>();
    mWorld->SetContactListener(mContactListener.get());

    for(auto components : mComponentVector)
    {
        components->InstallPhysics(mWorld, mContactListener);
        components->Reset();
    }
}