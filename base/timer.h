//
//  timer.h
//  ecs
//
//  Created by Nicholas Field on 28/03/2021.
//

#ifndef timer_h
#define timer_h

#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>

class Timer
{
private:
    //The clock time when the timer started
    uint32_t mStartTicks;

    //The ticks stored when the timer was paused
    uint32_t mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;

public:
    //Initializes variables
    Timer()
    {
        //Initialize the variables
        mStartTicks = 0;
        mPausedTicks = 0;

        mPaused = false;
        mStarted = false;
    }

    //The various clock actions
    void start()
    {
        //Start the timer
        mStarted = true;

        //Unpause the timer
        mPaused = false;

        //Get the current clock time
        mStartTicks = SDL_GetTicks();
        mPausedTicks = 0;
    };

    void stop()
    {
        //Stop the timer
        mStarted = false;

        //Unpause the timer
        mPaused = false;

        //Clear tick variables
        mStartTicks = 0;
        mPausedTicks = 0;
    };

    void pause()
    {
        //If the timer is running and isn't already paused
        if( mStarted && !mPaused )
        {
            //Pause the timer
            mPaused = true;

            //Calculate the paused ticks
            mPausedTicks = SDL_GetTicks() - mStartTicks;
            mStartTicks = 0;
        }
    };

    void unpause()
    {
        //If the timer is running and paused
        if( mStarted && mPaused )
        {
            //Unpause the timer
            mPaused = false;

            //Reset the starting ticks
            mStartTicks = SDL_GetTicks() - mPausedTicks;

            //Reset the paused ticks
            mPausedTicks = 0;
        }
    }

    //Gets the timer's time
    uint32_t getTicks()
    {
        //The actual timer time
        Uint32 time = 0;

        //If the timer is running
        if( mStarted )
        {
            //If the timer is paused
            if( mPaused )
            {
                //Return the number of ticks when the timer was paused
                time = mPausedTicks;
            }
            else
            {
                //Return the current time minus the start time
                time = SDL_GetTicks() - mStartTicks;
            }
        }

        return time;
    };

    //Checks the status of the timer
    bool isStarted()
    {
        //Timer is running and paused or unpaused
        return mStarted;
    };

    bool isPaused()
    {
        //Timer is running and paused
        return mPaused && mStarted;
    };
};


#endif /* timer_h */
