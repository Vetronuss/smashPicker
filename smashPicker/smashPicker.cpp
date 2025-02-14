// smashPicker.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#include <thread>
#include <string>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <C:\Users\Coope\Documents\OpenCv\opencv\build\include\opencv2\opencv.hpp>
using namespace std;

#include <iostream>

#include <string>
#include <vector>
#include <thread>

#define TOSTR(a) #a"= " << a

// Two-argument min function
template <typename T, typename T2>
constexpr T min(T a, T2 b) {
	return (a < b) ? a : b;
}

// Three-argument min function
template <typename T, typename T2, typename T3>
constexpr T min(T a, T2 b, T3 c) {
	return min(min(a, b), c);
}

// Two-argument max function
template <typename T, typename T2>
constexpr T max(T a, T2 b) {
	return (a > b) ? a : b;
}

// Three-argument max function
template <typename T, typename T2, typename T3>
constexpr T max(T a, T2 b, T3 c) {
	return max(max(a, b), c);
}
using namespace std;

class SOUNDCLIP {
private:
	std::wstring fileName;
	std::wstring alias; // Unique alias for the sound

	// Converts std::string to std::wstring (for Unicode compatibility)
	static std::wstring stringToWstring(const std::string& str) {
		return std::wstring(str.begin(), str.end());
	}

public:
	// Constructor (accepts std::string and converts to std::wstring)
	SOUNDCLIP(const std::string& file)
		: fileName(stringToWstring(file)) {
		static int id = 0; // Unique ID to avoid alias conflicts
		std::wostringstream oss;
		oss << L"sound" << id++; // Unique alias per instance
		alias = oss.str();
	}

	// Play the entire clip
	void play() {
		std::wstring command = L"open \"" + fileName + L"\" type mpegvideo alias " + alias;
		mciSendStringW(command.c_str(), NULL, 0, NULL);
		mciSendStringW((L"play " + alias).c_str(), NULL, 0, NULL);
	}

	// Play for a specific duration (non-blocking)
	void playFor(double seconds) {
		std::thread([this, seconds]() {
			play();  // Start playing
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(seconds * 1000)));
			stop();  // Stop after duration
			}).detach(); // Run in a separate thread (non-blocking)
	}

	// Stop playback
	void stop() {
		mciSendStringW((L"stop " + alias).c_str(), NULL, 0, NULL);
		mciSendStringW((L"close " + alias).c_str(), NULL, 0, NULL);
	}
};

void setConsoleColour(unsigned short colour)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout.flush();
	SetConsoleTextAttribute(hOut, colour);
}

void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}
std::wstring stringToWstring(const std::string& str) {
	return std::wstring(str.begin(), str.end());
}

// Function to play an audio file
void playAudio(const std::string& filename) {
	std::wstring wideFilename = stringToWstring(filename);
	std::wstring command = L"open \"" + wideFilename + L"\" type mpegvideo alias myMusic";

	mciSendString(command.c_str(), NULL, 0, NULL);
	mciSendString(L"play myMusic", NULL, 0, NULL);
	Sleep(10000);
	mciSendString(L"stop myMusic", NULL, 0, NULL);
}
void cls()
{
	// Get the Win32 handle representing standard output.
	// This generally only has to be done once, so we make it static.
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };

	// cout uses a buffer to batch writes to the underlying console.
	// We need to flush that to the console because we're circumventing
	// cout entirely; after we clear the console, we don't want
	// stale buffered text to randomly be written out.
	cout.flush();

	// Figure out the current width and height of the console window
	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		// TODO: Handle failure!
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

	DWORD written;

	// Flood-fill the console with spaces to clear it
	FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

	// Reset the attributes of every character to the default.
	// This clears all background colour formatting, if any.
	FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

	// Move the cursor back to the top left for the next sequence of writes
	SetConsoleCursorPosition(hOut, topLeft);
}
#include <set>

class Vec
{
public:
	double x = 0;
	double y = 0;
	Vec()
	{
	}
	Vec(double xx, double yy)
	{
		x = xx;
		y = yy;
	}
	Vec(double a)
	{
		x = a;
		y = a;
	}

	//Functions just because I accidently type width instead of x
	double width()
	{
		return x;
	}
	double height()
	{
		return y;
	}
};
// Constant placeholder for blank strings
const std::string BLANK_STRING = "                                                                   \n";

std::vector<std::string> insertBlanksCapped(std::vector<std::string> inputVec, size_t index, size_t count) {
	size_t originalSize = inputVec.size();
	cout << "OriginalSize: " << originalSize << endl; cout << "index:" << index << endl;
	if (index >= originalSize) {
		std::cerr << "Error: Index out of bounds!\n";
		return inputVec; // Return unmodified vector
	}

	// Insert `count` blank strings at the given index
	inputVec.insert(inputVec.begin() + index, count, BLANK_STRING);

	// Trim the vector to keep it at the original size
	if (inputVec.size() > originalSize) {
		inputVec.resize(originalSize);
	}

	return inputVec;
}

