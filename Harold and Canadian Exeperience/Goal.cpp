/**
 * @file Goal.cpp
 * @author Noor M.
 */

#include "pch.h"
#include "Goal.h"
#include "ContactListener.h"
#include <b2_contact.h>
#include <sstream>
#include <iomanip>



/// The color of the scoreboard background
const auto ScoreboardBackgroundColor = wxColor(24, 69, 59);

/// Width of the black line around the scoreboard
const int ScoreboarderLineWidth = 3;

/// Scoreboard font size (height) in cm
/// The font color is white
const int ScoreboardFontSize = 20;

/// Rectangle that represents the location relative to the
/// goal position for the scoreboard and its size.
const auto ScoreboardRectangle = wxRect2DDouble(5, 280, 30, 20);

/// Location of the scoreboard text relative to the
/// scoreboard location in cm.
const auto ScoreboardTextLocation = wxPoint2DDouble(9, 299);

/// Position of the goalpost polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble PostPosition = wxPoint2DDouble(22, 0);

/// Position of the basket goal polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble GoalPosition = wxPoint2DDouble(-12, 165);


/// Size to draw the entire goal post image
/// This does not go into the physics system at all
const auto GoalSize = wxSize(65, 247);

/// Size to create a rectangle in the physics system only
/// (does not draw) to reflect off of the backboard and post
const auto PostSize = wxSize(10, 250);


Goal::Goal(std::wstring imagesDir)
{
    mImage = imagesDir;
    mGoalImage.BottomCenteredRectangle(GoalSize);
    mGoalImage.SetImage(mImage);

    mPost.BottomCenteredRectangle(PostSize);
    mGoal.BottomCenteredRectangle(wxSize(20, 5));

}

void Goal::Draw(std::shared_ptr<wxGraphicsContext> graphics, int a, int b)
{
    mGoalImage.DrawPolygon(graphics, mPosition.m_x, mPosition.m_y, 0);

    double x = mPosition.m_x;
    double y = mPosition.m_y;

    // Brush and pen to draw the scoreboard
    wxBrush brush(ScoreboardBackgroundColor);
    graphics->SetBrush(brush);
    wxPen pen(*wxBLACK, ScoreboarderLineWidth);
    graphics->SetPen(pen);

    // Draw it
    graphics->DrawRectangle(x + ScoreboardRectangle.m_x, y + ScoreboardRectangle.m_y,
                            ScoreboardRectangle.m_width, ScoreboardRectangle.m_height);

    // Score to a string
    std::wstringstream score;
    score << std::setw(2) << std::setfill(L'0') << mScore << std::endl;

    // Font to draw the score
    wxFont font(wxSize(0, ScoreboardFontSize),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxWHITE);

    // From the centimeter pixels page
    graphics->PushState();
    graphics->Translate(x + ScoreboardTextLocation.m_x, y + ScoreboardTextLocation.m_y);
    graphics->Scale(1, -1);
    graphics->DrawText(score.str(), 0, 0);
    graphics->PopState();

}

void Goal::SetPosition(double a, double b)
{
    mPosition = wxPoint2DDouble(a, b);
    mPost.SetInitialPosition(a + PostPosition.m_x, b + PostPosition.m_y);
    mGoal.SetInitialPosition(a + GoalPosition.m_x, b + GoalPosition.m_y);
}

void Goal::Reset()
{
    mScore = 0;
}

void Goal::Update(double elapsed)
{
}


void Goal::UpdateMachineTime(double time)
{
}

void Goal::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contact)
{
    mPost.InstallPhysics(world);
    mGoal.InstallPhysics(world);
    contact->Add(mGoal.GetBody(), this);
}

void Goal::BeginContact(b2Contact *contact)
{
    mScore += 2;
}


void Goal::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetEnabled(false);
}
