#include <stdafx.h>

//two global variables to store the buffer device context
//and window handle
HWND gWindowHandle = nullptr;
HDC gBufferDevContex = nullptr;
//\===========================================================================================================
//static windows message handle callback function
static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
//\===========================================================================================================


int main(int argc, char* argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
#pragma region Console Window Set Up
	HANDLE hOrigCon = GetStdHandle(STD_OUTPUT_HANDLE);			//Get handle to original console buffer
	//Create a screen buffer
	COORD const size = { 80, 50 };
	unsigned int screenBufferSize = size.X * size.Y;
	wchar_t* screenBuffer = new wchar_t[screenBufferSize];
	//memset function use to fill memory with specific byte value
	memset(screenBuffer, ' ', screenBufferSize);
	HANDLE hNewScreenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//set the new screen buffer to the console window.
	SetConsoleActiveScreenBuffer(hNewScreenBuffer);
	//resize the console window to the new screen buffer dimensions
	//shrink the window to minimum size
	SMALL_RECT const minimal_window = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(hNewScreenBuffer, TRUE, &minimal_window);
	//then set the bufer size and then set the window size
	SetConsoleScreenBufferSize(hNewScreenBuffer, size);
	SMALL_RECT const window = { 0, 0, size.X - 1, size.Y - 1 };
	SetConsoleWindowInfo(hNewScreenBuffer, TRUE, &window);

	CONSOLE_FONT_INFOEX oldConsoleFont = { 0 };
	GetCurrentConsoleFontEx(hNewScreenBuffer, FALSE, &oldConsoleFont);
	//set the font for the console window
	//create a console font info structure and populate it's data
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	info.nFont = 8;							//Set Font Index
	info.dwFontSize.X = 8;					//Set font width
	info.dwFontSize.Y = 8;					//set font height
	info.FontFamily = FF_DONTCARE;			//set font family
	info.FontWeight = FW_NORMAL;			//set for weight
	wcscpy_s(info.FaceName, L"Terminal");	//set font face name
	//set console font
	SetCurrentConsoleFontEx(hNewScreenBuffer, FALSE, &info);

	//use sprintf_s to write some characters into our screen buffer
	swprintf(screenBuffer, 13, L"Hello World!");
	//write the buffer contents to the console window
	DWORD dwBytesWritten = 0;	//writeConsoleOutputCharacter returns how many bytes written
	WriteConsoleOutputCharacter(hNewScreenBuffer, (LPCWSTR)screenBuffer, 13, { 0,0 }, &dwBytesWritten);
#pragma endregion

#pragma region Bitmap Window Creation
	//Create our render window with a resolution of 640 x 480
	unsigned int windowWidth = 640; unsigned int windowHeight = 480;
	//register a windows class object with this application to get a HDC
	WNDCLASSEX wndClass = { 0 };
	// clear out the window class for use
	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));
	wndClass.cbSize = sizeof(WNDCLASSEX);				//Set Size of struct
	wndClass.style = CS_HREDRAW | CS_VREDRAW;			//Set Draw Style
	wndClass.lpfnWndProc = WndProc;							//FnPtr to Message Handle Function
	wndClass.hInstance = (HINSTANCE)GetModuleHandle(NULL);	//Get Handle to current Module
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);	//Set Cursor for window to default arrow
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		//Set background brush color
	wndClass.lpszMenuName = nullptr;							//Menu nullptr so no menu
	wndClass.lpszClassName = L"CT4101";						//Title of window class
	//Attempt to register window with OS
	if (!RegisterClassEx(&wndClass))
	{
		return EXIT_FAILURE;
	}
	//Create a rectangle area and set it to the dimensions we want for out window.
	RECT windowRect = { 0, 0, windowWidth, windowHeight };
	//Adjust the window size so that the client area will be the correct width and height
	//   Window borders, titles, close buttons etc take up space so make the windowRect larger to hold these
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	HWND windowHandle = CreateWindowEx(NULL,
		L"CT4101",								//Title of Window class (WNDCLASSEX.lpszClassName)
		L"Ray Tracer Render View",				//Title of the window view
		WS_OVERLAPPEDWINDOW,					//Window view style
		0,										//window x origin in pixels
		0,										//window y origin in pixels
		windowRect.right - windowRect.left,		//window width (total width of window not just client area)
		windowRect.bottom - windowRect.top,		//window height (total height of window not just client area)
		NULL,									//parent window, null as window has no parents
		NULL,									//any menu's being used, null if no menu
		(HINSTANCE)GetModuleHandle(NULL),		//application handle, call get module handle to fetch
		NULL);									//for use with multiple windows

	ShowWindow(windowHandle, SW_SHOW);			//Show the window, SW_SHOW display immediately

	//Create Bitmap rendering context
	HDC windowDC = GetDC(windowHandle);			//will need device context
	if (windowDC == NULL)
	{
		return EXIT_FAILURE;					//If we don't have a DC then close the application
	}


	//populate the bitmap data description of bitmapinfoheader here: https://docs.microsoft.com/en-us/previous-versions/dd183376(v=vs.85)
	BITMAPINFOHEADER bmpInfo = { 0 };
	bmpInfo.biSize = sizeof(BITMAPINFOHEADER);					//The size of our bitmap header
	bmpInfo.biWidth = (LONG)windowWidth;						//width in pixels of the bitmap
	bmpInfo.biHeight = -(LONG)windowHeight;						//Negative values here set the bitmap to draw from top left corner
	bmpInfo.biBitCount = 32;									//bit count per pixel - 32 bits per pixel only uses 8 bits per channel no alpha in bitmaps
	bmpInfo.biPlanes = 1;										//this should always be 1
	bmpInfo.biCompression = BI_RGB;								//type of compression used, RGB is not compressed
	bmpInfo.biSizeImage = 0;									//size of image in bytes for rgb images can be 0
	bmpInfo.biXPelsPerMeter = 0;								//this is for print, set to 0
	bmpInfo.biYPelsPerMeter = 0;								//this is for print, set to 0
	bmpInfo.biClrUsed = 0;										//colours used by the bitmap
	bmpInfo.biClrImportant = 0;									//how many colours are required to display the bitmap

	void* bitBuffer;											//the void pointer we will use to access the bitmap context
	HBITMAP bufferBmp = CreateDIBSection(windowDC, (PBITMAPINFO)&bmpInfo, DIB_RGB_COLORS, &bitBuffer, NULL, 0);
	if (bufferBmp == NULL) { return EXIT_FAILURE; }

	gBufferDevContex = CreateCompatibleDC(windowDC);			//Create a compatible Device context for the window
	if (gBufferDevContex == NULL) { return EXIT_FAILURE; }

	HBITMAP defBitmap = (HBITMAP)SelectObject(gBufferDevContex, bufferBmp); //Put the bitmap into the compatible device context
	if (defBitmap == NULL) { return EXIT_FAILURE; }				//defBitmap is the original bitmap context of the window 
																//restore defBitmap on close	