const string ASCII_CHARS = "@%#&*+=-:. ,";  // Dark to light

#define abs(a) (a<0?0:a)


vector<string> imageToASCII(const string& imagePath, int width = 100) {
	cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
	if (image.empty()) {
		cerr << "Error: Could not load image!\n";
		return {};
	}

	// Resize keeping aspect ratio
	int height = (image.rows * width) / image.cols;
	cv::resize(image, image, cv::Size(width, height));

	vector<string> asciiArt;

	for (int y = 0; y < image.rows / 3; ++y) {
		string line;
		for (int x = 0; x < image.cols; ++x) {
			int pixelValue = image.at<uchar>(y * 3, x);
			char asciiChar = ASCII_CHARS[(int)abs((pixelValue * (ASCII_CHARS.size() - 1)) / 200)];
			line += asciiChar;
		}
		asciiArt.push_back(line);
	}

	return asciiArt;
}

void maximizeConsole() {
	HWND consoleWindow = GetConsoleWindow(); // Get the console window handle
	ShowWindow(consoleWindow, SW_MAXIMIZE); // Maximize the console window
}

bool voiceloop = true;
//menu stays open for 30 seconds with no talking
void triggerVoiceTyping() {
	std::cout << "Voice Typing triggered!" << std::endl;
	INPUT inputs[4] = {};

	// Press Win key
	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = VK_LWIN;

	// Press H key
	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = 'H';

	// Release H key
	inputs[2].type = INPUT_KEYBOARD;
	inputs[2].ki.wVk = 'H';
	inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

	// Release Win key
	inputs[3].type = INPUT_KEYBOARD;
	inputs[3].ki.wVk = VK_LWIN;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(4, inputs, sizeof(INPUT));
	Sleep(1000 * 60 * 15);
	while (voiceloop) {
		// Send the keystrokes
		SendInput(4, inputs, sizeof(INPUT));
		Sleep(500);
		SendInput(4, inputs, sizeof(INPUT));
		Sleep(1000 * 60 * 15);
	}
}

namespace consoleDisplay
{
	class Display
	{
	public:
		vector<string> buffer;
		vector<string> backBuffer;
		Vec cursorPos;
		HANDLE hConsole;
		Vec size;
		bool threadRunning = false;
		bool needRedraw = false;
		string blanklayer;

		void setupConsole()
		{
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			if (hConsole == INVALID_HANDLE_VALUE) {
				cerr << "Failed to get console handle.\n";
			}
			// Define cursor information structure
			CONSOLE_CURSOR_INFO cursorInfo;
			maximizeConsole();
			// Get the current cursor info
			if (GetConsoleCursorInfo(hConsole, &cursorInfo)) {
				// Modify the cursor size and visibility
				cursorInfo.dwSize = 1;  // Cursor size (1-100, where 100 is the full block), doesn't matter in win 11
				cursorInfo.bVisible = FALSE;  //TRUE to show cursor, FALSE to hide

				// Apply the changes
				SetConsoleCursorInfo(hConsole, &cursorInfo);
			}
			else {
				cerr << "Failed to get console cursor info.\n";
			}
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
				size.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
				size.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
			}
			else {
				size.x = size.y = -1; // Error case, also i like this
			}

			//fill display buffer
			buffer = {};
			backBuffer = {};
			for (int y = 0; y < size.y; y++)
			{
				buffer.push_back("");
				backBuffer.push_back("");
				for (int x = 0; x < size.x; x++)
				{
					buffer[y] += " ";
					backBuffer[y] += " ";
				}
			}
			blanklayer = buffer[0];
			cout << "Display setup\n";
		}

		void swapBuffer()
		{
			int count = 0;
			for (string a : backBuffer)
			{
				if (count >= buffer.size())
				{
					Beep(100, 100);
					buffer.push_back("");
				}
				buffer[count] = a;
				count++;
			}
		}

		Display()
		{
			setupConsole();
		}

		void printBufferSetup() {
			//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD coord = { 0, 0 }; // Start at the top-left of the console
			DWORD written;

			// Clear the console
			cls();

			for (const auto& line : backBuffer) {
				WriteConsoleOutputCharacterA(hConsole, line.c_str(), static_cast<DWORD>(line.length()), coord, &written);
				coord.Y++; // Move to the next line
			}
			swapBuffer();
		}

