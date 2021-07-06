#include <iostream>
#include <string>
#include <map>


struct LightOutputs {
  bool red_ns;
  bool yellow_ns;
  bool green_ns;
  bool red_ew;
  bool yellow_ew;
  bool green_ew;
};

struct LightInputs {
  int time;
  bool car_sensor_n;
  bool car_sensor_s;
};

enum State { RR, GR, YR, RG, RY };

std::map<State, LightOutputs> StateValues = {
	{RR, {true, false, false, true, false, false}},
	{GR, {false, false, true, true, false, false}},
	{YR, {false, true, false, true, false, false}},
	{RG, {true, false, false, false, false, true}},
	{RY, {true, false, false, false, true, false}}
};


class Controller {
public:
	LightOutputs update(LightInputs inputs) {
		// Switch states if needed
		switch (state) {
			case RR:
				if (inputs.car_sensor_s || inputs.car_sensor_n) {
					state = GR;
				} else {
					state = RG;
				}
				transition = inputs.time + 5;
				break;
			case GR:
				if (inputs.time >= transition) {
					state = YR;
					transition = inputs.time + 2;
				}
				break;
			case YR:
				if (inputs.time >= transition) {
					state = RR;
				}
				break;
			case RG:
				if (inputs.time >= transition) {
					state = RY;
					transition = inputs.time + 2;
				}
				break;
			case RY:
				if (inputs.time >= transition) {
					state = RR;
				}
				break;
		}
		// Return values related to state
		return StateValues[state];
	}

private:
	State state = RR;
	int transition = 0;
};


int main() {
    int time = 0;
    Controller controller;

    while (true) {
        std::string input;
        std::getline(std::cin, input);
        if(input.size() != 2)
            break;

        LightInputs inputs = {time, input[0] == '1', input[1] == '1'};
        LightOutputs output = controller.update(inputs);
        std::cout << output.red_ns << output.yellow_ns << output.green_ns << output.red_ew << output.yellow_ew << output.green_ew << std::endl;
        time++;
    }

    return 0;
}
