/**
 * @file ActualMachine1Factory.cpp
 * @author Noor M.
 */

#include "pch.h"

#include "ActualMachine1Factory.h"
#include "MachineComponent.h"
#include "Goal.h"
#include "Body.h"
#include "Hamster.h"
#include "HamsterAndConveyorFactory.h"
#include "Conveyor.h"

/// image directory in resources
const std::wstring ImageDirectory = L"/images";


/**
 * Constructor
 * @param resourceDir Directory containing the machine resources
 */
ActualMachine1Factory::ActualMachine1Factory(std::wstring resourceDir)
    :mResourceDir(resourceDir)
{
    mImageDir = resourceDir + ImageDirectory;
}


/**
 * Create function to return the machine we draw
 * @return machine being drawn
 */
std::shared_ptr<MachineComponent> ActualMachine1Factory::Create()
{
    std::shared_ptr<MachineComponent> machine = std::make_shared<MachineComponent>();

    const double FloorWidth = 600;
    const double FloorHeight = 15;
    auto floor = std::make_shared<Body>();
    floor->Rectangle(-FloorWidth/2, -FloorHeight, FloorWidth, FloorHeight);
    floor->SetImage(mImageDir + L"/floor.png");
    machine->AddComponent(floor);


    TopBeamAndRamp(machine);

    BeamAndSpinningArm(machine);


    const auto DominoStack1Position = wxPoint2DDouble(-230, 0);

    DominoStack(machine, DominoStack1Position);


    const auto DominoStack2Position = wxPoint2DDouble(115, 0);

    DominoStack(machine, DominoStack2Position);



    HamsterAndConveyorFactory hamsterAndConveyorFactory(machine, mImageDir);


    hamsterAndConveyorFactory.Create(wxPoint2DDouble(240, 0), wxPoint2DDouble(100, 90));
    hamsterAndConveyorFactory.AddBall(40);
    auto hamster1 = hamsterAndConveyorFactory.GetHamster();
    auto conveyor1 = hamsterAndConveyorFactory.GetConveyor();
    hamster1->SetSpeed(-1);


    wxPoint2DDouble conveyor2position(-230, 130);


    DominoesOnBeam(machine, conveyor2position + wxPoint2DDouble(140, 0));

    hamsterAndConveyorFactory.Create(conveyor1->GetPosition() + wxPoint2DDouble(-105, -40), conveyor2position);
    hamsterAndConveyorFactory.AddBall(-40);
    auto hamster2 = hamsterAndConveyorFactory.GetHamster();
    auto conveyor2 = hamsterAndConveyorFactory.GetConveyor();


    wxPoint2DDouble conveyor3position(150, 200);

    hamsterAndConveyorFactory.Create(conveyor2position + wxPoint2DDouble(260, 20), conveyor3position);
    hamsterAndConveyorFactory.AddBall(-40);
    auto hamster3 = hamsterAndConveyorFactory.GetHamster();
    hamster3->SetSpeed(1.5);
    auto conveyor3 = hamsterAndConveyorFactory.GetConveyor();


    auto goal = std::make_shared<Goal>(mImageDir + L"/goal.png");
    goal->SetPosition(270, 0);
    machine->AddComponent(goal);

    return machine;


}


void ActualMachine1Factory::TopBeamAndRamp(std::shared_ptr<MachineComponent> machine)
{
    const double BeamX = -25;
    auto beam1 = std::make_shared<Body>();
    beam1->BottomCenteredRectangle(400, 20);
    beam1->SetImage(mImageDir + L"/beam.png");
    beam1->SetPosition(BeamX, 300);
    machine->AddComponent(beam1);

    auto wedge1 = std::make_shared<Body>();
    wedge1->AddPoint(-25, 0);
    wedge1->AddPoint(25, 0);
    wedge1->AddPoint(25, 4.5);
    wedge1->AddPoint(-25, 25);
    wedge1->SetImage(mImageDir + L"/wedge.png");
    wedge1->SetPosition(BeamX-175, 320);
    machine->AddComponent(wedge1);

    // Basketball 1
    auto basketball1 = std::make_shared<Body>();
    basketball1->Circle(12);
    basketball1->SetImage(mImageDir + L"/basketball1.png");
    basketball1->SetPosition(BeamX-186, 353);
    basketball1->SetDynamic();
    basketball1->SetPhysics(1, 0.5, 0.7);
    machine->AddComponent(basketball1);
}


void ActualMachine1Factory::BeamAndSpinningArm(std::shared_ptr<MachineComponent> machine)
{
    const double Beam2X = -25;
    auto beam2 = std::make_shared<Body>();
    beam2->BottomCenteredRectangle(400, 20);
    beam2->SetImage(mImageDir + L"/beam.png");
    beam2->SetPosition(Beam2X, 240);
    machine->AddComponent(beam2);

    // Basketball 2
    auto basketball2 = std::make_shared<Body>();
    basketball2->Circle(12);
    basketball2->SetImage(mImageDir + L"/basketball2.png");
    basketball2->SetPosition(Beam2X - 170, 240 + 12 + 20);
    basketball2->SetDynamic();
    basketball2->SetPhysics(1, 0.5, 0.75);
    machine->AddComponent(basketball2);


    auto hamster = std::make_shared<Hamster>(mImageDir);
    hamster->SetPosition(-220, 185);
    hamster->SetInitiallyRunning(true);      // Initially running
    hamster->SetSpeed(0.85);
    machine->AddComponent(hamster);
    auto hamster1shaft = hamster->GetShaftPosition();

    auto arm = std::make_shared<Body>();
    arm->SetPosition(hamster1shaft.x, hamster1shaft.y);
    arm->AddPoint(-7, 10);
    arm->AddPoint(7, 10);
    arm->AddPoint(7, -60);
    arm->AddPoint(-7, -60);
    arm->SetImage(mImageDir + L"/arm.png");
    arm->SetKinematic();
    machine->AddComponent(arm);

    hamster->GetSource()->AddSink(arm);
}

/**
 * Create the beam that has 10 dominoes on it.
 * @param machine Machine to add bem to
 * @param position Location to place the beam.
 */
void ActualMachine1Factory::DominoesOnBeam(std::shared_ptr<MachineComponent> machine, wxPoint2DDouble position)
{

    auto beam = std::make_shared<Body>();
    beam->BottomCenteredRectangle(150, 15);
    beam->SetImage(mImageDir + L"/beam.png");
    beam->SetPosition(position.m_x, position.m_y);
    machine->AddComponent(beam);

    for(int d=0; d<10; d++)
    {
        auto dominos = position + wxPoint2DDouble(-70 + d * 15, 27);
        Domino(machine, dominos, 0, DominoColor::Green);
    }
}

/**
 * Create a stack of 9 dominos.
 * @param machine Machine to add to
 * @param position The position to draw the domino stack at
 */
void ActualMachine1Factory::DominoStack(std::shared_ptr<MachineComponent> machine, wxPoint2DDouble position)
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
std::shared_ptr<Body>  ActualMachine1Factory::Domino(std::shared_ptr<MachineComponent> machine, wxPoint2DDouble position, double rotation, DominoColor color)
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
