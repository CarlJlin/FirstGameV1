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

const char* letters[][7] = {
    // A
    " 00 ",
    "0  0",
    "0  0",
    "0000",
    "0  0",
    "0  0",
    "0  0",

    // B
    "000 ",
    "0  0",
    "0  0",
    "000 ",
    "0  0",
    "0  0",
    "000",

    // C
    " 000",
    "0   ",
    "0   ",
    "0   ",
    "0   ",
    "0   ",
    " 000",

    // D
    "000 ",
    "0  0",
    "0  0",
    "0  0",
    "0  0",
    "0  0",
    "000 ",

    // E
    " 000",
    "0   ",
    "0   ",
    "000 ",
    "0   ",
    "0   ",
    " 000",

    // F
    "0000",
    "0   ",
    "0   ",
    "000 ",
    "0   ",
    "0   ",
    "0   ",

    // G
    " 000",
    "0   ",
    "0   ",
    "0 00",
    "0  0",
    "0  0",
    " 000",

    // H
    "0  0",
    "0  0",
    "0  0",
    "0000",
    "0  0",
    "0  0",
    "0  0",

    // I
    "00000",
    "  0 ",
    "  0 ",
    "  0 ",
    "  0 ",
    "  0 ",
    "00000",

    // J
    "  000",
    "   0 ",
    "   0 ",
    "   0 ",
    "0  0 ",
    "0  0 ",
    " 00  ",

    // K
    "0  0",
    "0 0 ",
    "00  ",
    "0 0 ",
    "0  0",
    "0   0",
    "0    0",

    // L
    "0    ",
    "0    ",
    "0    ",
    "0    ",
    "0    ",
    "0    ",
    "0000",

    // M
    "0   0",
    "00 00",
    "0 0 0",
    "0   0",
    "0   0",
    "0   0",
    "0   0",

    // N
    "0   0",
    "00  0",
    "0 0 0",
    "0  00",
    "0   0",
    "0   0",
    "0   0",

    // O
    " 000 ",
    "0   0",
    "0   0",
    "0   0",
    "0   0",
    "0   0",
    " 000 ",

    // P
    "0000",
    "0   0",
    "0   0",
    "0000",
    "0   ",
    "0   ",
        "0   ",

        // Q
        " 000 ",
        "0   0",
        "0   0",
        "0   0",
        "0 0 0",
        "0  0 ",
        " 00 0",

        // R
        "000 ",
        "0  0",
        "0  0",
        "000 ",
        "0  0",
        "0  0",
        "0   0",

        // S
        " 000",
        "0   ",
        "0   ",
        " 00",
        "   0",
        "   0",
        "000",

        // T
        "00000",
        "  0  ",
        "  0  ",
        "  0  ",
        "  0  ",
        "  0  ",
        "  0  ",

        // U
        "0   0",
        "0   0",
        "0   0",
        "0   0",
        "0   0",
        "0   0",
        " 000 ",

        // V
        "0   0",
        "0   0",
        "0   0",
        "0   0",
        " 0 0 ",
        " 0 0 ",
        "  0  ",

        // W
        "0   0",
        "0   0",
        "0   0",
        "0 0 0",
        "0 0 0",
        "00 00",
        "0   0",

        // X
        "0   0",
        "0   0",
        " 0 0 ",
        "  0  ",
        " 0 0 ",
        "0   0",
        "0   0",

        // Y
        "0   0",
        "0   0",
        " 0 0 ",
        "  0  ",
        "  0  ",
        "  0  ",
        "  0  ",

        // Z
        "00000",
        "    0",
        "   0 ",
        "  0  ",
        " 0   ",
        "0    ",
        "00000",

        // !
        "  0  ",
        "  0  ",
        "  0  ",
        "  0  ",
        "  0  ",
        "     ",
        "  0  ",
};

