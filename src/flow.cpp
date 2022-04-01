#include "raylib.h"
#include "Code_Utilities.h"
#include <chrono>
#include "flow.h"
#include <stdlib.h>         // Required for: malloc(), free()
#include <math.h>           // Required for: sinf()
#include <string.h>         // Required for: memcpy()

//
using namespace BdB;
using namespace std;
using namespace chrono;

namespace flow
{
	//HEALTH DEFINITIONS
	Health::Health()
	{
		b_flowPoint = (rand() % (LIFEPOINTMAX - LIFEPOINTMIN)) + (LIFEPOINTMAX - LIFEPOINTMIN + 1);
	}
	Health::Health(const Health& copy) {
		b_flowPoint = copy.b_flowPoint;
	}
	Health::~Health() { cout << "dest health" << endl; }

	//getter
	int Health::getFlowPoint() { return b_flowPoint; }

	//VOCALIZER DEFINITIONS
	Vocalizer::Vocalizer()
	{
		PlayAudioStream(b_stream);        // Start processing stream buffer (no data loaded currently)
		cout << "def Vocalizer" << endl;
	}
	Vocalizer::~Vocalizer()
	{
		// De-Initialization
		//--------------------------------------------------------------------------------------
//		free(b_data);                 // Unload sine wave data
//		free(b_writeBuf);             // Unload write buffer
//		UnloadAudioStream(b_stream);   // Close raw audio stream and delete buffers from RAM
	    cout << "dest Vocalizer" << endl;
	}
	void Vocalizer::emitSoundTest() //Updated each frame
	{
		// Rewrite the sine wave.
        // Compute two cycles to allow the buffer padding, simplifying any modulation, resampling, etc.
        if (b_frequency != b_oldFrequency)
        {
            // Compute wavelength. Limit size in both directions.
            int oldWavelength = b_waveLength;
            b_waveLength = (int)(22050/b_frequency);
            if (b_waveLength > MAX_SAMPLES/2) b_waveLength = MAX_SAMPLES/2;
            if (b_waveLength < 1) b_waveLength = 1;

            // Write sine wave.
            for (int i = 0; i < b_waveLength*2; i++)
            {
                b_data[i] = (short)(sinf(((2*PI*(float)i/b_waveLength)))*32000);
            }

            // Scale read cursor's position to minimize transition artifacts
            b_readCursor = (int)(b_readCursor * ((float)b_waveLength / (float)oldWavelength));
            b_oldFrequency = b_frequency;
        }

        // Refill audio stream if required
        if (IsAudioStreamProcessed(b_stream))
        {
            // Synthesize a buffer that is exactly the requested size
            int writeCursor = 0;

            while (writeCursor < MAX_SAMPLES_PER_UPDATE)
            {
                // Start by trying to write the whole chunk at once
                int writeLength = MAX_SAMPLES_PER_UPDATE-writeCursor;

                // Limit to the maximum readable size
                int readLength = b_waveLength-b_readCursor;

                if (writeLength > readLength) writeLength = readLength;

                // Write the slice
                memcpy(b_writeBuf + writeCursor, b_data + b_readCursor, writeLength*sizeof(short));

                // Update cursors and loop audio
                b_readCursor = (b_readCursor + writeLength) % b_waveLength;

                writeCursor += writeLength;
            }

    		SetAudioStreamVolume(b_stream, b_volume);
            // Copy finished frame to audio stream
            UpdateAudioStream(b_stream, b_writeBuf, MAX_SAMPLES_PER_UPDATE);
        }
        //----------------------------------------------------------------------------------



	}

	//BLOBIE DEFINITIONS
	Blobie::Blobie()
	{
		uint64_t ns = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
		b_birthtime = ns;
		cout << "def blobie" << endl;
	}
	Blobie::~Blobie() { cout << "dest blobie" << endl; }

	//getter
	string Blobie::getName() { return b_name; }
	time_t Blobie::getBirthTime() { return b_birthtime; }
	Health *Blobie::getHealth() { return &b_health; }
	Vocalizer *Blobie::getVoice() { return &b_voice; }
}
