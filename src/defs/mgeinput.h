/*

Copyright (c) 2010, Anton Petersson < anton (at) anp.nu >
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef _MGEINPUT_H_
#define _MGEINPUT_H_

/** @file mgeinput.h
This header file defines some useful input-related constants
*/

#include "basedefs.h"
#include "common.h"

namespace anp
{
	enum MouseButton
	{
		MOUSEBUTTON_LEFT	= (1<<0),
		MOUSEBUTTON_MIDDLE	= (1<<1),
		MOUSEBUTTON_RIGHT	= (1<<2),
		MOUSEBUTTON_THUMB1	= (1<<3),
		MOUSEBUTTON_THUMB2	= (1<<4),
		MOUSEBUTTON_EXTRA1	= (1<<5),
		MOUSEBUTTON_EXTRA2	= (1<<6),
		MOUSEBUTTON_WHEEL=MOUSEBUTTON_MIDDLE
	};

	enum MouseEventType
	{
		MOUSEBUTTON_DOWN,
		MOUSEBUTTON_UP,
		MOUSEMOVE
	};

	struct MouseEvent
	{
		MouseEventType type;
		union
		{
			MouseButton button;
			anp::unsigned int buttonState;
		};
		anp::Point2d position;
		anp::int32 xrel;
		anp::int32 yrel;
	};
} // namespace anp

#endif // _MGEINPUT_H_
