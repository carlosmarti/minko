/*
Copyright (c) 2014 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "minko/Canvas.hpp"
#include "minko/log/Logger.hpp"
#include "minko/SDLAudio.hpp"
#include "minko/audio/SDLSoundChannel.hpp"

#include "SDL_mixer.h"

using namespace minko;
using namespace minko::audio;

SDLAudio::SDLAudio(std::shared_ptr<Canvas> canvas)
{
    auto flags = MIX_INIT_OGG;
    int result = 0;

    if (flags != (result = Mix_Init(flags)))
    {
        LOG_ERROR("Could not initialize mixer: " << result << " (" << Mix_GetError());
    }
    else
    {
        Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 0);
        Mix_ChannelFinished(&SDLSoundChannel::channelComplete);
        Mix_AllocateChannels(32);
    }
}

std::shared_ptr<SDLAudio>
SDLAudio::create(std::shared_ptr<Canvas> canvas)
{
    return std::shared_ptr<SDLAudio>(new SDLAudio(canvas));
}
