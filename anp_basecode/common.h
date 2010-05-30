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

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef _COMMON_H_
#define _COMMON_H_

#include "basedefs.h"

namespace firc
{
	struct Point2d
	{
		Point2d():x(0), y(0) { }
		Point2d(mge::int32 in_x, mge::int32 in_y):x(in_x), y(in_y) { }
		Point2d(const mge::Point2d &point):x(point.x), y(point.y) { }
		mge::int32 x;
		mge::int32 y;
	};

	struct Size2d
	{
		Size2d():width(0), height(0) { }
		Size2d(mge::uint32 in_width, mge::uint32 in_height):width(in_width), height(in_height) { }
		Size2d(const mge::Size2d &size):width(size.width), height(size.height) { }
		mge::uint32 width;
		mge::uint32 height;
	};

	struct Rect
	{
		Rect():top(0), left(0), bottom(0), right(0) { }
		mge::int32 top;
		mge::int32 left;
		mge::int32 bottom;
		mge::int32 right;
	};

	static mge::bool32 pointInRect(const Point2d &point, const Rect &rect)
	{
		return ( point.x > rect.left
			&& point.x < rect.right
			&& point.y > rect.top
			&& point.y < rect.bottom );
	}
}

#endif // _COMMON_H_