		void printBufferLoop() {
			printBufferSetup();  // Initial print backbuffer

			threadRunning = true;
			while (threadRunning) {
				if (needRedraw) {
					needRedraw = false;

					// Ensure backBuffer matches buffer size
					if (backBuffer.size() != buffer.size()) {
						backBuffer.resize(buffer.size());
					}

					for (size_t i = 0; i < buffer.size(); i++) {
						// Resize backBuffer[i] if needed
						if (backBuffer[i].size() != buffer[i].size()) {
							backBuffer[i].resize(buffer[i].size(), ' ');
						}

						if (buffer[i] != backBuffer[i]) {
							int minIndex = INT_MAX;
							int maxIndex = -1;

							size_t minLength = min(buffer[i].size(), backBuffer[i].size());

							// Find changed character indices
							for (size_t c = 0; c < minLength; c++) {
								if (buffer[i][c] != backBuffer[i][c]) {
									minIndex = min(minIndex, (int)c);
									maxIndex = max(maxIndex, (int)c);
								}
							}

							// If a line changed in length, update the entire new part
							if (buffer[i].size() > backBuffer[i].size()) {
								minIndex = min(minIndex, (int)backBuffer[i].size());
								maxIndex = buffer[i].size() - 1;
							}

							// Only update if there's a valid range to draw
							if (maxIndex >= minIndex) {
								COORD coord = { (SHORT)minIndex, (SHORT)i };
								DWORD written;

								WriteConsoleOutputCharacterA(hConsole,
									backBuffer[i].c_str() + minIndex,
									maxIndex - minIndex + 1,
									coord,
									&written);
							}
						}
					}

					swapBuffer(); // Update backBuffer after drawing
				}
			}
			cls();
			cout << "Display destroyed\n";
		}

		void runDrawLoop()
		{
			needRedraw = true;

			thread a(&Display::printBufferLoop, this);
			cout << "Running thread...\n";
			while (!threadRunning) { Sleep(10); }
			a.detach();
		}

		string& operator[](int a)
		{
			return backBuffer[a];
		}

		//toggle redraw;
		void redraw()
		{
			needRedraw = true;
		}
		bool autoRedraw = false;
		//find function

		/*per pixel determination function(shader - like)/*
		template<typename type>
		void forevery(type func)
		{
			for (int y = 0; y < backBuffer.size(); y++)
			{
				for (int x = 0; x < backBuffer[y].length(); x++)
				{
					backbuffer[y][x] = func(x, y, backBuffer);
				}
			}
		}
		//shape drawing
		*/
		// Function to draw a line using Bresenham's algorithm
		void line(Vec a, Vec b, char mark = '#') {
			// Ensure points are within bounds before starting
			a.x = max(0, min(a.x, (int)backBuffer[0].size() - 1));
			a.y = max(0, min(a.y, (int)backBuffer.size() - 1));
			b.x = max(0, min(b.x, (int)backBuffer[0].size() - 1));
			b.y = max(0, min(b.y, (int)backBuffer.size() - 1));

			int dx = abs(b.x - a.x), sx = (a.x < b.x) ? 1 : -1;
			int dy = -abs(b.y - a.y), sy = (a.y < b.y) ? 1 : -1;
			int err = dx + dy, e2;

			while (true) {
				// Ensure we only draw within valid bounds
				if (a.y >= 0 && a.y < backBuffer.size() && a.x >= 0 && a.x < backBuffer[0].size()) {
					backBuffer[a.y][a.x] = mark;
				}

				if (a.x == b.x && a.y == b.y) break;
				e2 = 2 * err;
				if (e2 >= dy) { err += dy; a.x += sx; }
				if (e2 <= dx) { err += dx; a.y += sy; }

				// Stop if next step moves out of bounds
				if (a.x < 0 || a.x >= backBuffer[0].size() || a.y < 0 || a.y >= backBuffer.size()) break;
			}
		}

		void ellipse(const Vec& center, double width, double height, char c)
		{
			//TODO
		}

		void circle(const Vec& center, double size, char c)
		{
			ellipse(center, size, size, c);
		}

		void rect(const Vec& corner1, const Vec& corner2, char c)
		{
			//TODO
		}

		bool text(const Vec& a, string text) {
			if (a.y >= backBuffer.size()) return false; // Prevents out-of-bounds row access

			if (a.x + text.length() >= backBuffer[a.y].length())
			{
				int len = backBuffer[a.y].length() - a.x;
				text = text.substr(0, len < 0 ? 0 : len);
			}
			if (text.empty())
			{
				return false;
			}
			backBuffer[a.y] = backBuffer[a.y].substr(0, a.x) + text + backBuffer[a.y].substr((int)a.x + text.length());
			//backBuffer[a.y].resize(buffer[a.y].length(),' ');

			if (autoRedraw)
				needRedraw = true;

			return true;
		}

		void horizontalLine(int y, char c)
		{
			string ling = "";
			for (int i = 0; i < size.width(); i++)
			{
				ling += c;
			}
			backBuffer[y] = ling;
			if (autoRedraw)
				needRedraw = true;
		}

		void verticalLine(int x, char c)
		{
			for (int i = 0; i < size.height(); i++)
			{
				backBuffer[i][x] = c;
			}
			if (autoRedraw)
				needRedraw = true;
		}

		void spaceBuffer(int y, int space)
		{
			vector<string> temp;
			for (int i = 0; i < backBuffer.size(); i++)
			{
				temp.push_back(backBuffer[i]);
				if (y == i)
				{
					for (int lad = 0; lad < space; lad++)
					{
						temp.push_back(blanklayer);
					}
				}
			}
			backBuffer = temp;
			redraw();
		}

