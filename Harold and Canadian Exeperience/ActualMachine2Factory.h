/**
 * @file ActualMachine2Factory.h
 * @author Noor M.
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINE2FACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINE2FACTORY_H
class MachineComponent;
class Body;

/**
 * Machine Factory 2 class
 */
class ActualMachine2Factory
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


    void DominoStack(std::shared_ptr<MachineComponent> machine, wxPoint2DDouble position);
    std::shared_ptr<Body> Domino(std::shared_ptr<MachineComponent> machine, wxPoint2DDouble position, double rotation, DominoColor color);
public:
    ActualMachine2Factory(std::wstring resourceDir);
    /**
     * Create function to return the machine we draw
     * @return machine2 drawn
     */
    std::shared_ptr<MachineComponent> Create();
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINE2FACTORY_H
