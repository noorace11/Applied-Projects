/**
 * @file ActualMachine1Factory.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINE1FACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINE1FACTORY_H
class MachineComponent;
class Body;

/**
 * Actual Machine Factory number 1
 */
class ActualMachine1Factory
{
private:
    /// image directory member variable
    std::wstring mImageDir;
    /// resource directory member variable
    std::wstring mResourceDir;

    /// The possible domino colors
    enum class DominoColor { Black, Red, Green, Blue };

    /// Height of a Domino
    const double DominoHeight = 25;

    /// Width of a Domino
    const double DominoWidth = 5;

    /**
     * Function for displaying top beam and the ramp
     * @param machine
     */
    void TopBeamAndRamp(std::shared_ptr<MachineComponent> machine);
    /**
     * Function to display second beam and arm
     * @param machine
     */
    void BeamAndSpinningArm(std::shared_ptr<MachineComponent> machine);

    void DominoStack(std::shared_ptr<MachineComponent> machine, wxPoint2DDouble position);

    void DominoesOnBeam(std::shared_ptr<MachineComponent> machine, wxPoint2DDouble position);

    std::shared_ptr<Body> Domino(std::shared_ptr<MachineComponent> machine, wxPoint2DDouble position, double rotation, DominoColor color);
public:
    ActualMachine1Factory(std::wstring resourceDir);


    std::shared_ptr<MachineComponent> Create();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINE1FACTORY_H
