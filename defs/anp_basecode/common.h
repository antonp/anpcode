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

#ifndef _COMMON_H_
#define _COMMON_H_

#include "basedefs.h"

namespace anp
{
	struct Point2d
	{
		Point2d():x(0), y(0) { }
		Point2d(anp::int32 in_x, anp::int32 in_y):x(in_x), y(in_y) { }
		Point2d(const anp::Point2d &point):x(point.x), y(point.y) { }
		anp::int32 x;
		anp::int32 y;
	};

	struct Size2d
	{
		Size2d():width(0), height(0) { }
		Size2d(anp::uint32 in_width, anp::uint32 in_height):width(in_width), height(in_height) { }
		Size2d(const anp::Size2d &size):width(size.width), height(size.height) { }
		anp::uint32 width;
		anp::uint32 height;
	};

	struct Rect
	{
		Rect():top(0), left(0), bottom(0), right(0) { }
		anp::int32 top;
		anp::int32 left;
		anp::int32 bottom;
		anp::int32 right;
	};

	static anp::bool32 pointInRect(const Point2d &point, const Rect &rect)
	{
		return ( point.x > rect.left
			&& point.x < rect.right
			&& point.y > rect.top
			&& point.y < rect.bottom );
	}
} // namespace anp

#endif // _COMMON_H_
