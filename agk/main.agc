
#include 'gameStateMachine.agc'

// show all errors
SetErrorMode(2)

// set window properties
SetWindowTitle( "FurnaceAGK" )
SetWindowSize( 640, 480, 0 )
SetWindowAllowResize( 0 ) // allow the user to resize the window

// set display properties
SetVirtualResolution( 320, 240 ) // doesn't have to match the window
SetOrientationAllowed( 1, 1, 1, 1 ) // allow both portrait and landscape on mobile devices
//SetSyncRate( 30, 0 ) // 30fps instead of 60 to save battery
SetScissor( 0,0,0,0 ) // use the maximum available screen space, no black borders
UseNewDefaultFonts( 1 ) // since version 2.0.22 we can use nicer default fonts

do
    FUR_events()
    FUR_update()
    FUR_render()

loop

//===========================================================================

Function FUR_events()
	
EndFunction
	
Function FUR_update()
	Print( ScreenFPS() )
EndFunction

Function FUR_render()
	Sync()
EndFunction
