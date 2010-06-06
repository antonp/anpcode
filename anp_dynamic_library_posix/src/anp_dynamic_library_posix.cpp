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

#include <anp_dynamic_library.h>
#include <dlfcn.h>
#include <stdexcept>
#include <sstream>

namespace anp
{
	class DynamicLibraryImplementation
	{
	public:
		void *m_handle;
	
		DynamicLibraryImplementation(const int8 *fileName):
		m_handle(dlopen(fileName, RTLD_LAZY)) // RTLD_NOW ?
		{
			if ( NULL == m_handle )
			{
				std::stringstream errorMsg;
				errorMsg << "dlopen failed:" << dlerror() << std::endl;
				throw std::runtime_error(errorMsg.str());
			}
		}
		
		~DynamicLibraryImplementation()
		{
			dlclose(m_handle);
		}
		
		void *getSymbol(const int8 *symbolName)
		{
			void *symbol = dlsym(m_handle, symbolName);
			if ( NULL == symbol )
			{
				std::stringstream errorMsg;
				errorMsg << "dlsym returned NULL: "
					<< dlerror() << std::endl;
				throw std::runtime_error(errorMsg.str());
			}
		}
	};

	
	// DynamicLibrary function bodies
	DynamicLibrary::DynamicLibrary(const int8 *fileName):
	m_impl(new DynamicLibraryImplementation(fileName))
	{
		
	}
	DynamicLibrary::~DynamicLibrary()
	{
		delete m_impl;
	}
		
	void *DynamicLibrary::getSymbol(const int8 *symbolName)
	{
		return m_impl->getSymbol(symbolName);
	}
}
