/**
 * @file ActualMachine2Factory.cpp
 * @author Noor M.
 */

#include "pch.h"
#include "ActualMachine2Factory.h"
#include "MachineComponent.h"
#include "Goal.h"
#include "Body.h"
#include "Conveyor.h"
#include "Hamster.h"
#include "HamsterAndConveyorFactory.h"
#include "Curtains.h"
#include "Basket.h"


/// image directory in resources
const std::wstring ImageDirectory = L"/images";


/**
 * Constructor
 * @param resourceDir Directory containing the machine resources
 */
ActualMachine2Factory::ActualMachine2Factory(std::wstring resourceDir)
    :mResourceDir(resourceDir)
{
    mImageDir = resourceDir + ImageDirectory;
}

std::shared_ptr<MachineComponent> ActualMachine2Factory::Create()
{
    std::shared_ptr<MachineComponent> machine2 = std::make_shared<MachineComponent>();

    const double FloorWidth = 600;
    const double FloorHeight = 15;
    auto floor = std::make_shared<Body>();
    floor->Rectangle(-FloorWidth/2, -FloorHeight, FloorWidth, FloorHeight);
    floor->SetImage(mImageDir + L"/floor.png");
    machine2->AddComponent(floor);

    const double Beam2X = -25;
    auto beam2 = std::make_shared<Body>();
    beam2->BottomCenteredRectangle(400, 20);
    beam2->SetImage(mImageDir + L"/beam.png");
    beam2->SetPosition(Beam2X, 240);
    machine2->AddComponent(beam2);


    auto basketball1 = std::make_shared<Body>();
    basketball1->Circle(12);
    basketball1->SetImage(mImageDir + L"/basketball1.png");
    basketball1->SetPosition(Beam2X-186, 353);
    basketball1->SetDynamic();
    basketball1->SetPhysics(1, 0.5, 0.6);
    machine2->AddComponent(basketball1);


    auto basketball3 = std::make_shared<Body>();
    basketball3->Circle(12);
    basketball3->SetImage(mImageDir + L"/basketball1.png");
    basketball3->SetPosition(Beam2X-186, 330);
    basketball3->SetDynamic();
    basketball3->SetPhysics(1, 0.5, 0.6);
    machine2->AddComponent(basketball3);


    auto basketball2 = std::make_shared<Body>();
    basketball2->Circle(12);
    basketball2->SetImage(mImageDir + L"/basketball2.png");
    basketball2->SetPosition(Beam2X - 170, 240 + 12 + 20);
    basketball2->SetDynamic();
    basketball2->SetPhysics(1, 0.5, 0.85);
    machine2->AddComponent(basketball2);


    auto hamster = std::make_shared<Hamster>(mImageDir);
    hamster->SetPosition(-220, 185);
    hamster->SetInitiallyRunning(true);      // Initially running
    hamster->SetSpeed(0.85);
    machine2->AddComponent(hamster);
    auto hamster1shaft = hamster->GetShaftPosition();

    auto arm = std::make_shared<Body>();
    arm->SetPosition(hamster1shaft.x, hamster1shaft.y);
    arm->AddPoint(-7, 10);
    arm->AddPoint(7, 10);
    arm->AddPoint(7, -60);
    arm->AddPoint(-7, -60);
    arm->SetImage(mImageDir + L"/arm.png");
    arm->SetKinematic();
    machine2->AddComponent(arm);

    hamster->GetSource()->AddSink(arm);

    const auto DominoStack1Position = wxPoint2DDouble(-230, 0);

    DominoStack(machine2, DominoStack1Position);


    const auto DominoStack2Position = wxPoint2DDouble(115, 0);

    DominoStack(machine2, DominoStack2Position);


    HamsterAndConveyorFactory hamsterAndConveyorFactory(machine2, mImageDir);


    hamsterAndConveyorFactory.Create(wxPoint2DDouble(240, 0), wxPoint2DDouble(100, 90));
    hamsterAndConveyorFactory.AddBall(40);
    auto hamster1 = hamsterAndConveyorFactory.GetHamster();
    auto conveyor1 = hamsterAndConveyorFactory.GetConveyor();
    hamster1->SetSpeed(-2);


    auto basket = std::make_shared<Basket>(mImageDir);
    basket->SetPosition(-30, 20);
    machine2->AddComponent(basket);


    auto goal = std::make_shared<Goal>(mImageDir + L"/goal.png");
    goal->SetPosition(270, 0);
    machine2->AddComponent(goal);


    auto curtain = std::make_shared<Curtains>(mImageDir);
    curtain->SetPosition(curtain->GetPosition().x, curtain->GetPosition().y);

    machine2->AddComponent(curtain);


    return machine2;
}



/**
 * Create a stack of 9 dominos.
 * @param machine Machine to add to
 * @param position The position to draw the domino stack at
 */
void ActualMachine2Factory::DominoStack(std::shared_ptr<MachineComponent> machine, wxPoint2DDouble position)
{
    Domino(machine, position + wxPoint2DDouble(30, DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(10, DominoHeight/2), 0, DominoColor::Blue);
    Domino(machine, position + wxPoint2DDouble(20, DominoHeight + DominoWidth/2), 0.25, DominoColor::Green);

    Domino(machine, position + wxPoint2DDouble(-10, DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(-30, DominoHeight/2), 0, DominoColor::Green);
    Domino(machine, position + wxPoint2DDouble(-20, DominoHeight + DominoWidth/2), 0.25, DominoColor::Black);

    const int DominoLevel2 = DominoHeight + DominoWidth;

    Domino(machine, position + wxPoint2DDouble(10, DominoLevel2 + DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(-10, DominoLevel2 + DominoHeight/2), 0, DominoColor::Green);
    Domino(machine, position + wxPoint2DDouble(0, DominoLevel2 + DominoHeight + DominoWidth/2), 0.25, DominoColor::Black);
}



/**
 * Create a Domino and add it to the machine.
 *
 * This has been created to make it easier to create
 * a lot of dominos
 *
 * @param machine Machine to add the domino to
 * @param position Position to place the center of the domino
 * @param rotation Rotation in turns
 * @param color Color code
 * @return Returns the created domino body
 */
std::shared_ptr<Body>  ActualMachine2Factory::Domino(std::shared_ptr<MachineComponent> machine, wxPoint2DDouble position, double rotation, DominoColor color)
{
    auto x = position.m_x;
    auto y = position.m_y;

    auto domino = std::make_shared<Body>();
    domino->Rectangle(-DominoWidth/2, -DominoHeight/2, DominoWidth, DominoHeight);
    switch(color)
    {
        case DominoColor::Black:
            domino->SetImage(mImageDir + L"/domino-black.png");
            break;

        case DominoColor::Red:
            domino->SetImage(mImageDir + L"/domino-red.png");
            break;

        case DominoColor::Green:
            domino->SetImage(mImageDir + L"/domino-green.png");
            break;

        case DominoColor::Blue:
            domino->SetImage(mImageDir + L"/domino-blue.png");
            break;
    }

    domino->SetPosition(x, y);
    domino->SetInitialRotation(rotation);
    domino->SetDynamic();
    machine->AddComponent(domino);

    return domino;
}