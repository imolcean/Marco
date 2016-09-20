
#include <mutex>
#include <chrono>
#include "Robot.h"
#include "ControlEntity.h"
#include "InputHandler.h"

using namespace marco;

ControlEntity controlBuffer;
bool newCommand;
std::mutex lock;
InputHandler console(controlBuffer, newCommand, lock);

// TODO
Track leftTrack(0, 0, 0);
Track rightTrack(0, 0, 0);
Robot robot(leftTrack, rightTrack);
//

/**
 * Main function.
 */
int main(int argc, char **argv)
{
	console.run();

	while(1)
	{
		if(newCommand)
		{
			ControlEntity control;

			{
				std::lock_guard<std::mutex> guard(lock);

				control = controlBuffer;
				newCommand = false;
			}

			std::cout << "Command received" << std::endl;
			std::cout << "X: " << control.getX() << std::endl;
			std::cout << "Y: " << control.getY() << std::endl;
			std::cout << "T: " << control.getTime() << std::endl;
			std::cout << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}
