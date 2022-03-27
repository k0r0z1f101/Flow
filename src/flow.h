#pragma once
//#include "Code_Utilities.h" //I always have multiple declarations compile errors when using Code_Utilities (might be only on linux)
#include <chrono>
#include <iostream>
#include <string>
#include <array>
#include <random>
#include <iomanip>

#define MAX_SAMPLES               512
#define MAX_SAMPLES_PER_UPDATE   4096

using namespace std;
using namespace chrono;

//HEALTH class constants
const int LIFEPOINTMIN = 10;
const int LIFEPOINTMAX = 20;

namespace flow
{
	//HEALTH DECLARATIONS
	class Health
	{
		int b_flowPoint;		//energy of Blobie, Blobie dies when it reaches zero, replenishes by making "perfect beats"
	public:
		Health();
		Health(const Health& copy);
		~Health();

		//getter
		int getFlowPoint();
	};
//
//	//build blobie movement class
//	class Movement
//	{
//		float b_moveSpeed = {};
//	public:
//		Movement() {}
//		~Movement() {}
//	};
//
	//build blobie vocalizer class
	class Vocalizer
	{
		float b_speechLevel;
		AudioStream b_stream = LoadAudioStream(44100, 16, 1); // Init raw audio stream (sample rate: 22050, sample size: 16bit-short, channels: 1-mono)
		short *b_data = (short *)malloc(sizeof(short)*MAX_SAMPLES);
		short *b_writeBuf = (short *)malloc(sizeof(short)*MAX_SAMPLES_PER_UPDATE);
		float b_volume = 0.01f; //Volume level
		Vector2 b_randomFreq = { -100.0f, -100.0f }; // startup vector to determine next frequency
		float b_frequency = (rand() % 101) + 340.0f; // Cycles per second (hz)
		float b_oldFrequency = 1.0f; // Previous value, used to test if sine needs to be rewritten, and to smoothly modulate frequency
		int b_readCursor = 0; // Cursor to read and copy the samples of the sine wave buffer
		int b_waveLength = 1; // Computed size in samples of the sine wave
	    Vector2 b_position = { 0, 0 };
	public:
		Vocalizer();
		~Vocalizer();
		void emitSound();
	};
//
//	//build blobie listener class
//	class Listener
//	{
//
//	};
//
//
//	class Personality
//	{
//
//	};

	//BLOBIE DECLARATIONS
	class Blobie
	{
	protected:
		string b_name;
		time_t b_birthtime; //instanciation epoch in nanoseconds
//		Movement b_movement;
		Health b_health;
		Vocalizer b_voice;
	public:
		Blobie();
		virtual ~Blobie();

		//getter
		string getName();
		time_t getBirthTime();
		Health *getHealth();
		Vocalizer *getVoice();
	};
}