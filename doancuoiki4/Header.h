#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "utils.cpp"
#include <windows.h>
#pragma pack(push, 1)
#define SIZELANE 100
using namespace std;
struct BMPHeader {
	char signature[2];
	uint32_t fileSize; // increased by width * height * 4
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t dataOffset; // increased by 16 for color mask
};

struct Pixel {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	uint8_t alpha; // added for alpha value
};
struct InfoHeader {
	uint32_t size;
	int32_t width;
	int32_t height;
	uint16_t planes;
	uint16_t bitDepth; // changed to 32
	uint32_t compression; // changed to 3 for BI_BITFIELDS   BI_RGB
	uint32_t dataSize; // changed to width * height * 4
	int32_t horizontalRes;
	int32_t verticalRes;
	uint32_t colors;
	uint32_t importantColors;
	Pixel colorMask;
};



global_variable bool running = true;


struct Render_State {
	int height, width;
	void* memory;
	BITMAPINFO bitmap_info;
};
static Render_State render_state;
internal LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
	} break;

	case WM_SIZE: {
		RECT rect;
		GetClientRect(hwnd, &rect);
		render_state.width = rect.right - rect.left;
		render_state.height = rect.bottom - rect.top;
		/*render_state.width = 1350;
		render_state.height = 940;*/

		int size = render_state.width * (render_state.height) * sizeof(unsigned int);

		if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
		render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
		render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
		render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
		render_state.bitmap_info.bmiHeader.biPlanes = 1;
		render_state.bitmap_info.bmiHeader.biBitCount = 32;
		render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;

	} break;

	default: {
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
	return result;
}

internal void
clear_screen(u32 color, Render_State *a ) {
	unsigned int* pixel = (u32*)a->memory;
	for (int y = 0; y < a->height; y++) {
		for (int x = 0; x < a->width; x++) {
			*pixel++ = color;
		}
	}
}

internal
void loadImage(const std::string& inputFilename, Render_State* a, int x, int y, int r, int g, int b) {

	std::ifstream inputFile(inputFilename, std::ios::binary);
	if (!inputFile) {
		std::cerr << "Failed to open input file " << inputFilename << std::endl;
		return;
	}

	BMPHeader bmpHeader;
	InfoHeader infoHeader;
	inputFile.read((char*)&bmpHeader, sizeof(BMPHeader));
	inputFile.read((char*)&infoHeader, sizeof(InfoHeader));

	if (bmpHeader.signature[0] != 'B' || bmpHeader.signature[1] != 'M') {
		std::cerr << "File " << inputFilename << " is not a valid BMP file." << std::endl;
		inputFile.close();
		return;
	}
	if (infoHeader.bitDepth != 32) {
		std::cerr << "Unsupported BMP format (only 32-bit RGBA is supported)." << std::endl;
		return;
	}

	inputFile.read((char*)&infoHeader.colorMask, sizeof(Pixel));


	std::vector<Pixel> pixels(infoHeader.height * infoHeader.width);
	int padding = (4 - (infoHeader.width * sizeof(Pixel)) % 4) % 4;

	for (int y = 0; y < a->height; ++y) {
		inputFile.read((char*)(pixels.data() + infoHeader.width * y), infoHeader.width * sizeof(Pixel));
		inputFile.seekg(padding, std::ios::cur);
	}
	infoHeader.compression = BI_RGB;
	uint8_t* dest = (uint8_t*)a->memory;

	//cho nay chan khong cho no di ra
	//chan tat ca cac dau render lai

	int x0 = clamp(0, x, 1334);
	int startx = x0 - x;//
	int x1 = clamp(0, x + infoHeader.width, 1334);
	int endx = x1 - x;
	//con truong hop cay vuot qua vach
	//int y0=

	//int y0 = clamp(0, y, 925);
	//int starty = y0 - y;//
	//int y1 = clamp(0, y + infoHeader.height, 925);
	//int endy =  y1-y;//
	//
	//int y0=

	//............
	for (int i = 0; i < infoHeader.height; ++i) {
		for (int j = startx; j < endx; j++) {//0, infoHeader.width
			Pixel p = pixels[i * infoHeader.width + j];//truy cap toi tung phan tu

			if (p.red != r || p.green != g || p.blue != b) {
				// Convert RGB values to decimal value
				uint32_t decimalValue = (p.alpha << 24) | (p.red << 16) | (p.green << 8) | p.blue;
				// Save the decimal value to memory
				memcpy(dest + (a->width * (a->height - infoHeader.height - y + i) + j + x) * sizeof(Pixel), &decimalValue, 4);
			}
		}
	}
	inputFile.close();
}

