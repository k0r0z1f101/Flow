#include "raylib.h"
#include "flow.h"

using namespace flow;

int main(void)
{
	srand(time(0));
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Flow");

    InitAudioDevice();              // Initialize audio device

    SetAudioStreamBufferSizeDefault(MAX_SAMPLES_PER_UPDATE);

//    std::vector<Blobie> blobies = {};
//
//    //instanciate Blobie
//    Blobie blobie = Blobie();
//    blobies.push_back(blobie);
//
//    std::cout << blobie.getName() << std::endl;
//    std::cout << blobie.getBirthTime() << std::endl;
////    cout << blobie.getHealth().getFlowPoint() << endl;
//
//    //instanciate Blobie2
//    Blobie blobie2 = Blobie();
//    blobies.push_back(blobie2);
//
//    std::cout << blobie2.getName() << std::endl;
//    std::cout << blobie2.getBirthTime() << std::endl;
//    cout << blobie2.getHealth().getFlowPoint() << endl;


    SetTargetFPS(30);               // Set our game to run at 30 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

    	//Update Actors (blobies, notes)
//    	for(size_t i = 0; i < blobies.size(); ++i)
//    	{
//    		Vocalizer* voc = blobies[i].getVoice();
//    		voc->emitSoundTest();
//    	}

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        	ClearBackground(RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