		//vector<vector<string>> frames = {};
	};
}
using namespace consoleDisplay;

///FACE WORK
cv::Mat trimAndResize(const cv::Mat& image, int targetWidth, int targetHeight) {
	if (image.empty()) {
		std::cerr << "Error: Image is empty!" << std::endl;
		return cv::Mat();
	}

	// Convert to grayscale for thresholding
	cv::Mat gray;
	cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

	// Threshold the image (white is 255)
	cv::Mat thresh;
	cv::threshold(gray, thresh, 240, 255, cv::THRESH_BINARY);

	// Find contours to get bounding box of non-white area
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	if (contours.empty()) {
		std::cerr << "Error: No content found (image might be fully white)!" << std::endl;
		return cv::Mat();
	}

	// Get bounding rectangle of the largest contour
	cv::Rect boundingBox = cv::boundingRect(contours[0]);
	for (const auto& contour : contours) {
		boundingBox = boundingBox | cv::boundingRect(contour);
	}

	// Crop the image to remove white space
	cv::Mat cropped = image(boundingBox).clone();

	// Resize to the specified dimensions
	cv::Mat resized;
	cv::resize(cropped, resized, cv::Size(targetWidth, targetHeight), 0, 0, cv::INTER_AREA);

	return resized;
}
std::vector<cv::Mat> splitImage(const cv::Mat& image, double percent) {
	std::vector<cv::Mat> result;

	// Ensure valid percent range
	if (percent < 0.0 || percent > 1.0) {
		throw std::invalid_argument("Percent must be between 0 and 1.");
	}

	int splitRow = static_cast<int>(image.rows * percent); // Calculate split row

	// Ensure split is within valid range
	if (splitRow <= 0 || splitRow >= image.rows) {
		result.push_back(image.clone());  // If out of bounds, return original image in first part
		result.push_back(cv::Mat::zeros(0, 0, image.type())); // Empty second part
		return result;
	}

	// Split the image into two parts
	cv::Mat topPart = image(cv::Range(0, splitRow), cv::Range::all()).clone();
	cv::Mat bottomPart = image(cv::Range(splitRow, image.rows), cv::Range::all()).clone();

	result.push_back(topPart);
	result.push_back(bottomPart);
	return result;
}
HWND getOpenCVWindowHandle(const std::string& windowName) {
	return FindWindowA(nullptr, windowName.c_str());
}

