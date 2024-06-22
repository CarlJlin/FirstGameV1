//Author @CarlJlin
//File platform_common.cpp
//Project FirstGameV1

struct Button_State {
	bool is_down;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_Z,
	BUTTON_S,


	BUTTON_COUNT, // Should be the last item
};

struct Input {
	Button_State buttons[BUTTON_COUNT]; 
};