/**
 * @file HamsterAndConveyorFactory.cpp
 * @author Noor M.
 */

#include "pch.h"
#include "HamsterAndConveyorFactory.h"
#include "Hamster.h"
#include "Conveyor.h"
#include "Body.h"
#include "Pulley.h"
#include "MachineComponent.h"



void HamsterAndConveyorFactory::Create(wxPoint2DDouble hamsterPosition, wxPoint2DDouble conveyorPosition)
{
    auto hamster = std::make_shared<Hamster>(mImagesDir);
    mHamster = hamster;
    hamster->SetPosition(hamsterPosition.m_x, hamsterPosition.m_y);
    mMachine->AddComponent(hamster);
    auto hamsterShaft = hamster->GetShaftPosition();

    auto conveyor = std::make_shared<Conveyor>(mImagesDir);
    mConveyor = conveyor;
    conveyor->SetPosition(conveyorPosition.m_x, conveyorPosition.m_y);
    mMachine->AddComponent(conveyor);
    auto conveyorShaft = conveyor->GetShaftPosition();

    // The pulley driven by the hamster
    auto pulley1 = std::make_shared<Pulley>(10);
    pulley1->SetImage(mImagesDir + L"/pulley3.png");
    pulley1->SetPosition(hamsterShaft.x, hamsterShaft.y);
    mMachine->AddComponent(pulley1);

    hamster->GetSource()->AddSink(pulley1);

    auto pulley2 = std::make_shared<Pulley>(10);
    pulley2->SetImage(mImagesDir + L"/pulley3.png");
    pulley2->SetPosition(conveyorShaft.x, conveyorPosition.m_y);
    mMachine->AddComponent(pulley2);

    pulley1->Drive(pulley2);

    pulley2->GetSource()->AddSink(conveyor);
}


std::shared_ptr<Body> HamsterAndConveyorFactory::AddBall(double placement)
{
    // Ball
    auto ball = std::make_shared<Body>();
    ball->Circle(12);
    ball->SetImage(mImagesDir + L"/ball1.png");
    ball->SetPosition(mConveyor->GetPosition().x + placement, mConveyor->GetPosition().y + 26);
    ball->SetDynamic();
    ball->SetPhysics(2, 0.5, 0.1);
    mMachine->AddComponent(ball);

    return ball;
}