bool faceRunning = true;
bool faceTalking = false;
void FACEHAHA()
{
	cv::Mat image = cv::imread("mcride.jpg");
	if (image.empty()) {
		std::cerr << "Error: Could not load image!" << std::endl;
		return;
	}

	image = trimAndResize(image,500*1.5, 250*1.5);
	vector<cv::Mat> images = splitImage(image, 0.7);

	// Window name (must match the one in cv::imshow)
	std::string windowName = "Forehead";
	std::string windowName2 = "Chin";
	// Create the OpenCV window
	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
	cv::imshow(windowName, images[0]);

	cv::namedWindow(windowName2, cv::WINDOW_AUTOSIZE);
	cv::imshow(windowName2, images[1]);

	// Get the HWND (window handle)
	HWND hwnd[2] = { getOpenCVWindowHandle(windowName),getOpenCVWindowHandle(windowName2) };

	LONG style[2] = { GetWindowLong(hwnd[0], GWL_STYLE),GetWindowLong(hwnd[1], GWL_STYLE) };
	style[0] &= ~(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME);
	style[1] &= ~(WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME);
	SetWindowLong(hwnd[0], GWL_STYLE, style[0]);
	SetWindowLong(hwnd[1], GWL_STYLE, style[1]);
	// Apply changes and refresh window
	SetWindowPos(hwnd[0], nullptr, 0, 0, 0, 0,
		SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
	SetWindowPos(hwnd[1], nullptr, 0, 0, 0, 0,
		SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);

	RECT rect;
	GetWindowRect(hwnd[0], &rect);
	int windowHeight = (int)rect.bottom - (int)rect.top;;
	int x = 1000;
	int y = 500;
	while (faceRunning)
	{
		SetWindowPos(hwnd[0], nullptr, x, 400, 0, 0, SWP_NOSIZE| SWP_NOZORDER);
		SetWindowPos(hwnd[1], nullptr, x, 400 +windowHeight-40, 0, 0, SWP_NOSIZE);
		cv::waitKey(1);

		while(!faceTalking)
		{
			cv::waitKey(100);//nofin
		}
		Sleep(1000);
		int frame = 0;

		while(faceTalking)
		{

	
			SetWindowPos(hwnd[1], nullptr, x, 400 + windowHeight + abs((double)sin(frame/3)*40)-40, 0, 0, SWP_NOSIZE);

			frame++;

			cv::waitKey(10);

				
		}
	}
	cv::destroyWindow(windowName);
	cv::destroyWindow(windowName2);
}

//Ui render stuff

namespace types {
	enum SIZE { null, superLight, light, medium, heavy, superHeavy };
}
using namespace types;

class Character {
public:
	types::SIZE size;
	string name;
	string game;
	bool dlc;
	int timesPicked = 0;
	int index;
	bool custom = true;
	string soundFile = "";

	Character(types::SIZE si, string nam, string gam, bool isDlc = false)
		: size(si), name(nam), game(gam), dlc(isDlc) {
		static int ind = -1; ind++; index = ind;
	}
	Character(string filen, types::SIZE si, string nam, string gam, bool isDlc = false)
		: size(si), name(nam), game(gam), dlc(isDlc), soundFile(filen) {
		static int ind = -1; ind++; index = ind;
		
	}

	void print() const {
		setConsoleColour(3);
		cout << name << " (" << game << ") - ";
		switch (size) {
		case superLight: cout << "Super Light"; break;
		case light: cout << "Light"; break;
		case medium: cout << "Medium"; break;
		case heavy: cout << "Heavy"; break;
		case superHeavy: cout << "Super Heavy"; break;
		}
		cout << (dlc ? " [DLC]" : "") << " ";
		cout << (timesPicked <= 0 ? "" : "TimesPicked:" + to_string(timesPicked)) << endl;
		setConsoleColour(0xF);
	}

	void playNoise()
	{
		if (soundFile.empty())
		{
			return;
		}
		thread temp(playAudio,soundFile);///(soundFile);
		temp.detach();

	}
};

vector<Character> characters = {
	// Non-DLC Characters
	{"mario.mp3", medium, "Mario", "Super Mario"},
	{"donkeyKong.mp3", superHeavy, "Donkey Kong", "Donkey Kong"},
	{"link.mp3", medium, "Link", "The Legend of Zelda"},
	{"samus.mp3", heavy, "Samus", "Metroid"},
	{heavy, "Dark Samus", "Metroid"},
	{"yoshi.mp3", medium, "Yoshi", "Yoshi"},
	{"kirby.mp3", light, "Kirby", "Kirby"},
	{"fox.mp3", light, "Fox", "Star Fox"},
	{light, "Pikachu", "Pokémon"},
	{"luigi.mp3", medium, "Luigi", "Super Mario"},
	{medium, "Ness", "EarthBound"},
	{"captainfalcon.mp3", medium, "Captain Falcon", "F-Zero"},
	{light, "Jigglypuff", "Pokémon"},
	{"peach.mp3", medium, "Peach", "Super Mario"},
	{"daisy.mp3", medium, "Daisy", "Super Mario"},
	{"bowser.mp3", superHeavy, "Bowser", "Super Mario"},
	{"iceclimbers.mp3", light, "Ice Climbers", "Ice Climber"},
	{light, "Sheik", "The Legend of Zelda"},
	{"zelda.mp3", light, "Zelda", "The Legend of Zelda"},
	{"drmario.mp3", medium, "Dr. Mario", "Super Mario"},
	{superLight, "Pichu", "Pokémon"},
	{"falco.mp3", light, "Falco", "Star Fox"},
	{"marth.mp3", light, "Marth", "Fire Emblem"},
	{light, "Lucina", "Fire Emblem"},
	{light, "Young Link", "The Legend of Zelda"},
	{heavy, "Ganondorf", "The Legend of Zelda"},
	{light, "Mewtwo", "Pokémon"},
	{medium, "Roy", "Fire Emblem"},
	{medium, "Chrom", "Fire Emblem"},
	{"mrgamewatch.mp3", superLight, "Mr. Game & Watch", "Game & Watch"},
	{"metaknight.mp3", light, "Meta Knight", "Kirby"},
	{"pit.mp3", medium, "Pit", "Kid Icarus"},
	{medium, "Dark Pit", "Kid Icarus"},
	{light, "Zero Suit Samus", "Metroid"},
	{"wario.mp3", heavy, "Wario", "Wario"},
	{"snake.mp3", heavy, "Snake", "Metal Gear"},
	{heavy, "Ike", "Fire Emblem"},
	{medium, "Pokémon Trainer", "Pokémon"},
	{light, "Diddy Kong", "Donkey Kong"},
	{"lucas.mp3", medium, "Lucas", "EarthBound"},
	{"sonic.mp3", light, "Sonic", "Sonic the Hedgehog"},
	{"kingdedede.mp3", superHeavy, "King Dedede", "Kirby"},
	{superLight, "Olimar", "Pikmin"},
	{medium, "Lucario", "Pokémon"},
	{"rob.mp3", heavy, "R.O.B.", "R.O.B."},
	{light, "Toon Link", "The Legend of Zelda"},
	{medium, "Wolf", "Star Fox"},
	{light, "Villager", "Animal Crossing"},
	{"megaman.mp3", medium, "Mega Man", "Mega Man"},
	{medium, "Wii Fit Trainer", "Wii Fit"},
	{light, "Rosalina & Luma", "Super Mario"},
	{"littlemac.mp3", medium, "Little Mac", "Punch-Out!!"},
	{light, "Greninja", "Pokémon"},
	{medium, "Mii Brawler", "Mii"},
	{medium, "Mii Swordfighter", "Mii"},
	{heavy, "Mii Gunner", "Mii"},
	{"palutena.mp3", light, "Palutena", "Kid Icarus"},
	{"pacman.mp3", medium, "Pac-Man", "Pac-Man"},
	{medium, "Robin", "Fire Emblem"},
	{medium, "Shulk", "Xenoblade Chronicles"},
	{heavy, "Bowser Jr.", "Super Mario"},
	{"duckhunt.mp3", light, "Duck Hunt", "Duck Hunt"},
	{"ryu.mp3", heavy, "Ryu", "Street Fighter"},
	{"ken.mp3", heavy, "Ken", "Street Fighter"},
	{medium, "Cloud", "Final Fantasy"},
	{medium, "Corrin", "Fire Emblem"},
	{light, "Bayonetta", "Bayonetta"},
	{medium, "Inkling", "Splatoon"},
	{"ridley.mp3", heavy, "Ridley", "Metroid"},
	{heavy, "Richter", "Castlevania"},
	{superHeavy, "King K. Rool", "Donkey Kong"},
	{light, "Isabelle", "Animal Crossing"},
	{heavy, "Incineroar", "Pokémon"},

	// DLC Characters
	{"piranhaplant.mp3", heavy, "Piranha Plant", "Super Mario", true},
	{light, "Joker", "Persona", true},
	{medium, "Hero", "Dragon Quest", true},
	{heavy, "Banjo & Kazooie", "Banjo-Kazooie", true},
	{"terry.mp3", heavy, "Terry", "Fatal Fury", true},
	{medium, "Byleth", "Fire Emblem", true},
	{heavy, "Min Min", "ARMS", true},
	{medium, "Steve", "Minecraft", true},
	{light, "Sephiroth", "Final Fantasy", true},
	{medium, "Pyra/Mythra", "Xenoblade Chronicles", true},
	{heavy, "Kazuya", "Tekken", true},
	{light, "Sora", "Kingdom Hearts", true}
};
vector<string> toWords(string input)
{
	int index = 0;
	vector<string> out = {};
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == ' ' && i != 0)
		{
			while (i != input.length() - 1 && input[i + 1] == ' ')
			{
				input.erase(input.begin() + i + 1);
			}
			index++;
		}
		else
		{
			while (index >= out.size())
			{
				out.push_back("");
			}
			out[index] += ("" + input[i]);
		}
	}
	return out;
}
vector<string> toWords2(string input)
{
	int index = 0;
	vector<string> out = {};
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == ' ')
		{
			index++;
		}
		else
		{
			while (index >= out.size())
			{
				out.push_back("");
			}
			out[int(index / 2)] += input[i];
		}
	}
	return out;
}
// Levenshtein Distance Algorithm (Edit Distance)
int levenshteinDistance(const std::string& s1, const std::string& s2) {
	int len1 = s1.length(), len2 = s2.length();
	std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

	for (int i = 0; i <= len1; i++) dp[i][0] = i;
	for (int j = 0; j <= len2; j++) dp[0][j] = j;

	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
			dp[i][j] = std::min({ dp[i - 1][j] + 1,     // Deletion
								  dp[i][j - 1] + 1,     // Insertion
								  dp[i - 1][j - 1] + cost }); // Substitution
		}
	}
	return dp[len1][len2];
}

