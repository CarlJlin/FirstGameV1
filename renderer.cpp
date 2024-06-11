//Author @CarlJlin
//File renderer.cpp
//Project FirstGameV1

internal void
clear_screen(u32 color) {
	u32* pixel = (u32*)render_state.memory;
	for (s32 y = 0; y < render_state.height; y++) {
		for (s32 x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

internal void
draw_rect_in_pixels(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, u32 color) {

	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);


	for (int y = y0; y < y1; y++){
		u32* pixel = (u32*)render_state.memory+x0+y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

global_variable float render_scale = 0.01f;

internal void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {

	x *= render_state.height*render_scale;
	y *= render_state.height*render_scale;
	half_size_x *= render_state.height*render_scale;
	half_size_y *= render_state.height*render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	// Change to pixels
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;


	draw_rect_in_pixels(x0, y0, x1, y1, color);
}