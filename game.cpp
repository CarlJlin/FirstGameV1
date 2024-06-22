//Author @CarlJlin
//File game.cpp
//Project FirstGameV1

#define is_down(b) input->buttons[b].is_down
#define pressed(b) input->buttons[b].is_down && input->buttons[b].changed
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_1_p, player_1_dp, player_2_p, player_2_dp;


internal void 
simulate_game(Input* input, float dt) {
	clear_screen(0x3B2077);
	draw_rect(0, 0, 85, 45, 0xffaa33);

	float player_1_ddp = 0.f; // units per second
	if (is_down(BUTTON_UP)) player_1_ddp += 2000;
	if (is_down(BUTTON_DOWN)) player_1_ddp -= 2000;

	player_1_ddp -= player_1_dp * 10.f;

	player_1_p = player_1_p + player_1_dp * dt + player_1_ddp * dt * dt * .5f;
	player_1_dp = player_1_dp + player_1_ddp * dt;
		
	draw_rect(0, 0, 1, 1, 0xffffff);
	
	draw_rect(80, player_1_p, 2.5, 12, 0xff0000);
	draw_rect(-80, 0, 2.5, 12, 0xff0000);
}