// Normalize strings: Convert to lowercase and remove spaces
std::string normalizeString(const std::string& str) {
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
	return result;
}

// Compute similarity score (1 = identical, 0 = completely different)
double similarityScore(const std::string& phrase1, const std::string& phrase2) {
	std::string norm1 = normalizeString(phrase1);
	std::string norm2 = normalizeString(phrase2);

	int maxLen = std::max(norm1.length(), norm2.length());
	if (maxLen == 0) return 1.0; // Both strings empty

	int distance = levenshteinDistance(norm1, norm2);
	return 1.0 - (static_cast<double>(distance) / maxLen); // Normalize score
}
int pickVoice(vector<Character> dudes)
{
	string input;

	cout << "What character would you like?\n";
	string closestWord = "";
	string closestDude = "";
	double score = -1;
	int bestIndex = -1;
	while (true) {
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 27) break;
			if (ch == '\b' && !input.empty()) {
				input.pop_back();
				cout << "\b \b";
			}
			else if (isprint(ch)) {
				input += ch;
				cout << input << endl;
			}

			//find out when 2 words have been said
			vector<string> words = toWords(input);
			vector<string> words2 = toWords2(input);

			for (int i = 0; i < words.size(); i++)
			{
				if (words[i].empty())
				{
					words.erase(words.begin() + i);
					i--;
				}
			}

			/*
			Go through all characters and determine if any word or word pair is closest. save closest and return

			*/
			for (int i = 0; i < dudes.size(); i++)
			{
				for (int c = 0; c < words.size(); c++)
				{
					//each word
					double tempScore = similarityScore(dudes[i].name, words[c]);
					if (tempScore > score)
					{
						score = tempScore;
						bestIndex = i;
						closestWord = words[c];
						closestDude = dudes[i].name;
					}
				}
				for (int c = 0; c < words2.size(); c++)
				{
					//each word
					double tempScore = similarityScore(dudes[i].name, words2[c]);
					if (tempScore > score)
					{
						//cout << "[Words] " << dudes[i].name << ", " << words2[c] << "\t[Score] " << tempScore << endl;
						score = tempScore;
						bestIndex = i;
						closestWord = words[c];
						closestDude = dudes[i].name;
					}
				}
			}
			cout << "[Words] " << closestDude << ", " << closestWord << "\t[Score] " << score << endl;
		}

		if (score > 0.60)
		{
			return bestIndex;
		}
	}
	return -1;
}
string strtolower(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
	return str;
}