internal
void loadImage(const std::string& inputFilename, Render_State* a, int x, int y) {

	std::ifstream inputFile(inputFilename, std::ios::binary);
	if (!inputFile) {
		std::cerr << "Failed to open input file " << inputFilename << std::endl;
		return;
	}

	BMPHeader bmpHeader;
	InfoHeader infoHeader;
	inputFile.read((char*)&bmpHeader, sizeof(BMPHeader));
	inputFile.read((char*)&infoHeader, sizeof(InfoHeader));

	if (bmpHeader.signature[0] != 'B' || bmpHeader.signature[1] != 'M') {
		std::cerr << "File " << inputFilename << " is not a valid BMP file." << std::endl;
		inputFile.close();
		return;
	}
	if (infoHeader.bitDepth != 32) {
		std::cerr << "Unsupported BMP format (only 32-bit RGBA is supported)." << std::endl;
		return;
	}

	inputFile.read((char*)&infoHeader.colorMask, sizeof(Pixel));


	std::vector<Pixel> pixels(infoHeader.height * infoHeader.width);
	int padding = (4 - (infoHeader.width * sizeof(Pixel)) % 4) % 4;

	for (int y = 0; y < a->height; ++y) {
		inputFile.read((char*)(pixels.data() + infoHeader.width * y), infoHeader.width * sizeof(Pixel));
		inputFile.seekg(padding, std::ios::cur);
	}
	infoHeader.compression = BI_RGB;
	uint8_t* dest = (uint8_t*)a->memory;

	//cho nay chan khong cho no di ra
	//chan tat ca cac dau render lai

	int x0 = clamp(0, x, 1334);
	int startx = x0 - x;//
	int x1 = clamp(0, x + infoHeader.width, 1334);
	int endx = x1 - x;
	//con truong hop cay vuot qua vach
	//int y0=

	//int y0 = clamp(0, y, 925);
	//int starty = y0 - y;//
	//int y1 = clamp(0, y + infoHeader.height, 925);
	//int endy =  y1-y;//
	//
	//int y0=

	//............
	for (int i = 0; i < infoHeader.height; ++i) {
		for (int j = startx; j < endx; j++) {//0, infoHeader.width
			Pixel p = pixels[i * infoHeader.width + j];//truy cap toi tung phan tu


			// Convert RGB values to decimal value
			uint32_t decimalValue = (p.alpha << 24) | (p.red << 16) | (p.green << 8) | p.blue;
			// Save the decimal value to memory
			memcpy(dest + (a->width * (a->height - infoHeader.height - y + i) + j + x) * sizeof(Pixel), &decimalValue, 4);

		}
	}
	inputFile.close();
}

internal
int getRandomNumber(int min, int max) {
    // Seed the random number generator with the current time

    // Generate a random number between min and max
    return min + (std::rand() % (max - min + 1));
}
internal
void draw_rect(int x0, int y0, int x1, int y1, int color)//khong thay doi do dai khi ham thay doi
//=>do do neu thay doi console qua nho so voi kich thuoc cua do vat thi console se bien mat hoac loi
{
	//cach fix:
	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);
	for (int y = y0; y < y1; y++)
	{
		unsigned int* pixel = (unsigned int*)render_state.memory + x0 + y * render_state.width;
		//dua con tro xuong tung dong
		for (int x = x0; x < x1; x++)
		{
			*pixel++ = color;
		}
	}
}
internal
void swapi(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}
internal
void swaps(string& a, string& b)
{
    string temp = a;
    a = b;
    b = temp;
}
internal
void BubbleSort(int a[], int n, vector<string>& namefile)
{
    int i, j;
    bool haveSwap = false;
    for (i = 0; i < n - 1; i++) {
        // i phần tử cuối cùng đã được sắp xếp
        haveSwap = false;
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] < a[j + 1]) {
                swapi(a[j], a[j + 1]);
                swaps(namefile[j], namefile[j + 1]);
                haveSwap = true; // Kiểm tra lần lặp này có swap không
            }
        }
        // Nếu không có swap nào được thực hiện => mảng đã sắp xếp. Không cần lặp thêm
        if (haveSwap == false) {
            break;
        }
    }
}