#pragma endregion

#pragma region Main Loop

	uint32_t initialSeedValue = 1;				//Seed value for LFSR
	bool renderComplete = false;				//Boolean value to confirm when render is complete
	uint32_t lfsrVal = initialSeedValue;		//Result of Linear Feedback Shift Register Seeded to value of 1.
	uint16_t x = 0; uint16_t y = 0;				//X and Y values to keep track of pixel coordinates

	MSG msg = { 0 };											//Keep a local MSG object around we will populate this with PeekMessage
	while (msg.message != WM_QUIT)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))			//Check to see if any messages are waiting in the queue
		{
			if (msg.message == WM_QUIT) break;					//Break out of PeekMessage Loop if WM_QUIT received
			//if there is a message translate the message and dispatch it to WndProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//process render loop -- application update loop
		RECT clRect;
		GetClientRect(windowHandle, &clRect);					//Get the size of the client rectangle
		
		if (!renderComplete)							//If the render is not complete render the next pixel in the sequence
		{
			y = lfsrVal & 0x1FF;						//y = lower 9 bits of lfsr value	(0x001FF = 0b0000 0000 0001 1111 1111)
			x = (lfsrVal & 0x7FE00) >> 9;				//x = High 10 bits of lfsr value	(0x7FE00 = 0b1111 1111 1110 0000 0000)
			uint8_t lsb = lfsrVal & 1;					//Get the output bit Least Significant Bit (LSB)
			lfsrVal >>= 1;								//Shift register down one step
			if (lsb) {	lfsrVal ^= 0x400A1;	}			//If the LSB is 0, the xor is skipped

			if (x < windowWidth && y < windowHeight)	//Using the extracted pixel coordinates colour in the pixel
			{
				//calculate colour value as a float in range 0 -> 1 to produce a gradient
				float r = float(x) / (windowWidth - 1);
				float g = float(y) / (windowWidth - 1);
				float b = 1.f - r * g;
				//cast float colour values to char (byte) for output to file
				int red = static_cast<int>(255.999f * r);		//255.999f as range is from 0->1 exclusive
				int green = static_cast<int>(255.999f * g);
				int blue = static_cast<int>(255.999f * b);
				unsigned int colour = (red & 0xFF) << 16 | (green & 0xFF) << 8 | (blue & 0xFF);	//use bit shifts to get the colour data in the right spot
				int index = ((y * windowWidth) + x) * 4;
				memcpy(&(((char*)(bitBuffer))[index]), &colour, 3);
				RedrawWindow(windowHandle, nullptr, nullptr, RDW_INVALIDATE);//redraw the window
			}
			renderComplete = (lfsrVal == initialSeedValue);	//If we have wrapped around to the seed we have covered every pixel
		}
		
	}