void printVec(vector<Character> a)
{
	cout << "Characters:\n";
	for (Character b : a)
	{
		cout << b.name << " " << b.timesPicked << endl;
	}
}

void filterCharacters(std::vector<Character>& picked, int maxy) {
	std::unordered_set<std::string> seen;
	std::vector<Character> uniquePicked;

	// Remove duplicates (keep first occurrence)
	for (const auto& character : picked) {
		if (seen.insert(character.name).second) {
			uniquePicked.push_back(character);
		}
	}

	// If above max limit, remove random elements until within limit
	while (uniquePicked.size() > maxy) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<size_t> dist(0, uniquePicked.size() - 1);

		size_t removeIndex = dist(gen);
		uniquePicked.erase(uniquePicked.begin() + removeIndex);
	}

	// Update original vector
	picked = std::move(uniquePicked);
}
void pickRandomCharacters(int num, string game, bool noDuplicates, bool noDlc, bool smart, types::SIZE a) {
	vector<Character> pool;
	if (game.empty()) {
		cout << "SO THE GAME IS EMPTY" << endl;
		pool = characters;
	}
	else {
		cout << "FUCKING GAME: " << game << endl;
		for (const auto& c : characters) {
			if (strtolower(c.game) == strtolower(game.substr(0, c.game.length()))) pool.push_back(c);
		}
	}
	cout << "HERE IS A: " << a << endl;
	for (int i = 0; i < pool.size(); i++)
	{
		if (noDlc && pool[i].dlc == true)//delete
		{
			pool.erase(pool.begin() + i);
			i--;
			continue;
		}
		//cout << "\tTHING: " <<  pool[i].name << pool[i].name << pool[i].size << endl;
		//cout << "A:" << a << " " << pool[i].size << endl;
		if (a != null && a != pool[i].size)//delete
		{
			cout << "\tDeleting "  <<pool[i].name << pool[i].size << "a: " <<a << endl;
			pool.erase(pool.begin() + i);
			i--;
			continue;
		}
	}
	//cout << "=========================\n";
	//printVec(pool);
	//cout << "=========================\n";

	if (pool.empty()) {
		cout << "No characters found for this game." << endl;
		return;
	}

	srand(time(0));
	vector<Character> tempPool;

	vector<Character> chosen;

	int maxTimesPlayed = -1;
	if (smart)
	{
		for (int i = 0; i < pool.size(); i++)
		{
			maxTimesPlayed = max(maxTimesPlayed, pool[i].timesPicked);
		}
		for (int i = 0; i < pool.size(); i++)
		{
			for (int o = 0; o < maxTimesPlayed + 1 - pool[i].timesPicked; o++)
			{
				tempPool.push_back(pool[i]);
			}
		}
		pool = tempPool;
		//printVec(pool);
	}

	filterCharacters(pool, num);
	chosen = pool;

	vector<bool> found = {};
	found.resize(chosen.size());

	//thread t(animate,ref(display));
	//t.detach();
	string out = "You got ";
	bool dlc = false;
	int count = 0;
	for (auto& c : chosen) {
		c.print();
		characters[c.index].timesPicked++;
		out += c.name;

		if (c.dlc)
		{
			out += ". ew. ";
		}
		if (count == chosen.size() - 1)
		{
			if (rand() % 4 == 0)
				out += ". type SHIT!";
		}
		else if (count == chosen.size() - 2)
		{
			out += " and ";
		}
		else
		{
			out += ", ";
		}

		count++;
	}

	//
	faceTalking = true;
	string command = "cd C:\\Users\\Coope\\piper && echo off & echo \"" + out + (string)"\" | piper --model en_US-ryan-high.onnx --length-scale 1.0 --output-raw | ffplay.exe -f s16le -ar 22050 -nodisp -autoexit -";
	system(command.c_str());
	faceTalking = false;
	cout << out << endl;
	int pick = pickVoice(chosen);

	//run music
	if (pick >= 0 && pick < chosen.size())
	{
		chosen[pick].playNoise();
	}
}