internal void
draw_text(const char* text, float x, float y, float size, u32 color) {
    float half_size = size * .5f;
    float original_y = y;

    while (*text) {
        if (*text != 32) { // If character is not a space
            int letter_index = *text - 'A';
            if (letter_index >= 0 && letter_index < sizeof(letters) / sizeof(letters[0])) {
                const char** a_letter = letters[letter_index];
                if (a_letter) { // Check if a_letter is not null
                    float original_x = x;
                    for (int i = 0; i < 7; i++) {
                        const char* row = a_letter[i];
                        if (row) { // Check if row is not null
                            while (*row) {
                                if (*row == '0') {
                                    draw_rect(x, y+0.1, half_size, half_size, color);
                                }
                                x += size;
                                row++;
                            }
                        }
                        y -= size;
                        x = original_x;
                    }
                }
            }
        }
        text++;
        x += size * 6.f;
        y = original_y;
    }
}

internal void
draw_number(int number, float x, float y, float size, u32 color) {
    float half_size = size * .5f;

    bool drew_number = false;
    while (number || !drew_number) {
        drew_number = true;

        int digit = number % 10;
        number = number / 10;

        switch (digit) {
        case 0: {
            draw_rect(x - size, y, half_size, 2.5f * size, color);
            draw_rect(x + size, y, half_size, 2.5f * size, color);
            draw_rect(x, y + size * 2.f, half_size, half_size, color);
            draw_rect(x, y - size * 2.f, half_size, half_size, color);
            x -= size * 4.f;
        } break;

        case 1: {
            draw_rect(x + size, y, half_size, 2.5f * size, color);
            x -= size * 2.f;
        } break;

        case 2: {
            draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
            draw_rect(x, y, 1.5f * size, half_size, color);
            draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
            draw_rect(x + size, y + size, half_size, half_size, color);
            draw_rect(x - size, y - size, half_size, half_size, color);
            x -= size * 4.f;
        } break;

        case 3: {
            draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
            draw_rect(x - half_size, y, size, half_size, color);
            draw_rect(x - half_size, y - size * 2.f, size, half_size, color);
            draw_rect(x + size, y, half_size, 2.5f * size, color);
            x -= size * 4.f;
        } break;

        case 4: {
            draw_rect(x + size, y, half_size, 2.5f * size, color);
            draw_rect(x - size, y + size, half_size, 1.5f * size, color);
            draw_rect(x, y, half_size, half_size, color);
            x -= size * 4.f;
        } break;

        case 5: {
            draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
            draw_rect(x, y, 1.5f * size, half_size, color);
            draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
            draw_rect(x - size, y + size, half_size, half_size, color);
            draw_rect(x + size, y - size, half_size, half_size, color);
            x -= size * 4.f;
        } break;

        case 6: {
            draw_rect(x + half_size, y + size * 2.f, size, half_size, color);
            draw_rect(x + half_size, y, size, half_size, color);
            draw_rect(x + half_size, y - size * 2.f, size, half_size, color);
            draw_rect(x - size, y, half_size, 2.5f * size, color);
            draw_rect(x + size, y - size, half_size, half_size, color);
            x -= size * 4.f;
        } break;

        case 7: {
            draw_rect(x + size, y, half_size, 2.5f * size, color);
            draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
            x -= size * 4.f;
        } break;

        case 8: {
            draw_rect(x - size, y, half_size, 2.5f * size, color);
            draw_rect(x + size, y, half_size, 2.5f * size, color);
            draw_rect(x, y + size * 2.f, half_size, half_size, color);
            draw_rect(x, y - size * 2.f, half_size, half_size, color);
            draw_rect(x, y, half_size, half_size, color);
            x -= size * 4.f;
        } break;

        case 9: {
            draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
            draw_rect(x - half_size, y, size, half_size, color);
            draw_rect(x - half_size, y - size * 2.f, size, half_size, color);
            draw_rect(x + size, y, half_size, 2.5f * size, color);
            draw_rect(x - size, y + size, half_size, half_size, color);
            x -= size * 4.f;
        } break;
        }

    }
}