#pragma endregion

#pragma region Windows Context Clean Up Code
	//Clean up Window
	SelectObject(gBufferDevContex, defBitmap);		//restore the original bitmap object to the device context
	DeleteDC(gBufferDevContex);						//Delete the Bitmap DC 
	DeleteObject(bufferBmp);						//Delete the created bitmap object
	DestroyWindow(windowHandle);					//Destroy the window
	UnregisterClass(L"CT4101", (HINSTANCE)GetModuleHandle(NULL));	//Unregister the class
	//Clean up Console
	SetCurrentConsoleFontEx(hNewScreenBuffer,		//Set the font back to the original font
		FALSE, &oldConsoleFont);
	SetConsoleActiveScreenBuffer(hOrigCon);			//Set Console buffer back
	CloseHandle(hNewScreenBuffer);					//release consoleScreenBuffer

	//Remember to delete anything that you call 'new' on
	delete[] screenBuffer;
#pragma endregion

	return EXIT_SUCCESS;
}

//\===========================================================================================================
//static windows message handle callback function
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	PAINTSTRUCT paintStruct;
	HDC hDC;

	switch (message)
	{
	case WM_PAINT: // called when the window content is invalidated
	{
		hDC = BeginPaint(hwnd, &paintStruct);			//Prepares the window for painting, device info in paint struct
		RECT clRect = paintStruct.rcPaint;				//Get size of rectangle to paint
		//BitBlt function performs a bit-block transfer of the color data corresponding to a rectangle of pixels
		//from the specified source device context into a destination device context.
		BitBlt(paintStruct.hdc,							//Handle to the destination device context
			clRect.left,							//Upper Left x-coordinate
			clRect.top,								//Upper Left y-coordinate
			(clRect.right - clRect.left) + 1,		//width in logical units (pixels in this scenario)
			(clRect.bottom - clRect.top) + 1,		//height
			gBufferDevContex,						//handle o source device context
			0,										//x coord of source DC rect
			0,										//y coord of source DC rect
			SRCCOPY);								//raster operation code (how to paint)

		EndPaint(hwnd, &paintStruct);					//finish painting by calling endPaint (must be called for each beginPaint)
		return 0;										//return 0 as message handled
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);

	}
}
//\===========================================================================================================