void preprocess(string& input)
{
	input = strtolower(input);

	vector<string> nums = { "one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen" };
	for (int i = 0; i < nums.size(); i++)
	{
		size_t pos = input.find(nums[i]);
		if (pos != string::npos)
		{
			input = input.substr(0, pos) + to_string(i + 1) + input.substr(pos + nums[i].length());
		}
	}

	size_t pos2 = input.find("d l c");
	if (pos2 != string::npos)
	{
		input = input.substr(0, pos2) + "dlc" + input.substr(pos2 + 5);
	}
}

//last args
string lastgame = "";
bool lastNoDuplicates = false;
bool lastNoDlc = false;
int lastNum = 1;
types::SIZE lastWeight;

void processCommand(string input) {
	cout << input << endl;
	preprocess(input);
	cout << input << endl;

	if (input.find("kill yourself") != string::npos)
	{
		return;
	}

	if (input.find("pick") != string::npos || input.find("roll") != string::npos || input.find("give") != string::npos) {
		int num = 1;
		string game = "";
		bool noDuplicates = (input.find("no duplicates") != string::npos);

		size_t pos = input.find_first_of("0123456789");
		if (pos != string::npos) num = input[pos] - '0';

		size_t fromPos = input.find("from");
		
		if (fromPos != string::npos) {
			cout << "Found from :o\n";
			game = input.substr(fromPos + 5);
		}

		bool noDlc = input.find("no dlc") != string::npos;
		types::SIZE weight = null;
		cout << "Weight init: " << weight << endl;
		vector<string> weights = { "super light","light","super heavy","heavy","medium" };
		int count = 0;
		for (string wrd : weights)
		{
			if (input.find(wrd) != string::npos)
			{
				switch (count)
				{
				case 0:
					cout << "superlight\n";
					weight = types::superLight;
					break;
				case 1:
					cout << "light\n";
					weight = types::light;
					break;
				case 2:
					cout << "superheavy\n";
					weight = types::superHeavy;
					break;
				case 3:
					cout << "heavy\n";
					weight = types::heavy;
					break;
				case 4:
					cout << "medium\n";
					weight = types::medium;
					break;
				default:
					weight = null;
					cout << "default cause:.:" << weight << endl;
				}
			}
			count++;
		}

		if (input.find("again") != string::npos)
		{
			cout << "ROLLIN AGAINNN\n";
			num = lastNum;
			noDlc = lastNoDlc;
			noDuplicates = lastNoDuplicates;
			game = lastgame;
			weight = lastWeight;
		}

		/*
		game: GAME EMPTY
		num 9
		
		*/
		lastNum = num;
		lastNoDlc = noDlc;
		lastWeight = weight;
		lastNoDuplicates = noDuplicates;
		lastgame = game;
		cout << "weight: " << weight << endl;
		cout << "game: " << game << (game.empty()?"GAME EMPTY":"") << endl;
		cout << "num " << num << endl;
		pickRandomCharacters(num, game, noDuplicates, noDlc, true, weight);
	}
	else {
		cout << "Unknown command." << endl;
	}
}

//echo "Hello, this is a test." | piper --model en_US-lessac-medium.onnx --output-raw | ffplay -f s16le -ar 22050 -nodisp -autoexit -

int main() {
	string input;

	//cout << "Risize window and press enter...\n";
	//cin.get();

	cout << "Start typing (Press ESC to exit):\n";
	bool listening = false;

	for (Character& c : characters)
	{
		//cout << c.name << c.index << endl;
	}

	//Display display;
	Sleep(100);
	thread f(triggerVoiceTyping);

	thread g(FACEHAHA);
	Sleep(1000);
	
	
	//display.backBuffer = imageToASCII("mcride.jpg", display.size.x);
	//display.redraw();
	//display.loadFrames();

	//display.redraw();
	
	while (true) {
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 27) break;
			if (ch == '\b' && !input.empty()) {
				input.pop_back();
				cout << "\b \b";
			}
			else if (isprint(ch)) {
				input += ch;
				cout << ch;
			}

			if (!listening && strtolower(input).find("computer") != string::npos) {
				input.clear();
				cout << "\nListening...\n";
				listening = true;
			}
			else if (listening) {
				if (input.find("thank you") != string::npos || input.find("thanks") != string::npos) {
					cout << "\nStopped listening\n";
					listening = false;
					if (input.find("pick") != string::npos || input.find("roll") != string::npos) {
						cout << "\nProcessing command...\n";
						processCommand(input);

						//display.backBuffer = imageToASCII("mcride.jpg",display.size.x);
						//display.redraw();

						input.clear();
					}
					input.clear();
				}
			}
		}
	}
	faceRunning = false;
	g.join();
	f.join();
}

/*
cooper todo list yay:

-add weight pararmetrer
=fix no dlc option
-fix face animation and move ram to stack instead of heap
-add command aliases
-add auto listen
-funny jokes

*/